using System;
using System.IO;
using System.IO.Pipes;
using System.Text;

class PipeServer
{
    static void Main()
    {
        Console.WriteLine("Server: створюю іменований канал...");
        using (var pipe = new NamedPipeServerStream("DemoPipe", PipeDirection.Out))
        {
            Console.WriteLine("Очікую підключення клієнта...");
            pipe.WaitForConnection();

            Console.WriteLine("Клієнт підключився!");
            
            // using (var writer = new StreamWriter(pipe, Encoding.UTF8))
            // {
            //     writer.AutoFlush = true;
            //     writer.WriteLine("Hello from server 👋");
            // } 
            string msg = "Hello from server!";
            byte[] msgBytes = Encoding.UTF8.GetBytes(msg);
            pipe.Write(msgBytes, 0, msgBytes.Length);
            pipe.Flush();
            
            
            Console.WriteLine("Повідомлення відправлено. Завершення роботи сервера.");
        }
    }
}