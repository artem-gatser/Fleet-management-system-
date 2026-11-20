#pragma once
#include "BaseVehicle.hpp"
#include <memory>
#include <string>
#include <string_view>

namespace rental
{
	class Car : public BaseVehicle
	{
	private:
		int m_passengerCapacity{ 4 }; // Количество пассажирских мест — поле только для легковой машины

	public:
		// Конструктор с параметрами
		Car(std::uint64_t id, std::string_view model, double batteryLevel, double mileage, int passengerCapacity);

		// Деструктор (выводит сообщение для отслеживания порядка уничтожения)
		~Car() override;

		// Конструктор глубокого копирования и оператор копирующего присваивания
		Car(const Car& other);
		Car& operator=(const Car& other);

		// Конструктор и оператор перемещения
		Car(Car&&) = default;
		Car& operator=(Car&&) = default;

		// Виртуальный метод Describe()
		[[nodiscard]] std::string Describe() const override final;

		// Виртуальный метод клонирования
		[[nodiscard]] std::unique_ptr<BaseVehicle> Clone() const override;

		// Расчет стоимости техобслуживания (убери = 0 / override, если в BaseVehicle такого виртуального метода нет)
		[[nodiscard]] double CalculateServiceCost() const;

		// Геттер количества пассажирских мест
		[[nodiscard]] int GetPassengerCapacity() const;
	};
}  // namespace rental