using System;

namespace Rental
{
    public class Vehicle
    {
        public ulong Id { get; }
        public string Model { get; }
        private double _batteryLevel;

        public double BatteryLevel
        {
            get
            {
                return _batteryLevel;
            }
            private set
            {
                _batteryLevel = Math.Max(0.0, Math.Min(100.0, value));
            }
        }

        public double Mileage { get; private set; }

        private MaintenanceRecord[] _maintenanceHistory;
        private int _maintenanceCount; // Счетчик реально добавленных записей

        public Vehicle(ulong id, string model, double batteryLevel, double mileage)
        {
            Id = id;
            Model = model;
            BatteryLevel = batteryLevel;
            Mileage = mileage;

            // Инициализируем фиксированный массив на 10 элементов
            _maintenanceHistory = new MaintenanceRecord[10];
            _maintenanceCount = 0;

            Console.WriteLine($"[vehicle] Created vehicle id: {Id}, model: {Model}");
        }

        public void AddMaintenanceRecord(ulong id, string description, double cost, long timestamp)
        {
            // Проверяем, есть ли свободное место в фиксированном массиве
            if (_maintenanceCount < 10)
            {
                _maintenanceHistory[_maintenanceCount] = new MaintenanceRecord(id, description, cost, timestamp);
                _maintenanceCount++;
                Console.WriteLine($"[vehicle] Added maintenance record to vehicle id: {Id}");
            }
            else
            {
                Console.WriteLine($"[vehicle] Error: Maintenance history is full (max 10 records).");
            }
        }

        public bool CanBeRented() => BatteryLevel >= 20.0;

        public override string ToString()
        { 
            return $"{Model} (ID: {Id}, Заряд: {BatteryLevel}%, Пробег: {Mileage} км)"; 
        }
    }
}