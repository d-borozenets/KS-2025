using System;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using System.Text;

class Reader{
    [StructLayout(LayoutKind.Sequential)]
    struct SysInfo{
        public long Ticks;
        public long TotalMemory;
    }

    static void Main(){
        // StartSingleDirectionReader();
        // StartBiDirectionReader();
        // StartMonitoringReader();
        StartStructReader();
    }

    static void StartSingleDirectionReader(){
        const string mapName = "/mmf-lab12";
        const int capacity = 4096;
        
        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }

    static void StartBiDirectionReader(){
        const string mapName = "/mmf-file";
        const string mutexName = "/mmf-mutex";
        const int capacity = 4096;

        
        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }

    static void StartStructReader(){
        const string mapName = "/mmf-struct";
        const string mutexName = "/mmf-struct-mutex";
        const int capacity = 1024;

        Console.WriteLine("\nReader stopped.");
    }


    static void StartMonitoringReader(){
        const string mapName = "/mmf-monitor";
        const string mutexName = "/mmf-monitor-mutex";
        const int capacity = 1024;

        
        Console.WriteLine("\nReader stopped.");
    }
}