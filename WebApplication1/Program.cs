using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.Hosting;
//using System.Net.WebSockets;
using System.Text;
using System.Collections.Concurrent;


var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

var espSockets = new ConcurrentBag<WebSocket>();
var clientSockets = new ConcurrentBag<WebSocket>();
DB_Server DB = new DB_Server();

DB.Connection();

app.UseStaticFiles();
app.UseWebSockets();

app.Map("/esp32", async context =>
{
    if (context.WebSockets.IsWebSocketRequest)
    {
        if (context.Request.Headers.TryGetValue("Authorization", out var authHeader))
        {
            if (authHeader != null && authHeader.StartsWith("Basic "))
            {
                string encoded = authHeader.Substring("Basic ".Length).Trim();

                byte[] data = Convert.FromBase64String(encoded);
                string decoded = Encoding.UTF8.GetString(data);

                string[] parts = decoded.Split(':');
                if (parts.Length == 2)
                {
                    string login = parts[0];
                    string password = parts[1];
                    Console.WriteLine($"Login: {login}, Password: {password}");
                }
                else
                {
                    Console.WriteLine("Ошибка формата login:password");
                }
            }
            else
            {
                Console.WriteLine("Заголовок Authorization отсутствует или не Basic");
            }
        }
        var ws = await context.WebSockets.AcceptWebSocketAsync();
        espSockets.Add(ws);

        var buffer = new byte[1024 * 4];
        while (ws.State == WebSocketState.Open)
        {
            var result = await ws.ReceiveAsync(new ArraySegment<byte>(buffer), default);
            if (result.MessageType == WebSocketMessageType.Text)
            {
                var msg = Encoding.UTF8.GetString(buffer, 0, result.Count);
                Console.WriteLine($"[ESP] {msg}");

                // пересылаем всем клиентам
                foreach (var client in clientSockets)
                {
                    if (client.State == WebSocketState.Open)
                        await client.SendAsync(Encoding.UTF8.GetBytes(msg),
                            WebSocketMessageType.Text, true, default);
                }
            }
        }
    }
    else
    {
        context.Response.StatusCode = 400;
    }
});

app.MapPost("/esp/login", (EspLoginRequest req) =>
{



});

app.Map("/login", () => Results.Redirect("/login.html"));

app.MapPost("/api/login", (LoginRequest req) =>
{
    Console.WriteLine($"Login");
    if (DB.ClientLogin(req.Login, req.Password))
    {
        return Results.Json(new { success = true, message = $"Добро пожаловать, {req.Login}!" });
    }
    else
    {
        return Results.Json(new { success = false, message = "Неверный логин или пароль" });
    }
});

app.Map("/client", async context =>
{
    if (context.WebSockets.IsWebSocketRequest)
    {
        var ws = await context.WebSockets.AcceptWebSocketAsync();
        clientSockets.Add(ws);

        var buffer = new byte[1024 * 4];
        while (ws.State == WebSocketState.Open)
        {
            var result = await ws.ReceiveAsync(new ArraySegment<byte>(buffer), default);
            if (result.MessageType == WebSocketMessageType.Text)
            {
                var msg = Encoding.UTF8.GetString(buffer, 0, result.Count);
                Console.WriteLine($"[Client] {msg}");

                // пересылаем всем ESP
                foreach (var esp in espSockets)
                {
                    if (esp.State == WebSocketState.Open)
                        await esp.SendAsync(Encoding.UTF8.GetBytes(msg),
                            WebSocketMessageType.Text, true, default);
                }
            }
        }
    }
    else
    {
        context.Response.StatusCode = 400;
    }
});

app.Run("http://0.0.0.0:9000");

public record EspLoginRequest(string DeviceID, string Password);
public record LoginRequest(string Login, string Password);
