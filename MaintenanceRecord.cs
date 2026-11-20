using System;

namespace Rental
{
    public class MaintenanceRecord
    {
        public ulong Id { get; }
        public string Description { get; set; }
        public double Cost { get; set; }
        public long Timestamp { get; }

        public MaintenanceRecord(ulong id, string description, double cost, long timestamp)
        {
            Id = id;
            Description = description;
            Cost = cost;
            Timestamp = timestamp;
            Console.WriteLine($"[maintenance_record] Создана запись ТО id: {Id}, стоимость: {Cost}");
        }

        // Конструктор копирования для глубокого копирования истории ТО
        public MaintenanceRecord(MaintenanceRecord other)
        {
            if (other == null)
            {
                throw new ArgumentNullException(nameof(other));
            }

            Id = other.Id;
            Description = other.Description;
            Cost = other.Cost;
            Timestamp = other.Timestamp;
            Console.WriteLine($"[maintenance_record] Скопирована запись ТО id: {Id}");
        }

        public override string ToString()
        {
            return $"Запись ТО #{Id}: {Description}, Стоимость: {Cost}";
        }
    }
}