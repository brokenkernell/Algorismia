#include<iostream>
#include<map>
using namespace std;


int main() {
    map<string, int> casino;
    string nom, accio;
    while (cin >> nom >> accio) {
        auto it = casino.find(nom);
        if (accio == "enters") {
            if (it == casino.end()) casino[nom];
            else cout << nom << " is already in the casino" << endl;
        }
        else if (accio == "leaves") {
            if (it != casino.end()) {
                cout << nom << " has won " << it -> second << endl;
                casino.erase(nom);
            }
            else cout << nom << " is not in the casino" << endl;
            }
        else {
            int n;
            cin >> n;
            if (it != casino.end()) it -> second += n;
            else cout << nom << " is not in the casino" << endl;
        }
    }
    cout << "----------" << endl;
    for (auto it = casino.begin(); it != casino.end(); ++it) {
        cout << it -> first << " is winning " << it -> second << endl;
    }
}
