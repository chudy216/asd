#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
struct el {
    int klucz;
    struct el* nast;
};
typedef struct el elListy;
typedef elListy* lista;

string DDL(lista* l, int i)
{
    while (*l && i > (*l)->klucz) {
        l = &(*l)->nast;
    }
    lista p = (lista)malloc(sizeof(elListy));
    p->klucz = i;
    p->nast = *l;
    *l = p;
    return "poprawnie dodano wartosc do listy";
}

string wyswietl(lista l) {
    string komunikat = "[ ";
    while (l) {
        komunikat += to_string(l->klucz) + " ";
        cout << komunikat;
        l = l->nast;
    }
    komunikat += "]";
    return komunikat;
}

string OPL(lista l) {
    if (l == 0) return "lista byla pusta";
    return "pierwsza wartosc to "+to_string(l->klucz);
}
string OKL(lista l) {
    if (l == 0) return "lista byla pusta";
    while ((l)->nast)
        l = l->nast;
    return "ostatnia wartosc to "+ to_string(l->klucz);
}
string OEL(lista l, int i) {
    int x = 0;
    while (l && l->klucz <= i) {
        x++;
        if (l->klucz == i) {
            return "szukany element o wartosci " + to_string(i) + " jest " + to_string(x) + " elementem listy";
        }
        else
            l = l->nast;
    }
    return "szukany element nie zostal znaleziony";
}
string UWE(lista* l, int n) {
    lista* pop = NULL;
    lista nast = NULL;
    lista p  = *l;
    while (*l) {
        if ((*l)->klucz == n) {
            if(pop)
                nast = (*l)->nast;
            free(*l);
            *l = p;
            if (nast)
                (*l)->nast = nast;
            return "poprawnie usunieto pierwszy element o wartosci " + to_string(n);
        }
        else if ((*l)->klucz < n) {
            pop = l;
            l = &(*l)->nast;
        }
        else
            return "szukany element nie zostal znaleziony";
    }
}

string wczytaj(lista* l) {
    int y = 0;
    ifstream plik("lista.txt");
    string lista, listafull = "", liczba = "";
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
            DDL(l, stoi(liczba));
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
            << "1 - dodaj element do listy \n"
            << "2 - odczytaj pierwszy element listy \n"
            << "3 - odczytaj ostatni element listy \n"
            << "4 - odszukaj zadany element \n"
            << "5 - usun znaleziony element\n"
            << "6 - wyswietl zawartosc listy\n"
            << "7 - wczytaj liste z pliku\n"
            << "8 - zapisz liste do pliku\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = DDL(&l, klucz);
            break;
        case 2:
            komunikat = OPL(l);
            break;
        case 3:
            komunikat = OKL(l);
            break;
        case 4:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> klucz;
            komunikat = OEL(l, klucz);
            break;
        case 5:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            komunikat = UWE(&l, numer);
            break;
        case 6:
            komunikat = wyswietl(l);
            break;
        case 7:
            komunikat = wczytaj(&l);
            break;
        case 8:
            komunikat = zapisz(l);
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

