using System;
using System.Diagnostics;
using System.Threading;

class Program {
    static int counter = 0;
    static readonly object syncObj = new object();
    static SemaphoreSlim semaphore = new SemaphoreSlim(1);
    static int N = 1_000_000;
    // static int N = 1_000;

    static void Measure(string name, Action action) {
        var sw = Stopwatch.StartNew();
        action();
        sw.Stop();
        Console.WriteLine($"{name,-15} => {sw.ElapsedMilliseconds} ms");
    }

    static void Main() {
        Measure("lock", () => {
            for (int i = 0; i < N; i++) {
                lock (syncObj) { counter++; }
            }
        });

        counter = 0;
        Measure("Monitor", () => {
            for (int i = 0; i < N; i++) {
                bool taken = false;
                try {
                    Monitor.Enter(syncObj, ref taken);
                    counter++;
                } finally {
                    if (taken) Monitor.Exit(syncObj);
                }
            }
        });

        counter = 0;
        Measure("SemaphoreSlim", () => {
            for (int i = 0; i < N; i++) {
                semaphore.Wait();
                counter++;
                semaphore.Release();
            }
        });
    }
}