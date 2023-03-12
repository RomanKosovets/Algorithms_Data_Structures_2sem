#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    int x;
    int y;
};

int dist(Point A, Point B) {            // считаем дистанцию между точками
    return pow((B.x - A.x), 2)
         + pow((B.y - A.y),2);
}

double Prim(const vector<Point> &points){

    double result = 0;
    int n = points.size();
    vector<bool> used(n, false);                       // массив пройденных вершин
    vector<int> min_e(n, INT_MAX);                          // массив минимального веса
    min_e[0] = 0;                                           // начальная точка отсчета алгоритма

    for (int i = 0; i < n; i++) {                           // начинаем перебирать каждую вершину
        int v = -1;                                         // присваиваем -1, значение которого у нас нет в массиве
        for (int i = 0; i < n; i++) {                       // перебираем не пройденные вершины
            if ((!used[i]) && (v == -1 || min_e[i] < min_e[v])) // если !вершина и вес = -1, либо вес вершины i < веса вершины v
                v = i;                                      // присваиваем новый вес
        }

        used[v] = true;                                     // помечаем вершину пройденной
        result += v == 0 ? 0 : sqrt(min_e[v]);

        for (int to = 0; to < n; to++) {
            if (!used[to] && to != v && dist(points[v], points[to]) < min_e[to]) // если !вершина и next вершина != нашей вершине v и дистанция между этими вершинами меньше, чем была
                min_e[to] = dist(points[v], points[to]);    // тогда пересчитываем дистанцию
        }
    }
    return result;

}

int main() {
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");

    int n;
    fin >> n;

    vector<Point> points(n);

    int x, y;
    for (int i = 0; i < n; i++) {
        fin >> x >> y;
        points[i] = {x, y};
    }

    fout.precision(11);
    fout << Prim(points) << endl;
    return 0;
}
