#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;

VE V, col, diag1, diag2;
int n;
bool trobat = false;

void escriu() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) cout << (V[i] == j ? "Q" : ".");
		cout << endl;
	}
}

void g (int m) {
	if (m == n and not trobat) {
		trobat = true;
		return escriu();
	}
	for (int i = 0; i < n and not trobat; ++i) {
		if (not col[i] and not diag1[m+i] and not diag2[m-i+n-1]) {
			V[m] = i;
			col[i] = diag1[m+i] = diag2[m-i+n-1] = 1;
			 g(m+1);
			col[i] = diag1[m+i] = diag2[m-i+n-1] = 0;
		}
	}
}

int main () {
	cin >> n;
	V = VE(n);
	col = VE(n, 0);
	diag1 = diag2 = VE(2*n -1, 0);
	g(0);
	if (not trobat) cout << "NO SOLUTION" << endl;
}
