fin = open('input.txt', 'r')
fout = open('output.txt', 'w')

tops, edges = map(int, fin.readline().split())  # кол-во вершин и кол-во рёбер

matrix = []                                     # строим матрицу смежности
flag = 1
for i in range(tops):
    matrix.append([0] * tops)

for i in range(edges):                          # считываем ребра
    where, there = map(int, fin.readline().split())
    if matrix[where - 1][there - 1] == 1:       # если в матрицы уже есть такое ребро, то все плохо
        fout.write('YES')
        flag = 0
        break
    matrix[where - 1][there - 1] = 1            # заносим ребра в матрицу в верхнюю
    matrix[there - 1][where - 1] = 1            # и нижнюю часть
if flag:
    print('NO', file=fout)