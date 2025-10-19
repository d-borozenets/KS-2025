using System;
using System.IO;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

class Client
{
    static async Task Main()
    {
        const int port = 9000;
        const string host = "127.0.0.1";

        using var client = new TcpClient();
        Console.WriteLine("Connecting to server...");
        await client.ConnectAsync(host, port);
        Console.WriteLine("Connected.");

        using var stream = client.GetStream();
        string message = "Hello via TCP socket!";
        byte[] data = Encoding.UTF8.GetBytes(message);
        await stream.WriteAsync(data, 0, data.Length);
        Console.WriteLine($"Sent: {message}");

        byte[] buffer = new byte[1024];
        int bytesRead = await stream.ReadAsync(buffer, 0, buffer.Length);
        string response = Encoding.UTF8.GetString(buffer, 0, bytesRead);
        Console.WriteLine($"Received: {response}");
    }
}