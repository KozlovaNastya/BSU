using System;
using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;
using GrpcService.Models;

namespace GrpcService.Services
{
    public class PlayerDb
    {
        private const string ConnStr =
            "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=D:\\dp1\\lab1\\CRITTERS.accdb;Persist Security Info=False;";

        public List<Player> GetAll()
        {
            var list = new List<Player>();
            using (var conn = new OleDbConnection(ConnStr))
            using (var cmd = new OleDbCommand(
                "SELECT [playerid],[jersey],[fname],[sname],[position],[birthday],[weight],[height],[birthcity],[birthstate] FROM [roster] ORDER BY [sname]", conn))
            {
                conn.Open();
                using (var r = cmd.ExecuteReader())
                    while (r.Read()) list.Add(Map(r));
            }
            return list;
        }

        public List<Player> GetByPosition(string position)
        {
            var list = new List<Player>();
            using (var conn = new OleDbConnection(ConnStr))
            using (var cmd = new OleDbCommand(
                "SELECT [playerid],[jersey],[fname],[sname],[position],[birthday],[weight],[height],[birthcity],[birthstate] FROM [roster] WHERE [position] = ? ORDER BY [sname]", conn))
            {
                cmd.Parameters.AddWithValue("?", position);
                conn.Open();
                using (var r = cmd.ExecuteReader())
                    while (r.Read()) list.Add(Map(r));
            }
            return list;
        }

        public Player GetById(string playerId)
        {
            using (var conn = new OleDbConnection(ConnStr))
            using (var cmd = new OleDbCommand(
                "SELECT [playerid],[jersey],[fname],[sname],[position],[birthday],[weight],[height],[birthcity],[birthstate] FROM [roster] WHERE [playerid] = ?", conn))
            {
                cmd.Parameters.AddWithValue("?", playerId);
                conn.Open();
                using (var r = cmd.ExecuteReader())
                    return r.Read() ? Map(r) : null;
            }
        }

        public void Insert(Player p)
        {
            using (var conn = new OleDbConnection(ConnStr))
            using (var cmd = new OleDbCommand(
                "INSERT INTO [roster] ([playerid],[jersey],[fname],[sname],[position],[birthday],[weight],[height],[birthcity],[birthstate]) VALUES (?,?,?,?,?,?,?,?,?,?)", conn))
            {
                cmd.Parameters.AddWithValue("?", p.PlayerId);
                cmd.Parameters.AddWithValue("?", (object)p.Jersey ?? DBNull.Value);
                cmd.Parameters.AddWithValue("?", p.Fname);
                cmd.Parameters.AddWithValue("?", p.Sname);
                cmd.Parameters.AddWithValue("?", p.Position);
                cmd.Parameters.AddWithValue("?", (object)p.Birthday ?? DBNull.Value);
                cmd.Parameters.AddWithValue("?", (object)p.Weight ?? DBNull.Value);
                cmd.Parameters.AddWithValue("?", (object)p.Height ?? DBNull.Value);
                cmd.Parameters.AddWithValue("?", p.BirthCity);
                cmd.Parameters.AddWithValue("?", p.BirthState);
                conn.Open();
                cmd.ExecuteNonQuery();
            }
        }

        public void Update(Player p)
        {
            using (var conn = new OleDbConnection(ConnStr))
            using (var cmd = new OleDbCommand(
                "UPDATE [roster] SET [jersey]=?, [fname]=?, [sname]=?, [position]=?, [birthday]=?, [weight]=?, [height]=?, [birthcity]=?, [birthstate]=? WHERE [playerid]=?", conn))
            {
                cmd.Parameters.AddWithValue("?", (object)p.Jersey ?? DBNull.Value);
                cmd.Parameters.AddWithValue("?", p.Fname);
                cmd.Parameters.AddWithValue("?", p.Sname);
                cmd.Parameters.AddWithValue("?", p.Position);
                cmd.Parameters.AddWithValue("?", (object)p.Birthday ?? DBNull.Value);
                cmd.Parameters.AddWithValue("?", (object)p.Weight ?? DBNull.Value);
                cmd.Parameters.AddWithValue("?", (object)p.Height ?? DBNull.Value);
                cmd.Parameters.AddWithValue("?", p.BirthCity);
                cmd.Parameters.AddWithValue("?", p.BirthState);
                cmd.Parameters.AddWithValue("?", p.PlayerId);
                conn.Open();
                cmd.ExecuteNonQuery();
            }
        }

        public void Delete(string playerId)
        {
            using (var conn = new OleDbConnection(ConnStr))
            using (var cmd = new OleDbCommand("DELETE FROM [roster] WHERE [playerid] = ?", conn))
            {
                cmd.Parameters.AddWithValue("?", playerId);
                conn.Open();
                cmd.ExecuteNonQuery();
            }
        }

        private static Player Map(IDataRecord r)
        {
            return new Player
            {
                PlayerId = r["playerid"].ToString(),
                Jersey = r["jersey"] == DBNull.Value ? (int?)null : Convert.ToInt32(r["jersey"]),
                Fname = r["fname"].ToString(),
                Sname = r["sname"].ToString(),
                Position = r["position"].ToString(),
                Birthday = r["birthday"] == DBNull.Value ? (DateTime?)null : Convert.ToDateTime(r["birthday"]),
                Weight = r["weight"] == DBNull.Value ? (int?)null : Convert.ToInt32(r["weight"]),
                Height = r["height"] == DBNull.Value ? (int?)null : Convert.ToInt32(r["height"]),
                BirthCity = r["birthcity"].ToString(),
                BirthState = r["birthstate"].ToString()
            };
        }
    }
}