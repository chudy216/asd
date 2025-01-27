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
void DLE(drzewo* d, string wartosc){
    drzewo n = new elDrzewa(wartosc);
    n->przodek = *d;
    (*d)->lewy = n;
    *d = n;
}
void DPE(drzewo* d, string wartosc){
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
            return "usunieto pierwszy element o wartosci "+wartosc;
        }
    }
    return "nie znaleziono elementu do usuniecia";

}
string Dmin(drzewo d) {
    if (d == NULL)
        return "drzewo jest puste";
    while (d->lewy)
        d = d->lewy;
    return "minimum to " + d->klucz;
}
string Dmax(drzewo d) {
    if (d == NULL)
        return "drzewo jest puste";
    while (d->prawy)
        d = d->prawy;
    return "maksimum to " + d->klucz;
}
string Dpop(drzewo d) {
    if (d == NULL)
        return "drzewo jest puste";
    else if (d->lewy) {
        d = d->lewy;
        while (d->prawy)
            d = d->prawy;
        return "poprzedni element to " + d->klucz;
    }
    while (d->przodek) {
        if (d->przodek->prawy == d) {
            d = d->przodek;
            return "poprzedni element to " + d->klucz;
        }
        else
            d = d->przodek;
    }
    return "poprzednik nie istnieje";
}
string Dnast(drzewo d) {
    if (d == NULL)
        return "drzewo jest puste";
    else if (d->prawy) {
        d = d->prawy;
        while (d->lewy)
            d = d->lewy;
        return "nastepny element to " + d->klucz;
    }
    while (d->przodek) {
        if (d->przodek->lewy == d) {
            d = d->przodek;
            return "nastepny element to " + d->klucz;
        }
        else
            d = d->przodek;
    }
    return "nastepny element nie istnieje";
}
string Dszukaj(drzewo d, string i) {
    int glebokosc = 0;
    while (d) {
        if ((d)->klucz > i)
            d = d->lewy;
        else if (d->klucz < i)
            d = d->prawy;
        else
            return "znaleziono poszukiwany element na glebokosci "+to_string(glebokosc);
        glebokosc++;
    }
    return "nie znaleziono elementu";
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
string zapisz(drzewo d, int glebokosc, int strona) {
    if (d == NULL) {
        return "";
    }
    ofstream plik("lista.txt", ofstream::app);
    if (d && d->przodek == NULL) {
        plik.close();
        plik.open("lista.txt");
    }
    plik << d->klucz << "\n";
    plik << glebokosc << "\n";
    plik << strona << "\n";
    plik.close();
    zapisz(d->lewy, glebokosc+1, 0);
    zapisz(d->prawy, glebokosc+1, 1);
    return "Drzewo zapisano do pliku";
}
string wczytaj(drzewo* d) {
    drzewo start = *d;
    ifstream plik("lista.txt");
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
    int wybor = 0;
    string klucz = "", komunikat = "";
    while (1) {
        cout << "Elementy listy sa indeksowane od 1 w zwyz!\nwybierz operacje \n"
            << "1 - dodaj element do drzewa \n"
            << "2 - usun element z drzewa \n"
            << "3 - znajdz element minimalny\n"
            << "4 - znajdz element maksymalny\n"
            << "5 - znajdz element poprzedni\n"
            << "6 - znajdz element nastepny\n"
            << "7 - znajdz element o wartosci\n"
            << "8 - wyswietl zawartosc drzewa\n"
            << "9 - wczytaj drzewo z pliku\n"
            << "10 - zapisz drzewo do pliku\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat = DDD(&d, klucz);
            break;
        case 2:
            cout << "podaj wartosc elementu ktory chcesz usunac: ";
            cin >> klucz;
            komunikat = UZD(&d, klucz);
            break;
        case 3:
            komunikat = Dmin(d);
            break;
        case 4:
            komunikat = Dmax(d);
            break;
        case 5:
            komunikat = Dpop(d);
            break;
        case 6:
            komunikat = Dnast(d);
            break;
        case 7:
            cout << "podaj wartosc szukanego elementu ";
            cin >> klucz;
            komunikat = Dszukaj(d, klucz);
            break;
        case 8:
            komunikat = Pokaz(d, "");
            break;
        case 9:
            komunikat = wczytaj(&d);
            Dtop(&d);
            break;
        case 10:
            komunikat = zapisz(d, 0, 0);
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