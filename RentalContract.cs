using System;

namespace Rental
{
    public enum ContractState
    {
        Active,
        Completed
    }

    public class RentalContract
    {
        private const string Tag = "rental_contract";

        public ulong ContractId { get; }
        public string ClientName { get; }
        public uint DriverExperienceYears { get; }
        public uint RentalDays { get; }
        public double DailyRate { get; }
        public double TotalCost => RentalDays * DailyRate;
        public ContractState State { get; private set; } = ContractState.Active;

        // Агрегация: ссылка на внешний объект BaseVehicle
        private readonly BaseVehicle _targetVehicle;

        public RentalContract(ulong id, string clientName, uint driverExperience, BaseVehicle vehicle, uint days, double dailyRate)
        {
            ContractId = id;
            ClientName = clientName;
            DriverExperienceYears = driverExperience;
            // Если параметр vehicle оказался null, выбрасываем исключение
            _targetVehicle = vehicle ?? throw new ArgumentNullException(nameof(vehicle));
            RentalDays = days;
            DailyRate = dailyRate;

            Console.WriteLine($"[{Tag}] Создан договор id: {ContractId} для клиента: {ClientName}");
        }

        public bool ProcessIssue()
        {
            if (DriverExperienceYears < 3)
            {
                Console.WriteLine($"[{Tag}] Отказ в аренде по договору id: {ContractId} (стаж водителя {DriverExperienceYears} лет, требуется минимум 3 года)");
                return false;
            }

            if (!_targetVehicle.CanBeRented())
            {
                Console.WriteLine($"[{Tag}] Отказ в аренде: транспорт не готов к выдаче.");
                return false;
            }

            State = ContractState.Active;
            Console.WriteLine($"[{Tag}] Договор id: {ContractId} успешно оформлен и активен!");
            return true;
        }

        public void CompleteContract()
        {
            State = ContractState.Completed;
            Console.WriteLine($"[{Tag}] Договор id: {ContractId} завершен.");
        }

        public override string ToString()
        {
            return $"Договор #{ContractId} | Клиент: {ClientName} (Стаж: {DriverExperienceYears} лет) | Авто: {_targetVehicle.Model} | Срок: {RentalDays} дн.";
        }
    }
}