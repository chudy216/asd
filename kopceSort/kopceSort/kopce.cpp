#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void zrobKopiec(vector<string>* tab, int i, int size) {
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int maks = i;
    if (l < size && (*tab)[l] > (*tab)[maks])
        maks = l;
    if (r < size && (*tab)[r] >(*tab)[maks])
        maks = r;
    if (maks != i) {
        string x = (*tab)[i];
        (*tab)[i] = (*tab)[maks];
        (*tab)[maks] = x;
        zrobKopiec(tab, maks, size);
    }
}
void sort(vector<string>* tab, int size) {
    for (int i = size - 1; i > 0; i--) {
        string x = (*tab)[0];
        (*tab)[0] = (*tab)[i];
        (*tab)[i] = x;
        zrobKopiec(tab, 0, i);
    }
}
string Pokaz(vector<string> tab, int i, int size, string prefix) {
    if (i >= size)
        return "";
    string komunikat = "";
    komunikat += prefix;
    if(i!=0)
        komunikat += "|__" + tab[i] + "\n";
    else
        komunikat += tab[i] + "\n";
    if (i%2 != 0)
        prefix += "|  ";
    else
        prefix += "   ";
    komunikat += Pokaz(tab, i * 2 + 1, size, prefix);
    komunikat += Pokaz(tab, i * 2 + 2, size, prefix);
    return komunikat;
}
char generateRandomChar() {
    int randValue = rand() % 62;
    if (randValue < 10) {
        return '0' + randValue;
    }
    else if (randValue < 36) {
        return 'A' + (randValue - 10);
    }
    else {
        return 'a' + (randValue - 36);
    }
}

int main() {
    srand(time(NULL));
    int n = rand() % 70 + 30;
    vector<string> tab;
    for (int i = 0; i < n; i++) {
        string a = "";
        int m = rand() % 30 + 10;
        for (int i = 0; i < m; i++) {
            a += generateRandomChar();
        }
        tab.push_back(a);
    }
    for (int i = (n - 1) / 2; i >= 0; i--)
         zrobKopiec(&tab, i, n);
    cout << "porzadek to [0-9] < [A-Z] < [a-z] \n\n";
    string komunikat = Pokaz(tab, 0, n, "");
    cout << "przed sortowaniem: \n"<<komunikat<<endl;
    sort(&tab, n);
    komunikat = Pokaz(tab, 0, n, "");
    cout << "po sortowaniu: \n"<<komunikat<<endl;
}
