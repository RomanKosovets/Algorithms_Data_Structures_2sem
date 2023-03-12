#include <vector>
#include <iostream>
using namespace std;

int main() {

    int capacity;
    string text;
    cin >> capacity >> text;

    vector <vector <int>> statements (text.size() + 1, vector <int> (capacity, 0));
    vector<int> pr(text.size() + 1);
    pr[0] = -1;

    for (int i = 1; i < text.size() + 1; i++) { // ищем, какой префикс-суффикс можно расширить
        for (int k = pr[i - 1]; ; k = pr[k]) { // если можно расширить префикс, то расширяем, иначе берем длину меньшего суффикса
            if (k == -1 || text[k] == text[i - 1]) {
                pr[i] = k + 1;
                break;
            }
        }
    }
    pr.erase(pr.begin()); // удаляем 0 индекс с -1, он не нужен

    for (int i = 0; i < text.size() + 1; i++) {
        for (char letter = 'a'; letter < 'a' + capacity; letter++) {
            if (i > 0 && letter != text[i])
                statements[i][letter - 'a'] = statements[pr[i - 1]][letter - 'a'];
            else
                statements[i][letter - 'a'] = i + (letter == text[i]);
        }
    }

    for (int i = 0; i < statements.size(); i++) {
        for (int j = 0; j < statements[i].size(); j++) {
            cout << statements[i][j] << ' ';
        }
        cout << "\n";
    }
    return 0;

    public class Student
    {
        public string FirstName;

        public string LastName;

        public int Age;
    };

    public class Test
    {
        public void sd()
        {
            var Student = new Student();
            student.FirstName = "ssss";
        }
    };
}