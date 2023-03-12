fin = open('input.txt', 'r')
fout = open('output.txt', 'w')

tops = int(fin.readline())
matrix = []

for i in range(tops):                               # создаём матрицу
    line = list(map(int, fin.readline().split()))
    matrix.append(line)


def check(matrix):                                  # проверяем верхнюю часть матрицы
    for i in range(tops):                           # с нижней на одинаковость
        for j in range(tops):                       # и главную диагональ на единицы
            if matrix[i][j] != matrix[j][i] or (i == j and matrix[i][j] == 1):
                return 'NO'
    return 'YES'


print(check(matrix), file=fout)
