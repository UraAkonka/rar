#include <iostream>
#include <fstream>
#include <vector>

#include <cstdint>

using namespace std;

// ���������� 1-�������� ������������
#pragma pack(push, 1)

// ��������� ��������� ������ RAR4
struct RarHeader
{
    uint16_t crc;          // 2-�������� ����� ��� �����
    uint8_t type;          // 1-�������� ����� ��� �����
    uint16_t flags;
    uint16_t size;
};

// ��������� ��������� ������������ �����
struct FileHead
{
    uint32_t packSize;     // ������ ����������� ������
    uint32_t unpackSize;   // ������ ������������� ������
    uint16_t fileNameSize; // ����� ����� �����
    uint16_t headerSize;   // ������ ��������� ������
};

// ������������ ������������
#pragma pack(pop)

// ������� ��� ������ ���������� ������ RAR4
void readRarContents(const vector<char>& rarData)
{
    size_t offset = 7; // ������ ������ ������ ����� 7 ������ ���������

    while (offset < rarData.size())
    {
        RarHeader* header = const_cast<RarHeader*>(reinterpret_cast<const RarHeader*>(&rarData[offset]));
        offset += sizeof(RarHeader);

        if (header->type == 0x74) // ��� ������ 0x74 - ����������� ����
        {
            FileHead* fileHead = const_cast<FileHead*>(reinterpret_cast<const FileHead*>(&rarData[offset]));
            offset += sizeof(FileHead);

            // ��� ����� ���������� ����� ��������� FILE_HEAD
            char* fileName = const_cast<char*>(&rarData[offset + sizeof(FileHead)]);
            offset += fileHead->packSize;

            cout << "��� �����: " << fileName << endl;
            cout << "������ ����������� ������: " << fileHead->packSize << endl;
            cout << "������ ������������� ������: " << fileHead->unpackSize << endl;
        }
        else
        {
            offset += header->size; // ������� ������������ �������
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    // ������� ���� � �������� ������
    ifstream rarFile("D:\\rar\\Example.rar", ios::binary);

    // ���������, ��� ��������
    if (rarFile.is_open())
    {
        // ���������� ������ �����
        rarFile.seekg(0, ios::end);
        int fileSize = rarFile.tellg();
        cout << "������ �����: " << fileSize << " ����" << endl;

        // ����� ������������������ � ������ �����
        rarFile.seekg(0, ios::beg);

        // �������� ������
        vector<char> rarData(fileSize, 0);

        // ������� ������
        rarFile.read(rarData.data(), fileSize);

        // ������ ���������� ������
        readRarContents(rarData);
    }

    return 0;
}
