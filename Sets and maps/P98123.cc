#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main () {
    int n;
    cin >> n;
    set <long long> grans;
    set <long long> petites;
    
    long long robar = 0;
    string s;
    long long joia;
    
    while (cin >> s >> joia) {
        if (s == "deixar") {
            if (grans.size() < n) {
                grans.insert(-joia);
                robar += joia;
            }
            
            else if (joia > -*grans.rbegin()) {
                robar += joia + *grans.rbegin();
                petites.insert(*grans.rbegin());
                grans.erase(*grans.rbegin());
                grans.insert(-joia);
            }
            else petites.insert(-joia);
        }
        else {
            if (petites.size() == 0) {
                grans.erase(-joia);
                robar -= joia;
            }
            else if (grans.find(-joia) != grans.end()) {
                robar -= *petites.begin() + joia;
                grans.erase(-joia);
                grans.insert(*petites.begin());
                petites.erase(*petites.begin());
            }
            else petites.erase(-joia);
        }
        cout << robar << endl;
    }
}
