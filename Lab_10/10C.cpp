#include <algorithm>
#include <iostream>
#include <vector>
#include "fstream"
typedef long long ll;

using namespace std;

vector <ll> p;
ll find(ll x);
void unite(pair<ll, ll> e);


ll find(ll x) {                     // проверяем вершины на то, что они находятся в разных компонентах
    if (p[x] == x)
        return x;
    return p[x] = find(p[x]);
}

void unite(pair<ll, ll> v) {        //объединяем наши вершины в компоненту связности  и заносим в P ту вершину с которой она связана
    v.first = find(v.first);
    v.second = find(v.second);
    if (v.first != v.second)
        p[v.first] = v.second;
}

int main() {

    ifstream fin("C:\\Users\\roman\\Programming\\CLionProjects\\Algos_C++\\10 lab\\input.txt");
    ofstream fout("C:\\Users\\roman\\Programming\\CLionProjects\\Algos_C++\\10 lab\\output.txt");

    ll n, m;
    fin >> n >> m;

    p.resize(n + 1);
    vector<pair<ll, pair<ll, ll>>> edges;
    ll from, to, w;
    for (int i = 0; i < m; i++) {           // считываем данные
        fin >> from >> to >> w;
        edges.push_back({w, {from, to}});
    }

    ll result = 0;
    sort(edges.begin(), edges.end());       // сортируем массив по весам

    for (int i = 1; i <= n; i++)            // создаем множества для каждой вершины (лес)
        p[i] = i;

    for (int i = 0; i < m; i++) {
        ll a = edges[i].second.first, b = edges[i].second.second;
        if (find(a) != find(b)) {           // определяем пренадлежат ли концы ребра разным деревьям
            unite(edges[i].second);
            result += edges[i].first;       // считаем результат
        }
    }

    fout << result << "\n";
    return 0;
}