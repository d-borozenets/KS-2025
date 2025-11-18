using System;
using System.Threading;

class Program {
    static readonly object locker = new object();
    static bool ready = false;

    static void Worker() {
        lock (locker) {
            while (!ready) {
                Console.WriteLine("Потік чекає сигналу...");
                Monitor.Wait(locker); // звільняє замок і чекає
            }
            Console.WriteLine("Потік отримав сигнал і працює!");
        }
    }

    static void Main() {
        Thread t = new Thread(Worker);
        t.Start();

        Thread.Sleep(2000); // імітація підготовки даних
        lock (locker) {
            ready = true;
            Console.WriteLine("Головний потік подає сигнал.");
            // Monitor.Pulse(locker); // сигналізує очікуючому потоку
            // Console.WriteLine("Головний потік після пульс.");
        }

        t.Join();
        Console.WriteLine("Роботу завершено.");
    }
}