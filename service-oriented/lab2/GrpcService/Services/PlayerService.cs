using Grpc.Core;
using GrpcService.Models;
using GrpcService.Services;

namespace GrpcService
{
    public class PlayerGrpcService : GrpcService.PlayerService.PlayerServiceBase
    {
        private readonly PlayerDb _db = new PlayerDb();
        private readonly ILogger<PlayerGrpcService> _logger;

        public PlayerGrpcService(ILogger<PlayerGrpcService> logger)
        {
            _logger = logger;
        }

        public override Task<PlayerList> GetAll(EmptyRequest request, ServerCallContext context)
        {
            _logger.LogInformation("GetAll: запрос всех игроков");
            var list = new PlayerList();
            foreach (var p in _db.GetAll())
                list.Players.Add(ToReply(p));
            _logger.LogInformation($"GetAll: возвращено {list.Players.Count} записей");
            return Task.FromResult(list);
        }

        public override Task<PlayerList> GetByPosition(PositionRequest request, ServerCallContext context)
        {
            _logger.LogInformation($"GetByPosition: запрос игроков с позицией '{request.Position}'");
            var list = new PlayerList();
            foreach (var p in _db.GetByPosition(request.Position))
                list.Players.Add(ToReply(p));
            _logger.LogInformation($"GetByPosition: возвращено {list.Players.Count} записей");
            return Task.FromResult(list);
        }

        public override Task<PlayerReply> GetById(IdRequest request, ServerCallContext context)
        {
            _logger.LogInformation($"GetById: запрос игрока с ID '{request.Id}'");
            var p = _db.GetById(request.Id);
            if (p == null)
            {
                _logger.LogWarning($"GetById: игрок с ID '{request.Id}' не найден");
                throw new RpcException(new Status(StatusCode.NotFound, "Player not found"));
            }
            return Task.FromResult(ToReply(p));
        }

        public override Task<EmptyReply> Insert(PlayerRequest request, ServerCallContext context)
        {
            _logger.LogInformation($"Insert: добавление игрока '{request.PlayerId}' ({request.Fname} {request.Sname})");
            _db.Insert(FromRequest(request));
            _logger.LogInformation($"Insert: игрок '{request.PlayerId}' успешно добавлен");
            return Task.FromResult(new EmptyReply());
        }

        public override Task<EmptyReply> Update(PlayerRequest request, ServerCallContext context)
        {
            _logger.LogInformation($"Update: обновление игрока '{request.PlayerId}'");
            _db.Update(FromRequest(request));
            _logger.LogInformation($"Update: игрок '{request.PlayerId}' успешно обновлён");
            return Task.FromResult(new EmptyReply());
        }

        public override Task<EmptyReply> Delete(IdRequest request, ServerCallContext context)
        {
            _logger.LogInformation($"Delete: удаление игрока с ID '{request.Id}'");
            _db.Delete(request.Id);
            _logger.LogInformation($"Delete: игрок с ID '{request.Id}' успешно удалён");
            return Task.FromResult(new EmptyReply());
        }

        // ================ Маппинг ================
        private static PlayerReply ToReply(Player p)
        {
            return new PlayerReply
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

        private static Player FromRequest(PlayerRequest r)
        {
            DateTime? bd = null;
            if (!string.IsNullOrWhiteSpace(r.Birthday) && DateTime.TryParse(r.Birthday, out var parsed))
                bd = parsed;

            return new Player
            {
                PlayerId = r.PlayerId,
                Jersey = r.Jersey == 0 ? (int?)null : r.Jersey,
                Fname = r.Fname,
                Sname = r.Sname,
                Position = r.Position,
                Birthday = bd,
                Weight = r.Weight == 0 ? (int?)null : r.Weight,
                Height = r.Height == 0 ? (int?)null : r.Height,
                BirthCity = r.BirthCity,
                BirthState = r.BirthState
            };
        }
    }
}