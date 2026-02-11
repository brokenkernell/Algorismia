#include<iostream>
#include<map>
#include<set>
#include<stack>
#include<queue>
using namespace std;


int main() {
    string accio, nom;
    map<string, int> jugadors;
    set<string> desconnectats;
    while (cin >> accio >> nom) {
        if (accio == "LOGIN") {
            auto it = jugadors.find(nom);
            if (it == jugadors.end()) jugadors[nom] = 1200;
            desconnectats.erase(nom);
        }
        else if (accio == "LOGOUT") desconnectats.insert(nom);
        else if (accio == "GET_ELO") {
            auto it = jugadors.find(nom);
            cout << nom << " " << it -> second << endl;
        }
        else {
            string nom2;
            cin >> nom2;
            auto it1 = jugadors.find(nom);
            auto it2 = jugadors.find(nom2);
            bool j1 = (desconnectats.find(nom) == desconnectats.end());
            bool j2 = (desconnectats.find(nom2) == desconnectats.end());
            if (j1 and j2 and it1 != jugadors.end() and it2 != jugadors.end()) {
                it1 -> second += 10;
                it2 -> second = max(1200, it2 -> second - 10);
            }
            else cout << "jugador(s) no connectat(s)" << endl;
        }
    }
    cout << endl << "RANKING" << endl;
    
    priority_queue<pair<int, string> > Q;
    for (auto it = jugadors.begin(); it != jugadors.end(); ++it) {
        Q.push({-it -> second, it -> first});
    }
    stack<pair<int, string> > S;
    while (!Q.empty()) { S.push({-Q.top().first, Q.top().second}); Q.pop(); }
    while (!S.empty()) { cout << S.top().second << " " << S.top().first << endl; S.pop(); }
}
