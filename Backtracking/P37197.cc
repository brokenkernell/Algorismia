#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VC = vector<char>;
using M = vector<VE>;

VE V, U;
VC esp;
int n, nprob;
M prob;

void escriu() {
	for (int i = 0; i < n; ++i) cout << esp[V[i]];
	cout << endl;
}

void g (int m) {
	if ( m == n) return escriu();
	for (int i = 0; i < n; ++i) {
		if (not U[i]and (m == 0 or prob[i][V[m - 1]])) {
			V[m] = i;
			U[i] = 1;
			g(m+1);
			U[i] = 0;
		}
	}

}
void f (char c1, char c2) {
	int especie1, especie2;
	for (int j = 0; j < n; ++j) {
		if (esp[j] == c1) especie1 = j;
		else if (esp[j] == c2) especie2 = j;
	}
	prob[especie1][especie2] = 0;
	prob[especie2][especie1] = 0;	
}

int main () {
	cin >> n;
	V = VE(n);
	U = VE(n, 0);
	esp = VC(n);
	prob = M(n, VE(n, 1));
	for (int i = 0; i < n; ++i) cin >> esp[i];
	cin >> nprob;
	for (int i = 0; i < nprob; ++i) {
		char c1, c2;
		cin >> c1 >> c2;
		f(c1, c2);
	}
	g(0);
}
