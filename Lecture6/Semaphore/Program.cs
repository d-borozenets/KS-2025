using System;
using System.Threading;

class Program {
    static SemaphoreSlim semaphore = new SemaphoreSlim(3); // дозволяє до 3 потоків одночасно

    static void DoWork(int id) {
        Console.WriteLine($"Потік {id} чекає доступу...");

        semaphore.Wait(); // спроба зайти в критичну секцію
        try {
            Console.WriteLine($"Потік {id} отримав доступ.");
            Thread.Sleep(2000); // імітація роботи
            Console.WriteLine($"Потік {id} завершує роботу.");
        } finally {
            semaphore.Release(); // звільняє місце
        }
    }

    static void Main() {
        for (int i = 1; i <= 8; i++) {
            int localId = i;
            new Thread(() => DoWork(localId)).Start();
        }
    }
}
