using System;
using System.Threading;

class Program {
    static CountdownEvent countdown = new CountdownEvent(3);

    static void Worker(int id) {
        Console.WriteLine($"Потік {id} працює...");
        Thread.Sleep(1000 + id * 300);
        Console.WriteLine($"Потік {id} завершив роботу.");
        countdown.Signal(); // зменшує лічильник
    }

    static void Main() {
        for (int i = 1; i <= 3; i++) {
            int localId = i;
            new Thread(() => Worker(localId)).Start();
        }

        Console.WriteLine("Головний потік очікує завершення всіх...");
        countdown.Wait(); // блокується, поки Signal() не викличуть 3 рази
        Console.WriteLine("Усі потоки завершили роботу!");
    }
}