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

string DNPL(lista* l, int i) {
    lista p = (lista)malloc(sizeof(elListy));
    if (*l) {
        p->klucz = (*l)->klucz;
        p->nast = (*l)->nast;
        (*l)->nast = p;
        (*l)->klucz = i;
    }
    else {
        *l = p;
        p->nast = p;
        p->klucz = i;
    }
    return "poprawnie dodano wartosc na poczatek listy";
}
string DNKL(lista* l, int i)
{
    DNPL(l, i);
    *l = (*l)->nast;
    return "poprawnie dodano wartosc na koniec listy";
}
string wyswietl(lista l) {
    lista start = l;
    string komunikat = "[ ";
    if (l) {
        komunikat += to_string(l->klucz) + " ";
        l = l->nast;
    }
    while (l && l != start) {
        komunikat += to_string(l->klucz) + " ";
        l = l->nast;
        std::cout << komunikat;
    }
    komunikat += "]";
    return komunikat;
}
string wyswietl_kon(lista l) {
    string komunikat = "";
    lista start = l;
    if (l) {
        komunikat = to_string(l->klucz);
        l = l->nast;
    }
    while (l && l != start) {
        komunikat = to_string(l->klucz) + " " + komunikat;
        l = l->nast;
    }
    komunikat = "[ " + komunikat + " ]";
    return komunikat;
}
string UPL(lista* l) {
    lista p = 0;
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    p = (*l)->nast;
    if (p == *l) {
        free(*l);
        *l = NULL;
        return "poprawnie usunieto wartosc z poczatku listy";
    }
    (*l)->klucz = p->klucz;
    (*l)->nast = p->nast;
    free(p);
    return "poprawnie usunieto wartosc z poczatku listy";
}
string UKL(lista* l) {
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    lista start = *l;
    if ((*l)->nast == *l) {
        free(*l);
        *l = NULL;
        return "poprawnie usunieto wartosc z końca listy";
    }
    while ((*l)->nast->nast != start) {
        l = &(*l)->nast;
    }
    lista p = (*l)->nast;
    (*l)->nast = p->nast;
    free(p);
    return "poprawnie usunieto wartosc z konca listy";
}
string OEL(lista l, int i) {
    int x = 0;
    lista start = l;
    if (l)
        do {
            x++;
            if (l->klucz == i) {
                return "szukany element o wartosci " + to_string(i) + " jest " + to_string(x) + " elementem listy";
            }
            else
                l = l->nast;
        } while (l != start);
    return "szukany element nie zostal znaleziony";
}
string DPEL(lista* l, int i, int n) {
    int x = 1;
    lista start = *l;
    if (*l) {
        if (x < n)
            do {
                x++;
                l = &(*l)->nast;
                if (*l == start || x <= 1)
                    return "lista nie posiada tylu elementow";
            } while (x < n);
        DNPL(l, i);
    }
    else
        return "lista nie posiada tylu elementow";
    return "poprawnie dodano nowy element przed elementem numer " + to_string(n);
}
string DZEL(lista* l, int i, int n) {
    int x = 1;
    lista start = *l;
    if (*l) {
        if (x <= n)
            do {
                x++;
                l = &(*l)->nast;
                if (*l == start || x <= 1)
                    return "lista nie posiada tylu elementow";
            } while (x <= n);
        DNPL(l, i);
    }
    else
        return "lista nie posiada tylu elementow";
    return "poprawnie dodano nowy element przed elementem numer " + to_string(n);
}
string DPWE(lista* l, int i, int n) {
    lista start = *l;
    if (*l)
        do {
            if ((*l)->klucz == n) {
                DNPL(l, i);
                return "poprawnie dodano nowy element przed pierwszym elementem o wartosci " + to_string(n);
            }
            else
                l = &(*l)->nast;
        } while (*l != start);
    return "szukany element nie zostal znaleziony";

}
string DZWE(lista* l, int i, int n) {
    lista start = *l;
    if (*l)
        do {
            if ((*l)->klucz == n) {
                l = &(*l)->nast;
                DNPL(l, i);
                return "poprawnie dodano nowy element za pierwszym elementem o wartosci " + to_string(n);
            }
            else
                l = &(*l)->nast;
        } while (*l != start);
    return "szukany element nie zostal znaleziony";

}
string UEL(lista* l, int i) {
    int x = 1;
    lista start = *l;
    if (*l) {
        if (x < i)
            do {
                x++;
                l = &(*l)->nast;
                if (*l == start || i <= 1)
                    return "lista nie posiada tylu elementow";
            } while (x < i);
        if ((*l)->nast == start)
            UKL(&start);
        else
            UPL(l);
    }
    else
        return "lista nie posiada tylu elementow";
    return "poprawnie usunieto element numer " + to_string(i);
}
string UWE(lista* l, int n) {
    lista start = *l;
    if (*l)
        do {
            if ((*l)->klucz == n) {
                if ((*l)->nast == start)
                    UKL(&start);
                else
                    UPL(l);
                return "usunieto pierwszy element o wartosci " + to_string(n);
            }
            else
                l = &(*l)->nast;
        } while (*l != start);
    return "szukany element nie zostal znaleziony";
}
lista UWE_all(lista* l, int n) {
    lista start = *l;
    if (*l)
        do {
            if ((*l)->klucz == n) {
                if ((*l)->nast == start)
                    UKL(&start);
                else
                    UPL(l);
            }
            else
                l = &(*l)->nast;
        } while (*l != start);
    return start;
}
string wczytaj(lista* l, string name) {
    int y = 0;
    ifstream plik(name);
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
string zapisz(lista l, string name) {
    ofstream plik(name);
    string list = wyswietl(l);
    plik << list.substr(1, list.length() - 2);;
    plik.close();
    return "Liste zapisano do pliku";
}
string zad12(lista *l1, lista l2){
    lista start = l2;
    if (l2 == NULL || *l1 == NULL)return "lista byla pusta";
    do {
        UWE_all(l1, (l2)->klucz);
        l2 = l2->nast;
    } while (l2 != start);
    return "Usunieto wszystkie elementy drugiej listy";
}
    int main()
{
    lista l = 0;
    int wybor = 0;
    int klucz = 0;
    int numer = 0;
    int list = 0;
    lista l2 = 0;
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
            << "16 - zadanie 12\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        while (list != 1 && list != 2 && wybor != 0) {
            cout << "wybierz dla ktorej listy dzialasz 1 / 2 ";
            cin >> list;
        }
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = (list == 1) ? DNPL(&l, klucz) : DNPL(&l2, klucz);
            break;
        case 2:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = (list == 1) ? DNKL(&l, klucz) : DNKL(&l2, klucz);
            break;
        case 3:
            komunikat = (list == 1) ? UPL(&l) : UPL(&l2);
            break;
        case 4:
            komunikat = (list == 1) ? UKL(&l) : UKL(&l2);
            break;
        case 5:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> klucz;
            komunikat = (list == 1) ? OEL(l, klucz) : OEL(l2, klucz);
            break;
        case 6:
            cout << "podaj numer elementu przed ktorym chcesz dodac ";
            cin >> numer;
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = (list == 1) ? DPEL(&l, klucz, numer) : DPEL(&l2, klucz, numer);
            break;
        case 7:
            cout << "podaj numer elementu za ktorym chcesz dodac ";
            cin >> numer;
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = (list == 1) ? DZEL(&l, klucz, numer) : DZEL(&l2, klucz, numer);
            break;
        case 8:
            cout << "podaj numer elementu ktory chcesz usunac ";
            cin >> numer;
            komunikat = (list == 1) ? UEL(&l, numer) : UEL(&l2, numer);
            break;
        case 9:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = (list == 1) ? DPWE(&l, klucz, numer) : DPWE(&l2, klucz, numer);
            break;
        case 10:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = (list == 1) ? DZWE(&l, klucz, numer) : DZWE(&l2, klucz, numer);
            break;
        case 11:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            komunikat = (list == 1) ? UWE(&l, numer) : UWE(&l2, numer);
            break;
        case 12:
            komunikat = (list == 1) ? wyswietl(l) : wyswietl(l2);
            break;
        case 13:
            komunikat = (list == 1) ? wyswietl_kon(l) : wyswietl_kon(l2);
            break;
        case 14:
            komunikat = (list == 1) ? wczytaj(&l, "lista.txt") : wczytaj(&l2, "lista2.txt");
            break;
        case 15:
            komunikat = (list == 1) ? zapisz(l, "lista.txt") : zapisz(l2, "lista2.txt");
            break;
        case 16:
            komunikat = (list == 1) ? zad12(&l, l2) : zad12(&l2, l);
            break;
        default:
            komunikat = "prosze wybrac poprawna wartosc";
        }
        system("cls");
        list = 0;
        cout << komunikat + "\n";
        komunikat = "";
    }
    return 0;
}