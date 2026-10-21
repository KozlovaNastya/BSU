using System;
using System.Runtime.Serialization;

namespace WcfService.Models
{
    [DataContract]
    public class Player
    {
        [DataMember] public string PlayerId { get; set; }
        [DataMember] public int? Jersey { get; set; }
        [DataMember] public string Fname { get; set; }
        [DataMember] public string Sname { get; set; }
        [DataMember] public string Position { get; set; }
        [DataMember] public DateTime? Birthday { get; set; }
        [DataMember] public int? Weight { get; set; }
        [DataMember] public int? Height { get; set; }
        [DataMember] public string BirthCity { get; set; }
        [DataMember] public string BirthState { get; set; }
    }
}