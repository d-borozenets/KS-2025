using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

class Server{
    static async Task Main(){
        const int port = 9000;
        var listener = new TcpListener(IPAddress.Any, port);
        listener.Start();
        Console.WriteLine($"Server started on port {port}. Waiting for connection...");

        using var client = await listener.AcceptTcpClientAsync();
        Console.WriteLine("Client connected.");

        using var stream = client.GetStream();
        byte[] buffer = new byte[1024];

        int bytesRead = await stream.ReadAsync(buffer, 0, buffer.Length);
        string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);
        Console.WriteLine($"Received: {message}");

        // Echo back to client
        byte[] response = Encoding.UTF8.GetBytes("Echo: " + message);
        await stream.WriteAsync(response, 0, response.Length);
        Console.WriteLine("Echo sent back to client.");

        listener.Stop();
    }
}