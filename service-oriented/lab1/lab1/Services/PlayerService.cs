using System.Data;
using System.Data.OleDb;
using lab1.Models;

namespace lab1.Services
{
    public class PlayerService
    {
        private readonly string _connectionString;

        public PlayerService(IConfiguration configuration)
        {
            _connectionString = configuration.GetConnectionString("AccessDb")
                ?? throw new InvalidOperationException("Строка подключения AccessDb не найдена");
        }

        public void EnsureStoredQueries()
        {
            using var conn = new OleDbConnection(_connectionString);
            conn.Open();

            // Удаляем старые версии запросов, если есть
            string[] drops = { "qrySelectAll", "qrySelectByPosition", "qryDeleteById", "qryUpdateFname", "qryInsertPlayer", "qryTest" };
            foreach (var d in drops)
            {
                try
                {
                    using var cmd = new OleDbCommand($"DROP PROCEDURE {d}", conn);
                    cmd.ExecuteNonQuery();
                }
                catch {}
            }

            // Создаём 4 (плюс один вспомогательный) сохранённых запроса
            string[] creates = new[]
            {
                // 1. Выборка всех (без параметров)
                "CREATE PROCEDURE qrySelectAll AS " +
                "SELECT [playerid],[jersey],[fname],[sname],[position],[birthday],[weight],[height],[birthcity],[birthstate] " +
                "FROM [roster] ORDER BY [sname]",

                // 2. Выборка по позиции (с параметром)
                "CREATE PROCEDURE qrySelectByPosition AS " +
                "PARAMETERS pos TEXT; " +
                "SELECT [playerid],[jersey],[fname],[sname],[position],[birthday],[weight],[height],[birthcity],[birthstate] " +
                "FROM [roster] WHERE [position]=pos ORDER BY [sname]",

                // 3. Удаление по ID (с параметром)
                "CREATE PROCEDURE qryDeleteById AS " +
                "PARAMETERS pid TEXT; " +
                "DELETE FROM [roster] WHERE [playerid]=pid",

                // 4. Изменение имени по ID
                "CREATE PROCEDURE qryUpdateFname AS " +
                "PARAMETERS newName TEXT, pid TEXT; " +
                "UPDATE [roster] SET [fname]=newName WHERE [playerid]=pid",

                // 5. Пополнение (с десятью параметрами)
                "CREATE PROCEDURE qryInsertPlayer AS " +
                "PARAMETERS pid TEXT, jrs SHORT, fn TEXT, sn TEXT, pos TEXT, bd DATETIME, w SHORT, h SHORT, bc TEXT, bs TEXT; " +
                "INSERT INTO [roster] ([playerid],[jersey],[fname],[sname],[position],[birthday],[weight],[height],[birthcity],[birthstate]) " +
                "VALUES (pid, jrs, fn, sn, pos, bd, w, h, bc, bs)"
            };

            foreach (var q in creates)
            {
                using var cmd = new OleDbCommand(q, conn);
                cmd.ExecuteNonQuery();
            }
        }

        // ВЫЗОВ ХРАНИМЫХ ЗАПРОСОВ

        // SELECT всех (хранимый запрос qrySelectAll)
        public List<Player> GetAll()
        {
            var list = new List<Player>();
            using var conn = new OleDbConnection(_connectionString);
            using var cmd = new OleDbCommand("qrySelectAll", conn);
            cmd.CommandType = CommandType.StoredProcedure;
            conn.Open();
            using var reader = cmd.ExecuteReader();
            while (reader.Read())
                list.Add(Map(reader));
            return list;
        }

        // SELECT по позиции (хранимый запрос qrySelectByPosition с параметром)
        public List<Player> GetByPosition(string position)
        {
            var list = new List<Player>();
            using var conn = new OleDbConnection(_connectionString);
            using var cmd = new OleDbCommand("qrySelectByPosition", conn);
            cmd.CommandType = CommandType.StoredProcedure;
            cmd.Parameters.AddWithValue("pos", position);
            conn.Open();
            using var reader = cmd.ExecuteReader();
            while (reader.Read())
                list.Add(Map(reader));
            return list;
        }

        // Получить одного игрока (для Details/Edit/Delete форм)
        public Player? GetById(string playerId)
        {
            using var conn = new OleDbConnection(_connectionString);
            using var cmd = new OleDbCommand(
                "SELECT [playerid],[jersey],[fname],[sname],[position],[birthday],[weight],[height],[birthcity],[birthstate] FROM [roster] WHERE [playerid] = ?", conn);
            cmd.Parameters.AddWithValue("?", playerId);
            conn.Open();
            using var reader = cmd.ExecuteReader();
            return reader.Read() ? Map(reader) : null;
        }

        // DELETE (хранимый запрос qryDeleteById с параметром)
        public void Delete(string playerId)
        {
            using var conn = new OleDbConnection(_connectionString);
            using var cmd = new OleDbCommand("qryDeleteById", conn);
            cmd.CommandType = CommandType.StoredProcedure;
            cmd.Parameters.AddWithValue("pid", playerId);
            conn.Open();
            cmd.ExecuteNonQuery();
        }

        // UPDATE имени (хранимый запрос qryUpdateFname с двумя параметрами)
        public void UpdateFname(string playerId, string newFname)
        {
            using var conn = new OleDbConnection(_connectionString);
            using var cmd = new OleDbCommand("qryUpdateFname", conn);
            cmd.CommandType = CommandType.StoredProcedure;
            cmd.Parameters.AddWithValue("newName", newFname);
            cmd.Parameters.AddWithValue("pid", playerId);
            conn.Open();
            cmd.ExecuteNonQuery();
        }

        // INSERT (хранимый запрос qryInsertPlayer с десятью параметрами)
        public void Insert(Player p)
        {
            using var conn = new OleDbConnection(_connectionString);
            using var cmd = new OleDbCommand("qryInsertPlayer", conn);
            cmd.CommandType = CommandType.StoredProcedure;
            cmd.Parameters.AddWithValue("pid", p.PlayerId);
            cmd.Parameters.AddWithValue("jrs", (object?)p.Jersey ?? DBNull.Value);
            cmd.Parameters.AddWithValue("fn", p.Fname);
            cmd.Parameters.AddWithValue("sn", p.Sname);
            cmd.Parameters.AddWithValue("pos", p.Position);
            cmd.Parameters.AddWithValue("bd", (object?)p.Birthday ?? DBNull.Value);
            cmd.Parameters.AddWithValue("w", (object?)p.Weight ?? DBNull.Value);
            cmd.Parameters.AddWithValue("h", (object?)p.Height ?? DBNull.Value);
            cmd.Parameters.AddWithValue("bc", p.BirthCity);
            cmd.Parameters.AddWithValue("bs", p.BirthState);
            conn.Open();
            cmd.ExecuteNonQuery();
        }

        // Вспомогательный маппинг
        private static Player Map(IDataRecord r)
        {
            return new Player
            {
                PlayerId = r["playerid"].ToString() ?? "",
                Jersey = r["jersey"] == DBNull.Value ? null : Convert.ToInt32(r["jersey"]),
                Fname = r["fname"].ToString() ?? "",
                Sname = r["sname"].ToString() ?? "",
                Position = r["position"].ToString() ?? "",
                Birthday = r["birthday"] == DBNull.Value ? null : Convert.ToDateTime(r["birthday"]),
                Weight = r["weight"] == DBNull.Value ? null : Convert.ToInt32(r["weight"]),
                Height = r["height"] == DBNull.Value ? null : Convert.ToInt32(r["height"]),
                BirthCity = r["birthcity"].ToString() ?? "",
                BirthState = r["birthstate"].ToString() ?? ""
            };
        }
    }
}