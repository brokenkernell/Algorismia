#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;

VE V, U;
int valors;
long long n;
string m;
bool trobat;

void escriu() {
	trobat = true;
	cout << n << " = " << m[0] - '0';
	for (int j = 1; j < valors; ++j) cout << (V[j] ? " + " : "") << m[j] - '0';
	cout << endl;
}

void g (int p, int k, int s) {
	if (p == valors) {
		if (k+s == n) escriu();
		return;
	}
	if (k+s > n) return;
	int valor = m[p] - '0';
	if (p == 0) return g(1, 0, valor);
	V[p] = 1;
	g(p+1,s+k,valor);
	V[p] = 0;
	g(p+1,k,10*s+valor);
}

int main () {
	while (cin >> n >> m) {
		valors = m.size();
		V = VE(valors);
		trobat = false;
		g(0,0,0);
		if (not trobat) cout << "No solution for " << n << " " << m << "." << endl;
	}
}
