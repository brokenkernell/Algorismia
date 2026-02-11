#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;

string paraula;
int n;
VE V;

int f(int p) {
    if (V[p] != -1) return V[p];
    int aux = 0;
    for (int i = p+1; i < n; ++i) {
        if (paraula[i] > paraula[p]) aux += 1 + f(i);
    }
    return V[p] = aux;
}

int main () {
    while (cin >> paraula) {
        n = paraula.size();
        V = VE(n, -1);
        int aux = 0;
        for (int i = 0; i < n; ++i) aux += f(i);
        cout << aux << endl;
    }
}
