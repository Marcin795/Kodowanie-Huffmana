#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void loadTree(string plik,  map<int, pair<int, int> > &tree, int &root) {
    ifstream ifs;
    ifs.open(plik.c_str(), fstream::in);
    int tmp;
    while(ifs >> tmp) {
        ifs >> tree[tmp].first;
        ifs >> tree[tmp].second;
        if(tmp < root) {
            root = tmp;
        }
    }
    ifs.close();
}

void dhuff(string codefile, string plik) {
    ofstream ofs;
    ifstream ifs;
    map<int, pair<int, int> > tree;
    int root = 0, i, current, buffer, valid;
    unsigned char tmp;
    loadTree(codefile, tree, root);
    current = root;
    ifs.open(plik.c_str(), fstream::binary);
    plik = plik.substr(0, plik.find_last_of('.')) + ".dhuff";
    ofs.open(plik.c_str(), fstream::binary);
    valid = ifs.get();
    buffer = ifs.get();
    buffer = buffer << 8;
    tmp = ifs.get();
    buffer += tmp;
    while(!ifs.eof()) {
        for(i = 0; i < 8; i++) {
            if (buffer & 0x8000) {
                current = tree[current].second;
                if(current >= 0){
                    tmp = current;
                    ofs << tmp;
                    current = root;
                }
            } else {
                current = tree[current].first;
                if(current >= 0){
                    tmp = current;
                    ofs << tmp;
                    current = root;
                }
            }
            buffer = buffer << 1;
        }
        tmp = ifs.get();
        buffer += tmp;
    }
    for(i = 0; i < valid; i++) {
        if (buffer & 0x8000) {
            current = tree[current].second;
            if(current >= 0){
                tmp = current;
                ofs << tmp;
                current = root;
            }
        } else {
            current = tree[current].first;
            if(current >= 0){
                tmp = current;
                ofs << tmp;
                current = root;
            }
        }
        buffer = buffer << 1;
    }
    ifs.close();
    ofs.close();
}

int dekompresja(string plikTree , string plik) {
    dhuff(plikTree, plik);
    return 0;
}