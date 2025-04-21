/**
 * @mainpage ������������ �� ������� Hotel
 *
 * <img src="logo.jpg" alt="������� �����" width="200" height="200">
 *
 * # ��������
 * ��������� ���������� ��������� � ����� �������� (������� ���� ��������) � ������������ ����������������� ������� � ����� �����.
 *
 * ## ��������� �������
 * \dot
 * digraph G {
 *   node [fontname="Arial", fontsize=12, shape=box, style="rounded,filled"];
 *   edge [fontname="Arial", fontsize=10];

 *   Hotel [fillcolor="#E6E6FA"];
 *   Room [fillcolor="#E0FFFF"];
 *   LuxuryRoom [fillcolor="#FFF0F5"];

 *   Hotel -> Room [label="�������� 2", headlabel="2", arrowhead="diamond"];
 *   Hotel -> LuxuryRoom [label="�������� 1", headlabel="1", arrowhead="diamond"];
 *   LuxuryRoom -> Room [arrowhead="empty", label="���������"];

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
 * * # ������
 * - Room � �����
 * - LuxuryRoom � �����
 * - Hotel � ���������
 */

#include <iostream>
#include <windows.h>
#include <cstring>

 /// @class Room
 /// @brief ����� ��� ������������� �������� ������
class Room {
private:
    int area;              ///< ������� ������
    float costPerDay;      ///< ��������� ���������� �� �����
public:
    /// @brief ������������� ������
    /// @param a �������
    /// @param cost ��������� �� �����
    void Init(int a, float cost);

    /// @brief ���� ���������� ������ � ����������
    void Read();

    /// @brief ����������� ���������� ������
    void Display();

    /// @brief ���������� ����������������� (��� ������, ��� �����)
    /// @details ����������������� �������������� �� �������:
    /// \f[ Appeal = \frac{CostPerDay}{Area} \f]
    /// ���:
    /// - CostPerDay � ��������� ���������� �� �����
    /// - Area � ������� ������
    /// @return ��������� �� ���������� ����
    float Appeal();

    /// @brief ��������� ��������� �� �����
    /// @return ���������
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
    std::cout << "������� ������� ������: ";
    std::cin >> area;
    std::cout << "������� ��������� ���������� �� �����: ";
    std::cin >> costPerDay;
}

void Room::Display() {
    std::cout << "������� ������: " << area << " ��.�, ��������� �� �����: " << costPerDay << " ���\n";
}

float Room::Appeal() {
    return costPerDay / area;
}

/// @class LuxuryRoom
/// @brief ����� ��� ��������� ������, ����������� �� Room
class LuxuryRoom : public Room {
private:
    bool breakfastIncluded;  ///< ������� ����������� ��������
public:
    /// @brief ������������� ��������� ������
    /// @param a �������
    /// @param cost ���������
    /// @param breakfast ������� �� �������
    void Init(int a, float cost, bool breakfast);

    /// @brief ���� ��������� ������ � ����������
    void Read();

    /// @brief ����������� ���������� � ������
    void Display();

    /// @brief ���������� ����������������� � ������ ��������
    /// @return ��������� �� ���������� ���� (����������� ��� ������� ��������)
    float Appeal();
};

void LuxuryRoom::Init(int a, float cost, bool breakfast) {
    Room::Init(a, cost);
    breakfastIncluded = breakfast;
}

void LuxuryRoom::Read() {
    Room::Read();
    std::cout << "������� �� ������� (1 - ��, 0 - ���): ";
    std::cin >> breakfastIncluded;
}

void LuxuryRoom::Display() {
    Room::Display();
    std::cout << "������� �������: " << (breakfastIncluded ? "��" : "���") << "\n";
}

float LuxuryRoom::Appeal() {
    float baseAppeal = Room::Appeal();
    return breakfastIncluded ? baseAppeal * 1.2f : baseAppeal;
}

/// @class Hotel
/// @brief �����, �������������� ��������� � ��������
class Hotel {
private:
    Room room1, room2;            ///< ������� ������
    LuxuryRoom luxuryRoom;        ///< �������� �����
    int seasonDuration;           ///< ������������ �������������� ������
    char name[50];                ///< �������� ���������
public:
    /// @brief ������������� �����
    void Init(char* hotelName, int duration, Room r1, Room r2, LuxuryRoom lr);

    /// @brief ���� ���������� �����
    void Read();

    /// @brief ����� ���������� �� �����
    void Display();

    /// @brief ������ ������ ������ ����� �� �����
    /// @return ����� �����
    float TotalIncome();

    /// @brief ����� ������ ���������������� ������
    /// @return ��������� �� ����� ��������������� �����
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
    std::cout << "������� �������� ���������: ";
    std::cin.ignore();
    std::cin.getline(name, 50);

    std::cout << "������� ������������ �������������� ������ (� ����): ";
    std::cin >> seasonDuration;

    std::cout << "����� 1:\n";
    room1.Read();
    std::cout << "����� 2:\n";
    room2.Read();
    std::cout << "����-�����:\n";
    luxuryRoom.Read();
}

void Hotel::Display() {
    std::cout << "���������: " << name << "\n";
    std::cout << "������������ ������: " << seasonDuration << " ����\n";
    std::cout << "����� 1:\n";
    room1.Display();
    std::cout << "����� 2:\n";
    room2.Display();
    std::cout << "����-�����:\n";
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

/// @brief ������� ������� ���������
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Hotel hotel;
    hotel.Read();
    hotel.Display();

    std::cout << "����� ��������� ����� �� �����: " << hotel.TotalIncome() << " ���\n";

    Room* bestRoom = hotel.MostAppealingRoom();
    std::cout << "����� ��������������� �����:\n";
    bestRoom->Display();

    return 0;
}
