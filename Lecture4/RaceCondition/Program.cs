// File: Program.cs
using System;
using System.Threading;

class Program
{
    static int counter = 0;                 // shared resource (intentionally unprotected)
    const int THREADS = 8;
    const int ITERATIONS_PER_THREAD = 1_000_000;
    static readonly object locker = new object();

    static void Worker()
    {
        for (int i = 0; i < ITERATIONS_PER_THREAD; i++)
        {
            // Non-atomic operation: read -> modify -> write
            lock (locker) 
            {
                counter++;   
            }
        }
    }

    static void Main()
    {
        Thread[] threads = new Thread[THREADS];

        for (int i = 0; i < THREADS; i++)
        {
            threads[i] = new Thread(Worker);
            threads[i].Start();
        }

        foreach (Thread t in threads)
            t.Join();

        Console.WriteLine($"Expected: {THREADS * ITERATIONS_PER_THREAD}");
        Console.WriteLine($"Actual:   {counter}");
    }
}