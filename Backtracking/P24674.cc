#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VS = vector<string>;

VE V, U;
VS par;
int n;

void escriu() {
	for (int i = 0; i < n; ++i) cout << (i ? "," : "(") << par[V[i]];
	cout << ")" << endl;
}

void f (int m) {
	if (m == n) return escriu();
	for (int i = 0; i < n; ++i) {
		if (not U[i]) {
			V[m] = i;
			U[i] = 1;
			f(m+1);
			U[i] = 0;
		}
	}
}

int main () {
	cin >> n;
	V = VE(n);
	U = VE(n, 0);
	par = VS(n);
	for ( int i = 0; i < n; ++i) cin >> par[i];
	f(0);
}
