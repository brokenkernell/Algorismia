#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;

int n;
VE V;
VE monedes = {1, 2, 5, 10, 20, 50};

void escriu() {
    for (int i = 0; i < V.size(); ++i) cout << (i ? " " : "") << V[i];
        cout << endl;
}

void g (int t, int j) {
    if (t == n) return escriu();
    for (int i = j; i >= 0; --i) {
        if (t + monedes[i] <= n) {
            V.push_back(monedes[i]);
            g(t + monedes[i],i);
            V.pop_back();
        }
    }
}

int main () {
    while (cin >> n) {
        g(0,5);
        cout << endl;
    }
}

