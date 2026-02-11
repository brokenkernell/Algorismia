#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VS = vector<string>;
using Matriu = vector<VE>;

Matriu nombres;
VE abecedari(26, 1);
VS lletres;

int f (int i, int j) {
    nombres[i][j] = nombres[i-1][j] + nombres[i][j-1] - nombres[i-1][j-1];
    return nombres[i][j] += abecedari[lletres[i-1][j-1] - 'A'];
}

int main() {
    string s;
    while (cin >> s) lletres.push_back(s);
    int r = lletres.size();
    int c = lletres[0].size();
    nombres = Matriu(r+1, VE(c+1, 0));
    for (int i = 1; i < 26; ++i) abecedari[i] += abecedari[i-1] + i;
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j < c; ++j) cout << f(i,j) << " ";
        cout << f(i,c) << endl;
    }
}
