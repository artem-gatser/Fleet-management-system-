using System;

namespace Rental
{
    // Второй наследник: грузовик, запрещаем дальнейшее наследование через sealed
    public sealed class Truck : BaseVehicle
    {
        public double LoadCapacityTons { get; }

        public Truck(ulong id, string model, double batteryLevel, double mileage, double loadCapacityTons)
            : base(id, model, batteryLevel, mileage)
        {
            LoadCapacityTons = loadCapacityTons;
            Console.WriteLine($"[truck] Создан грузовик id: {Id}, грузоподъемность: {LoadCapacityTons} т");
        }

        // Переопределение без вызова базового метода
        public override bool CanBeRented() => BatteryLevel >= 20.0 && LoadCapacityTons > 0.0;

        // Переопределение с вызовом базы и запрет дальнейшего переопределения в потомках
        public sealed override string ToString()
        {
            return $"{base.ToString()}, Грузоподъемность: {LoadCapacityTons} т";
        }
    }
}