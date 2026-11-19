#include "car.hpp"
#include <iostream>

namespace rental
{
	// Реализация конструктора с параметрами
	Car::Car(std::uint64_t id, std::string_view model, double batteryLevel, double mileage, int passengerCapacity)
		: BaseVehicle(id, model, batteryLevel, mileage)
		, m_passengerCapacity{ passengerCapacity }
	{
		std::cout << "[Car] Constructor called for inventory #" << GetInventoryNumber() << "\n";
	}

    // Конструктор глубокого копирования
    Car::Car(const Car& other)
        : BaseVehicle(other) // Копируем базовую часть
        , m_passengerCapacity{ other.m_passengerCapacity }
    {
        std::cout << "[Car] Deep copy constructor called for inventory #" << GetInventoryNumber() << "\n";
    }

    // Оператор присваивания
    Car& Car::operator=(const Car& other)
    {
        if (this != &other)
        {
            BaseVehicle::operator=(other); // Базовая часть
            m_passengerCapacity = other.m_passengerCapacity;
        }
        return *this;
    }

    // Реализация метода Clone()
    std::unique_ptr<BaseVehicle> Car::Clone() const
    {
        return std::make_unique<Car>(*this); // Вызывает конструктор копирования
    }

    // Реализация метода Describe
    std::string Car::Describe() const
    {
        return BaseVehicle::Describe() + ", seats " + std::to_string(m_passengerCapacity);
    }

	// Деструктор
	Car::~Car()
	{
		std::cout << "[Car] Destructor called for inventory #" << GetInventoryNumber() << "\n";
	}

	// Реализация чисто виртуального метода
	double Car::CalculateServiceCost() const
	{
		// Расчет стоимости техобслуживания для легкового авто
		return 1000.0 + (m_passengerCapacity * 1200.0);
	}

    int Car::GetPassengerCapacity() const
	{
		return m_passengerCapacity;
	}
}  // namespace rental