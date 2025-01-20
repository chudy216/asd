#include <iostream>
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

string DDL(lista* l, int i, lista wart)
{
    lista* pop = NULL;
    while (*l!=wart && i > (*l)->klucz) {
        pop = l;
        l = &(*l)->nast;
    }
    lista p = (lista)malloc(sizeof(elListy));
    p->klucz = i;
    p->nast = *l;
    if (pop)
        p->pop = *pop;
    else
        p->pop = NULL;
    if (*l != wart && (*l)->pop) {
            (*l)->pop->nast = p;
            (*l)->nast->pop = p;
    }
    else
        (*l)->pop = p;

    *l = p;
    return "poprawnie dodano wartosc";
}

string wyswietl(lista l, lista wart) {
    string komunikat = "[ ";
    while (l!=wart) {
        komunikat += to_string(l->klucz) + " ";
        cout << komunikat;
        l = l->nast;
    }
    komunikat += "]";
    return komunikat;
}

string OPL(lista l, lista wart) {
    if (l == wart) return "lista byla pusta";
    return "pierwsza wartosc to " + to_string(l->klucz);
}
string OKL(lista l, lista wart) {
    if (l == wart) return "lista byla pusta";
    while ((l)->nast != wart)
        l = l->nast;
    return "ostatnia wartosc to " + to_string(l->klucz);
}
string OEL(lista l, int i, lista wart) {
    int x = 0;
    while (l!=wart && l->klucz <= i) {
        x++;
        if (l->klucz == i) {
            return "szukany element o wartosci " + to_string(i) + " jest " + to_string(x) + " elementem listy";
        }
        else
            l = l->nast;
    }
    return "szukany element nie zostal znaleziony";
}
string UWE(lista* l, int n, lista wart) {
    lista* pop = NULL;
    while (*l!=wart) {
        if ((*l)->klucz == n) {
            lista fr = *l;
            if (pop) {
                if ((*l)->nast)
                    (*l)->nast->pop = *pop;
            }
            if ((*l)->nast) {
                *l = (*l)->nast;
            }
            else
                *l = NULL;
            free(fr);

            return "poprawnie usunieto pierwszy element o wartosci " + to_string(n);
        }
        else if ((*l)->klucz < n) {
            pop = l;
            l = &(*l)->nast;
        }
        else
            return "szukany element nie zostal znaleziony";
    }
    return "szukany element nie zostal znaleziony";
}

string wczytaj(lista* l, lista wart) {
    int y = 0;
    while (*l!=wart) {
        UWE(l, (*l)->klucz, wart);
    }
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
            DDL(l, stoi(liczba), wart);
            liczba = "";
        }
    }
    if (listafull == "") {
        return "plik nie zawiera odpowiedniej listy";
    }
    return "odczytano liste " + wyswietl(*l, wart);
}
string zapisz(lista l, lista wart) {
    ofstream plik("lista.txt");
    string list = wyswietl(l, wart);
    plik << list.substr(1, list.length() - 2);;
    plik.close();
    return "Liste zapisano do pliku";
}
lista DKL(lista* l)
{
    while (*l) {
        l = &(*l)->nast;
    }
    lista p = (lista)malloc(sizeof(elListy));
    p->klucz = INT_MAX;
    p->nast = NULL;
    *l = p;
    return p;
}
int main()
{
    lista l = 0;
    int wybor = 0;
    int klucz = 0;
    int numer = 0;
    lista wart = DKL(&l);
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
            komunikat = DDL(&l, klucz, wart);
            break;
        case 2:
            komunikat = OPL(l, wart);
            break;
        case 3:
            komunikat = OKL(l, wart);
            break;
        case 4:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> klucz;
            komunikat = OEL(l, klucz, wart);
            break;
        case 5:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            komunikat = UWE(&l, numer, wart);
            break;
        case 6:
            komunikat = wyswietl(l, wart);
            break;
        case 7:
            komunikat = wczytaj(&l, wart);
            break;
        case 8:
            komunikat = zapisz(l, wart);
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

