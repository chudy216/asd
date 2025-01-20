#include "zad1.hpp"
#include <string>
#include "lista.h"
std::string DNPL(lista* l, int i)
{
    lista p = (lista)malloc(sizeof(elListy));
    p->klucz = i;
    p->nast = *l;
    *l = p;
    return "poprawnie dodano wartosc na poczatek listy";
}
std::string DNKL(lista* l, int i)
{
    while ((*l)) {
        l = &(*l)->nast;
    }
    DNPL(l, i);
    return "poprawnie dodano wartosc na koniec listy";
}
std::string UPL(lista* l) {
    lista p = 0;
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    p = (*l)->nast;
    free(*l);
    *l = p;
    return "poprawnie usunieto wartosc z poczatku listy";
}
std::string UKL(lista* l) {
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    while ((*l)->nast)
        l = &(*l)->nast;
    free(*l);
    *l = 0;
    return "poprawnie usunieto wartosc z konca listy";
}
std::string OEL(lista l, int i) {
    int x = 0;
    while (l) {
        x++;
        if (l->klucz == i) {
            return "szukany element o wartosci " + to_string(i) + " jest " + to_string(x) + " elementem listy";
        }
        else
            l = l->nast;
    }
    return "szukany element nie zostal znaleziony";
}
std::string DPEL(lista* l, int i, int n) {
    int x = 1;
    while (x++ < n && *l) {
        l = &(*l)->nast;
    }
    if (!(*l)) {
        return "lista nie posiada tylu elementow";
    }
    DNPL(l, i);
    return "poprawnie dodano nowy element przed elementem numer " + to_string(n);
}
std::string DPWE(lista* l, int i, int n) {
    while (*l) {
        if ((*l)->klucz == n) {
            DNPL(l, i);
            return "poprawnie dodano nowy element przed pierwszym elementem o wartosci " + to_string(n);
        }
        else
            l = &(*l)->nast;
    }
    return "szukany element nie zostal znaleziony";

}
std::string DZWE(lista* l, int i, int n) {
    while (*l) {
        if ((*l)->klucz == n) {
            l = &(*l)->nast;
            DNPL(l, i);
            return "poprawnie dodano nowy element za pierwszym elementem o wartosci " + to_string(n);
        }
        else
            l = &(*l)->nast;
    }
    return "szukany element nie zostal znaleziony";

}
std::string DZEL(lista* l, int i, int n) {
    int x = 0;
    while (x++ < n) {
        if (!(*l)) {
            return "lista nie posiada tylu elementow";
        }
        l = &(*l)->nast;
    }
    DNPL(l, i);
    return "poprawnie dodano nowy element za elementem numer " + to_string(n);
}
std::string UEL(lista* l, int i) {
    int x = 1;
    while (x++ < i && *l) {
        l = &(*l)->nast;
    }
    if (!(*l)) {
        return "lisa nie posiada tylu elementow";
    }
    UPL(l);
    return "poprawnie usunieto element numer " + to_string(i);
}
std::string UWE(lista* l, int n) {
    while (*l) {
        if ((*l)->klucz == n) {
            UPL(l);
            return "poprawnie usunieto pierwszy element o wartosci " + to_string(n);
        }
        else
            l = &(*l)->nast;
    }
    return "szukany element nie zostal znaleziony";
}
std::string wyswietl(lista l) {
    std::string komunikat = "[ ";
    while (l) {
        komunikat += to_string(l->klucz) + " ";
        l = l->nast;
    }
    komunikat += "]";
    return komunikat;
}
std::string wyswietl_kon(lista l) {
    std::string komunikat = "";
    while (l) {
        komunikat = to_string(l->klucz) + " " + komunikat;
        l = l->nast;
    }
    komunikat = "[ " + komunikat + " ]";
    return komunikat;
}