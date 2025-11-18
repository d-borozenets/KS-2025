using System;
using System.Threading;

class Program {
    static readonly ReaderWriterLockSlim rwLock = new();
    static int value = 0;
    private static bool running = true;

    static void Reader(int id) {
        while (running) {
            rwLock.EnterReadLock();
            Console.WriteLine($"Reader {id} бачить значення: {value}");
            Thread.Sleep(300);
            rwLock.ExitReadLock();
        }
    }

    static void Writer() {
        while (running) {
            rwLock.EnterWriteLock();
            value++;
            Console.WriteLine($"Writer змінив значення: {value}");
            Thread.Sleep(1000);
            rwLock.ExitWriteLock();
        }
    }

    static void Main() {
        new Thread(Writer).Start();
        for (int i = 1; i <= 3; i++) {
            int localId = i;
            new Thread(() => Reader(localId)).Start();
        }
        
        Console.WriteLine("Натисніть будь-яку клавішу для завершення...");
        Console.ReadKey(); // очікуємо натискання клавіші
        running = false;   // сигнал усім потокам завершитись
        
        // даємо потокам трохи часу коректно завершити
        Thread.Sleep(1500);
        Console.WriteLine("Програма завершена.");
    }
}