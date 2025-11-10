using System;
using System.IO;
using System.IO.Pipes;
using System.Text;

class PipeClient{
    static void Main(){
        Console.WriteLine("Client: підключаюся до DemoPipe...");
        using (var pipe = new NamedPipeClientStream(".", "DemoPipe", PipeDirection.In)) {
            pipe.Connect();
            Console.WriteLine("Підключено до сервера!");

            // using (var reader = new StreamReader(pipe, Encoding.UTF8)) {
            //     string message = reader.ReadLine();
            //     Console.WriteLine($"Отримано повідомлення: {message}");
            // }
            byte[] buffer = new byte[256];
            int bytesRead = pipe.Read(buffer, 0, buffer.Length);
            string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
            Console.WriteLine($"Client received: {message}");
        }

        Console.WriteLine("👋 Клієнт завершує роботу.");
    }
}