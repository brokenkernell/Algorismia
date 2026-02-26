#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>
using namespace std;

using VS = vector<string>;
using VI = vector<int>;
using MI = vector<VI>;

//Direccions de moviment
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void resoldre_cas (int n, int m, VS& tauler) {
    MI dist(n, VI(m, -1));
    queue<pair<int, int>> cua;
    
    //Inicialitzem la distància per als tresors i obstacles
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (tauler[i][j] == 'T') {
                dist[i][j] = 0;
                cua.push({i,j});  //Posem els tresors com a inici del BFS
            }
            else if (tauler[i][j] == 'X') {
                dist[i][j] = -2; //Marquem els obstacles
            }
        }
    }
    
    //BFS per trobar la distància a un tresor
    while (!cua.empty()) {
        auto [x, y] = cua.front();
        cua.pop();
        
        //Explorem les direccions
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            //Comprovem que la nova posició sigui correcte
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && tauler[nx][ny] == '.' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                cua.push({nx, ny}); //Afegim la nova posició a la cua per continuar
            }
        }
    }
    
    //Escrivim les distàncies per aquest cas
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m-1; ++j) {
            cout << dist[i][j] << " ";
        }
        cout << dist[i][m-1] << endl;
    }
    cout << "----------" << endl;
}

int main () {
    int n, m;
    while (cin >> n >> m) {
        VS tauler(n);
        for (int i = 0; i < n; ++i) {
            cin >> tauler[i];
        }
        resoldre_cas(n, m, tauler);
    }
    return 0;
}
