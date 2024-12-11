#include <iostream>
#include <fstream>
#include <vector>

#include <cstdint>

using namespace std;

// Установить 1-байтовое выравнивание
#pragma pack(push, 1)

// Структура заголовка архива RAR4
struct RarHeader
{
    uint16_t crc;          // 2-байтовое целое без знака
    uint8_t type;          // 1-байтовое целое без знака
    uint16_t flags;
    uint16_t size;
};

// Структура заголовка упакованного файла
struct FileHead
{
    uint32_t packSize;     // Размер упакованных данных
    uint32_t unpackSize;   // Размер распакованных данных
    uint16_t fileNameSize; // Длина имени файла
    uint16_t headerSize;   // Размер заголовка записи
};

// Восстановить выравнивание
#pragma pack(pop)

// Функция для чтения оглавления архива RAR4
void readRarContents(const vector<char>& rarData)
{
    size_t offset = 7; // Начало первой записи после 7 байтов заголовка

    while (offset < rarData.size())
    {
        RarHeader* header = const_cast<RarHeader*>(reinterpret_cast<const RarHeader*>(&rarData[offset]));
        offset += sizeof(RarHeader);

        if (header->type == 0x74) // Тип записи 0x74 - упакованный файл
        {
            FileHead* fileHead = const_cast<FileHead*>(reinterpret_cast<const FileHead*>(&rarData[offset]));
            offset += sizeof(FileHead);

            // Имя файла начинается после заголовка FILE_HEAD
            char* fileName = const_cast<char*>(&rarData[offset + sizeof(FileHead)]);
            offset += fileHead->packSize;

            cout << "Имя файла: " << fileName << endl;
            cout << "Размер упакованных данных: " << fileHead->packSize << endl;
            cout << "Размер распакованных данных: " << fileHead->unpackSize << endl;
        }
        else
        {
            offset += header->size; // Пропуск неинтересных записей
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    // Открыть файл в двоичном режиме
    ifstream rarFile("D:\\rar\\Example.rar", ios::binary);

    // Убедиться, что открылся
    if (rarFile.is_open())
    {
        // Определить размер файла
        rarFile.seekg(0, ios::end);
        int fileSize = rarFile.tellg();
        cout << "Размер файла: " << fileSize << " байт" << endl;

        // Снова спозиционироваться в начало файла
        rarFile.seekg(0, ios::beg);

        // Выделить память
        vector<char> rarData(fileSize, 0);

        // Считать данные
        rarFile.read(rarData.data(), fileSize);

        // Чтение оглавления архива
        readRarContents(rarData);
    }

    return 0;
}
