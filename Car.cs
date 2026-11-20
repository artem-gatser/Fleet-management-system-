using System;

namespace Rental
{
    // Класс закрыт от дальнейшего наследования через sealed
    public sealed class Car : BaseVehicle
    {
        public int PassengerCapacity { get; }

        public Car(ulong id, string model, double batteryLevel, double mileage, int passengerCapacity)
            : base(id, model, batteryLevel, mileage)
        {
            this.PassengerCapacity = passengerCapacity;
            Console.WriteLine($"[car] Создан легковой автомобиль id: {Id}, мест: {PassengerCapacity}");
        }

        // Конструктор копирования: создает глубокую копию через базу и копирует поля Car
        public Car(Car other) : base(other)
        {
            this.PassengerCapacity = other.PassengerCapacity;
            Console.WriteLine($"[car] Создана глубокая копия автомобиля id: {Id}");
        }

        // Поверхностная копия: ссылки внутри (например, массив записей ТО) остаются общими
        public Car ShallowCopy() => (Car)MemberwiseClone();

        // Глубокая копия: независимый объект и собственная копия истории ТО
        public Car DeepCopy() => new Car(this);

        // Переопределение без вызова базового метода
        public override bool CanBeRented() => BatteryLevel >= 20.0;

        // Переопределение с вызовом метода базового класса
        public override string ToString()
        {
            return $"{base.ToString()}, Мест: {PassengerCapacity}";
        }
    }
}