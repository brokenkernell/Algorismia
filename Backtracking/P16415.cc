#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VC = vector<char>;

VE V, col, diag1, diag2;
int n;

void escriu() {
}

int g (int m) {
	if (m == n) return 1;
	int tot = 0;
	for (int i = 0; i < n; ++i) {
		if (not col[i] and not diag1[m+i] and not diag2[m-i+n-1]) {
			V[m] = i;
			col[i] = diag1[m+i] = diag2[m-i+n-1] = 1;
			tot += g(m+1);
			col[i] = diag1[m+i] = diag2[m-i+n-1] = 0;
		}
	}
	return tot;
}

int main () {
	cin >> n;
	V = VE(n);
	col = VE(n, 0);
	diag1 = diag2 = VE(2*n -1, 0);
	cout << g(0) << endl;
}
