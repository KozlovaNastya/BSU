using System;

namespace GrpcService.Models
{
    public class Player
    {
        public string PlayerId { get; set; } = string.Empty;
        public int? Jersey { get; set; }
        public string Fname { get; set; } = string.Empty;
        public string Sname { get; set; } = string.Empty;
        public string Position { get; set; } = string.Empty;
        public DateTime? Birthday { get; set; }
        public int? Weight { get; set; }
        public int? Height { get; set; }
        public string BirthCity { get; set; } = string.Empty;
        public string BirthState { get; set; } = string.Empty;
    }
}