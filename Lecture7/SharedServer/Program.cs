using System;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

class Writer{
    static void Main(){
        const string mapName = "/mmf-demo";
        const string path = "/tmp/mmf_lab12.bin";
        const int capacity = 4096;

        bool useFile = RuntimeInformation.IsOSPlatform(OSPlatform.OSX) ||
                       RuntimeInformation.IsOSPlatform(OSPlatform.Linux);

        MemoryMappedFile mmf;

        if (useFile) {
            // Для Linux/macOS створюємо MMF на базі реального файла
            using var fs = new FileStream(path, FileMode.OpenOrCreate, FileAccess.ReadWrite, FileShare.ReadWrite);
            fs.SetLength(capacity);
            mmf = MemoryMappedFile.CreateFromFile(fs, null, capacity, MemoryMappedFileAccess.ReadWrite,
                HandleInheritability.None, false);
        } else {
            // Для Windows можна створювати іменовану карту напряму
            mmf = MemoryMappedFile.CreateOrOpen(mapName, capacity);
        }

        using var accessor = mmf.CreateViewAccessor();

        // Clear flag
        accessor.Write(0, 0); // flag = 0

        string message = "Hello from process 1!";
        byte[] data = Encoding.UTF8.GetBytes(message);

        if (data.Length + 8 > capacity) {
            Console.WriteLine("Message too large.");
            return;
        }

        // Write length and payload
        accessor.Write(4, data.Length); // length
        accessor.WriteArray(8, data, 0, data.Length); // bytes

        // Publish
        accessor.Write(0, 1); // flag = 1 (data ready)
        accessor.Flush();

        Console.WriteLine("Writer: message published.");
        // Keep alive a bit so reader can read (optional)
        // Thread.Sleep(1000);
        Console.ReadKey();
    }
}