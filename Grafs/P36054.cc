#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using VP = vector<pair<int, pair<int, int> > >;
using VE = vector<int>;

VE pare;
VP arestes;

int busca (int i) {
    if (pare[i] == i) return i;
    pare[i] = busca(pare[i]);
    return pare[i];
}

void uneix (int a, int b) {
    pare[busca(a)] = busca(b);
}

int main () {
    int n, e;
    while (cin >> n >> e) {
        pare = VE(n);
        for (int i = 0; i < n; ++i) pare[i] = i;
        arestes = VP(e);
        for (int i = 0; i < e; ++i) cin >> arestes[i].second.first >> arestes[i].second.second >> arestes[i].first;
        sort(arestes.begin(), arestes.end());
        vector<bool> usat(e, false);
        for (int i = 0; i < e; ++i) {
            int a = arestes[i].second.first;
            int b = arestes[i].second.second;
            if (busca(a) != busca(b)) {
                uneix(a, b); usat[i] = true;
            }
        }
        int c = 0, m = 0, M = 0;
        for (int i = 0; i < e; ++i) {
            if (usat[i] or arestes[i].first < 0) { ++m; ++M; c += arestes[i].first;}
            else if (arestes[i].first == 0) ++M;
        }
        cout << c << ' ' << m << ' ' << M << endl;
    }
}

