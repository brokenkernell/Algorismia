#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>     // Per a cos, sin, acos
#include <iomanip>   // Per a setprecision, fixed

// Definim M_PI si no està disponible (no és estrictament estàndard C++)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

// Una estructura simple per a un punt o vector 2D
struct Point {
    double x, y;
};

// Una estructura per emmagatzemar una mesura
struct Measurement {
    string A, B, C;
    double angle;
};

/**
 * Gira un vector 'v' un angle 'rad' (en radians) en sentit antihorari.
 */
Point rotate(Point v, double rad) {
    return {
        v.x * cos(rad) - v.y * sin(rad),
        v.x * sin(rad) + v.y * cos(rad)
    };
}

/**
 * Calcula la posició de C donades dues mesures.
 * Mesura 1: Angle des de BA a BC, amb vèrtex a B.
 * Mesura 2: Angle des de DE a DC, amb vèrtex a E.
 */
Point calculate_intersection(Point A, Point B, double angle1, Point D, Point E, double angle2) {
    // Convertim els angles a radians
    double rad1 = angle1 * M_PI / 180.0;
    double rad2 = angle2 * M_PI / 180.0;

    // Vector BA
    Point vec_BA = {A.x - B.x, A.y - B.y};
    // Vector ED (D i E, no E i D)
    Point vec_ED = {D.x - E.x, D.y - E.y};

    // Direcció de la Línia 1 (que comença a B)
    Point v1 = rotate(vec_BA, rad1);
    // Direcció de la Línia 2 (que comença a E)
    Point v2 = rotate(vec_ED, rad2);

    // Resolem la intersecció de dues línies paramètriques:
    // L1(t) = B + t*v1
    // L2(s) = E + s*v2
    // Volem trobar t, s tals que L1(t) = L2(s)
    // B + t*v1 = E + s*v2  =>  t*v1 - s*v2 = E - B
    
    // Anomenem delta = E - B
    Point delta = {E.x - B.x, E.y - B.y};

    // Resolem el sistema 2x2 per a 't' usant la regla de Cramer:
    // | v1.x  -v2.x | | t | = | delta.x |
    // | v1.y  -v2.y | | s | = | delta.y |

    double det = v1.x * (-v2.y) - (-v2.x) * v1.y;
    double det_t = delta.x * (-v2.y) - (-v2.x) * delta.y;
    // El problema assegura que no hi ha problemes de precisió[cite: 95],
    // la qual cosa implica que D no serà (proper a) zero.
    double t = det_t / det;

    // Un cop tenim t, podem trobar el punt d'intersecció C
    return {
        B.x + t * v1.x,
        B.y + t * v1.y
    };
}

int main() {
    // Optimització d'E/S
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Mapa per guardar les localitzacions conegudes
    map<string, Point> locations;
    // Mapa per agrupar les mesures per la característica 'C'
    map<string, vector<Measurement>> measurements_by_C;
    // Un set per portar el compte de tots els noms
    set<string> all_feature_names;

    // Llegim les dues característiques de referència
    string name;
    double x, y;
    
    cin >> name >> x >> y;
    locations[name] = {x, y};
    all_feature_names.insert(name);

    cin >> name >> x >> y;
    locations[name] = {x, y};
    all_feature_names.insert(name);

    // Llegim totes les mesures (fins al final de l'entrada)
    Measurement meas;
    while (cin >> meas.A >> meas.B >> meas.C >> meas.angle) {
        measurements_by_C[meas.C].push_back(meas);
        all_feature_names.insert(meas.A);
        all_feature_names.insert(meas.B);
        all_feature_names.insert(meas.C);
    }

    // Trobem quines característiques són desconegudes
    set<string> unknown_features;
    for (const string& fname : all_feature_names) {
        if (locations.find(fname) == locations.end()) {
            unknown_features.insert(fname);
        }
    }

    // Bucle principal: iterar fins que s'hagin resolt totes les incògnites
    while (!unknown_features.empty()) {
        bool changed = false;
        
        // Iterem sobre una còpia per poder modificar l'original 'unknown_features'
        set<string> current_unknown = unknown_features;
        
        for (const string& C_name : current_unknown) {
            // Segons l'enunciat, les desconegudes tenen exactament 2 mesures
            vector<Measurement>& C_measurements = measurements_by_C[C_name];
            
            Measurement m1 = C_measurements[0];
            Measurement m2 = C_measurements[1];

            // Comprovem si totes les dependències (A, B, D, E) són conegudes
            if (locations.count(m1.A) && locations.count(m1.B) &&
                locations.count(m2.A) && locations.count(m2.B)) {
                
                // Sí! Podem calcular la posició de C_name
                Point A = locations[m1.A];
                Point B = locations[m1.B];
                Point D = locations[m2.A];
                Point E = locations[m2.B];

                Point C_point = calculate_intersection(A, B, m1.angle, D, E, m2.angle);
                
                // Afegim la nova localització i la marquem com a resolta
                locations[C_name] = C_point;
                unknown_features.erase(C_name);
                changed = true;
            }
        }

        // Si fem una passada sencera i no resolem res, hi ha un problema
        // (això no hauria de passar si l'entrada és vàlida)
        if (!changed && !unknown_features.empty()) {
            break;
        }
    }

    // Imprimim totes les localitzacions en ordre lexicogràfic
    // amb 3 decimals
    cout << fixed << setprecision(3);
    for (const auto& pair : locations) {
        cout << pair.first << " " << pair.second.x << " " << pair.second.y << "\n";
    }

    return 0;
}
