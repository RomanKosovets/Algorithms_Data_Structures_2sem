def find_components(graph):
    visited = [0] * koltop                              # создадим массив номеров компонент
    kolcomponents = 0
    for node in range(len(graph)):                      # проверим каждую вершину
        if visited[node] == 0:                          # если мы ее не посещали
            kolcomponents = kolcomponents + 1
            visited[node] = kolcomponents               # то присваиваем ей новый номер компоненты
            dfs(graph, node, visited, kolcomponents)    # запускаем поиск в глубину
    return kolcomponents, visited


def dfs(graph, first_top, visited, kolcomponents):      # Выполняем поиск в глубину
    stack = [first_top]                                 # заносим в стек начальное значение узла
    while stack:
        children = graph[stack.pop()]                   # достаем его из стека
        for child in children:                          # проверяем всех детей этой вершины
            if visited[child] == 0:                     # если мы еще их не посещали,
                visited[child] = kolcomponents          # то заходим в них и присваиваем номер компоненты
                stack.append(child)                     # и проверяем детей ребёнка,
                                                        # таким образом находим вcю компоненты


fin = open('components.in', 'r')
fout = open('components.out', 'w')

koltop, koledge = map(int, fin.readline().split())

graph = []
for i in range(koltop):             # создаём пустой граф
    graph.append([])

for i in range(koledge):            # заполняем граф
    where, there = map(int, fin.readline().split())
    graph[where - 1].append(there - 1)
    graph[there - 1].append(where - 1)

kolcomponents, numbers = find_components(graph)

print(str(kolcomponents), file=fout)
print(' '.join(map(str, numbers)), file=fout)
