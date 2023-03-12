#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void MakeParts(int index, vector<vector<int>> &tree, vector<vector<int>> &parts) {
    parts[index][0] = 0;
    parts[index][1] = 1;

    for (int i : tree[index])
        MakeParts(i, tree, parts);

    for (int i : tree[index]) {
        parts[index][0] += max(parts[i][0], parts[i][1]);
        parts[index][1] += parts[i][0];
    }
}

int main() {
    int n, root;
    cin >> n;
    vector<vector<int>> tree(n);
    vector<vector<int>> parts(n, vector<int>(2, 0));

    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        if (a != 0)
            tree[a - 1].push_back(i);
        else
            root = i;
    }

    MakeParts(root, tree, parts);
    cout << max(parts[root][0], parts[root][1]);
}

