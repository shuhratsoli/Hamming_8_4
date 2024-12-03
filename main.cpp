#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>
#include "Hamming_8_4.h"

std::vector<uint8_t> MakeVector(unsigned long long number) {
    std::string input = std::bitset<64>(number).to_string();
    input.erase(0, input.find_first_not_of('0'));

    std::cout << "Число " << number << " в двоичном представление: " << input << std::endl;

    std::vector<uint8_t> bytes;
    while (input.size() % 4 != 0) {
        input = "0" + input;
    }

    int index = 0;

    std::cout << "Число " << number << " была разделена на " << input.size() / 4 << " блоков из 4 битовых значений:" << std::endl;

    for (size_t i = 0; i < input.size(); i += 4) {
        std::string temp = input.substr(i, 4);
        uint8_t value = static_cast<uint8_t>(std::stoi(temp, nullptr, 2));
        std::cout << ++index << ". " << std::bitset<4>(value) << std::endl;
        bytes.push_back(value);
    }

    return bytes;
}

void ShowCommands()
{
    std::cout << "Список команд" << std::endl;
    std::cout << " 1. Составить вектор." << std::endl;
    std::cout << " 2. Кодирование." << std::endl;
    std::cout << " 3. Декодирование." << std::endl;
    std::cout << " 4. Инвертировать бит в кодированном векторе." << std::endl;
    std::cout << " 5. Ввести новое значение." << std::endl;
    std::cout << " 6. Выход." << std::endl;
}

int main() {
    setlocale(LC_ALL, "");

    unsigned long long number;
    std::cout << "Введите целое число, не превосходящее 2^64-1: ";
    std::cin >> number;
    std::vector<uint8_t> bytes, encodedBytes, decodedBytes;
    bool vectorMaked = false, encoded = false;

    ShowCommands();

    while(true) {
        int command, index = 0;
        std::cout << "Выберите команду: ";
        std::cin >> command;

        if (command == 1) {
            bytes = MakeVector(number);
            vectorMaked = true;
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 2) {
            if (vectorMaked) {
                encodedBytes = Hamming_8_4::Encode(bytes);
                std::cout << "Число " << number << " после кодирования: " << std::endl;
                for (uint8_t byte: encodedBytes) {
                    std::cout << ++index << ". " << std::bitset<8>(byte) << std::endl;
                }
                encoded = true;
                index = 0;
            }
            else {
                std::cout << "Вектор 4 битовых значений не была составлена, пожалуйста, сначала составьте вектор.";
            }
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 3) {
            if (encoded) {
                decodedBytes = Hamming_8_4::Decode(encodedBytes);
                if (decodedBytes.size() > 0) {
                    std::cout << "Двоичный результать декодирования: " << std::endl;
                    for (uint8_t byte: decodedBytes) {
                        std::cout << std::bitset<4>(byte);
                    }
                }
                else {
                    std::cout << "Данные не подлежать исправлению." << std::endl;
                }
            }
            else {
                std::cout << "Вектор 4 битовых значений не была кодирована, пожалуйста, сначала кодируйте вектор.";
            }
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 4) {
            if (encoded) {
                int itemNumber, byteNumber;
                if (encodedBytes.size() > 1){
                    std::cout << "Введите в каком элементе вектора, вы хотите инвертировать бит (целое число от 1 до " << encodedBytes.size() << "): ";
                    std::cin >> itemNumber;
                }
                itemNumber = 1;
                std::cout << "Введите в каком бите элемента, вы хотите инвертировать бит (целое число от 1 до 8): ";
                std::cin >> byteNumber;

                if (byteNumber >= 1 && byteNumber <= 8) {
                    int itemIndex = itemNumber - 1;
                    int bitPosition = byteNumber - 1;

                    encodedBytes[itemIndex] ^= (1 << bitPosition);

                    std::cout << "Бит успешно инвертирован:" << std::endl;

                    for (uint8_t byte: encodedBytes) {
                        std::cout << ++index << ". " << std::bitset<8>(byte) << std::endl;
                    }
                    index = 0;
                }
                else {
                    std::cout << "Ошибка: Номер бита должен быть от 1 до 8." << std::endl;
                }
            }
            else {
                std::cout << "Вектор 4 битовых значений не была кодирована, пожалуйста, сначала кодируйте вектор.";
            }
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 5) {
            std::cout << "Введите целое число, не превосходящее 2^64-1: ";
            std::cin >> number;
            vectorMaked = encoded = false;
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 6) {
            std::cout << "Конец работы программы..." << std::endl;
            return 0;
        }
        else {
            std::cout << "Команда под таким номером не существует." << std::endl;
            ShowCommands();
        }
    }
}
