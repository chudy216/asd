#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
typedef struct elDrzewa {
    string klucz;
    struct elDrzewa* przodek;
    struct elDrzewa* lewy;
    struct elDrzewa* prawy;
    elDrzewa(string wartosc) : klucz(wartosc), lewy(nullptr), prawy(nullptr) {}
};
typedef elDrzewa* drzewo;
string DDD(drzewo* d, string wartosc) {
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
    return "dodano element do drzewa";
}
void DLE(drzewo* d, string wartosc) {
    drzewo n = new elDrzewa(wartosc);
    n->przodek = *d;
    (*d)->lewy = n;
    *d = n;
}
void DPE(drzewo* d, string wartosc) {
    drzewo n = new elDrzewa(wartosc);
    n->przodek = *d;
    (*d)->prawy = n;
    *d = n;
}
string UZD(drzewo* d, string wartosc) {
    drzewo start = *d;
    while (*d) {
        if ((*d)->klucz > wartosc)
            d = &(*d)->lewy;
        else if ((*d)->klucz < wartosc)
            d = &(*d)->prawy;
        else {
            drzewo x = *d;
            if ((*d)->lewy == NULL && (*d)->prawy == NULL)
            {
                if ((*d)->przodek) {
                    if ((*d)->przodek->prawy == *d)
                        (*d)->przodek->prawy = NULL;
                    else
                        (*d)->przodek->lewy = NULL;
                }
                else
                    *d = NULL;
                free(x);
            }
            else if ((*d)->lewy != NULL && (*d)->prawy == NULL)
            {
                (*d)->lewy->przodek = (*d)->przodek;
                *d = (*d)->lewy;
                free(x);
            }
            else if ((*d)->lewy == NULL && (*d)->prawy != NULL)
            {
                (*d)->prawy->przodek = (*d)->przodek;
                *d = (*d)->prawy;
                free(x);
            }
            else {
                drzewo prawy = (*d)->prawy;
                (*d)->lewy->przodek = (*d)->przodek;
                *d = (*d)->lewy;
                while ((*d)->prawy != NULL) {
                    d = &(*d)->prawy;
                }
                (*d)->prawy = prawy;
                prawy->przodek = *d;
                free(x);
            }
            return "usunieto pierwszy element o wartosci " + wartosc;
        }
    }
    return "nie znaleziono elementu do usuniecia";

}
drzewo Dnast(drzewo d) {
    if (d == NULL)
        return NULL;
    else if (d->prawy) {
        d = d->prawy;
        while (d->lewy)
            d = d->lewy;
        return d;
    }
    while (d->przodek) {
        if (d->przodek->lewy == d) {
            d = d->przodek;
            return d;
        }
        else
            d = d->przodek;
    }
    return NULL;
}
string zad_16(drzewo d1, drzewo d2) {
    if (d1 == NULL && d2 == NULL) {
        return "Drzewa sa puste i takie same";
    }
    if (d1 == NULL || d2 == NULL) {
        return "Tylko jedno drzewo jest puste, nie sa takie same";
    }
    while (d1->lewy) {
        d1 = d1->lewy;
    }
    while (d2->lewy) {
        d2 = d2->lewy;
    }
    while (d1->klucz == d2->klucz) {
        d1 = Dnast(d1);
        d2 = Dnast(d2);
        if (d1 == NULL && d2 == NULL) {
            return "Drzewa zawieraja te same wartosci";
        }
        if (d1 == NULL || d2 == NULL) {
            return "Drzewa nie zawieraja tych samych wartosci";
        }
    }
    return "Drzewa nie zawieraja tych samych wartosci";
}
void Dtop(drzewo* d) {
    while (*d && (*d)->przodek)
        *d = (*d)->przodek;
}
string Pokaz(drzewo d, string prefix) {
    if (d == NULL)
        return "";
    string komunikat = "";
    komunikat += prefix;
    komunikat += "|__" + d->klucz + "\n";
    if (d->przodek && d == d->przodek->lewy)
        prefix += "|  ";
    else
        prefix += "   ";
    komunikat += Pokaz(d->lewy, prefix);
    komunikat += Pokaz(d->prawy, prefix);
    return komunikat;
}
string zapisz(drzewo d, int glebokosc, int strona, string path) {
    if (d == NULL) {
        return "";
    }
    ofstream plik(path, ofstream::app);
    if (d && d->przodek == NULL) {
        plik.close();
        plik.open(path);
    }
    plik << d->klucz << "\n";
    plik << glebokosc << "\n";
    plik << strona << "\n";
    plik.close();
    zapisz(d->lewy, glebokosc + 1, 0, path);
    zapisz(d->prawy, glebokosc + 1, 1, path);
    return "Drzewo zapisano do pliku";
}
string wczytaj(drzewo* d, string path) {
    drzewo start = *d;
    ifstream plik(path);
    string lista;
    vector <string> listafull;
    while (getline(plik, lista)) {
        listafull.push_back(lista);
    }
    if (listafull.empty()) {
        return "plik nie zawiera odpowiedniej listy";
    }
    while (*d) {
        UZD(d, (*d)->klucz);
    }
    int pop_g = -1;
    for (int i = 0; i < listafull.size(); i++) {
        string klucz = listafull[i++];
        int glebokosc = stoi(listafull[i++]);
        string prawy = listafull[i];
        while (glebokosc <= pop_g) {
            d = &(*d)->przodek;
            pop_g--;
        }
        pop_g = glebokosc;
        if (glebokosc == 0)
            DDD(d, klucz);
        else if (prawy == "0")
            DLE(d, klucz);
        else
            DPE(d, klucz);
    }
    plik.close();
    return "poprawnie odczytano liste";
}
int main() {
    drzewo d = 0;
    drzewo d2= 0;
    int wybor = 0;
    string klucz = "", komunikat = "";
    int drzewo = 0;
    while (1) {
        cout << "Elementy listy sa indeksowane od 1 w zwyz!\nwybierz operacje \n"
            << "1 - dodaj element do drzewa \n"
            << "2 - usun element z drzewa \n"
            << "3 - wyswietl zawartosc drzewa\n"
            << "4 - wczytaj drzewo z pliku\n"
            << "5 - zapisz drzewo do pliku\n"
            << "6 - porownaj zawartosc drzew\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        while (drzewo != 1 && drzewo != 2 && wybor !=6 && wybor != 0) {
            cout << "Dla ktorego drzewa chcesz dzialac 1/2 ";
            cin >> drzewo;
        }
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = drzewo == 1 ? DDD(&d, klucz) : DDD(&d2, klucz);
            break;
        case 2:
            cout << "podaj wartosc elementu ktory chcesz usunac: ";
            cin >> klucz;
            komunikat = drzewo == 1 ? UZD(&d, klucz) : UZD(&d2, klucz);
            break;
        case 3:
            komunikat = drzewo == 1 ? Pokaz(d, "") : Pokaz(d2, "");
            break;
        case 4:
            komunikat = drzewo == 1 ? wczytaj(&d, "drzewo.txt") : wczytaj(&d2, "drzewo2.txt");
            drzewo == 1 ? Dtop(&d) : Dtop(&d2);
            break;
        case 5:
            komunikat = drzewo == 1 ? zapisz(d, 0, 0, "drzewo.txt") : zapisz(d2, 0 , 0, "drzewo2.txt");
            break;
        case 6:
            komunikat = zad_16(d, d2);
            break;
        default:
            komunikat = "prosze wybrac poprawna wartosc";
        }
        system("cls");
        cout << komunikat + "\n";
        drzewo = 0;
        komunikat = "";
    }
    return 0;
}