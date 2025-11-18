using System;
using System.Diagnostics;
using System.Threading;

class Program{
    static int counter;
    // const int N = 200_000_000;
    const int N = 100_000; // use for quick debugging

    static void Main(){
        Console.WriteLine("=== Lab 8: Basic Synchronization ===\n");
        IncrementUnsafe();
        // RunTest("1. No synchronization", IncrementUnsafe);
        // RunTest("2. lock", IncrementLock);
        // RunTest("3. Monitor.Enter/Exit", IncrementMonitor);
        // RunTest("4. Interlocked", IncrementAtomic);
    }

    static void RunTest(string title, ThreadStart method){
    }

    static void IncrementUnsafe(){
        Thread thread1 = new Thread(() => {
            for (int i = 0; i < N; i++) {
                counter++;
            }
        });
        Thread thread2 = new Thread(() => {
            for (int i = 0; i < N; i++) {
                counter++;
            }
        });
        // Thread thread1 = new Thread(() =>  IncCounter());
        // Thread thread2 = new Thread(() =>  IncCounter());
        thread1.Start();
        thread2.Start();
        thread1.Join();
        thread2.Join();
        Console.WriteLine($"counter:{counter}");
    }

    private static void IncCounter(){
        for (int i = 0; i < N; i++) {
            counter++;
        }
    }

    static void IncrementLock(){
    }

    static void IncrementMonitor(){
    }

    static void IncrementAtomic(){
    }
}