#include <iostream>
#include <cstdlib>
#include <fstream>
#include <list>
#include <map>

using namespace std;

void loadcode(string plik, map<int, string> &code){
    ifstream ifs;
    int sym;
    ifs.open(plik.c_str(), fstream::in);
    while(ifs >> sym){
        ifs >> code[sym];
    }
    ifs.close();
}

void huff(string codefile, string plik){
    ifstream ifs;
    ofstream ofs;
    map<int, string> codemap;
    string code = "";
    unsigned char sym;
    loadcode(codefile, codemap);
    ifs.open(plik.c_str(), fstream::binary);
    plik = plik.substr(0, plik.find_last_of('.')) + ".huff";
    ofs.open(plik.c_str(), fstream::binary);
    ofs << 0;
    for(sym = ifs.get(); !ifs.eof(); sym = ifs.get()){
        code += codemap[sym];
        if(code.length() >= 8){
            ofs << (unsigned char)strtol(code.substr(0, 8).c_str(), NULL, 2);
            code.erase(0, 8);
        }
    }
    if(code.length() > 0){
        ofs << (unsigned char)(strtol(code.substr(0, 8).c_str(), NULL, 2) << (8-code.length()));
        ofs.seekp(0);
        ofs << (unsigned char)code.length();
    } else {
        ofs.seekp(0);
        ofs << (unsigned char)8;
    }
    ifs.close();
    ofs.close();
}

int kompresja(string plikCode, string plik){
    huff(plikCode, plik);
    return 0;
}
