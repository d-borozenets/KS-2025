using System;
using System.Diagnostics;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;
using System.Text;

class Writer{
    // опис структури для спільної пам’яті
    [StructLayout(LayoutKind.Sequential)]
    struct SysInfo{
        public long Ticks; // час у тиках
        public long TotalMemory; // загальна пам’ять у байтах
    }

    static void Main(){
        // StartSingleDirectionWriter();
        // StartBiDirectionWriter();
        // StartMonitoringWriter();
        // StartStructWriter();
    }

    static void StartSingleDirectionWriter(){
        const string mapName = "/mmf-lab12"; // універсальне ім’я
        const int capacity = 4096;

      
        Console.WriteLine("Press any key to exit (keep open until Reader runs)...");
        Console.ReadKey();
    }

    static void StartBiDirectionWriter(){
        const string mapName = "/mmf-file";
        const string mutexName = "/mmf-mutex";
        const int capacity = 4096;
        
        Console.WriteLine("Press any key to exit...");
        Console.ReadKey();
    }

    static void StartStructWriter(){
        const string mapName = "/mmf-struct";
        const string mutexName = "/mmf-struct-mutex";
        const int capacity = 1024;
        

        Console.WriteLine("\nWriter stopped.");
    }

    static void StartMonitoringWriter(){
        const string mapName = "/mmf-monitor";
        const string mutexName = "/mmf-monitor-mutex";
        const int capacity = 1024;
        

        Console.WriteLine("\nWriter stopped.");
    }
}