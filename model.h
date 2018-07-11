#include <iostream>
#include <fstream>
#include <list>

using namespace std;

void ile(string plik){
    ifstream ifs;
    ofstream ofs;
    ifs.open(plik.c_str(), fstream::binary);
    plik = plik.substr(0, plik.find_last_of('.')) + ".ile";
    ofs.open(plik.c_str(), fstream::binary);
    ifs.seekg(0, fstream::end);
    ofs << ifs.tellg();
    ifs.close();
    ofs.close();
}

void check(list<pair<unsigned char, int> > &symcounts, unsigned char bchar){
    pair<unsigned char, int> para;
    for(list<pair<unsigned char, int> >::iterator I = symcounts.begin(); I != symcounts.end(); ++I){
        if(I->first == bchar){
            I->second++;
            return;
        }
    }
    para.first = bchar;
    para.second = 1;
    symcounts.push_back(para);
}

void licz(string plik, list<pair<unsigned char, int> > &symcounts){
    ifstream ifs;
    unsigned char bchar;
    ifs.open(plik.c_str(), fstream::binary);
    bchar = ifs.get();
    while(!ifs.eof()){
        check(symcounts, bchar);
        bchar = ifs.get();
    }
    ifs.close();
    ofstream ofs;
    plik = plik.substr(0, plik.find_last_of('.')) + ".licz";
    ofs.open(plik.c_str(), ofstream::out);
    for(list<pair<unsigned char, int> >::iterator I = symcounts.begin(); I != symcounts.end(); ++I){
        ofs << (int)I->first << " " << I->second << endl;
    }
    ofs.close();
}

bool comp(pair<unsigned char, int> &a, pair<unsigned char, int> &b){
    if(a.second > b.second || b.second > a.second)
        return a.second > b.second ? 1 : 0;
    return a.first > b.first ? 0 : 1;
}

void msort(string plik, list<pair<unsigned char, int> > &symcounts){
    ofstream ofs;
    plik = plik.substr(0, plik.find_last_of('.')) + ".msort";
    ofs.open(plik.c_str(), ofstream::out);
    symcounts.sort(comp);
    for(list<pair<unsigned char, int> >::iterator I = symcounts.begin(); I != symcounts.end(); ++I){
        ofs << (int)I->first << " " << I->second << endl;
    }
    ofs.close();
}

int model(string plik){
    list<pair<unsigned char, int> > symcounts;
    ile(plik);
    licz(plik, symcounts);
    msort(plik, symcounts);
    return 0;
}