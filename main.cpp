#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <cstdint>

using namespace std;

#pragma pack(push, 1)

struct header {
    uint16_t header_crc;
    uint8_t header_type;
    uint16_t header_flags;
    uint16_t header_size;
    char padding[8]; // Пропуск 8 байтов
};



struct filehead {
    uint8_t PackSize;
    uint8_t UnpSize;
    uint8_t HostOS;
    uint8_t FileCRC;
    uint8_t FileTime;
    uint8_t UnpVer;
    uint8_t Method;
    uint8_t NameSize;
    uint8_t FileAttr;
    uint16_t FileName;
    uint32_t PackedData;
};

#pragma pack(pop)

void rar(){
    ifstream rar_file("C:\\1111\\Example.rar");
    if (!rar_file.is_open()){
        cout << "Неудалось открыть файл" << endl;
    }
    else{
        rar_file.seekg(0,ios::end);
        int size = rar_file.tellg();
        cout << size << endl;

        vector<char> rar_data(size, 0);

        rar_file.read(rar_data.data(), size);

        header *p_header = reinterpret_cast<header*> (&rar_data[7]);

        cout << int(p_header->header_size) << endl;
        cout << int(p_header->header_type) << endl;


        rar_file.seekg(0,ios::beg);
        char c;
        rar_file.get(c);
        cout << int(c);

    }

}



int main()
{
    setlocale(LC_ALL,"Russian");
    rar();
    return 0;
}
