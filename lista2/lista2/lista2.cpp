﻿#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
struct el {
    int klucz;
    struct el* nast;
    struct el* pop;
};
typedef struct el elListy;
typedef elListy* lista;

string DNPL(lista* l, int i)
{
    lista p = (lista)malloc(sizeof(elListy));
    p->klucz = i;
    p->nast = *l;
    p->pop = NULL;
    if (*l)
        (*l)->pop = p;
    *l = p;
    return "poprawnie dodano wartosc na poczatek listy";
}
string DNKL(lista* l, int i)
{
    lista pop = *l;
    while ((*l)) {
        pop = *l;
        l = &(*l)->nast;
    }
    DNPL(l, i);
    (*l)->pop = pop;
    return "poprawnie dodano wartosc na koniec listy";
}
string wyswietl(lista l) {
    string komunikat = "[ ";
    while (l) {
        komunikat += to_string(l->klucz) + " ";
        l = l->nast;
    }
    komunikat += "]";
    return komunikat;
}
string wyswietl_kon(lista l) {
    string komunikat = to_string(l->klucz);
    while (l->nast) {
        l = l->nast;
        komunikat = to_string(l->klucz) + " " + komunikat;
    }
    komunikat = "[ " + komunikat + " ]";
    return komunikat;
}
string wyswietl_obie(lista l) {
    string komunikat = to_string(l->klucz);
    while (l->nast) {
        l = l->nast;
        komunikat = to_string(l->klucz) + " " + komunikat;
    }
    komunikat = "[ " + komunikat + " ]";
    string komunikat2 = to_string(l->klucz);
    while (l->pop) {
        l = l->pop;
        komunikat2 = to_string(l->klucz) + " " + komunikat2;
    }
    komunikat2 = "[ " + komunikat2 + " ]";
    komunikat = komunikat + " " + komunikat2;
    return komunikat;
}
string UPL(lista* l) {
    lista p = 0;
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    p = (*l)->nast;
    free(*l);
    *l = p;
    if(p)
        p->pop = NULL;
    return "poprawnie usunieto wartosc z poczatku listy";
}
string UKL(lista* l) {
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    while ((*l)->nast)
        l = &(*l)->nast;
    free(*l);
    *l = 0;
    return "poprawnie usunieto wartosc z konca listy";
}
string OEL(lista l, int i) {
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
string DPEL(lista* l, int i, int n) {
    int x = 1;
    while (x++ < n && *l) {
        l = &(*l)->nast;
    }
    if (!(*l)) {
        return "lista nie posiada tylu elementow";
    }
    lista pop = (*l)->pop;
    DNPL(l, i);
    (*l)->pop = pop;
    return "poprawnie dodano nowy element przed elementem numer " + to_string(n);
}
string DPWE(lista* l, int i, int n) {
    lista pop;
    while (*l) {
        if ((*l)->klucz == n) {
            pop = (*l)->pop;
            DNPL(l, i);
            (*l)->pop = pop;
            return "poprawnie dodano nowy element przed pierwszym elementem o wartosci " + to_string(n);
        }
        else
            l = &(*l)->nast;
    }
    return "szukany element nie zostal znaleziony";

}
string DZWE(lista* l, int i, int n) {
    lista pop;
    while (*l) {
        if ((*l)->klucz == n) {
            pop = *l;
            l = &(*l)->nast;
            DNPL(l, i);
            (*l)->pop = pop;
            return "poprawnie dodano nowy element za pierwszym elementem o wartosci " + to_string(n);
        }
        else
            l = &(*l)->nast;
    }
    return "szukany element nie zostal znaleziony";

}
string DZEL(lista* l, int i, int n) {
    int x = 1;
    lista pop = *l;
    while (x++ <= n) {
        if (!(*l)) {
            return "lista nie posiada tylu elementow";
        }
        pop = *l;
        l = &(*l)->nast;
    }
    DNPL(l, i);
    (*l)->pop = pop;
    return "poprawnie dodano nowy element za elementem numer " + to_string(n);
}
string UEL(lista* l, int i) {
    int x = 1;
    while (x++ < i && *l) {
        l = &(*l)->nast;
    }
    if (!(*l)) {
        return "lisa nie posiada tylu elementow";
    }
    lista p = (*l)->pop;
    UPL(l);
    (*l)->pop = p;
    return "poprawnie usunieto element numer " + to_string(i);
}
string UWE(lista* l, int n) {
    while (*l) {
        if ((*l)->klucz == n) {
            lista p = (*l)->pop;
            UPL(l);
            (*l)->pop = p;
            return "poprawnie usunieto pierwszy element o wartosci " + to_string(n);
        }
        else
            l = &(*l)->nast;
    }
    return "szukany element nie zostal znaleziony";
}
string wczytaj(lista* l) {
    int y = 0;
    ifstream plik("lista.txt");
    string lista, listafull = "", liczba = "";
    while (*l) {
        UPL(l);
    }
    while (getline(plik, lista)) {
        listafull += lista;
    }
    for (int i = 0; i < listafull.length(); i++) {
        while (isdigit(listafull[i])) {
            liczba += listafull[i];
            y++;
            i++;
        }
        if (y > 0) {
            y = 0;
            DNKL(l, stoi(liczba));
            liczba = "";
        }
    }
    if (listafull == "") {
        return "plik nie zawiera odpowiedniej listy";
    }
    return "odczytano liste " + wyswietl(*l);
}
string zapisz(lista l) {
    ofstream plik("lista.txt");
    string list = wyswietl(l);
    plik << list.substr(1, list.length() - 2);;
    plik.close();
    return "Liste zapisano do pliku";
}
int main()
{
    lista l = 0;
    int wybor = 0;
    int klucz = 0;
    int numer = 0;
    lista p = 0;
    string komunikat = "";
    while (1) {
        cout << "Elementy listy sa indeksowane od 1 w zwyz!\nwybierz operacje \n"
            << "1 - dodaj element na poczatku listy \n"
            << "2 - dodaj element na koncu listy \n"
            << "3 - usun pierwszy element listy \n"
            << "4 - usun ostatni element listy \n"
            << "5 - odszukaj zadany element \n"
            << "6 - dodaj nowy element przed wskazanym\n"
            << "7 - dodaj nowy element za wskazanym\n"
            << "8 - usun wskazany element\n"
            << "9 - dodaj nowy element przed znalezionym\n"
            << "10 - dodaj nowy element za znalezionym\n"
            << "11 - usun znaleziony element\n"
            << "12 - wyswietl zawartosc listy\n"
            << "13 - wyswietl zawartosc listy od konca\n"
            << "14 - wczytaj liste z pliku\n"
            << "15 - zapisz liste do pliku\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = DNPL(&l, klucz);
            break;
        case 2:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = DNKL(&l, klucz);
            break;
        case 3:
            komunikat = UPL(&l);
            break;
        case 4:
            komunikat = UKL(&l);
            break;
        case 5:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> klucz;
            komunikat = OEL(l, klucz);
            break;
        case 6:
            cout << "podaj numer elementu przed ktorym chcesz dodac ";
            cin >> numer;
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = DPEL(&l, klucz, numer);
            break;
        case 7:
            cout << "podaj numer elementu za ktorym chcesz dodac ";
            cin >> numer;
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = DZEL(&l, klucz, numer);
            break;
        case 8:
            cout << "podaj numer elementu ktory chcesz usunac ";
            cin >> numer;
            komunikat = UEL(&l, numer);
            break;
        case 9:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = DPWE(&l, klucz, numer);
            break;
        case 10:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = DZWE(&l, klucz, numer);
            break;
        case 11:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            komunikat = UWE(&l, numer);
            break;
        case 12:
            komunikat = wyswietl(l);
            break;
        case 13:
            komunikat = wyswietl_kon(l);
            break;
        case 14:
            komunikat = wczytaj(&l);
            break;
        case 15:
            komunikat = zapisz(l);
            break;
        case 16:
            komunikat = wyswietl_obie(l);
            break;
        default:
            komunikat = "prosze wybrac poprawna wartosc";
        }
        system("cls");
        cout << komunikat + "\n";
        komunikat = "";
    }
    return 0;
}

