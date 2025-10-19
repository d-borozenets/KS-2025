using System;
using System.Threading;

class Program {
    static int counter = 0;                      // спільна змінна для всіх потоків
    static readonly object locker = new object(); // об’єкт для синхронізації

    static void IncrementCounter() {
        for (int i = 0; i < 1000; i++) {
            lock (locker) { 
                counter++; // критична секція
            }
        }
    }

    static void Main() {
        Thread t1 = new Thread(IncrementCounter);
        Thread t2 = new Thread(IncrementCounter);
        Thread t3 = new Thread(IncrementCounter);

        t1.Start();
        t2.Start();
        t3.Start();

        t1.Join();
        t2.Join();
        t3.Join();

        Console.WriteLine($"Final counter value: {counter}");
    }
}