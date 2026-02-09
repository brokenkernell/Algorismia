#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> Vec;

int n, t, x, y;
Vec V;

void escriu() {
	cout << "{";
	string coma = "";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < V[i]; ++j) {
			cout << coma << i+1;
			coma = ",";
		}
	}
	cout << "}" << endl;
}

void f(int m, int suma) {
	if (suma + (n-m)*x > t) return;
	if (suma + (n-m)*y < t) return;
	if (m == n) return escriu();
	for (int i = x; i <= y; ++i) {
		V[m] = i;
		f (m+1, suma+i);
	}
}

int main() {
  cin >> n >> x >> y >> t;
  V = Vec(n);
  f (0,0);
}
