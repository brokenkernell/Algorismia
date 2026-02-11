#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using Matriu = vector<VE>;

Matriu  S, fil, col, quad;

void escriu() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) cout << (j ? " " : "") << S[i][j];
		cout << endl;
	}
}

bool g (int f, int c) {
	if (f == 9) return true;
	if (c == 9) return g(f+1,0);
	if (S[f][c]) return g(f,c+1);
	for (int i = 1; i <= 9; ++i) {
		int p = 3*(f/3) + c/3;
		if (fil[f][i-1] and col[c][i-1] and quad[p][i-1]) {
			S[f][c] = i;
			fil[f][i-1] = col[c][i-1] = quad[p][i-1] = 0;
			if (g(f,c+1)) return true;
			S[f][c] = 0;
			fil[f][i-1] = col[c][i-1] = quad[p][i-1] = 1;
		}
	}			
	return false;
}

int main () {
	int n;
	cin >> n;
	cout << n << endl << endl;
	while (n--) {
		S = Matriu(9, VE(9,0));
		fil = col = quad = Matriu(9, VE(9,1));
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				char c;
				cin >> c;
				if ( c!= '.') {
					S[i][j] = c - '0';
					fil[i][S[i][j]-1] = col[j][S[i][j]-1] = 0;
					quad[(i/3)*3 + j/3][S[i][j]-1] = 0;
				}
			}
		}
		if (g(0,0)) escriu();
		if (n > 0) cout << endl;
	}
}
