fin = open('input.txt', 'r')
fout = open('output.txt', 'w')

tops, edges = map(int, fin.readline().split())  # кол-во вершин и кол-во рёбер

matrix = []
for i in range(tops):                           # создаём матрицу и заполняем нулями
    matrix.append([0] * tops)

for i in range(edges):                          # считываем наши пути
    where, there = map(int, fin.readline().split())
    matrix[where - 1][there - 1] = 1            # заносим в матрицу

for line in matrix:                             # выводим матрицу
    print(' '.join(map(str, line)), file=fout)
    print('\n')
