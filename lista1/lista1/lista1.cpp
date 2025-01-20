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

string DNPL(lista *l, int i)
{
    lista p = (lista)malloc(sizeof(elListy));
    p-> klucz = i;
    p-> nast = *l;
    *l = p;
    return "poprawnie dodano wartosc na poczatek listy";
}
string DNKL(lista* l, int i)
{
    while ((*l)) {
        l = &(*l)->nast;
    }
    DNPL(l, i);
    return "poprawnie dodano wartosc na koniec listy";
}
string wyswietl(lista l) {
    string komunikat = "[ ";
    while (l) {
        komunikat += to_string(l->klucz)+" ";
        l = l->nast;
    }
    komunikat += "]";
    return komunikat;
}
string wyswietl_kon(lista l) {
    string komunikat = "";
    while (l) {
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
    free(*l);
    *l = p;
    return "poprawnie usunieto wartosc z poczatku listy";
}
string UKL(lista* l) {
    if (*l == 0) return "lista byla pusta wiec nic nie usunieto";
    while ((*l)-> nast)
        l = &(*l)-> nast;
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
    DNPL(l, i);
    return "poprawnie dodano nowy element przed elementem numer " + to_string(n);
}
string DPWE(lista* l, int i, int n) {
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
string DZWE(lista* l, int i, int n) {
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
string DZEL(lista* l, int i, int n) {
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
string UEL(lista* l, int i) {
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
string IUWW(lista* l, int n) {
    int x = 0;
    while (*l) {
        if ((*l)->klucz == n) {
            UPL(l);
            x++;
        }
        else
            l = &(*l)->nast;
    }
    if(x==0)
    return "szukany element nie zostal znaleziony";
    return "usunieto wszystkie elementy o wartosci " + to_string(n);
}
string RUWW(lista* l, int n) {
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
string WNW(lista l) {
    map <int, int> lista;
    int max=0, num=0;
    while (l) {
        lista[l->klucz] += 1;
        l = l->nast;
    }
    for (const auto& n : lista)
        if (n.second > max)max = n.second, num = n.first;
    if (max)
        return "najczesciej wystepuje wartosc " + to_string(num) + ", wystapila " + to_string(max) + " razy";
    return "lista jest pusta";
}
string usunniepodz(lista* l, int k) {

    while (*l) {
        if ((*l)->klucz % k != 0) {
            UPL(l);
        }
        else
            l = &(*l)->nast;
    }

    return "usunieto wszystkie elementy niepodzielne przez " + to_string(k);
}
string IOL(lista* l) {
    lista n = 0, n2 = 0;
    if (*l) {
        n = (*l) -> nast;
        (*l)->nast = 0;
    }
    while (n) {
        n2 = n->nast;
        n->nast = *l;
        *l = n;
        n = n2;
    }
    return "liste odwrocono";
}
string ROL(lista* l, lista* pop) {
    lista temp = NULL;
    if (*l == NULL) {
        cout << "\n" << wyswietl(*pop);
        *l = *pop;
        return "lista zbyt krotka na odwracanie";
    }
    temp = (*l)->nast;
    (*l)->nast = (*pop);
    pop = l;
    l = &temp;
    cout << wyswietl(*pop);
    ROL(l, pop);
    return "lista odwrocona rekurencyjnie";
}

string wczytaj(lista* l) {
    int y = 0;
    ifstream plik("lista.txt");
    string lista, listafull = "", liczba="";
    while(getline(plik, lista)){
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
    return "odczytano liste "+wyswietl(*l);
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
            << "14 - usun wszystkie znalezione elementy iteracyjnie\n"
            << "15 - usun wszystkie znalezione elementy rekurencyjnie\n"
            << "16 - wyznacz wartosc wystepujaca najczesciej\n"
            << "17 - usun elementy niepodzielne przez podana wartosc\n"
            << "18 - odwroc liste iteracyjnie\n"
            << "19 - odwroc liste rekurencyjnie\n"
            << "20 - wczytaj liste z pliku\n"
            << "21 - zapisz liste do pliku\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            cout << "podaj wartosc dla nowego elementu: ";
            cin >> klucz;
            komunikat=DNPL(&l, klucz);
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
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            komunikat = IUWW(&l, numer);
            break;
        case 15:
            cout << "podaj wartosc szukanego elementu: ";
            cin >> numer;
            komunikat = RUWW(&l, numer);
            break;
        case 16:
            komunikat = WNW(l);
            break;
        case 17:
            cout << "podaj wartosc dzielenia elementu: ";
            cin >> numer;
            komunikat = usunniepodz(&l, numer);
            break;
        case 18:
            komunikat = IOL(&l);
            break;
        case 19:
            komunikat = ROL(&l, &p);
            break;
        case 20:
            komunikat = wczytaj(&l);
            break;
        case 21:
            komunikat = zapisz(l);
            break;
        default:
            komunikat = "prosze wybrac poprawna wartosc";
        }
        system("cls");
        cout << komunikat+"\n";
        komunikat = "";
    }
    return 0;
}

