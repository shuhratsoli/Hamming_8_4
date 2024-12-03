#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>
#include "Hamming_8_4.h"

std::vector<uint8_t> MakeVector(unsigned long long number) {
    std::string input = std::bitset<64>(number).to_string();
    input.erase(0, input.find_first_not_of('0'));

    std::cout << "����� " << number << " � �������� �������������: " << input << std::endl;

    std::vector<uint8_t> bytes;
    while (input.size() % 4 != 0) {
        input = "0" + input;
    }

    int index = 0;

    std::cout << "����� " << number << " ���� ��������� �� " << input.size() / 4 << " ������ �� 4 ������� ��������:" << std::endl;

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
    std::cout << "������ ������" << std::endl;
    std::cout << " 1. ��������� ������." << std::endl;
    std::cout << " 2. �����������." << std::endl;
    std::cout << " 3. �������������." << std::endl;
    std::cout << " 4. ������������� ��� � ������������ �������." << std::endl;
    std::cout << " 5. ������ ����� ��������." << std::endl;
    std::cout << " 6. �����." << std::endl;
}

int main() {
    setlocale(LC_ALL, "");

    unsigned long long number;
    std::cout << "������� ����� �����, �� ������������� 2^64-1: ";
    std::cin >> number;
    std::vector<uint8_t> bytes, encodedBytes, decodedBytes;
    bool vectorMaked = false, encoded = false;

    ShowCommands();

    while(true) {
        int command, index = 0;
        std::cout << "�������� �������: ";
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
                std::cout << "����� " << number << " ����� �����������: " << std::endl;
                for (uint8_t byte: encodedBytes) {
                    std::cout << ++index << ". " << std::bitset<8>(byte) << std::endl;
                }
                encoded = true;
                index = 0;
            }
            else {
                std::cout << "������ 4 ������� �������� �� ���� ����������, ����������, ������� ��������� ������.";
            }
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 3) {
            if (encoded) {
                decodedBytes = Hamming_8_4::Decode(encodedBytes);
                if (decodedBytes.size() > 0) {
                    std::cout << "�������� ���������� �������������: " << std::endl;
                    for (uint8_t byte: decodedBytes) {
                        std::cout << std::bitset<4>(byte);
                    }
                }
                else {
                    std::cout << "������ �� ��������� �����������." << std::endl;
                }
            }
            else {
                std::cout << "������ 4 ������� �������� �� ���� ����������, ����������, ������� ��������� ������.";
            }
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 4) {
            if (encoded) {
                int itemNumber, byteNumber;
                if (encodedBytes.size() > 1){
                    std::cout << "������� � ����� �������� �������, �� ������ ������������� ��� (����� ����� �� 1 �� " << encodedBytes.size() << "): ";
                    std::cin >> itemNumber;
                }
                itemNumber = 1;
                std::cout << "������� � ����� ���� ��������, �� ������ ������������� ��� (����� ����� �� 1 �� 8): ";
                std::cin >> byteNumber;

                if (byteNumber >= 1 && byteNumber <= 8) {
                    int itemIndex = itemNumber - 1;
                    int bitPosition = byteNumber - 1;

                    encodedBytes[itemIndex] ^= (1 << bitPosition);

                    std::cout << "��� ������� ������������:" << std::endl;

                    for (uint8_t byte: encodedBytes) {
                        std::cout << ++index << ". " << std::bitset<8>(byte) << std::endl;
                    }
                    index = 0;
                }
                else {
                    std::cout << "������: ����� ���� ������ ���� �� 1 �� 8." << std::endl;
                }
            }
            else {
                std::cout << "������ 4 ������� �������� �� ���� ����������, ����������, ������� ��������� ������.";
            }
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 5) {
            std::cout << "������� ����� �����, �� ������������� 2^64-1: ";
            std::cin >> number;
            vectorMaked = encoded = false;
            std::cout << std::endl;
            ShowCommands();
        }
        else if (command == 6) {
            std::cout << "����� ������ ���������..." << std::endl;
            return 0;
        }
        else {
            std::cout << "������� ��� ����� ������� �� ����������." << std::endl;
            ShowCommands();
        }
    }
}
