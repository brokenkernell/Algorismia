#include <iostream>
#include <vector>
#include <set>
using namespace std;

using MS = multiset<string, greater<string> >;

int main () {
    string s;
    MS llista;
    MS::iterator med;
    int n = 1;
    while (cin >> s, s != "END") {
        llista.insert(s);
        if (n == 1) med = llista.begin();
        else {
            if (n%2 == 0)  {
                if(s <= *med) ++med;
            }
            else {
                if (s > *med) --med;
            }
        }
    cout << *med << endl;
    ++n;
    }
}
