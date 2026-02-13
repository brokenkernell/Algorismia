#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <list>

using namespace std;

class Node {
public:
    Node(string val) : deps(0), val(val) {}

    std::vector<Node*> nb;
    unsigned deps;
    string val;
};
class NodeComp {
public:
    bool operator() (Node * const &lhs, Node * const &rhs) const {
        return lhs->val < rhs->val;
    }
};

int main() {
    int n;
    while (cin >> n) {
        vector<Node> nodes;
        nodes.reserve(n);
        
        // Priority list of nodes
        set <Node*, NodeComp> pend;

        // Reverse node mapping!
        map <string, Node*> rtable;

        for (unsigned i = 0; i < n; i++) {
            string w;
            cin >> w;
            nodes.push_back(Node(w));
            pend.insert(&nodes[i]);
            rtable[w] = &nodes[i];
        }

        unsigned m;
        cin >> m;
        while (m--) {
            string from, to;
            cin >> from >> to;
            Node * before = rtable[from];
            Node * after = rtable[to];

            before->nb.push_back(after);
            after->deps++;

            // "to" node cannot be a starting node!
            if (pend.find(after) != pend.end())
                pend.erase(after);
        }


        list<string> solution;

        // Keep iterating!
        unsigned ndone = nodes.size();
        while (pend.size()) {
            Node * curr = *pend.begin();
            pend.erase(curr);

            solution.push_back(curr->val);
            ndone--;

            for (unsigned i = 0; i < curr->nb.size(); i++) {
                // Remove this edge!
                if (--curr->nb[i]->deps == 0)
                    pend.insert(curr->nb[i]);
            }
        }

        if (ndone == 0) {
            for (auto c: solution)
                cout << c;
            cout << endl;
        }
        else
            cout << "NO VALID ORDERING" << endl;
    }
}
