#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void MakeParts(int index, vector<vector<int>> &tree, vector<vector<int>> &parts, vector<int> &nodeWeight) {
    parts[index][0] = 0;
    parts[index][1] = nodeWeight[index];

    for (int i : tree[index])
        MakeParts(i, tree, parts, nodeWeight);

    for (int i : tree[index]) {
        parts[index][0] += max(parts[i][0], parts[i][1]);
        parts[index][1] += parts[i][0];
    }
}

int main() {
    ifstream fin("selectw.in");
    ofstream fout("selectw.out");
    int n, root;
    fin >> n;
    vector<vector<int>> tree(n);
    vector<vector<int>> parts(n, vector<int>(2, 0));
    vector<int> nodeWeight(n, 0);

    for (int i = 0; i < n; ++i) {
        int a;
        fin >> a >> nodeWeight[i];
        if (a != 0)
            tree[a - 1].push_back(i);
        else
            root = i;
    }

    MakeParts(root, tree, parts, nodeWeight);
    fout << max(parts[root][0], parts[root][1]);
}

