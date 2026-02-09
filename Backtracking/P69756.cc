#include <iostream>
#include <string>
#include <vector>
using namespace std;

using VE = vector<int>;
using VC = vector<char>;

VE V, U;
int n, k;
void escriu() {
	for (int i = 0; i < n; ++i) cout << (i ? "," : "(") << V[i] + 1;
	cout << ")" << endl;
}

void g (int m, int p) {
	if ( m == n) return escriu();
	int pos = 0;
	for (int i = 0; i < n; ++i) {
		if (not U[i]) {
			int suma = ((n - m - 1)*(n - m- 2))/2;
			if (p + pos <= k and p + pos + suma >= k) {
				V[m] = i;
				U[i] = 1;
				g(m+1, p+pos);
				U[i] = 0;
			}
			++pos;
		}
	}
}

int main () {
	cin >> n >> k;
	V = VE(n);
	U = VE(n, 0);
	g(0, 0);
}
