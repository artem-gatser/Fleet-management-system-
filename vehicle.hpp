#pragma once
#include "maintenance_record.hpp"
#include <cstdint>
#include <string>
#include <string_view>
#include <memory>

namespace rental
{

    class BaseVehicle
    {
    private:
        static constexpr auto TAG = "vehicle";
        // Статическое поле для хранения последнего выданного номера
        inline static int m_lastNumber{ 0 };
        // Поле для индивидуального инвентарного номера текущего транспорта
        int m_inventoryNumber{ 0 };
        // Статическое поле-счетчик всех созданных объектов BaseVehicle и его наследников
        static std::size_t s_totalCreatedVehicles;

    protected:
        std::uint64_t m_id{ 0 };
        std::string m_model{};
        double m_batteryLevel{ 100.0 }; // Уровень заряда или топлива в процентах
        double m_mileage{ 0.0 };        // Пробег автомобиля

        std::unique_ptr<MaintenanceRecord> m_maintenanceHistory[10];
        std::size_t m_maintenanceCount{ 0 };              // Текущее количество записей

        [[nodiscard]] std::string Header() const;

    public:
        // Статический метод для генерации следующего инвентарного номера
        [[nodiscard]] static int NextInventoryNumber();

        // Конструктор с параметрами
        BaseVehicle(std::uint64_t id, std::string_view model, double batteryLevel, double mileage);

        // Запрет на создание объектов без параметров
        BaseVehicle() = delete;

        // Конструктор копирования и оператор копирующего присваивания
        BaseVehicle(const BaseVehicle&);
        BaseVehicle& operator=(const BaseVehicle&);

        // Операции перемещения генерируются компилятором автоматически (благодаря unique_ptr)
        BaseVehicle(BaseVehicle&&) = default;
        BaseVehicle& operator=(BaseVehicle&&) = default;

        virtual ~BaseVehicle() = default;

        [[nodiscard]] virtual std::unique_ptr<BaseVehicle> Clone() const = 0;

        // Виртуальный метод описания транспорта (по умолчанию реализуется в базе)
        [[nodiscard]] virtual std::string Describe() const;

        // Геттеры
        [[nodiscard]] int GetInventoryNumber() const;
        [[nodiscard]] std::uint64_t GetId() const;
        [[nodiscard]] std::string_view GetModel() const;
        [[nodiscard]] double GetBatteryLevel() const;
        [[nodiscard]] double GetMileage() const;

        // Статический метод возвращает общее количество созданных объектов транспорта
        [[nodiscard]] static std::size_t GetTotalCreatedVehicles();

        // Метод добавления записи о техобслуживании (реализация композиции)
        void AddMaintenanceRecord(std::uint64_t id, std::string_view description, double cost, std::int64_t timestamp);

        // Метод проверки: можно ли арендовать машину (заряд >= 20%)
        [[nodiscard]] bool CanBeRented();
    };

} // namespace rental