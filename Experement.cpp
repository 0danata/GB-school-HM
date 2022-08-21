
#include <iostream>
#include <tuple>
#include <optional>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


//1. Создайте структуру Person с 3 полями: фамилия, имя, отчество.Поле отчество должно быть опционального типа,
//т.к.не у всех людей есть отчество.
//Перегрузите оператор вывода данных для этой структуры.Также перегрузите операторы < и == (используйте std::tie).

struct Person {
    std::string name, surname;
    std::optional<std::string> patronymic = std::nullopt;

    Person() = default;
};
bool operator<(const Person& p1, const Person& p2)
{
    if(p1.patronymic.has_value())
        return std::tie(p1.name,p1.surname, p1.patronymic) < std::tie(p2.name, p2.surname, p2.patronymic);
    else
        return std::tie(p1.name, p1.surname) < std::tie(p2.name, p2.surname);
}

std::ostream& operator<<(std::ostream& out, const Person& pers)
{
        out << pers.name<< "  " << pers.surname<< "  " << pers.patronymic.value_or("");
    return out;
}

bool operator==(const Person& p1, const Person& p2)
{
    if (p1.patronymic.has_value())
        return std::tie(p1.name,p1.surname,p1.patronymic) == std::tie(p2.name, p2.surname, p2.patronymic);
    else
        return std::tie(p1.name, p1.surname) == std::tie(p2.name, p2.surname);
}

//2. Создайте структуру PhoneNumber с 4 полями:
//· код страны(целое число)
//· код города(целое число)
//· номер(строка)
//· добавочный номер(целое число, опциональный тип)
//Также перегрузите операторы < и == (используйте std::tie)
struct PhoneNumber {
    size_t country_num;
    size_t city_num;
    std::string number;
    std::optional<size_t> add_num = std::nullopt;

    PhoneNumber() = default;
};

bool operator < (const PhoneNumber& pn1, const PhoneNumber& pn2) {
    if (pn1.add_num.has_value())
        return std::tie(pn1.country_num, pn1.city_num, pn1.number, pn1.add_num)
        < std::tie(pn2.country_num, pn2.city_num, pn2.number, pn2.add_num);
    else
        return std::tie(pn1.country_num, pn1.city_num, pn1.number) < std::tie(pn2.country_num, pn2.city_num, pn2.number);
}

bool operator == (const PhoneNumber& pn1,const PhoneNumber& pn2) {
    if (pn1.add_num.has_value())
        return std::tie(pn1.country_num, pn1.city_num, pn1.number, pn1.add_num)
        == std::tie(pn2.country_num, pn2.city_num, pn2.number, pn2.add_num);
    else
        return std::tie(pn1.country_num, pn1.city_num, pn1.number)
        == std::tie(pn2.country_num, pn2.city_num, pn2.number);
 }

 std::ostream& operator << (std::ostream& out, PhoneNumber& Pn) {
     out << "+" << Pn.country_num << "(" << Pn.city_num << ")" << Pn.number << " " << Pn.add_num.value_or("");
     return out;
}

//3. Создайте класс PhoneBook, который будет в контейнере хранить пары : Человек – Номер телефона.
//Конструктор этого класса должен принимать параметр типа ifstream – поток данных, полученных из файла.
//В теле конструктора происходит считывание данных из файла и заполнение контейнера.
//Класс PhoneBook должен содержать перегруженный оператор вывода, для вывода всех данных из контейнера в консоль.

class PhoneBook {
protected:
    std::vector<std::pair<Person,PhoneNumber>> val;  
public:
    PhoneBook() = default;
    PhoneBook(std::ifstream& file) {
        Person pers;
        PhoneNumber pn;
        while (!file.eof()) {
             std::string count;
             std::getline(file, count);
             std::stringstream str;
             str << count;
            
             std::pair<Person, PhoneNumber> entry;

             for (int i = 0; str; ++i)
             {
                 switch (i)
                 {
                 case 0:
                     str >> entry.first.name;
                     break;
                 case 1:
                     str >> entry.first.surname;
                     break;
                 case 2:
                     str >> count;
                     entry.first.patronymic = count;
                     break;
                 case 3:
                     str >> entry.second.country_num;
                     break;
                 case 4:
                     str >> entry.second.city_num;
                     break;
                 case 5:
                     str >> entry.second.number;
                     break;
                 case 6:
                     int num;
                     str >> num;
                     entry.second.add_num = num;
                     break;
                 }
             }
             val.push_back(entry);
        }
        file.close();
    }




};
std::ostream& operator <<(std::ostream& out, const PhoneBook &val)
{

    for (const auto& [person, number] : val)
    {
        out << person << " " << number << std::endl;
    }
    return out;
}

int main()
{
    // путь к файлу PhoneBook.txt PhoneBook book(file)
    std::ifstream file("ХХХ"); 
    PhoneBook book;
    std::cout << book;
    //std::cout << "------SortByPhone-------" << std::endl;
    //book.SortByPhone();
    //std::cout << book;
    //std::cout << "------SortByName--------" << std::endl;
    //book.SortByName();
    //std::cout << book;
    //std::cout << "-----GetPhoneNumber-----" << std::endl;
    //// лямбда функция, которая принимает фамилию и выводит номер телефона
    ////человека, либо строку с ошибкой
    //    auto print_phone_number = [&book](const std::string& surname) {
    //        std::cout << surname << "\t";
    //    auto answer = book.GetPhoneNumber(surname);
    //    if (std::get<0>(answer).empty())
    //        std::cout << std::get<1>(answer);
    //    else
    //        std::cout << std::get<0>(answer);
    //    std::cout << std::endl;
    //};
    //// вызовы лямбды
    //print_phone_number("Ivanov");
    //print_phone_number("Petrov");
    //std::cout << "----ChangePhoneNumber----" << std::endl;
    //book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" },
    //    PhoneNumber{ 7, 123, "15344458", nullopt });
    //book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" },
    //    PhoneNumber{ 16, 465, "9155448", 13 });
    //std::cout << book;
    //
    //std::vector<std::pair<std::string, int>> pho;
    //pho = { {"Pushkin", 1799}, {"Lermontov", 1814}, {"Zhukovsky", 1783} };
    return 0;
}

