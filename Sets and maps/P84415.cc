#include<iostream>
#include<map>
using namespace std;


int main() {
    map<string, int> bossa;
    string accio;
    while (cin >> accio) {
        if (accio == "minimum?") {
            auto it = bossa.begin();
            if (it == bossa.end()) cout << "indefinite minimum" << endl;
            else cout << "minimum: " << it -> first << ", " << it -> second << " time(s)" << endl;
        }
        else if (accio == "maximum?") {
            auto it = bossa.rbegin();
            if (it == bossa.rend()) cout << "indefinite maximum" << endl;
            else cout << "maximum: " << it -> first << ", " << it -> second << " time(s)" << endl;
        }
        else {
            string s;
            cin >> s;
            if (accio == "store") ++bossa[s];
            else {
                auto it = bossa.find(s);
                if (it != bossa.end()) {
                    it -> second -= 1;
                    if (it -> second == 0) bossa.erase(s);
                }
            }
        }
    }
}
