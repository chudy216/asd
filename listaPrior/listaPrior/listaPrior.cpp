#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct el {
    int klucz;
    int wartosc;
    struct el* nast;
};
typedef struct el elListy;
typedef elListy* lista;

string DDL(lista* l, int i, int j)
{
    while (*l && i <= (*l)->klucz) {
        l = &(*l)->nast;
    }
    lista p = (lista)malloc(sizeof(elListy));
    p->klucz = i;
    p->wartosc = j;
    p->nast = *l;
    *l = p;
    return "poprawnie dodano wartosc do listy";
}

string wyswietl(lista l) {
    string komunikat = "Wartosci: [ ";
    string komunikat2 = "] Priorytety: [ ";
    while (l) {
        komunikat += to_string(l->wartosc) + " ";
        komunikat2 += to_string(l->klucz) + " ";
        cout << komunikat;
        l = l->nast;
    }
    komunikat2 += "]";
    komunikat += komunikat2;
    return komunikat;
}
string UPL(lista* l) {
    lista p = 0;
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    p = (*l)->nast;
    free(*l);
    *l = p;
    return "poprawnie usunieto wartosc z poczatku listy";
}
string OEL(lista *l, int i, int j) {
    int x = 0;
    lista pop = 0;
    lista start = *l;
    while (*l) {
        x++;
        if ((*l)->wartosc == j) {
            if (pop && (*l)->nast) {
                pop->nast = (*l)->nast;
            }
            else if (pop)
                pop->nast = NULL;
            if (*l == start)
                start = start->nast;
            UPL(l);
            DDL(&start, i, j);
            *l = start;
            return "priorytet pierwszego elementu z wartoscia " + to_string(j) + " zostal zmieniony na " + to_string(i);
        }
        else
            pop = *l;
            *l = (*l)->nast;
    }
    *l = start;
    return "szukany element nie zostal znaleziony";
}
string UWE(lista* l, lista* el) {
    lista *i=l;
    if (*l == NULL)
        return "kolejka jest pusta";
    int max = (*l)->klucz;
    lista p = (lista)malloc(sizeof(elListy));
    p->klucz = (*l)->klucz;
    p->wartosc = (*l)->klucz;
    p->nast = NULL;
    UPL(l);
    *el = p;
    return "element z najwyzszym priorytetem " + to_string(p->klucz) + " ma wartosc " + to_string(p->wartosc);
}
int main()
{
    lista l = 0;
    lista el = 0;
    int wybor = 0;
    int klucz = 0;
    int priorytet = 0;
    string komunikat = "";
    while (1) {
        cout << "Elementy listy sa indeksowane od 1 w zwyz!\nwybierz operacje \n"
            << "1 - dodaj element do listy \n"
            << "2 - zmien priorytet elementu \n"
            << "3 - pobierz element o najwyszym priorytecie\n"
            << "4 - wyswietl zawartosc listy\n"
            << "5 - wyswietl pobrany element\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            cout << "podaj priorytet dla nowego elementu: ";
            cin >> priorytet;
            komunikat = DDL(&l, priorytet, klucz);
            break;
        case 2:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> klucz;
            cout << "podaj nowy priorytet dla elementu: ";
            cin >> priorytet;
            komunikat = OEL(&l, priorytet, klucz);
            break;
        case 3:
            komunikat = UWE(&l, &el);
            break;
        case 4:
            komunikat = wyswietl(l);
            break;
        case 5:
            komunikat = wyswietl(el);
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