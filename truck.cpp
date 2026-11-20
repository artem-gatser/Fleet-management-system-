#include "truck.hpp"
#include <iostream>
#include <memory>

namespace rental
{
	// Конструктор грузового автомобиля с параметрами
	Truck::Truck(std::uint64_t id, std::string_view model, double batteryLevel, double mileage, double loadCapacityTons)
		: BaseVehicle(id, model, batteryLevel, mileage)
		, m_loadCapacityTons{ loadCapacityTons }
	{
		std::cout << "[Truck] Constructor called for inventory #" << GetInventoryNumber() << "\n";
	}

	// Конструктор глубокого копирования (история ТО уже глубоко копируется в BaseVehicle)
	Truck::Truck(const Truck& other)
		: BaseVehicle(other)
		, m_loadCapacityTons{ other.m_loadCapacityTons }
	{
		std::cout << "[Truck] Deep copy constructor called for inventory #" << GetInventoryNumber() << "\n";
	}

	// Оператор копирующего присваивания (история ТО обновляется в BaseVehicle::operator=)
	Truck& Truck::operator=(const Truck& other)
	{
		if (this != &other)
		{
			BaseVehicle::operator=(other);
			m_loadCapacityTons = other.m_loadCapacityTons;
		}
		return *this;
	}

	// Деструктор грузового автомобиля
	Truck::~Truck()
	{
		std::cout << "[Truck] Destructor called for inventory #" << GetInventoryNumber() << "\n";
	}

	// Полиморфное описание грузового автомобиля
	std::string Truck::Describe() const
	{
		return "[TRUCK #" + std::to_string(GetInventoryNumber()) + "] Model: " +
			std::string(GetModel()) + ", payload: " + std::to_string(m_loadCapacityTons) + " t";
	}

	// Полиморфное клонирование объекта через конструктор копирования
	std::unique_ptr<BaseVehicle> Truck::Clone() const
	{
		return std::make_unique<Truck>(*this);
	}

	// Расчет стоимости техобслуживания грузовика в зависимости от грузоподъемности
	double Truck::CalculateServiceCost() const
	{
		return 5000.0 + (m_loadCapacityTons * 1200.0);
	}

	// Геттер грузоподъемности в тоннах
	double Truck::GetLoadCapacityTons() const
	{
		return m_loadCapacityTons;
	}
}  // namespace rental