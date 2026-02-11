#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using ME = vector<VE>;

string p1, p2;
ME comu;

bool petit (int i, int maxim, int max_i) {
    if (i == max_i) return false;
    for (int k = maxim; k > 0; --k) {
        if (p1[max_i - k + 1] > p1[i - k]) return true;
        if (p1[max_i - k + 1] < p1[i - k]) return false;
    }
    return false;
}

int main () {
    while (cin >> p1 >> p2) {
        int n1 = p1.size();
        int n2 = p2.size();
        comu = ME(n1 +1, VE(n2 +1, 0));
        int maxim = 0;
        int max_i = 0;
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
            if (p1[i-1] == p2[j-1]) comu[i][j] = 1 + comu[i-1][j-1];
            if (comu[i][j] > maxim) {
                maxim = comu[i][j];
                max_i = i - 1;
            }
            }
        }
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (comu[i][j] == maxim and petit(i, maxim, max_i)) max_i = i - 1;
            }
        }
        for (int i = maxim; i > 0; --i) cout << p1[max_i - i + 1];
        cout << endl;
    }
}
