using System;
namespace Rental

{

    class Program

    {


        // Создает временный объект автомобиля внутри метода и возвращает слабую ссылку на него.
        static WeakReference CreateTemporaryCarWatcher()
        {
            var tempCar = new Vehicle(999, "Списанный автобус", 0.0, 300000.0);
            return new WeakReference(tempCar);
        }



        static void Main(string[] args)

        {

            // Поддержка кириллицы в консоли

            Console.OutputEncoding = System.Text.Encoding.UTF8;



            Console.WriteLine("СТАРТ ТЕСТИРОВАНИЯ\n");



            // Создание автомобиля и композиция

            var myCar = new Vehicle(101, "Tesla Model 3", 85.0, 15000.0);

            myCar.AddMaintenanceRecord(1, "Проверка батареи", 250.0, 1728000000);



            // Тест 1: Неуспешная аренда (маленький стаж)

            Console.WriteLine("\nТЕСТ 1: Попытка аренды клиентом со стажем 1 год");

            var badContract = new RentalContract(501, "Иван", 1, myCar, 3, 50.0);

            badContract.ProcessIssue();



            // Тест 2: Успешная аренда

            Console.WriteLine("\nТЕСТ 2: Успешная аренда клиентом со стажем 5 лет");

            var goodContract = new RentalContract(502, "Алексей", 5, myCar, 5, 50.0);

            if (goodContract.ProcessIssue())

            {

                goodContract.CompleteContract();

            }



            // Демонстрация памяти: Ссылки и копии

            Console.WriteLine("\nДЕМОНСТРАЦИЯ ПАМЯТИ: Ссылки и копии");

            var firstVehicle = new Vehicle(102, "Nissan Leaf", 90.0, 5000.0);

            var secondVehicle = firstVehicle;

            Console.WriteLine($"firstVehicle == secondVehicle: {firstVehicle == secondVehicle}");



            // Демонстрация отличия struct от class на примере координат автомобиля
            Console.WriteLine("\nДЕМОНСТРАЦИЯ ПАМЯТИ: Значимый тип (struct) на примере координат");
            var startPoint = new GeoPoint { Latitude = 53.3498, Longitude = 83.7836 };
            var currentPoint = startPoint; // Создается полная независимая копия в памяти

            currentPoint.Latitude = 55.7558; // Изменяем координаты только для текущей точки

            Console.WriteLine($"Начальная широта (startPoint): {startPoint.Latitude} (не изменилась)");
            Console.WriteLine($"Текущая широта (currentPoint): {currentPoint.Latitude}");



            // Демонстрация освобождения ресурса через IDisposable и using

            Console.WriteLine("\nДЕМОНСТРАЦИЯ: Освобождение ресурса (using)");

            using (var log = new IssueLog("Абонемент проката"))

            {

                log.Write("выдан автомобиль Tesla Model 3");

            }



            // Демонстрация сборщика мусора через WeakReference
            Console.WriteLine("\nДЕМОНСТРАЦИЯ: Сборщик мусора (Garbage Collector)");
            var watcher = CreateTemporaryCarWatcher();
            Console.WriteLine($"Автомобиль жив до сборки мусора? {watcher.IsAlive}");

            GC.Collect(); // Принудительный сбор мусора
            GC.WaitForPendingFinalizers(); // Ожидание завершения очистки
            Console.WriteLine($"Автомобиль жив после GC.Collect()? {watcher.IsAlive}");


            Console.WriteLine("\nТЕСТИРОВАНИЕ ЗАВЕРШЕНО");

        }

    }


    // Структура для географических координат автомобиля (значимый тип)
    public struct GeoPoint
    {
        public double Latitude;
        public double Longitude;
    }

}