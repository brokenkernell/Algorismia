#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VB = vector<bool>;
using VS = vector<string>;

VE V, col;
int f, c;

void escriu() {
	for (int i = 0; i < f; ++i) {
		for (int j = 0; j < c; ++j) cout << (V[i] == j ? "R" : ".");
		cout << endl;
	}
	cout << endl;
}

void g (int m) {
	if ( m == f) return escriu();
	for (int i = 0; i < c; ++i) {
		if (not col[i]) {
			V[m] = i;
			col[i] = 1;
			g(m+1);
			col[i] = 0;
		}
	}

}

int main () {
	cin >> f >> c;
	V = VE(f);
	col = VE(c, 0);
	g(0);
}
