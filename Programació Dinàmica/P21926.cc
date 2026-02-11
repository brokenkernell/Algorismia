#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using Matriu = vector<VE>;

int main() {
    int n, m;
    while (cin >> n >> m) {
        VE fib(n+1,0);
        fib[1] = 1;
        for (int i = 2; i <= n; ++i) fib[i] = (fib[i-1] + fib[i-2])%m;
        cout << fib[n] << endl;
    }
}
