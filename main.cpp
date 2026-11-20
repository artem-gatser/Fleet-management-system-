#include "vehicle.hpp"
#include "rental_contract.hpp"
#include "car.hpp"
#include "truck.hpp"
#include <iostream>
#include <memory>

int main()
{
    std::cout << "Virtual Destructor Demonstration\n";
    {
        std::cout << "Creating a Car object via a BaseVehicle pointer...\n";
        std::unique_ptr<rental::BaseVehicle> vehicle =
            std::make_unique<rental::Car>(101, "Toyota Camry", 90.0, 15000.0, 5);

        std::cout << "Exiting the block, automatic destruction...\n";
    } // Здесь unique_ptr уничтожается, вызывая корректную цепочку деструкторов (снизу вверх)

    std::cout << "\nDeep Copy (Clone) Demonstration\n";
    {
        // Создаем оригинал
        auto originalCar = std::make_unique<rental::Car>(102, "Skoda Octavia", 100.0, 10000.0, 5);

        // Добавляем запись в историю техобслуживания оригинала
        originalCar->AddMaintenanceRecord(501, "Oil change", 5000.0, 1718000000);

        std::cout << "\nCalling Clone() method to create an independent copy...\n";

        // Создаем глубокую копию через метод Clone()
        std::unique_ptr<rental::BaseVehicle> clonedVehicle = originalCar->Clone();

        // Проверяем результаты
        std::cout << "\nParameters Inspection \n";
        std::cout << "Original: inventory No. " << originalCar->GetInventoryNumber()
            << ", model: " << originalCar->GetModel() << "\n";

        std::cout << "Copy:     inventory No. " << clonedVehicle->GetInventoryNumber()
            << ", model: " << clonedVehicle->GetModel() << "\n";

        std::cout << "The copy generated its own unique inventory number, and data was deeply copied.\n";
    } // Здесь корректно удалятся и оригинал, и копия


    std::cout << "\nstd::string Operations Demonstration\n";
    {
        // Создаем объекты транспорта для проверки строковых операций
        rental::Car car1(201, "Tesla Model 3 Long Range", 85.0, 12400.0, 5);
        rental::Car car2(202, "Tesla Model 3 Long Range", 70.0, 25000.0, 5);
        rental::Truck truck1(203, "Volvo FH16 Electric", 60.0, 48000.0, 18.5);

        // Конкатенация строк (формируем метку транспорта)
        std::string model1(car1.GetModel());
        std::string fleetLabel = "FLEET-" + std::to_string(car1.GetInventoryNumber()) + ": ";
        fleetLabel += model1;
        std::cout << "Concatenation: " << fleetLabel << "\n";

        // Сравнение строк (сравниваем модели)
        std::string model2(car2.GetModel());
        std::string truckModel(truck1.GetModel());

        if (model1 == model2)
        {
            std::cout << "Comparison: car1 and car2 share the same model (" << model1 << ").\n";
        }

        if (model1 != truckModel)
        {
            std::cout << "Comparison: car1 and truck1 have different models.\n";
        }

        // Поиск подстроки через find()
        std::size_t pos = truckModel.find("Electric");
        if (pos != std::string::npos)
        {
            std::cout << "Search (find): found \"Electric\" in \"" << truckModel
                << "\" at index " << pos << ".\n";
        }
        else
        {
            std::cout << "Search (find): \"Electric\" not found.\n";
        }

        // Выделение подстроки через substr()
        if (model1.size() >= 5)
        {
            std::string prefix = model1.substr(0, 5);
            std::cout << "Substring (substr): first 5 chars of \"" << model1
                << "\" -> \"" << prefix << "\"\n";
        }
    }


    std::cout << "\nPointer 'this' Demonstration\n";
    {
        // Создаем объекты Car для проверки самоприсваивания и цепочки присваивания
        rental::Car carA(301, "Mazda CX-5", 80.0, 22000.0, 5);
        rental::Car carB(302, "Honda Civic", 95.0, 11000.0, 5);
        rental::Car carC(303, "Ford Focus", 75.0, 34000.0, 5);

        // Самоприсваивание (срабатывает проверка if (this != &other))
        carA = carA;
        std::cout << "Self-assignment check passed for inventory No. " << carA.GetInventoryNumber() << "\n";

        // Цепочка присваивания (проверка возврата *this из operator=)
        carA = carB = carC;
        std::cout << "Chained assignment (carA = carB = carC) result model: " << carA.GetModel() << "\n";

        // Передача текущего объекта (через shared_ptr на объект) в договор аренды RentalContract
        std::cout << "\nPassing the vehicle object (via std::shared_ptr) to RentalContract...\n";
        auto rentedCar = std::make_shared<rental::Car>(304, "Hyundai Tucson", 92.0, 8500.0, 5);
        rental::RentalContract contract(9001, "Alexey Smirnov", 5, rentedCar, 4, 50.0);

        std::cout << "Processing contract issue for inventory No. " << rentedCar->GetInventoryNumber() << "...\n";
        contract.ProcessIssue();
    }


    std::cout << "\nStatic Members Demonstration\n";
    {
        std::cout << "Total vehicles created before creating new ones: "
            << rental::BaseVehicle::GetTotalCreatedVehicles() << "\n";

        rental::Car staticCar(401, "Audi A4", 88.0, 19500.0, 5);
        rental::Truck staticTruck(402, "MAN TGX", 140.0, 62000.0, 20.0);

        // Статический метод можно вызывать через имя класса (без экземпляра объекта)
        std::cout << "Total vehicles created after creating Car and Truck: "
            << rental::BaseVehicle::GetTotalCreatedVehicles() << "\n";
    }


    std::cout << "\nArray Demonstration (Raw Array of std::unique_ptr<BaseVehicle>)\n";
    {
        // Создаем обычный статический массив умных указателей на базовый класс
        std::unique_ptr<rental::BaseVehicle> fleet[3] = {
            std::make_unique<rental::Car>(501, "BMW 320i", 95.0, 14200.0, 5),
            std::make_unique<rental::Truck>(502, "Mercedes-Benz Actros", 120.0, 53000.0, 24.0),
            std::make_unique<rental::Car>(503, "Volkswagen Golf", 78.0, 19800.0, 5)
        };

        // Перебираем элементы массива и работаем через указатель на базовый класс
        for (std::size_t i = 0; i < 3; ++i)
        {
            // Вызываем виртуальные методы через std::unique_ptr<rental::BaseVehicle>
            std::cout << fleet[i]->Describe() << "\n";
            std::cout << "  -> Available for rent: "
                << (fleet[i]->CanBeRented() ? "Yes" : "No") << "\n";
        }
    } // При выходе из блока каждый unique_ptr автоматически удалит свой объект через виртуальный деструктор
    return 0;
}