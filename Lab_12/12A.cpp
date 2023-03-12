#include <vector>
#include "iostream"
using namespace std;

int main() {

    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> maxLen(n);
    vector<int> next(n);

    for (int i = n - 1; i >= 0; i--) {
        int maxNextLen = 0;
        int bestNext = -1;
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[i]) {
                if (maxLen[j] > maxNextLen) {
                    maxNextLen = maxLen[j];
                    bestNext = j;
                }
            }
        }
        next[i] = bestNext;
        maxLen[i] = maxNextLen + 1;
    }

    int max = 0;
    int bestStart = -1;
    for (int i =0; i < n; i++) {
        if (maxLen[i] > max) {
            max = maxLen[i];
            bestStart = i;
        }
    }

    cout << max << "\n" << a[bestStart];
    for (int i = next[bestStart]; i != -1; i  = next[i] ) {
        cout << " " << a[i];
    }

    return 0;
}
