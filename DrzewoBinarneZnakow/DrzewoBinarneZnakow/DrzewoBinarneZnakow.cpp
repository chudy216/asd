#include <iostream>
using namespace std;
typedef struct elDrzewa {
    string klucz;
    struct elDrzewa* przodek;
    struct elDrzewa* lewy;
    struct elDrzewa* prawy;
    elDrzewa(string wartosc) : klucz(wartosc), lewy(nullptr), prawy(nullptr) {}
};
typedef elDrzewa* drzewo;
void DDD(drzewo* d, string wartosc) {
    drzewo pop = 0;
    while (*d) {
        pop = *d;
        if ((*d)->klucz > wartosc)
            d = &(*d)->lewy;
        else
            d = &(*d)->prawy;   
    }
    drzewo n = new elDrzewa(wartosc);
    if (pop) {
        n->przodek = pop;
    }
    else
        n->przodek = NULL;
    *d = n;
}
void UZD(drzewo* d, string wartosc) {
    while (*d) {
        if ((*d)->klucz > wartosc)
            d = &(*d)->lewy;
        else if ((*d)->klucz < wartosc) 
            d = &(*d)->prawy;
        else {
            if ((*d)->przodek) {
                if (*d == (*d)->przodek->prawy) {
                    cout << "usun prawy";
                    return;
                }
                else {
                    cout << "usun lewy";
                    return;
                }
            }
        }
    }
    cout << "nie ma drania ";
    return;

}
void Dmin(drzewo d) {

}
void Dmax(drzewo d) {

}
void Dpop(drzewo* d) {

}
void Dnast(drzewo* d) {

}
void Dtop(drzewo* d) {

}
void Pokaz(drzewo d) {

}
int main() {
    drzewo d = 0;
    DDD(&d, "aaa");
    DDD(&d, "bbb");
    DDD(&d, "ccc");
    DDD(&d, "a21");
    cout << "dodawanie chyba git";
    UZD(&d, "a21");
    UZD(&d, "a22");
    UZD(&d, "bbb");
	return 0;
}