/**
 * @mainpage Документация по проекту Hotel
 *
 * <img src="logo.jpg" alt="Логотип отеля" width="200" height="200">
 *
 * # Описание
 * Программа моделирует гостиницу с тремя номерами (включая один люксовый) и рассчитывает привлекательность номеров и общий доход.
 *
 * ## Диаграмма классов
 * \dot
 * digraph G {
 *   node [fontname="Arial", fontsize=12, shape=box, style="rounded,filled"];
 *   edge [fontname="Arial", fontsize=10];

 *   Hotel [fillcolor="#E6E6FA"];
 *   Room [fillcolor="#E0FFFF"];
 *   LuxuryRoom [fillcolor="#FFF0F5"];

 *   Hotel -> Room [label="содержит 2", headlabel="2", arrowhead="diamond"];
 *   Hotel -> LuxuryRoom [label="содержит 1", headlabel="1", arrowhead="diamond"];
 *   LuxuryRoom -> Room [arrowhead="empty", label="наследует"];

 *   Room -> "Init(a: int, cost: float)" [arrowhead="none", dir=none];
 *   Room -> "Read()" [arrowhead="none", dir=none];
 *   Room -> "Display()" [arrowhead="none", dir=none];
 *   Room -> "Appeal(): float" [arrowhead="none", dir=none];
 *   Room -> "GetCostPerDay(): float" [arrowhead="none", dir=none];

 *   LuxuryRoom -> "Init(a: int, cost: float, breakfast: bool)" [arrowhead="none", dir=none];
 *   LuxuryRoom -> "Read()" [arrowhead="none", dir=none];
 *   LuxuryRoom -> "Display()" [arrowhead="none", dir=none];
 *   LuxuryRoom -> "Appeal(): float" [arrowhead="none", dir=none];

 *   Hotel -> "Init(...)" [arrowhead="none", dir=none];
 *   Hotel -> "Read()" [arrowhead="none", dir=none];
 *   Hotel -> "Display()" [arrowhead="none", dir=none];
 *   Hotel -> "TotalIncome(): float" [arrowhead="none", dir=none];
 *   Hotel -> "MostAppealingRoom(): Room*" [arrowhead="none", dir=none];
 * }
 * \enddot
 * * # Классы
 * - Room — номер
 * - LuxuryRoom — номер
 * - Hotel — гостиница
 */

#include <iostream>
#include <windows.h>
#include <cstring>

 /// @class Room
 /// @brief Класс для представления обычного номера
class Room {
private:
    int area;              ///< Площадь номера
    float costPerDay;      ///< Стоимость проживания за сутки
public:
    /// @brief Инициализация номера
    /// @param a Площадь
    /// @param cost Стоимость за сутки
    void Init(int a, float cost);

    /// @brief Ввод параметров номера с клавиатуры
    void Read();

    /// @brief Отображение параметров номера
    void Display();

    /// @brief Вычисление привлекательности (чем меньше, тем лучше)
    /// @details Привлекательность рассчитывается по формуле:
    /// \f[ Appeal = \frac{CostPerDay}{Area} \f]
    /// где:
    /// - CostPerDay — стоимость проживания за сутки
    /// - Area — площадь номера
    /// @return Стоимость за квадратный метр
    float Appeal();

    /// @brief Получение стоимости за сутки
    /// @return Стоимость
    float GetCostPerDay();
};

float Room::GetCostPerDay() {
    return costPerDay;
}

void Room::Init(int a, float cost) {
    area = a;
    costPerDay = cost;
}

void Room::Read() {
    std::cout << "Введите площадь номера: ";
    std::cin >> area;
    std::cout << "Введите стоимость проживания за сутки: ";
    std::cin >> costPerDay;
}

void Room::Display() {
    std::cout << "Площадь номера: " << area << " кв.м, Стоимость за сутки: " << costPerDay << " руб\n";
}

float Room::Appeal() {
    return costPerDay / area;
}

/// @class LuxuryRoom
/// @brief Класс для люксового номера, наследуется от Room
class LuxuryRoom : public Room {
private:
    bool breakfastIncluded;  ///< Признак включённого завтрака
public:
    /// @brief Инициализация люксового номера
    /// @param a Площадь
    /// @param cost Стоимость
    /// @param breakfast Включен ли завтрак
    void Init(int a, float cost, bool breakfast);

    /// @brief Ввод люксового номера с клавиатуры
    void Read();

    /// @brief Отображение информации о номере
    void Display();

    /// @brief Вычисление привлекательности с учётом завтрака
    /// @return Стоимость за квадратный метр (уменьшается при наличии завтрака)
    float Appeal();
};

void LuxuryRoom::Init(int a, float cost, bool breakfast) {
    Room::Init(a, cost);
    breakfastIncluded = breakfast;
}

void LuxuryRoom::Read() {
    Room::Read();
    std::cout << "Включён ли завтрак (1 - да, 0 - нет): ";
    std::cin >> breakfastIncluded;
}

void LuxuryRoom::Display() {
    Room::Display();
    std::cout << "Завтрак включён: " << (breakfastIncluded ? "Да" : "Нет") << "\n";
}

float LuxuryRoom::Appeal() {
    float baseAppeal = Room::Appeal();
    return breakfastIncluded ? baseAppeal * 1.2f : baseAppeal;
}

/// @class Hotel
/// @brief Класс, представляющий гостиницу с номерами
class Hotel {
private:
    Room room1, room2;            ///< Обычные номера
    LuxuryRoom luxuryRoom;        ///< Люксовый номер
    int seasonDuration;           ///< Длительность туристического сезона
    char name[50];                ///< Название гостиницы
public:
    /// @brief Инициализация отеля
    void Init(char* hotelName, int duration, Room r1, Room r2, LuxuryRoom lr);

    /// @brief Ввод параметров отеля
    void Read();

    /// @brief Вывод информации об отеле
    void Display();

    /// @brief Расчёт общего дохода отеля за сезон
    /// @return Общий доход
    float TotalIncome();

    /// @brief Поиск самого привлекательного номера
    /// @return Указатель на самый привлекательный номер
    Room* MostAppealingRoom();
};

void Hotel::Init(char* hotelName, int duration, Room r1, Room r2, LuxuryRoom lr) {
    strncpy_s(name, hotelName, 50);
    seasonDuration = duration;
    room1 = r1;
    room2 = r2;
    luxuryRoom = lr;
}

void Hotel::Read() {
    std::cout << "Введите название гостиницы: ";
    std::cin.ignore();
    std::cin.getline(name, 50);

    std::cout << "Введите длительность туристического сезона (в днях): ";
    std::cin >> seasonDuration;

    std::cout << "Номер 1:\n";
    room1.Read();
    std::cout << "Номер 2:\n";
    room2.Read();
    std::cout << "Люкс-номер:\n";
    luxuryRoom.Read();
}

void Hotel::Display() {
    std::cout << "Гостиница: " << name << "\n";
    std::cout << "Длительность сезона: " << seasonDuration << " дней\n";
    std::cout << "Номер 1:\n";
    room1.Display();
    std::cout << "Номер 2:\n";
    room2.Display();
    std::cout << "Люкс-номер:\n";
    luxuryRoom.Display();
}

float Hotel::TotalIncome() {
    return (room1.GetCostPerDay() + room2.GetCostPerDay() + luxuryRoom.GetCostPerDay()) * seasonDuration;
}

Room* Hotel::MostAppealingRoom() {
    Room* bestRoom = &room1;
    if (room2.Appeal() < bestRoom->Appeal()) bestRoom = &room2;
    if (luxuryRoom.Appeal() < bestRoom->Appeal()) bestRoom = &luxuryRoom;
    return bestRoom;
}

/// @brief Главная функция программы
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Hotel hotel;
    hotel.Read();
    hotel.Display();

    std::cout << "Общий ожидаемый доход за сезон: " << hotel.TotalIncome() << " руб\n";

    Room* bestRoom = hotel.MostAppealingRoom();
    std::cout << "Самый привлекательный номер:\n";
    bestRoom->Display();

    return 0;
}
