#include <iostream>
#include "model.h"
#include "drzewo.h"
#include "kompresja.h"
#include "dekompresja.h"

using namespace std;

int main(int argc, char *argv[]) {
    string plik = argv[1];
    model(plik);
    drzewo(plik = plik.substr(0, plik.find_last_of('.')) + ".msort");
    kompresja(plik = plik.substr(0, plik.find_last_of('.')) + ".code", argv[1]);
    dekompresja(plik = plik.substr(0, plik.find_last_of('.')) + ".tree", plik = plik.substr(0, plik.find_last_of('.')) + ".huff");
    return 0;
}