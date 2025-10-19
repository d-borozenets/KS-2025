using System;
using System.IO.MemoryMappedFiles;
using System.Text;
using System.Threading;

class Reader
{
    static void Main()
    {
        const string mapName = "/mmf-demo";
        const int capacity = 4096;

        // Writer should be started first to create the map
        using var mmf = MemoryMappedFile.OpenExisting(mapName);
        using var accessor = mmf.CreateViewAccessor();

        // Poll flag until data is ready
        while (true)
        {
            int flag = accessor.ReadInt32(0);
            if (flag == 1) break;
            Thread.Sleep(50);
        }

        int length = accessor.ReadInt32(4);
        if (length < 0 || length + 8 > capacity)
        {
            Console.WriteLine("Reader: invalid length.");
            return;
        }

        byte[] buffer = new byte[length];
        accessor.ReadArray(8, buffer, 0, length);
        string message = Encoding.UTF8.GetString(buffer);

        Console.WriteLine("Reader: received -> " + message);

        // Acknowledge: reset flag
        accessor.Write(0, 0);
        accessor.Flush();
        Console.ReadKey();
    }
}