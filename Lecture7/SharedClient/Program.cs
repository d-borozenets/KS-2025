using System;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

class Reader{
    static void Main(){
        const string mapName = "/mmf-demo";
        const string filePath = "/tmp/mmf_lab12.bin";
        const int capacity = 4096;

        bool useFile = RuntimeInformation.IsOSPlatform(OSPlatform.OSX) ||
                       RuntimeInformation.IsOSPlatform(OSPlatform.Linux);

        MemoryMappedFile mmf;

        if (useFile) {
            // На macOS/Linux читаємо зі спільного файлу
            if (!File.Exists(filePath)) {
                Console.WriteLine("Reader: shared file not found. Start Writer first.");
                return;
            }

            using var fs = new FileStream(filePath, FileMode.Open, FileAccess.ReadWrite, FileShare.ReadWrite);
            mmf = MemoryMappedFile.CreateFromFile(fs, null, capacity, MemoryMappedFileAccess.ReadWrite,
                HandleInheritability.None, false);
        } else {
            // На Windows — звичайна іменована пам’ять
            mmf = MemoryMappedFile.OpenExisting(mapName);
        }

        using var accessor = mmf.CreateViewAccessor();

        Console.WriteLine("Reader started. Waiting for data...");

        // Очікуємо, поки Writer виставить прапорець
        while (true) {
            int flag = accessor.ReadInt32(0);
            if (flag == 1)
                break;
            Thread.Sleep(50);
        }

        int length = accessor.ReadInt32(4);
        if (length <= 0 || length + 8 > capacity) {
            Console.WriteLine("Reader: invalid message length.");
            return;
        }

        byte[] buffer = new byte[length];
        accessor.ReadArray(8, buffer, 0, length);
        string message = Encoding.UTF8.GetString(buffer);

        Console.WriteLine($"Reader: received -> {message}");

        // Скидаємо прапорець після читання
        accessor.Write(0, 0);
        accessor.Flush();

        Console.WriteLine("Reader finished. Press any key to exit.");
        Console.ReadKey();
    }
}