#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VC = vector<char>;

VE V, U, W;
int n;
void escriu() {
	for (int i = 0; i < n; ++i) cout << (i ? "," : "(") << V[i] + 1;
	cout << ")" << endl;
}

void g (int m, int p) {
	if ( p == n) return escriu();
	W[m] = 1;
	for (int i = 0; i < n; ++i) {
		if (not U[i] and (not W[i] or p == n -1)) {
			V[m] = i;
			U[i] = 1;
			g(i,p+1);
			U[i] = 0;
		}
	}
	W[m] = 0;
}

int main () {
	cin >> n;
	V = VE(n);
	U = VE(n, 0);
	W = VE(n, 0);
	g(0, 0);
}
