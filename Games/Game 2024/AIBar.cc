#include "Player.hh"

#define PLAYER_NAME Bar

struct PLAYER_NAME : public Player {
  const vector<Dir> dirsmag = {Down, Right, Up, Left};
  const vector<Dir> dirsfantasma = {Down, DR, Right, RU, Up, UL, Left, LD};
  
  static Player* factory () {
    return new PLAYER_NAME;

}

  int dist(const Pos& a, const Pos& b) const {
    int posx, posy;

    if (a.i > b.i) {
        posx = a.i - b.i;
    } else {
        posx = b.i - a.i;
    }

    if (a.j > b.j) {
        posy = a.j - b.j;
    } else {
        posy = b.j - a.j;
    }

    return posx + posy;
}



    bool voldemort_lejos(const Pos& pos) const {
    return dist(pos, pos_voldemort()) > 3;
}

    bool puedoir1(Pos obj) {
    Cell c = cell(obj);
    if (pos_ok(obj) and c.type == Corridor and voldemort_lejos(obj)) return true;
    return false;
}
    bool puedoir_bfs(Pos obj) {
    Cell c = cell(obj);
    if (pos_ok(obj) and c.type == Corridor) return true;
    return false;
}

bool puedoir(Pos obj) {
    Cell c = cell(obj);
    if (pos_ok(obj) and c.type == Corridor and voldemort_lejos(obj)) {
        if (c.id != -1) {
        Unit u = unit(c.id);
        if (u.type == Ghost) return false;

        if (u.player == me()) {
            if (u.is_in_conversion_process()) return true;
        }

        if (u.player != me()) {
            if (u.is_in_conversion_process()) return false;
            if (gano_yo(magic_strength(me()), magic_strength(u.player))) return true;
        }
        return false;
    }
    return true;
    }
    return false;
}

  bool haylibro(Pos ini, Dir& dir_libro, map<Pos, int>& vamos, int radio, int& dista) {
      queue<pair<Pos, Dir>> q;
      set<Pos> visited;
      visited.insert(ini);

      for (Dir d : dirsmag) {
          Pos obj = ini + d;
          if (puedoir_bfs(obj)) {
              q.push({obj, d});
              visited.insert(obj);
          }
      }

      while (!q.empty()) {
          pair<Pos, Dir> front = q.front();
          Pos act = front.first;
          Dir dnd = front.second;
          q.pop();

          if (cell(act).book and puedoir1(act)) {
            auto it = vamos.find(act);
            if (it == vamos.end()) {
                ++vamos[act];
            dir_libro = dnd;
            return true;
            }
            else {
                if (vamos[act] < 3) {
                     ++vamos[act];
            dir_libro = dnd;
             dista = dist(ini, act);
            return true;
                }
            }
            
          }

          for (Dir d : dirsmag) {
              Pos obj = act + d;
              if (puedoir_bfs(obj) and visited.find(obj) == visited.end() and dist(ini, obj) <= radio ) {
                  q.push({obj, dnd});
                  visited.insert(obj);
              }
          }
      }

      return false;
}

 bool haylibro2(Pos ini, Dir& dir_libro) {
      queue<pair<Pos, Dir>> q;
      set<Pos> visited;
      visited.insert(ini);

      for (Dir d : dirsfantasma) {
          Pos obj = ini + d;
          if (puedoir_bfs(obj)) {
              q.push({obj, d});
              visited.insert(obj);
          }
      }

      while (!q.empty()) {
          pair<Pos, Dir> front = q.front();
          Pos act = front.first;
          Dir dnd = front.second;
          q.pop();
       
          if (cell(act).book and puedoir1(act)) {
            dir_libro = dnd;
            return true;
          }

          for (Dir d : dirsfantasma) {
              Pos obj = act + d;
              if (puedoir_bfs(obj) and visited.find(obj) == visited.end()) {
                  q.push({obj, dnd});
                  visited.insert(obj);
              }
          }
      
      }

      return false;
}
bool es_mago_mas_fuerte_alrededor(Pos pos, int fuerza_yo, int radio) {
    queue<Pos> q;
    set<Pos> visited;
    visited.insert(pos);
    

    for (Dir d : dirsmag) {
        Pos obj = pos + d;
        if (puedoir_bfs(obj)) {
            q.push(obj);
            visited.insert(obj);
        }
    }

    while (!q.empty()) {
        Pos act = q.front();
        q.pop();
        
        Cell c = cell(act);
        int id = c.id;
         Unit enemy = unit(id);
        if (id != -1 and enemy.player != me()) {
             if (enemy.type ==  Wizard and !enemy.is_in_conversion_process()) {
              int fuerza_yo = magic_strength(me());
              int fuerza_el = magic_strength(enemy.player);
                if (!gano_yo(fuerza_yo, fuerza_el)) {
                     return true;
                }
             }
            
        }

        for (Dir d : dirsmag) {
            Pos obj = act + d;
            if (puedoir_bfs(obj) and visited.find(obj) == visited.end() and dist(pos, obj) <= radio) {
                q.push(obj);
                visited.insert(obj);
            }
        }
    }

    return false;
}
bool mago_aliado(Pos pos, int fuerza_yo, int radio, bool yo) {
    queue<Pos> q;
    set<Pos> visited;
    visited.insert(pos);
    int aliados = 0;
    for (Dir d : dirsmag) {
        Pos obj = pos + d;
        if (puedoir_bfs(obj)) {
            q.push(obj);
            visited.insert(obj);
        }
    }

    while (!q.empty()) {
        Pos act = q.front();
        q.pop();
        
        Cell c = cell(act);
        int id = c.id;
         Unit enemy = unit(id);
        if (id != -1 and enemy.player == me() and yo) {
             if (yo and enemy.type ==  Wizard and !enemy.is_in_conversion_process()) {
              ++aliados;
             }
            
        } else if (!yo and id != -1 and enemy.player == me() ) {
             if (enemy.type ==  Wizard and !enemy.is_in_conversion_process()) {
              ++aliados;
             }
            
        }
        if (aliados > 1) return true;
        for (Dir d : dirsmag) {
            Pos obj = act + d;
            if (puedoir_bfs(obj) and visited.find(obj) == visited.end() and dist(pos, obj) <= radio) {
                q.push(obj);
                visited.insert(obj);
            }
        }
    }

    return false;
}
bool hayenemigo(Pos ini, Dir& dir_enemic, int radio, int& dista) {
    queue<pair<Pos, Dir>> q;
    set<Pos> visited;
    visited.insert(ini);

    for (Dir d : dirsmag) {
        Pos obj = ini + d;
        if (puedoir_bfs(obj)) {
            q.push({obj, d});
            visited.insert(obj);
        }
    }

    while (!q.empty()) {
        pair<Pos, Dir> front = q.front();
        Pos act = front.first;
        Dir dnd = front.second;
        q.pop();
        if (dist(ini, act) <= radio) {
        Cell c = cell(act);
        int id = c.id;
        Unit enemy = unit(id);
        if (id != -1 and enemy.player != me()) {
             if (enemy.type ==  Wizard and !enemy.is_in_conversion_process()) {
              int fuerza_yo = magic_strength(me());
              int fuerza_el = magic_strength(enemy.player);
    
                    if (mago_aliado(ini, fuerza_yo, 5, true) or mago_aliado(act, fuerza_yo, 5, false)) {
                            dir_enemic = dnd;
                            dista = dist(ini, act);
                            return true;
                        }
                  
             }
            
        }
        
        for (Dir d : dirsmag) {
            Pos obj = act + d;
            if (puedoir_bfs(obj) and visited.find(obj) == visited.end()) {
                q.push({obj, dnd});
                visited.insert(obj);
            }
        }
    }
    }

    return false;
}
bool haymago(Pos ini, Dir& dir_mago,  Dir& dirres, bool conversion_process, int radio, bool& reserva) {
    queue<pair<Pos, Dir>> q;
    set<Pos> visited;
    visited.insert(ini);

    for (Dir d : dirsmag) {
        Pos obj = ini + d;
        if (puedoir_bfs(obj)) {
            q.push({obj, d});
            visited.insert(obj);
        }
    }

    while (!q.empty()) {
        pair<Pos, Dir> front = q.front();
        Pos act = front.first;
        Dir dnd = front.second;
        q.pop();

        if (dist(ini, act) <= radio) {
            Cell c = cell(act);
            int id = c.id;
            if (id != -1) {
                Unit u = unit(id);
                if (conversion_process and u.type == Wizard and u.player == me() and !u.is_in_conversion_process()) {
                    dir_mago = dnd;
                    return true;
                }
                if ( u.type == Wizard and u.player == me() and u.is_in_conversion_process() and !reserva) {
                    if (conversion_process) {
                        dirres = dnd;
                        reserva = true;
                    }
                    else {
                    dir_mago = dnd;
                    return true;
                    }
                }
            }
        }

        for (Dir d : dirsmag) {
            Pos obj = act + d;
            if (puedoir_bfs(obj) and visited.find(obj) == visited.end()  and dist(ini, obj) <= radio) {
                q.push({obj, dnd});
                visited.insert(obj);
            }
        }
    }

    return false;
}
bool gano_yo(int fuerza_yo, int fuerza_el) {
    if (fuerza_yo >= 2 * fuerza_el) return true;
    if (fuerza_el >= 2 * fuerza_yo) return false;

    if (random(0, 99) < 30) return true;

    if (fuerza_yo + fuerza_el == 0) return random(0, 99) < 50;
    return random(0, fuerza_yo + fuerza_el - 1) < fuerza_yo;
}

bool haycampo(Pos ini, Dir& dir_campo, map<Pos, int>& vamos) {
    queue<pair<Pos, Dir>> q;
    set<Pos> visited;
    visited.insert(ini);

    for (Dir d : dirsmag) {
        Pos obj = ini + d;
        if (puedoir_bfs(obj)) {
            q.push({obj, d});
            visited.insert(obj);
        }
    }

    while (!q.empty()) {
        pair<Pos, Dir> front = q.front();
        Pos act = front.first;
        Dir dnd = front.second;
        q.pop();

            Cell c = cell(act);
            if (puedoir(act) and c.owner != me()) {
                auto it = vamos.find(act);
            if (it == vamos.end() or vamos[act] < 3) {
                ++vamos[act];
               dir_campo = dnd;
                return true;
            }

            }
        

        for (Dir d : dirsmag) {
            Pos obj = act + d;
            if (puedoir_bfs(obj) and visited.find(obj) == visited.end()) {
                q.push({obj, dnd});
                visited.insert(obj);
            }
        }
    }

    return false;
}

void movemago(int id, map<Pos, int>& vamos) {
    Unit u = unit(id);
    Dir dir_mago;
    bool reserva = false;
    Dir dirres;
    if (u.is_in_conversion_process()) {
        if (haymago(u.pos, dir_mago, dirres, true, 5, reserva)) {
            move(id, dir_mago);
            return;
        } else if (reserva) {
            Pos adj = u.pos + dirres;
            if (puedoir1(adj)) {move(id, dirres);}
            return;
        }
    }
    else {
        Dir dir_mago;
        if (haymago(u.pos, dir_mago, dirres, false, 5, reserva)) {
            Pos adj = u.pos + dir_mago;
            if (puedoir(adj)) {move(id, dir_mago);}
            return;
        }
    }

       if (!voldemort_lejos(u.pos)) {
        for (Dir d : dirsmag) {
            Pos adj = u.pos + d;
            if (puedoir1(adj)) {
                move(id, d);
                return;
            }
        }
        
    }
    for (Dir d : dirsmag) {
            Pos adj = u.pos + d;
            Cell c = cell(adj);
            Unit enemy = unit(c.id);
            if (puedoir1(adj)) {
                if (c.id != -1) {
                     if (enemy.player != me()) {
                    if (enemy.type == Wizard) {
                        if (puedoir(adj)) move(id, d);
                }
                     }
                    else if (enemy.player == me()) {
                     if (puedoir(adj)) move(id, d);
            }
        }
            }
    }
    Dir dir_enemic;
    int diste;
    int distl; int dist3;
    Dir alibro;
    bool librito = false;
    bool enmig = false;

    if (round() < 75) {
        enmig = hayenemigo(u.pos, dir_enemic, 7, diste);
        librito =  haylibro(u.pos, alibro, vamos, 15, distl);
        if (enmig and librito) {
                     move(id, dir_enemic);
                
            }
            else if(enmig) {
                if (diste <= distl+3) {
                     move(id, dir_enemic);
                }
               
            }
            else if(librito){
                Pos obj = u.pos + alibro;
            if (puedoir1(obj)) {
            move(id, alibro);
            return;
            }
            }
        

    } else if (round() > 50 and round() < 150 ) {
          enmig = hayenemigo(u.pos, dir_enemic, 12, diste);
        librito =  haylibro(u.pos, alibro, vamos, 6, distl);
        if (enmig and librito) {
                     move(id, dir_enemic);

        }
            else if(enmig) {
                move(id, dir_enemic);
            }

            else if(librito) {
                Pos obj = u.pos + alibro;
            if (puedoir1(obj)) {
            move(id, alibro);
            return;
            }
            }
        
    } else if ( round() > 150) {
          enmig = hayenemigo(u.pos, dir_enemic, 12, diste);
        librito =  haylibro(u.pos, alibro, vamos, 3, distl);
        if (enmig and librito) {
            if (diste <= distl+1) {
                 move(id, dir_enemic);
            } else if  (distl <= diste-3) {
                move(id, alibro);
            }
        }
            else if(enmig) {
                move(id, dir_enemic);
            }

            else if(librito) {
                Pos obj = u.pos + alibro;
            if (puedoir1(obj)) {
                cerr << "voy3" << endl;
            move(id, alibro);
            return;
            }
            }
    }


    Dir pasto;
 if (haycampo(u.pos, pasto, vamos) and round() > 100) {
        Pos obj = u.pos + pasto;
        if (puedoir1(obj)) {
            move(id, pasto);
            return;
        }
    }

      for (Dir d : dirsmag) {
        Pos obj = u.pos + d;
        Cell cir = cell(obj);
        if (puedoir1(obj) and cir.owner != me()) {
            move(id, d);
            return;
        }
    }
          for (Dir d : dirsmag) {
        Pos obj = u.pos + d;
        if (puedoir1(obj)) {
            move(id, d);
            return;
        }
    }
}

bool backtrack(const vector<int>& ingredients, vector<int>& solu, vector<vector<int>>& grups, vector<int>& suma_grupos, int index, int obj) {
    if (index == (int)ingredients.size()) {
        return true;
    }

    for (int g = 0; g < (int)grups.size(); g++) {
        if (suma_grupos[g] + ingredients[index] <= obj and grups[g].size() < 3) {
            suma_grupos[g] += ingredients[index];
            solu[index] = g;
            grups[g].push_back(ingredients[index]);

            if (backtrack(ingredients, solu, grups, suma_grupos, index + 1, obj)) {
                return true;
            }

            suma_grupos[g] -= ingredients[index];
            grups[g].pop_back();
            solu[index] = -1;
        }
    }

    return false;
}

vector<int> resoldre_encanteri(vector<int> ingredients) {

 int sumatotal = 0;
for (int ingredient : ingredients) {
    sumatotal += ingredient;
}

    int obj = sumatotal / 5;

    vector<int> solu(ingredients.size(), -1);
    vector<int> suma_grupos(5, 0);
    vector<vector<int>> grups(5);

    if (backtrack(ingredients, solu, grups, suma_grupos, 0, obj)) {
        return solu;
    }

    return {};
}


void movefantasma(int id) {
    Unit u = unit(id);

    for (Dir d : dirsfantasma) {
        Pos adj = u.pos + d;
        if (pos_ok(adj)) {
            Cell c = cell(adj);
            if (c.id != -1) {
                Unit adj_unit = unit(c.id);
                if (adj_unit.type == Wizard and adj_unit.player != me()) {
                    Dir contraria;
                    if (d == Down) contraria = Up;
                    else if (d == Up) contraria = Down;
                    else if (d == Left) contraria = Right;
                    else if (d == Right) contraria = Left;
                    else if (d == DR) contraria = UL;
                    else if (d == UL) contraria = DR;
                    else if (d == RU) contraria = LD;
                    else contraria = RU;

                    vector<Dir> escapo = {contraria, Left, Right, Up};
                    
                    for (Dir dir_escapo : escapo) {
                        Pos pos_escapo = u.pos + dir_escapo;
                        Cell car = cell(pos_escapo);
                        if (puedoir1(pos_escapo) and car.book) {
                            move(id, dir_escapo);
                            return;
                        }
                    }
                    for (Dir dir_escapo : escapo) {
                        Pos pos_escapo = u.pos + dir_escapo;
                        if (puedoir1(pos_escapo)) {
                            move(id, dir_escapo);
                            return;
                        }
                    }
                }
            }
        }
    }
    if (u.resting_rounds() == 0 and round() > 50 and round() < 150) {
        vector<int> ingredients = spell_ingredients();
        vector<int> solucion = resoldre_encanteri(ingredients);
        if (!solucion.empty()) {
            spell(id, solucion);
        }
    }
    Dir alibro;
    if (haylibro2(u.pos, alibro)) {
        Pos obj = u.pos + alibro;
        if (puedoir1(obj)) {
            move(id, alibro);
            return;
        }
    }

    for (Dir d : dirsfantasma) {
        Pos obj = u.pos + d;
        Cell cir = cell(obj);
        if (puedoir1(obj) and cir.owner != me()) {
            move(id, d);
            return;
        }
    }

    for (Dir d : dirsfantasma) {
        Pos obj = u.pos + d;
        if (puedoir1(obj)) {
            move(id, d);
            return;
        }
    }
}

  virtual void play() {
    map<Pos,int> vamos;
    for (int id : wizards(me())) {

      movemago(id, vamos);
    }
      movefantasma(ghost(me()));
    
  }
};


RegisterPlayer(PLAYER_NAME);
