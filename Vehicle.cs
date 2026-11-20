using System;

namespace Rental
{
    // Абстрактный базовый класс: нельзя создать напрямую, только через наследников
    public abstract class BaseVehicle
    {
        private const int MaxMaintenanceRecords = 10;
        private static int _lastVehicleSequence;

        public int VehicleSequenceNumber { get; }
        public ulong Id { get; }
        public string Model { get; }

        private double _batteryLevel;
        public double BatteryLevel
        {
            get => _batteryLevel;
            protected set => _batteryLevel = Math.Max(0.0, Math.Min(100.0, value));
        }

        public double Mileage { get; protected set; }

        // Защищенные поля: доступны наследникам, но скрыты снаружи
        protected readonly MaintenanceRecord[] _maintenanceHistory;
        protected int _maintenanceCount;

        protected BaseVehicle(ulong id, string model, double batteryLevel, double mileage)
        {
            VehicleSequenceNumber = NextVehicleSequenceNumber();
            this.Id = id;
            this.Model = model;
            this.BatteryLevel = batteryLevel;
            this.Mileage = mileage;

            this._maintenanceHistory = new MaintenanceRecord[MaxMaintenanceRecords];
            this._maintenanceCount = 0;

            Console.WriteLine($"[base_vehicle] Создан транспорт #{VehicleSequenceNumber} (id: {Id}, модель: {Model})");
        }

        // Конструктор копирования: глубоко копирует записи ТО в новый массив
        protected BaseVehicle(BaseVehicle other)
        {
            if (other == null)
            {
                throw new ArgumentNullException(nameof(other));
            }

            VehicleSequenceNumber = NextVehicleSequenceNumber();
            this.Id = other.Id;
            this.Model = other.Model;
            this.BatteryLevel = other.BatteryLevel;
            this.Mileage = other.Mileage;

            this._maintenanceHistory = new MaintenanceRecord[MaxMaintenanceRecords];
            this._maintenanceCount = other._maintenanceCount;

            for (int i = 0; i < other._maintenanceCount; i++)
            {
                if (other._maintenanceHistory[i] is MaintenanceRecord record)
                {
                    this._maintenanceHistory[i] = new MaintenanceRecord(record);
                }
            }

            Console.WriteLine($"[base_vehicle] Скопирован транспорт #{VehicleSequenceNumber} (id: {Id}, записей ТО: {_maintenanceCount})");
        }

        public static int NextVehicleSequenceNumber() => ++_lastVehicleSequence;

        public void AddMaintenanceRecord(ulong id, string description, double cost, long timestamp)
        {
            if (_maintenanceCount < MaxMaintenanceRecords)
            {
                _maintenanceHistory[_maintenanceCount] = new MaintenanceRecord(id, description, cost, timestamp);
                _maintenanceCount++;
                Console.WriteLine($"[base_vehicle] Добавлена запись ТО для транспорта id: {Id}");
            }
            else
            {
                Console.WriteLine($"[base_vehicle] Ошибка: история ТО заполнена (максимум {MaxMaintenanceRecords} записей).");
            }
        }

        public int GetMaintenanceCount() => _maintenanceCount;

        // Абстрактный метод: каждый наследник обязан определить своё условие аренды
        public abstract bool CanBeRented();

        // Сравнение объектов по содержимому (по Id) + согласованный GetHashCode
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(this, obj))
            {
                return true;
            }

            BaseVehicle other = obj as BaseVehicle;
            if (other == null)
            {
                return false;
            }

            return this.Id == other.Id;
        }

        public override int GetHashCode()
        {
            return Id.GetHashCode();
        }

        public override string ToString()
        {
            return $"{Model} (ID: {Id}, Заряд: {BatteryLevel}%, Пробег: {Mileage} км)";
        }
    }
}