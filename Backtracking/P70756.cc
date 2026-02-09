#include <iostream>
#include <vector>
#include <string>
using namespace std;

using VE = vector<int>;
using VS = vector <string>;

int n, p;
VE contingut;
VS particio;

void escriu () {
	for ( int j = 0; j <  p; ++j ) {
		cout << "subconjunt " << j+1 << ": ";
		cout << "{";
		
		bool primer = true;
		for ( int t = 0; t < n; ++t ) {
			if ( contingut[t] == j ) {
				if ( primer ) primer = false;
				else cout << ',';
				cout << particio[t];
			}
		}
		cout << "}";
		cout << endl;
	}
	cout << endl;
}

void f ( int i ) {
	if ( i == n ) escriu();
	else {
		for ( int k = 0; k < p; ++k ) {
			contingut[i] = k;
			f(i+1);
		}
	}

}

int main () {
	cin >> n;
	particio = VS(n);
	contingut = VE(n);
	
	for ( string& e : particio ) cin >> e;
	cin >> p;
	f(0);

}
