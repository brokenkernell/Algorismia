#include <iostream>
#include <vector>
using namespace std;

using VE = vector<int>;
using Matriu = vector<VE>;

int n, k;
Matriu M(101, VE(101, -1));

long long binomial (int n, int k) {
    if(M[n][k] != -1) return M[n][k];
    if (k == 0 or n == k) return M[n][k] = 1;
    return M[n][k] = binomial(n-1,k-1) + binomial(n-1,k);
}
int main() {
    while (cin >> n >> k) cout << binomial(n,k) << endl;
}
