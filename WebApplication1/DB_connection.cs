using System;
using Npgsql;

public class DB_Server
{
    static string connString = "Host=localhost;Port=5432;Username=postgres;Password=35+F9-SQi-?bgag;Database=project_d";
    private NpgsqlConnection conn = new NpgsqlConnection(connString);
    public void Connection()
    {
            conn.Open();

            Console.WriteLine("Connection Opened");
            //Пример INSERT с параметрами
            /*using (var cmd = new NpgsqlCommand("INSERT INTO devices (name) VALUES (@name)", conn))
            {
                cmd.Parameters.AddWithValue("name", "Новый пользователь");
                cmd.ExecuteNonQuery();
            }*/
    }
    public bool DeviceLogin(string DeviceId, string Password)
    {
        using (var cmd = new NpgsqlCommand("SELECT password FROM devices WHERE id = @id", conn))
        {
            cmd.Parameters.AddWithValue("id", DeviceId);
            var result = cmd.ExecuteReader();
            Console.WriteLine($"Login: {DeviceId}");
            Console.WriteLine($"Password from DB: {result}");
            Console.WriteLine($"Password: {Password}");
            if (result != null)
            {
                if (result.ToString() == Password)
                {
                    return true;
                }
                else
                {
                    Console.WriteLine("Device password is incorect");
                    return false;
                }
            }
        }
        Console.WriteLine("Device has no password or not singin");
        return false;
    }

    public bool ClientLogin(string username, string password)
    {
        using (var cmd = new NpgsqlCommand("SELECT password FROM users WHERE login = @login", conn))
        {
            cmd.Parameters.AddWithValue("login", username);
            var result = cmd.ExecuteScalar();
            Console.WriteLine($"Login: {username}");
            Console.WriteLine($"Password from DB: {result}");
            Console.WriteLine($"Password: {password}");
            if (result != null && result.ToString() == password)
            {
                return true;
            }
            else
            {
                Console.WriteLine("User has no password or not singin");
                return false;
            }
        }
    }
    
}
