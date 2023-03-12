#include <vector>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin ("prefix.in");
    ofstream fout ("prefix.out");

    string text;
    fin >>  text;

    vector<int> pr(text.size() + 1);
    pr[0] = -1;

    for (int i = 1; i < text.size() + 1; i++) { // ищем, какой префикс-суффикс можно расширить
        for (int k = pr[i - 1]; ; k = pr[k]) { // если можно расширить префикс, то расширяем, иначе берем длину меньшего суффикса
            if (k == -1 || text[k] == text[i - 1]) {
                pr[i] = k + 1;
                break;
            }
        }
        fout << pr[i] << ' ';
    }
    return 0;
}
