#include "vehicle.hpp"
#include <iostream>
#include <utility>
#include <memory>

namespace rental
{
    // Основной конструктор
    BaseVehicle::BaseVehicle(std::uint64_t id, std::string_view model, double batteryLevel, double mileage)
        : m_inventoryNumber(NextInventoryNumber()) // Генерация уникального инвентарного номера
        , m_id(id)
        , m_model(model)
        , m_batteryLevel(batteryLevel)
        , m_mileage(mileage)
        , m_maintenanceCount(0) // Инициализируем счетчик записей техобслуживания
    {
        // Увеличиваем счетчик при создании каждого объекта
        ++s_totalCreatedVehicles;

        std::cout << "[" << TAG << "] Created transport #" << m_inventoryNumber
            << " (id: " << m_id << "), model: " << m_model << "\n";
    }

    // Конструктор копирования базового класса
    BaseVehicle::BaseVehicle(const BaseVehicle& other)
        : m_inventoryNumber(NextInventoryNumber()) // Новая копия получает новый инвентарный номер
        , m_id(other.m_id)
        , m_model(other.m_model)
        , m_batteryLevel(other.m_batteryLevel)
        , m_mileage(other.m_mileage)
        , m_maintenanceCount(other.m_maintenanceCount)
    {
        ++s_totalCreatedVehicles;

        // Глубокое копирование записей техобслуживания
        for (std::size_t i = 0; i < m_maintenanceCount; ++i)
        {
            if (other.m_maintenanceHistory[i])
            {
                m_maintenanceHistory[i] = std::make_unique<MaintenanceRecord>(
                    other.m_maintenanceHistory[i]->GetId(),
                    other.m_maintenanceHistory[i]->GetDescription(),
                    other.m_maintenanceHistory[i]->GetCost(),
                    other.m_maintenanceHistory[i]->GetDate()
                );
            }
        }
    }

    // Оператор копирующего присваивания базового класса
    BaseVehicle& BaseVehicle::operator=(const BaseVehicle& other)
    {
        if (this != &other)
        {
            // m_inventoryNumber оставляем собственным уникальным номером объекта
            m_id = other.m_id;
            m_model = other.m_model;
            m_batteryLevel = other.m_batteryLevel;
            m_mileage = other.m_mileage;

            // Очищаем текущую историю техобслуживания
            for (std::size_t i = 0; i < 10; ++i)
            {
                m_maintenanceHistory[i].reset();
            }

            // Копируем записи заново
            m_maintenanceCount = other.m_maintenanceCount;
            for (std::size_t i = 0; i < m_maintenanceCount; ++i)
            {
                if (other.m_maintenanceHistory[i])
                {
                    m_maintenanceHistory[i] = std::make_unique<MaintenanceRecord>(
                        other.m_maintenanceHistory[i]->GetId(),
                        other.m_maintenanceHistory[i]->GetDescription(),
                        other.m_maintenanceHistory[i]->GetCost(),
                        other.m_maintenanceHistory[i]->GetDate()
                    );
                }
            }
        }
        return *this;
    }

    // Генерация следующего инвентарного номера
    int BaseVehicle::NextInventoryNumber()
    {
        return ++m_lastNumber;
    }

    // Реализация защищенного метода Header()
    std::string BaseVehicle::Header() const
    {
        return "Transport #" + std::to_string(m_inventoryNumber) + " (" + m_model + ")";
    }

    // Реализация Describe()
    std::string BaseVehicle::Describe() const
    {
        return Header() + ", mileage: " + std::to_string(m_mileage) + " km, energy: " + std::to_string(m_batteryLevel) + "%";
    }

    // Геттеры
    int BaseVehicle::GetInventoryNumber() const
    {
        return m_inventoryNumber;
    }

    std::uint64_t BaseVehicle::GetId() const
    {
        return m_id;
    }

    std::string_view BaseVehicle::GetModel() const
    {
        return m_model;
    }

    double BaseVehicle::GetBatteryLevel() const
    {
        return m_batteryLevel;
    }

    double BaseVehicle::GetMileage() const
    {
        return m_mileage;
    }

    // Определение статического поля класса
    std::size_t BaseVehicle::s_totalCreatedVehicles = 0;

    // Реализация статического метода
    std::size_t BaseVehicle::GetTotalCreatedVehicles()
    {
        return s_totalCreatedVehicles;
    }

    // Метод добавления записи о техобслуживании
    void BaseVehicle::AddMaintenanceRecord(std::uint64_t id, std::string_view description, double cost, std::int64_t timestamp)
    {
        if (m_maintenanceCount < 10)
        {
            // Создаем одиночный unique_ptr и помещаем в фиксированный массив
            m_maintenanceHistory[m_maintenanceCount] = std::make_unique<MaintenanceRecord>(id, description, cost, timestamp);
            m_maintenanceCount++;
            std::cout << "[" << TAG << "] Added maintenance record to transport #" << m_inventoryNumber << "\n";
        }
    }

    // Проверка возможности аренды (заряд >= 20%)
    bool BaseVehicle::CanBeRented()
    {
        return m_batteryLevel >= 20.0;
    }

} // namespace rental