#pragma once
#include "BaseVehicle.hpp"

namespace rental
{
	class Truck : public BaseVehicle
	{
	private:
		double m_loadCapacityTons{ 5.0 }; // Поле только только для грузовика

	public:
		// Конструктор с параметрами
		Truck(std::uint64_t id, std::string_view model, double batteryLevel, double mileage, double loadCapacityTons);

		// Деструктор (будет выводить сообщение для отслеживания порядка уничтожения)
		~Truck() override;

		// Конструкторы перемещения/копирования
		Truck(const Truck& other);
		Truck& operator=(const Truck& other);

		Truck(Truck&&) = default;
		Truck& operator=(Truck&&) = default;

		[[nodiscard]] std::unique_ptr<BaseVehicle> Clone() const override;

		// Обязательная реализация чисто виртуального метода из BaseVehicle
		[[nodiscard]] double CalculateServiceCost() const;

		// Виртуальный метод Describe() с запретом дальнейшего наследования
		[[nodiscard]] std::string Describe() const override final;

		[[nodiscard]] double GetLoadCapacityTons() const;
	};
}  // namespace rental