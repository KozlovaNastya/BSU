using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Text;
using lab1.Models;
using Newtonsoft.Json;

namespace lab1.Services
{
    public class PlayerService
    {
        private readonly HttpClient _http;

        private const string BaseUrl = "http://localhost:52073/PlayerService.svc";

        public PlayerService()
        {
            _http = new HttpClient();
        }

        public List<Player> GetAll()
        {
            var url = $"{BaseUrl}/players";
            var json = _http.GetStringAsync(url).Result;
            return JsonConvert.DeserializeObject<List<Player>>(json) ?? new List<Player>();
        }

        public List<Player> GetByPosition(string position)
        {
            var url = $"{BaseUrl}/players/position/{position}";
            var json = _http.GetStringAsync(url).Result;
            return JsonConvert.DeserializeObject<List<Player>>(json) ?? new List<Player>();
        }

        public Player GetById(string id)
        {
            var url = $"{BaseUrl}/players/{id}";
            var json = _http.GetStringAsync(url).Result;
            return JsonConvert.DeserializeObject<Player>(json);
        }

        public void Insert(Player p)
        {
            var url = $"{BaseUrl}/players";
            var content = new StringContent(JsonConvert.SerializeObject(p), Encoding.UTF8, "application/json");
            var response = _http.PostAsync(url, content).Result;
            response.EnsureSuccessStatusCode();
        }

        public void Update(Player p)
        {
            var url = $"{BaseUrl}/players";
            var content = new StringContent(JsonConvert.SerializeObject(p), Encoding.UTF8, "application/json");
            var response = _http.PutAsync(url, content).Result;
            response.EnsureSuccessStatusCode();
        }

        public void Delete(string id)
        {
            var url = $"{BaseUrl}/players/{id}";
            var response = _http.DeleteAsync(url).Result;
            response.EnsureSuccessStatusCode();
        }
    }
}