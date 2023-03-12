#include <vector>
#include <fstream>

using namespace std;

int main() {

    ifstream fin ("C:\\Users\\roman\\Programming\\CLionProjects\\Algos_C++\\input.txt");
    ofstream fout ("C:\\Users\\roman\\Programming\\CLionProjects\\Algos_C++\\output.txt");

    string prefics, text;
    fin >> prefics >> text;

    string s = prefics + '#' + text;

    vector<int> pr(s.size() + 1);
    pr[0] = -1;

    vector<int> ans;

    for (int i = 1; i < s.size() + 1; i++) { // ищем, какой префикс-суффикс можно расширить
        for (int k = pr[i - 1]; ; k = pr[k]) { // если можно расширить префикс, то расширяем, иначе берем длину меньшего суффикса
            if (k == -1 || s[k] == s[i - 1]) {
                pr[i] = k + 1;
                break;
            }
        }
        if (pr[i] == prefics.size()) {
            ans.push_back((int)(i - 2 * prefics.size()));
        }
    }

    fout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i] << ' ';
    }
    return 0;
}