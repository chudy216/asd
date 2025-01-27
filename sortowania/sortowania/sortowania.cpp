#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
struct Dane {
    int zapytania;
    int przestawienia;
    double czas;
};

Dane babelkowa(vector<int> tab, int N){
    cout << "sortowanie babelkowe dla probki " << N << endl;
    Dane *dane = new Dane;
    dane->zapytania = 0;
    dane->przestawienia = 0;
    dane->czas = 0;
    clock_t x = clock();
    int a, b;
    for (int i = 1; i < N; i++) {
        for (int j = N-1; j >= i; j--) {
            a = tab[j-1];
            b = tab[j];
            if (a > b) {
                tab[j-1] = b;
                tab[j] = a;
                dane->przestawienia++;
            }
            dane->zapytania++;
        }
    }
    clock_t x2 = clock();
    dane->czas = double(x2 - x) / CLOCKS_PER_SEC;
    cout << "czas to " << dane->czas << " sekund." << endl;
    return *dane;
}

Dane wstawianie(vector<int> tab, int N){
    cout << "sortowanie przez wstawianie dla probki " << N << endl;
    Dane* dane = new Dane;
    dane->zapytania = 0;
    dane->przestawienia = 0;
    dane->czas = 0;
    clock_t x = clock();
    int a, j;
    for (int i = 1; i < N; i++) {
        for (j = i; j > 0 && tab[j-1] > tab[j]; j--) {
            dane->przestawienia++;
            dane->zapytania++;
            a = tab[j];
            tab[j] = tab[j-1];
            tab[j-1] = a;
        }
        if (j > 0)
            dane->zapytania++;
    }
    clock_t x2 = clock();
    dane->czas = double(x2 - x) / CLOCKS_PER_SEC;
    cout << "czas to " << dane->czas << " sekund." << endl;
    return *dane;
}
Dane shella(vector<int> tab, int N){
    cout << "sortowanie shella dla probki " << N << endl;
    Dane* dane = new Dane;
    dane->zapytania = 0;
    dane->przestawienia = 0;
    dane->czas = 0;
    clock_t x = clock();
    int i, j, a, b;
    b = N / 2;
    while (b >= 1) {
        /*for (int i = 0; i < N - b ; i++) {
            for (int j = 0; j < N - b - i; j+=b) {
                if (tab[j] > tab[j + b]) {
                    a = tab[j];
                    tab[j] = tab[j + b];
                    tab[j + b] = a;
                    dane->przestawienia++;
                }
                dane->zapytania++;
            }
        }*/
        for (int i = 0; i < N-b; i++) {
            for (int j = N - 1; j-b >= i; j-=b) {
                a = tab[j - b];
                if (a > tab[j]) {
                    tab[j - b] = tab[j];
                    tab[j] = a;
                    dane->przestawienia++;
                }
                dane->zapytania++;
            }
        }
        b /= 2;
    }
    clock_t x2 = clock();
    dane->czas = double(x2 - x) / CLOCKS_PER_SEC;
    cout << "czas to " << dane->czas << " sekund." << endl;
    return *dane;
}

int partition(vector<int>& array, int low, int high, Dane* dane) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            dane->przestawienia++;
            swap(array[i], array[j]);
        }
        dane->zapytania++;
    }
    swap(array[i + 1], array[high]);
    return (i + 1);
}

void quicksort(vector<int>& tab, int low, int high, Dane* dane){
    if (low < high) {
        int pi = partition(tab, low, high, dane);
        quicksort(tab, low, pi - 1, dane);
        quicksort(tab, pi + 1, high, dane);
    }
}

Dane quick(vector<int> tab, int N) {
    cout << "sortowanie quicksort dla probki " << N << endl;
    Dane* dane = new Dane;
    dane->zapytania = 0;
    dane->przestawienia = 0;
    dane->czas = 0;
    clock_t x = clock();
    int low = 0, high = N - 1;
    quicksort(tab, low, high, dane);
    clock_t x2 = clock();
    dane->czas = double(x2 - x) / CLOCKS_PER_SEC;
    cout << "czas to " << dane->czas << " sekund." << endl;
    return *dane;
}
Dane zliczanie(vector<int> tab, int N, int maks) {
    cout << "sortowanie przez zliczanie dla probki " << N << endl;
    Dane* dane = new Dane;
    dane->zapytania = 0;
    dane->przestawienia = 0;
    dane->czas = 0;
    clock_t x = clock();
    vector<int> B, C;
    for (int i = 0; i < maks; i++)
        C.push_back(0);
    for (int i = 0; i < N; i++) {
        B.push_back(0);
        C[tab[i]]++;
    }
    for (int i = 1; i < maks; i++) {
        C[i] += C[i - 1];
    }
    for (int i = 0; i < N; i++) {
        B[--C[tab[i]]] = tab[i];
    }
    clock_t x2 = clock();
    dane->czas = double(x2 - x) / CLOCKS_PER_SEC;
    cout << "czas to " << dane->czas << " sekund." << endl;
    return *dane;
}
void min(Dane** min, Dane* akt) {
    if (*min == NULL) {
        Dane* n = new Dane;
        n->czas = akt->czas;
        n->przestawienia = akt->przestawienia;
        n->zapytania = akt->zapytania;
        *min = n;
        return;
    }
    if ((*min)->czas > akt->czas)
        (*min)->czas = akt->czas;
    if ((*min)->przestawienia > akt->przestawienia)
        (*min)->przestawienia = akt->przestawienia;
    if ((*min)->zapytania > akt->zapytania)
        (*min)->zapytania = akt->zapytania;
}
void maks(Dane** maks, Dane* akt) {
    if (*maks == NULL) {
        Dane *n = new Dane;
        n->czas = akt->czas;
        n->przestawienia = akt->przestawienia;
        n->zapytania = akt->zapytania;
        *maks = n;
        return;
    }
    if ((*maks)->czas < akt->czas)
        (*maks)->czas = akt->czas;
    if ((*maks)->przestawienia < akt->przestawienia)
        (*maks)->przestawienia = akt->przestawienia;
    if ((*maks)->zapytania < akt->zapytania)
        (*maks)->zapytania = akt->zapytania;
}
void avg(Dane** avg, Dane* akt, int i) {
    if (*avg == NULL) {
        Dane* n = new Dane;
        n->czas = akt->czas;
        n->przestawienia = akt->przestawienia;
        n->zapytania = akt->zapytania;
        *avg = n;
        return;
    }
    (*avg)->czas = ((*avg)->czas * i + akt->czas) / (i+1);
    (*avg)->zapytania = ((*avg)->zapytania * i + akt->zapytania) / (i+1);
    (*avg)->przestawienia = ((*avg)->przestawienia * i + akt->przestawienia) / (i+1);
}
int main() {
    srand(time(NULL));
    int M = rand() % 100 + 950;
    int maks_int = 100000;
    //maks_int = 100;
    //M = 10;
    Dane* babelkowe_min = NULL;
    Dane* babelkowe_avg = NULL;
    Dane* babelkowe_maks = NULL;
    Dane *babelkowe_now = new Dane;
    Dane* wstawianie_min = NULL;
    Dane* wstawianie_avg = NULL;
    Dane* wstawianie_maks = NULL;
    Dane* wstawianie_now = new Dane;
    Dane* shella_min = NULL;
    Dane* shella_avg = NULL;
    Dane* shella_maks = NULL;
    Dane* shella_now = new Dane;
    Dane* quick_now = new Dane;
    Dane* quick_min = NULL;
    Dane* quick_avg = NULL;
    Dane* quick_maks = NULL;
    Dane* zliczanie_min = NULL;
    Dane* zliczanie_avg = NULL;
    Dane* zliczanie_maks = NULL;
    Dane* zliczanie_now = new Dane;
    for (int i = 0; i < M; i++) {
        int N = rand() % 1000 + 9500;
        //N = 100;
        vector<int> tab;
        for (int j = 0;j < N;j++) {
            tab.push_back(rand() % maks_int);
        }
        cout << "zestaw " << i+1 << " z " << M << endl;
        *babelkowe_now = babelkowa(tab, N);
        *wstawianie_now = wstawianie(tab, N);
        *shella_now = shella(tab, N);
        *quick_now = quick(tab, N);
        *zliczanie_now = zliczanie(tab, N, maks_int);
        cout << "\n";
        min(&babelkowe_min, babelkowe_now);
        maks(&babelkowe_maks, babelkowe_now);
        avg(&babelkowe_avg, babelkowe_now, i);
        min(&wstawianie_min, wstawianie_now);
        maks(&wstawianie_maks, wstawianie_now);
        avg(&wstawianie_avg, wstawianie_now, i);
        min(&shella_min, shella_now);
        maks(&shella_maks, shella_now);
        avg(&shella_avg, shella_now, i);
        min(&quick_min, quick_now);
        maks(&quick_maks, quick_now);
        avg(&quick_avg, quick_now, i);
        min(&zliczanie_min, zliczanie_now);
        maks(&zliczanie_maks, zliczanie_now);
        avg(&zliczanie_avg, zliczanie_now, i);
    }
    system("cls");
    cout << "sortowanie babelkowe: " << endl;
    cout << "minimum    liczba przestawien: " << babelkowe_min->przestawienia << " liczba zapytan: " << babelkowe_min->zapytania << " czas: " << babelkowe_min->czas << endl;
    cout << "srednia    liczba przestawien: " << babelkowe_avg->przestawienia << " liczba zapytan: " << babelkowe_avg->zapytania << " czas: " << babelkowe_avg->czas << endl;
    cout << "maksimum    liczba przestawien: " << babelkowe_maks->przestawienia << " liczba zapytan: " << babelkowe_maks->zapytania << " czas: " << babelkowe_maks->czas << endl;
    cout << "\nsortowanie przez wstawianie "<< endl;
    cout << "minimum    liczba przestawien: " << wstawianie_min->przestawienia << " liczba zapytan: " << wstawianie_min->zapytania << "czas: " << wstawianie_min->czas << endl;
    cout << "srednia    liczba przestawien: " << wstawianie_avg->przestawienia << " liczba zapytan: " << wstawianie_avg->zapytania << "czas: " << wstawianie_avg->czas << endl;
    cout << "maksimum    liczba przestawien: " << wstawianie_maks->przestawienia << " liczba zapytan: " << wstawianie_maks->zapytania << "czas: " << wstawianie_maks->czas << endl;
    cout << "\nsortowanie shella " << endl;
    cout << "minimum    liczba przestawien: " << shella_min->przestawienia << " liczba zapytan: " << shella_min->zapytania << " czas: " << shella_min->czas << endl;
    cout << "srednia    liczba przestawien: " << shella_avg->przestawienia << " liczba zapytan: " << shella_avg->zapytania << " czas: " << shella_avg->czas << endl;
    cout << "maksimum    liczba przestawien: " << shella_maks->przestawienia << " liczba zapytan: " << shella_maks->zapytania << " czas: " << shella_maks->czas << endl;
    cout << "\nsortowanie quicksort " << endl;
    cout << "minimum    liczba przestawien: " << quick_min->przestawienia << " liczba zapytan: " << quick_min->zapytania << " czas: " << quick_min->czas << endl;
    cout << "srednia    liczba przestawien: " << quick_avg->przestawienia << " liczba zapytan: " << quick_avg->zapytania << " czas: " << quick_avg->czas << endl;
    cout << "maksimum    liczba przestawien: " << quick_maks->przestawienia << " liczba zapytan: " << quick_maks->zapytania << " czas: " << quick_maks->czas << endl;
    cout << "\nsortowanie przez zliczanie ( tylko czas) " << endl;
    cout << "minimum    czas: " << zliczanie_min->czas << endl;
    cout << "srednia    czas: " << zliczanie_avg->czas << endl;
    cout << "maksimum    liczba przestawien: czas: " << zliczanie_maks->czas << endl;

}
