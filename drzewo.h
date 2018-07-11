#include <iostream>
#include <cstdlib>
#include <fstream>
#include <list>
#include <map>

using namespace std;

void load(string plik, list<pair<int, int> > &symcounts){
    ifstream ifs;
    pair<int, int> para;    //symbol    ilosc
    ifs.open(plik.c_str(), fstream::in);
    while(ifs >> para.first){
        ifs >> para.second;
        symcounts.push_back(para);
    }
    ifs.close();
}

bool codecomp(pair<int, pair<int, string> > &a, pair<int, pair<int, string> > &b){
    if(a.second.first > b.second.first || b.second.first > a.second.first)
        return a.second.first > b.second.first;
    return a.first <= b.first;
}

void codinggen(map<int, pair<int, pair<int, int> > > &tree, list<pair<int, pair<int, string> > > &codetab, int pos, string code){
    pair<int, pair<int, string> > para;
    if(pos < 0){
        codinggen(tree, codetab, tree[pos].second.first, code + '0');
        codinggen(tree, codetab, tree[pos].second.second, code + '1');
    }
    para.first = pos;
    para.second.first = tree[pos].first;
    para.second.second = code;
    codetab.push_back(para);
}

void codegen(map<int, pair<int, pair<int, int> > > &tree, list<pair<int, pair<int, string> > > &codetab, int pos, string code){
    pair<int, pair<int, string> > para;
    if(pos < 0){
        codegen(tree, codetab, tree[pos].second.first, code + '0');
        codegen(tree, codetab, tree[pos].second.second, code + '1');
    } else {
        para.first = pos;
        para.second.first = tree[pos].first;
        para.second.second = code;
        codetab.push_back(para);
    }
}

void coding(string plik, map<int, pair<int, pair<int, int> > > &tree, int i){
    ofstream ofs;
    plik = plik.substr(0, plik.find_last_of('.')) + ".coding";
    pair<int, pair<int, string> >para;
    list<pair<int, pair<int, string> > > codetab;
    codinggen(tree, codetab, i, "");
    codetab.sort(codecomp);
    ofs.open(plik.c_str(), fstream::out);
    for(list<pair<int, pair<int, string> > >::iterator I = codetab.begin(); I != codetab.end(); ++I){
        ofs << I->first << " " << I->second.second << endl;
    }
    ofs.close();
}


void code(string plik, map<int, pair<int, pair<int, int> > > &tree, int i){
    ofstream ofs;
    plik = plik.substr(0, plik.find_last_of('.')) + ".code";
    pair<int, pair<int, string> >para;
    list<pair<int, pair<int, string> > > codetab;
    codegen(tree, codetab, i, "");
    codetab.sort(codecomp);
    ofs.open(plik.c_str(), fstream::out);
    for(list<pair<int, pair<int, string> > >::iterator I = codetab.begin(); I != codetab.end(); ++I){
        ofs << I->first << " " << I->second.second << endl;
    }
    ofs.close();
}

void tree(string plik){
    ofstream ofs;
    pair<int, int> para;    //lewy  prawy
    pair<int, int> epara;   //lewy  prawy
    pair<int, pair<int, int> > ipara;   //ilosc   lewy    prawy
    pair<int, pair<int, int> > cpara;   //ilosc   lewy    prawy
    map<int, pair<int, pair<int, int> > > tree; //symbol  ilosc   lewy    prawy
    list<pair<int, int> > symcounts;
    int i = 0;
    int j = 0;
    load(plik, symcounts);
    epara.first = 404;
    epara.second = 404;
    cpara.second = epara;
    while(symcounts.size() > 1){
        i++;
        para.first = symcounts.back().first;
        ipara.first = symcounts.back().second;
        cpara.first = symcounts.back().second;
        if(symcounts.back().first >= 0){
            tree[symcounts.back().first] = cpara;
        }
        symcounts.pop_back();
        para.second = symcounts.back().first;
        ipara.first += symcounts.back().second;
        cpara.first = symcounts.back().second;
        if(symcounts.back().first >= 0){
            tree[symcounts.back().first] = cpara;
        }
        symcounts.pop_back();
        ipara.second = para;
        tree[-i] = ipara;
        para.first = -i;
        para.second = ipara.first;
        list<pair<int, int> >::reverse_iterator I;
        for(I = symcounts.rbegin(); I != symcounts.rend() || tree[-i].first < I->second; ++I){
            if(tree[-i].first < I->second){
                symcounts.insert(I.base(), para);
                break;
            }
        }
        if(tree[-i].first > I->second){
            symcounts.insert(I.base(), para);
        }
    }
    j = i;
    plik = plik.substr(0, plik.find_last_of('.')) + ".tree";
    ofs.open(plik.c_str(), fstream::out);
    for(i; i > 0; --i){
        ofs << -i << " " << tree[-i].second.first << " " << tree[-i].second.second << endl;
    }
    ofs.close();
    coding(plik, tree, -j);
    code(plik, tree, -j);
}

int drzewo(string msort){
    tree(msort);
    return 0;
}
