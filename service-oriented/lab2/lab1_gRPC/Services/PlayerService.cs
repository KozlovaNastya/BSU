using System;
using System.Collections.Generic;
using System.Linq;
using Grpc.Net.Client;
using lab1.Models;

namespace lab1.Services
{
    public class PlayerService
    {
        private readonly GrpcChannel _channel;

        private const string ServerUrl = "http://localhost:5006";

        public PlayerService()
        {
            AppContext.SetSwitch("System.Net.Http.SocketsHttpHandler.Http2UnencryptedSupport", true);
            _channel = GrpcChannel.ForAddress("http://localhost:5006");
        }

        public List<Player> GetAll()
        {
            var client = new GrpcService.PlayerService.PlayerServiceClient(_channel);
            var reply = client.GetAll(new GrpcService.EmptyRequest());
            return reply.Players.Select(ToModel).ToList();
        }

        public List<Player> GetByPosition(string position)
        {
            var client = new GrpcService.PlayerService.PlayerServiceClient(_channel);
            var reply = client.GetByPosition(new GrpcService.PositionRequest { Position = position });
            return reply.Players.Select(ToModel).ToList();
        }

        public Player GetById(string id)
        {
            var client = new GrpcService.PlayerService.PlayerServiceClient(_channel);
            var reply = client.GetById(new GrpcService.IdRequest { Id = id });
            return ToModel(reply);
        }

        public void Insert(Player p)
        {
            var client = new GrpcService.PlayerService.PlayerServiceClient(_channel);
            client.Insert(ToRequest(p));
        }

        public void Update(Player p)
        {
            var client = new GrpcService.PlayerService.PlayerServiceClient(_channel);
            client.Update(ToRequest(p));
        }

        public void Delete(string id)
        {
            var client = new GrpcService.PlayerService.PlayerServiceClient(_channel);
            client.Delete(new GrpcService.IdRequest { Id = id });
        }

        // ================ Маппинг ================
        private static Player ToModel(GrpcService.PlayerReply r)
        {
            return new Player
            {
                PlayerId = r.PlayerId,
                Jersey = r.Jersey == 0 ? (int?)null : r.Jersey,
                Fname = r.Fname,
                Sname = r.Sname,
                Position = r.Position,
                Birthday = string.IsNullOrWhiteSpace(r.Birthday) ? (DateTime?)null : DateTime.Parse(r.Birthday),
                Weight = r.Weight == 0 ? (int?)null : r.Weight,
                Height = r.Height == 0 ? (int?)null : r.Height,
                BirthCity = r.BirthCity,
                BirthState = r.BirthState
            };
        }

        private static GrpcService.PlayerRequest ToRequest(Player p)
        {
            return new GrpcService.PlayerRequest
            {
                PlayerId = p.PlayerId ?? "",
                Jersey = p.Jersey ?? 0,
                Fname = p.Fname ?? "",
                Sname = p.Sname ?? "",
                Position = p.Position ?? "",
                Birthday = p.Birthday?.ToString("yyyy-MM-dd") ?? "",
                Weight = p.Weight ?? 0,
                Height = p.Height ?? 0,
                BirthCity = p.BirthCity ?? "",
                BirthState = p.BirthState ?? ""
            };
        }
    }
}