using System.Collections.Generic;
using WcfService.Models;
using WcfService.Services;

namespace WcfService
{
    public class PlayerService : IPlayerService
    {
        private readonly PlayerDb _db = new PlayerDb();

        public List<Player> GetAll() => _db.GetAll();

        public List<Player> GetByPosition(string position) => _db.GetByPosition(position);

        public Player GetById(string id) => _db.GetById(id);

        public void Insert(Player player) => _db.Insert(player);

        public void Update(Player player) => _db.Update(player);

        public void Delete(string id) => _db.Delete(id);
    }
}