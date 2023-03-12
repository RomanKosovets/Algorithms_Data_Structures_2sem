from collections import deque

fin = open('pathbge1.in', 'r')
fout = open('pathbge1.out', 'w')

koltop, koledge = map(int, fin.readline().split())

graph = []                                          # создаём пустой граф
for i in range(koltop):
    graph.append([])

for i in range(koledge):                            # заполняем граф
    where, there = map(int, fin.readline().split())
    graph[where - 1].append(there - 1)
    graph[there - 1].append(where - 1)


def count_dist(graph, first_top):
    dist = [10 ** 6] * len(graph)                  # устанавливаем расстояния между нач. вершиной и всеми другими вершинами в большое значение
    dist[first_top] = 0                            # расстоянию между нач. вершиной и самим собой присваиваем 0
    queue = deque([first_top])                     # заводим очередь

    while queue:
        node = queue.popleft()                     # удаляем вершину из очереди и возвращаем её, присваивая в узел
        for child in graph[node]:                  # дальше просматриваем всех детей нашей вершины
            if dist[child] > dist[node] + 1:       # проверка на непосещаемых детей, которые всегда будут бесконечностью, иначе мы их уже посетили
                dist[child] = dist[node] + 1       # меняем бесконечность на количество путей, прибавляя 1
                queue.append(child)                # заносим в очередь ребёнка вершины, чтобы проверить её детей и т.д.
    return dist


short_dist = count_dist(graph, 0)
print(' '.join(map(str, short_dist)), file=fout)