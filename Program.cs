using System;
using static System.Console;
using GeoCoord = Rental.GeoPoint;
using LogStream = Rental.IssueLog;

namespace Rental
{
    internal static class Program
    {
        // Создаёт временный объект автомобиля внутри метода и возвращает слабую ссылку на него.
        private static WeakReference CreateTemporaryCarWatcher()
        {
            var tempCar = new Car(999, "Списанный седан", 0.0, 300000.0, 4);
            return new WeakReference(tempCar);
        }

        private static void Main(string[] args)
        {
            // Поддержка кириллицы в консоли
            OutputEncoding = System.Text.Encoding.UTF8;

            // Абстрактный класс BaseVehicle, два наследника (Car и Truck), : base(...), this, статика
            WriteLine("ИЕРАРХИЯ, КОНСТРУКТОРЫ И СТАТИКА");
            BaseVehicle car = new Car(101, "Tesla Model 3", 85.0, 15000.0, 5);
            BaseVehicle truck = new Truck(201, "Volvo FH Electric", 45.0, 42000.0, 18.5);
            BaseVehicle lowBatteryTruck = new Truck(202, "MAN eTGM", 15.0, 60000.0, 12.0);

            car.AddMaintenanceRecord(1, "Проверка батареи", 250.0, 1728000000);
            truck.AddMaintenanceRecord(2, "Диагностика тормозной системы", 600.0, 1728500000);

            WriteLine($"Следующий порядковый номер по статическому методу: {BaseVehicle.NextVehicleSequenceNumber()}");

            // Переопределение без вызова базы (CanBeRented) и с вызовом базы (ToString -> base.ToString())
            WriteLine("\nПЕРЕОПРЕДЕЛЕНИЕ МЕТОДОВ И SEALED");
            WriteLine($"Car: {car}");
            WriteLine($"Car доступен для аренды? {car.CanBeRented()}");

            WriteLine($"Truck: {truck}");
            WriteLine($"Truck доступен для аренды? {truck.CanBeRented()}");

            WriteLine($"LowBatteryTruck: {lowBatteryTruck}");
            WriteLine($"LowBatteryTruck доступен для аренды? {lowBatteryTruck.CanBeRented()}");

            // Проверка аренды через RentalContract
            WriteLine("\nОФОРМЛЕНИЕ АРЕНДЫ (RentalContract)");
            var badContract = new RentalContract(501, "Иван", 1, car, 3, 50.0);
            badContract.ProcessIssue();

            var goodContract = new RentalContract(502, "Алексей", 5, car, 5, 50.0);
            if (goodContract.ProcessIssue())
            {
                goodContract.CompleteContract();
            }

            // Поверхностная копия (MemberwiseClone) и глубокая копия (конструктор копирования)
            WriteLine("\nПОВЕРХНОСТНАЯ И ГЛУБОКАЯ КОПИЯ");
            var originalCar = new Car(103, "Hyundai Ioniq 5", 80.0, 12000.0, 5);
            originalCar.AddMaintenanceRecord(10, "Плановый осмотр", 150.0, 1729000000);

            Car shallowCopy = originalCar.ShallowCopy();
            Car deepCopy = originalCar.DeepCopy();

            WriteLine($"До добавления новой записи ТО -> оригинал: {originalCar.GetMaintenanceCount()}, " +
                      $"поверхностная копия: {shallowCopy.GetMaintenanceCount()}, " +
                      $"глубокая копия: {deepCopy.GetMaintenanceCount()}");

            // В ShallowCopy массив _maintenanceHistory общий с оригиналом, поэтому счётчик записей ТО меняется у обоих
            originalCar.AddMaintenanceRecord(11, "Замена тормозных колодок", 300.0, 1730000000);

            WriteLine($"После добавления записи ТО в оригинал -> оригинал: {originalCar.GetMaintenanceCount()}, " +
                      $"поверхностная копия: {shallowCopy.GetMaintenanceCount()}, " +
                      $"глубокая копия: {deepCopy.GetMaintenanceCount()}");

            // Сравнение объектов по содержимому (Equals и GetHashCode по Id)
            WriteLine("\nСРАВНЕНИЕ ОБЪЕКТОВ ПО СОДЕРЖИМОМУ (Equals / GetHashCode)");
            BaseVehicle sameIdCar = new Car(103, "Другое название модели", 10.0, 99999.0, 2);
            BaseVehicle differentIdCar = new Car(104, "Kia EV6", 80.0, 12000.0, 5);

            WriteLine($"Ссылка (==) originalCar и sameIdCar: {originalCar == sameIdCar}");
            WriteLine($"Содержимое (Equals по Id) originalCar и sameIdCar: {originalCar.Equals(sameIdCar)}");
            WriteLine($"Хэш-коды совпадают (Id = 103)? {originalCar.GetHashCode() == sameIdCar.GetHashCode()} " +
                      $"({originalCar.GetHashCode()} vs {sameIdCar.GetHashCode()})");
            WriteLine($"Содержимое (Equals по Id) originalCar и differentIdCar: {originalCar.Equals(differentIdCar)}");

            // Значимый тип (struct) vs ссылочный тип (class)
            WriteLine("\nЗНАЧИМЫЙ ТИП (struct)");
            var startPoint = new GeoCoord { Latitude = 53.3498, Longitude = 83.7836 };
            var currentPoint = startPoint;
            currentPoint.Latitude = 55.7558;
            WriteLine($"startPoint.Latitude: {startPoint.Latitude}, currentPoint.Latitude: {currentPoint.Latitude}");

            // Освобождение ресурса через using var + сборщик мусора
            WriteLine("\nUSING VAR И СБОРЩИК МУСОРА");
            using (var log = new LogStream("Абонемент проката"))
            {
                log.Write($"Выдан автомобиль: {car}");
            }

            var watcher = CreateTemporaryCarWatcher();
            WriteLine($"Временный автомобиль жив до GC.Collect()? {watcher.IsAlive}");
            GC.Collect();
            GC.WaitForPendingFinalizers();
            WriteLine($"Временный автомобиль жив после GC.Collect()? {watcher.IsAlive}");

            WriteLine("\nДЕМОНСТРАЦИЯ ЗАВЕРШЕНА");
        }
    }

    // Структура для географических координат автомобиля (значимый тип)
    public struct GeoPoint
    {
        public double Latitude;
        public double Longitude;
    }
}