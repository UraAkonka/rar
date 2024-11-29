#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

using namespace std;

#pragma pack(push, 1)

struct VolumeHeaderFormat {
    uint8_t signature;
    uint8_t header_crc;
    uint8_t header_type;
    uint8_t header_flags;
    uint8_t header_size;
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

void rar(const string &filename){
    ifstream rar_file("Example.rar");
    if (rar_file.is_open()){
        cout << "Неудалось открыть файл" << endl;
    }
    else{
        vector<char> signature(7);
        rar_file.read(signature.data(),7);
        string signature_str(signature.data());
        if (signature_str == "Rar!"){
            cout << "Reading rar" << endl;
        }

    }
}



int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
