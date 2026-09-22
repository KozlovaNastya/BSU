using System.ComponentModel.DataAnnotations;

namespace lab1.Models
{
    public class Player
    {
        [Display(Name = "ID игрока")]
        public string PlayerId { get; set; } = string.Empty;

        [Display(Name = "Номер")]
        public int? Jersey { get; set; }

        [Display(Name = "Имя")]
        public string Fname { get; set; } = string.Empty;

        [Display(Name = "Фамилия")]
        public string Sname { get; set; } = string.Empty;

        [Display(Name = "Позиция")]
        public string Position { get; set; } = string.Empty;

        [Display(Name = "Дата рождения")]
        [DataType(DataType.Date)]
        public DateTime? Birthday { get; set; }

        [Display(Name = "Вес")]
        public int? Weight { get; set; }

        [Display(Name = "Рост")]
        public int? Height { get; set; }

        [Display(Name = "Город рождения")]
        public string BirthCity { get; set; } = string.Empty;

        [Display(Name = "Штат/Страна")]
        public string BirthState { get; set; } = string.Empty;
    }
}