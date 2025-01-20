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

string UPL(lista* l) {
    lista p = 0;
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    p = (*l)->nast;
    free(*l);
    *l = p;
    return "poprawnie usunieto wartosc z poczatku listy";
}
string UWE(lista* l, int n) {
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

string wczytaj(lista* l, string nazwa) {
    int y = 0;
    ifstream plik(nazwa);
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
string zapisz(lista l, string nazwa) {
    ofstream plik(nazwa);
    string list = wyswietl(l);
    plik << list.substr(1, list.length() - 2);;
    plik.close();
    return "Liste zapisano do pliku";
}
lista fuzja(lista l1, lista l2) {
    lista l3;
    if (l2->klucz < l1->klucz) {
        l3 = l2;
        l2 = l2->nast;
    }
    else
    {
        l3 = l1;
        l1 = l1->nast;
    }
    lista start = l3;
    while (l1 || l2) {
        if (l1 && l2) {
            if (l2->klucz < l1->klucz) {
                l3->nast = l2;
                while (l2 && l2->klucz < l1->klucz) {
                    l3 = l3->nast;
                    l2 = l2->nast;
                }
            }
            else
            {
                l3->nast = l1;
                while (l1 && l2->klucz >= l1->klucz) {
                    l3 = l3->nast;
                    l1 = l1->nast;
                }
                
            }
            wyswietl(start);
        }
        else if (l1) {
            l3->nast = l1;
            break;  
        }
        else {
            l3->nast = l2;
            break;
        }
    }
    return start;
}
int main()
{
    lista l1 = 0;
    lista l2 = 0;
    int wybor = 0;
    int klucz = 0;
    int numer = 0;
    lista p = 0;
    string komunikat = "";
    while (1) {
        cout << "Elementy listy sa indeksowane od 1 w zwyz!\nwybierz operacje \n"
            << "1 - dodaj element do listy\n"
            << "2 - usun znaleziony element\n"
            << "3 - wyswietl zawartosc listy\n"
            << "4 - wczytaj liste z pliku\n"
            << "5 - zapisz liste do pliku\n"
            << "6 - polacz liste\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            while (numer != 1 && numer != 2) {
                cout << "wybierz dla ktorej listy dzialasz 1 / 2 ";
                cin >> numer;
            }
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = (numer == 1) ? DDL(&l1, klucz) : DDL(&l2, klucz);
            break;
        case 2:
            while (numer != 1 && numer != 2) {
                cout << "wybierz dla ktorej listy dzialasz 1 / 2 ";
                cin >> numer;
            }
            cout << "podaj wartosc szukanego elementu: ";
            cin >> klucz;
            komunikat = (numer == 1) ? UWE(&l1, klucz) : UWE(&l2, klucz);
            break;
        case 3:
            while (numer != 1 && numer != 2) {
                cout << "wybierz dla ktorej listy dzialasz 1 / 2 ";
                cin >> numer;
            }
            komunikat = (numer == 1) ? wyswietl(l1) : wyswietl(l2);
            break;
        case 4:
            while (numer != 1 && numer != 2) {
                cout << "wybierz dla ktorej listy dzialasz 1 / 2 ";
                cin >> numer;
            }
            komunikat = (numer == 1) ? wczytaj(&l1, "lista1") : wczytaj(&l2, "lista2");
            break;
        case 5:
            while (numer != 1 && numer != 2) {
                cout << "wybierz dla ktorej listy dzialasz 1 / 2 ";
                cin >> numer;
            }
            komunikat = (numer == 1) ? zapisz(l1, "lista1") : zapisz(l2, "lista2");
            break;
        case 6:
            komunikat = wyswietl(fuzja(l1, l2));
            break;
        default:
            komunikat = "prosze wybrac poprawna wartosc";
        }
        system("cls");
        cout << komunikat + "\n";
        numer = 0;
        komunikat = "";
    }
    return 0;
}

