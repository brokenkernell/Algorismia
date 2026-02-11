#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    vector <long long> p(68, 0);
    p[0] = 1;
    for (int i = 2; i < 68; i += 2) {
        for (int j = 0; j < i; ++j) p[i] += p[j]*p[i-2-j];
    }
    int n;
    while (cin >> n) cout << p[n] << endl;
}
