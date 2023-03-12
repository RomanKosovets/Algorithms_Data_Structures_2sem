#include <fstream>
#include <vector>

using namespace std;

bool kuhn(int from, vector <vector<int>> &graph, vector<bool> &visited, vector<int> &matching) {
    if (visited[from])          // пока в графе удаётся найти увеличивающую цепь,
        return false;           // будем выполнять чередование паросочетания вдоль этой цепи и повторять процесс поиска увеличивающей цепи
    visited[from] = true;
    for (int i = 0; i < graph[from].size(); i++) {
        int to = graph[from][i];
        if (matching[to] == -1 || kuhn(matching[to], graph, visited, matching)) { // Если не удалось найти цепь, значит паросочетание максимальное
            matching[to] = from;
            return true;
        }
    }
    return false;
}

int main() {

    ifstream fin("matching.in");
    ofstream fout("matching.out");

    int tops1, tops2, edges;
    fin >> tops1 >> tops2 >> edges;

    vector <vector<int>> graph(tops1, vector<int>());
    vector<int> matching(tops2, -1);
    vector<bool> visited(tops1);
    vector<bool> used(tops1);

    for (int i = 0; i < edges; i++) {     // считываем граф
        int from, to;
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
    }

    for (int i = 0; i < tops1; i++)                 // Находим возможные паросочетания
        for (int j = 0; j < graph[i].size(); j++)
            if (matching[graph[i][j]] == -1) {
                matching[graph[i][j]] = i;
                used[i] = true;
                break;
            }

    for (int i = 0; i < tops1; i++) {  // запускаем алгоритм Куна для пустого паросочетания
        if (used[i])
            continue;
        for (int j = 0; j < tops1; j++)
            visited[j] = false;
        kuhn(i, graph, visited, matching);
    }

    int value = 0;
    for (int i = 0; i < tops2; i++)
        if (matching[i] != -1)
            value++;
    fout << value;

    return 0;
}
