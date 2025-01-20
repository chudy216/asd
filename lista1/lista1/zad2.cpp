#include "zad2.hpp"
#include <string>
#include "lista.h"
#include "zad1.h"
using namespace std;
std::string IUWW(lista* l, int n) {
    int x = 0;
    while (*l) {
        if ((*l)->klucz == n) {
            UPL(l);
            x++;
        }
        else
            l = &(*l)->nast;
    }
    if (x == 0)
        return "szukany element nie zostal znaleziony";
    return "usunieto wszystkie elementy o wartosci " + to_string(n);
}
std::string RUWW(lista* l, int n) {
    if (*l) {
        if ((*l)->klucz == n) {
            UPL(l);
            RUWW(l, n);
        }
        else
            RUWW(&(*l)->nast, n);
    }
    return "lista juz nie zawiera zadnego elementu o wartosc " + to_string(n);
}