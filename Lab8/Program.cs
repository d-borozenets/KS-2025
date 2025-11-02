using System;
using System.Diagnostics;
using System.Threading;

class Program{
    static int counter;
    const int N = 200_000_000;
    // const int N = 100_000; // use for quick debugging

    static void Main(){
        Console.WriteLine("=== Lab 8: Basic Synchronization ===\n");
        RunTest("1. No synchronization", IncrementUnsafe);
        RunTest("2. lock", IncrementLock);
        RunTest("3. Monitor.Enter/Exit", IncrementMonitor);
        RunTest("4. Interlocked", IncrementAtomic);
    }

    static void RunTest(string title, ThreadStart method){
    }

    static void IncrementUnsafe(){
    }

    static void IncrementLock(){
    }

    static void IncrementMonitor(){
    }

    static void IncrementAtomic(){
    }
}