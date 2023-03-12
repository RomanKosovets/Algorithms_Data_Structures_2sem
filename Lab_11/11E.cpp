#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

struct edge {
    int from, to, weight;
};

void ford(int& tops, vector<int>& dist, vector<int>& parent, vector<edge> graph, int &C_Start) {
    dist[0] = 0;
    for (int i = 0; i < tops; i++) {
        C_Start = -1;
        for (edge edge : graph) {
            if (dist[edge.to] > dist[edge.from] + edge.weight) {    //релаксируем
                dist[edge.to] = dist[edge.from] + edge.weight;
                parent[edge.to] = edge.from;                        // заносим родителя
                C_Start = edge.to;                                  // новое начало цикла
            }
        }
    }
}

int main() {
    ifstream fin("negcycle.in");
    ofstream fout("negcycle.out");

    int tops;
    fin >> tops;
    int  C_Start = -1;

    vector<edge> graph;
    vector<int> parent(tops);
    vector<int> dist(tops, INT_MAX);

    for (int from = 0; from < tops; from++) {
        for (int to = 0; to < tops; to++) {
            int weight;
            fin >> weight;
            graph.push_back({from, to, weight});
        }
    }

    ford(tops,dist, parent, graph, C_Start);

    if (C_Start != -1) {
        vector<int> way;
        int C_End = C_Start;

        for (int i = 0; i < tops; i++)  // находим вершину лежащую в цикле, потому что может быть вершина достижимая из цикла, это нам не нужно
            C_End = parent[C_End];

        for (int top = C_End; top != C_End || way.empty(); top = parent[top])   // заносим всех предков
            way.push_back(top);

        way.push_back(C_End);
        reverse(way.begin(), way.end());

        fout << "YES\n";
        fout << way.size() << endl;

        for (int i = 0; i < way.size(); i++)
            fout << way[i] + 1 << ' ';
    }
    else
        fout << "NO";
    return 0;
}
//    if (C_Start != -1) {
//        vector<int> way;
//        int C_End = C_Start;            // конец равен началу
//
//        way.push_back(C_Start);
//
//        for (int i = 0; i < tops; i++) {
//            C_End = parent[C_End];
//            way.push_back(C_End);
//        }
//        reverse(way.begin(), way.end());
