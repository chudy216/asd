#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
struct el {
    int odleglosc;
    int wierzcholek;
    struct el* nast;
};
typedef struct el elListy;
typedef elListy* lista;

bool OEL(lista l, int i) {
    while (l) {
        if (l->wierzcholek == i) {
            return true;
        }
        else
            l = l->nast;
    }
    return false;
}
string DNPL(lista* l, int i, int j)
{
    if (OEL(*l, i))
        return "krawedz juz istnieje";
    lista p = (lista)malloc(sizeof(elListy));
    p->wierzcholek = i;
    p->nast = *l;
    p->odleglosc = j;
    *l = p;
    return "poprawnie dodano wartosc na poczatek listy";
}
string wyswietl(lista l) {
    string komunikat = "odleglosc: [ ";
    string komunikat2 = "] sasiad: [ ";
    while (l) {
        komunikat += to_string(l->odleglosc) + " ";
        komunikat2 += to_string(l->wierzcholek) + " ";
        l = l->nast;
    }
    komunikat2 += "]";
    komunikat += komunikat2;
    cout << komunikat << endl;
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
    while ((*l)->nast)
        l = &(*l)->nast;
    free(*l);
    *l = 0;
    return "poprawnie usunieto wartosc z konca listy";
}
string UWE(lista* l, int n) {
    while (*l) {
        if ((*l)->wierzcholek == n) {
            UPL(l);
            return "poprawnie usunieto element o wartosci " + to_string(n);
        }
        else
            l = &(*l)->nast;
    }
    return "szukany element nie zostal znaleziony";
}

void zapiszGraf(const vector<lista>& graf) {
    ofstream plik("graf.txt");
    if (!plik) {
        cerr << "Błąd przy otwieraniu pliku do zapisu!" << endl;
        return;
    }
    for (int i = 0; i < graf.size(); ++i) {
        lista l = graf[i];
        plik << i << ": ";
        while (l) {
            plik << "(" << l->wierzcholek << ", " << l->odleglosc << ") ";
            l = l->nast;
        }
        plik << endl;
    }

    plik.close();
    cout << "Graf zapisany do pliku: " << endl;
}
void wczytajGraf(vector<lista>& graf) {
    ifstream plik("graf.txt");
    int wierzcholek, sasiad, waga;
    string linia;
    while (getline(plik, linia)) {
        stringstream ss(linia);
        ss >> wierzcholek;
        while (graf.size() <= wierzcholek) {
            graf.push_back(nullptr);
        }
        char ch;
        ss >> ch;
        while (ss >> ch) {
            if (ch == '(') {
                ss >> sasiad >> ch >> waga >> ch;
                if (ch == ')') {
                    DNPL(&graf[wierzcholek], sasiad, waga);
                }
            }
        }
    }

    plik.close();
    cout << "Graf wczytany z pliku." << endl;
}

string DDL(lista* l, int i, int j)
{
    while (*l && j >= (*l)->odleglosc) {
        l = &(*l)->nast;
    }
    lista p = (lista)malloc(sizeof(elListy));
    p->wierzcholek = i;
    p->odleglosc = j;
    p->nast = *l;
    *l = p;
    return "poprawnie dodano wartosc do listy";
}
bool Zmien_prior(lista* l, int i, int j) {
    int x = 0;
    lista pop = 0;
    lista start = *l;
    while (*l) {
        x++;
        if ((*l)->wierzcholek == i) {
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
            return true;
        }
        else
            pop = *l;
        *l = (*l)->nast;
    }
    *l = start;
    return false;
}
string Pobierz(lista* l, lista* el) {
    lista* i = l;
    if (*l == NULL)
        return "kolejka jest pusta";
    int max = (*l)->odleglosc;
    lista p = (lista)malloc(sizeof(elListy));
    p->wierzcholek = (*l)->wierzcholek;
    p->odleglosc = (*l)->odleglosc;
    p->nast = NULL;
    UPL(l);
    *el = p;
    return "element z najwyzszym priorytetem " + to_string(p->odleglosc) + " ma wartosc " + to_string(p->wierzcholek);
}
void Dijkstry(vector<lista> graf) {
    int n = graf.size();
    vector<int> odleglosc(n, INT16_MAX);
    vector<int> skad(n, 0);
    lista kolejka = 0;
    DDL(&kolejka, 0, 0);
    for (int i = 1; i < n; i++) {
        DDL(&kolejka, i, INT16_MAX);
    }
    int pop = 0;
    while (kolejka) {
        lista el = 0;
        Pobierz(&kolejka, &el);
        odleglosc[el->wierzcholek] = el->odleglosc;
        lista l = graf[el->wierzcholek];
        while (l) {
            if (Zmien_prior(&kolejka, l->wierzcholek, l->odleglosc))
                skad[l->wierzcholek] = el->wierzcholek;
            l = l->nast;
        }
        
    }
    for (int i = 0; i < n; i++) {
        if (odleglosc[i] == 0)
            cout << "wierzcholek " << i << " to wierzcholek startowy" << endl;
        else if (odleglosc[i] == INT16_MAX)
            cout << "do wierzcholka nr " << i << " nie mozna sie dostac" << endl;
        else
            cout << "Wierzcholek " << i << " mozna osiagnac kosztem " << odleglosc[i] << " z wierzcholka nr " << skad[i] << endl;
    }
    return;
}
int main()
{
    vector <lista> graf;
    int wybor = 0;
    int klucz = 0;
    int numer = 0;
    int wierzcholek = -1;
    string komunikat = "";
    int i = 0;
    while (1) {
        cout << "Elementy listy sa indeksowane od 1 w zwyz!\nwybierz operacje \n"
            << "1 - dodaj wierzcholek \n"
            << "2 - usun wierzcholek \n"
            << "3 - operacje dla wierzcholka\n"
            << "4 - zapisz graf\n"
            << "5 - wczytaj graf\n"
            << "6 - wyswietl graf\n"
            << "7 - algorytm wyznaczania najkrotszych sciezek\n"
            << "0 - zakoncz dzialanie programu\n";
        cin >> wybor;
        system("cls");
        switch (wybor) {
        case 0:
            return 0;
        case 1:
            graf.push_back(0);
            break;
        case 2:
            cout << "podaj numer wierzcholka do usuniecia: ";
            cin >> numer;
            if (numer > 0 && numer <= graf.size());
            graf.erase(graf.begin() + numer-1);
            break;
        case 3:
            cout << "podaj numer wierzcholka dla ktorego chcesz dzialac: ";
            cin >> wierzcholek;
            if (--wierzcholek >= graf.size() || wierzcholek < 0)
                komunikat = "niepoprawny wierzcholek";
            system("cls");
            break;
        case 4:
            zapiszGraf(graf);
            break;
        case 5:
            wczytajGraf(graf);
            break;
        case 6:
             for(i = 0; i < graf.size(); i++)
                 wyswietl(graf[i]);
            break;
        case 7:
            Dijkstry(graf);
            break;
        default:
            komunikat = "prosze wybrac poprawna wartosc";
    }
        cout << komunikat;
        komunikat = "";
        while (wierzcholek >= 0) {
            lista l = graf[wierzcholek];
            cout << "Elementy listy sa indeksowane od 1 w zwyz!\nwybierz operacje \n"
                << "1 - dodaj krawedz \n"
                << "2 - usun osatnio dodana krawedz \n"
                << "3 - usun pierwsza dodana krawedz \n"
                << "4 - odszukaj czy krawedz istnieje \n"
                << "5 - usun wskazana krawedz\n"
                << "6 - wyswietl liste sasiadow\n"
                << "0 - zakoncz dzialanie dla wierzcholka\n";
            cin >> wybor;
            switch (wybor) {
            case 0:
                wierzcholek = -1;
                break;
            case 1:
                cout << "podaj do ktorego wierzcholka chcesz dodac krawedz: ";
                cin >> klucz;
                if (klucz > graf.size()) {
                    komunikat = "wierzcholek nie istnieje";
                    break;
                }
                cout << "podaj odleglosc ";
                cin >> numer;
                komunikat = DNPL(&l, klucz, numer);
                break;
            case 2:
                komunikat = UPL(&l);
                break;
            case 3:
                komunikat = UKL(&l);
                break;
            case 4:
                cout << "podaj numer szukanego wierzcholka: ";
                cin >> klucz;
                komunikat = OEL(l, klucz) ? "wierzcholek jest sasiadem" : "wierzcholek nie jest sasiadem";
                break;
            case 5:
                cout << "podaj numer szukanego wierzcholka: ";
                cin >> numer;
                komunikat = UWE(&l, numer);
                break;
            case 6:
                komunikat = wyswietl(l);
                break;
            default:
                komunikat = "prosze wybrac poprawna wartosc";
            }
            if(wierzcholek>=0)
                graf[wierzcholek] = l;
            system("cls");
            cout << komunikat + "\n";
            komunikat = "";
        }
    }
    return 0;
}

