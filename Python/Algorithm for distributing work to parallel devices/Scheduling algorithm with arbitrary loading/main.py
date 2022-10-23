import random


def input_random_matr(n: int = 5, m: int = 3) -> list:
    return [[random.randint(1, 100) for i in range(m)] for j in range(n)]


def matr_increment(matr: list) -> list:
    res = [sum(line) for line in matr]
    return res


def matr_permutation(matr: list, incr: list) -> None:
    N = len(incr)
    for i in range(N - 1):
        for j in range(N - i - 1):
            if incr[j] < incr[j + 1]:
                incr[j], incr[j + 1] = incr[j + 1], incr[j]
                matr[j], matr[j + 1] = matr[j + 1], matr[j]


def step_2(matr: list) -> list:
    sums = [0 for _ in matr[0]]

    for index_line, line in enumerate(matr):
        min_index, min_num = min(list(enumerate(line)), key=lambda x: x[1])
        if index_line + 1 < len(matr):
            matr[index_line + 1][min_index] += min_num
    return sums


def step_1(matr: list) -> int:
    incr = matr_increment(matr)
    matr_permutation(matr, incr)
    res = step_2(matr)
    return max(res)


def main():
    # n = int(input('Введи разиерность матрицы n * m\n n = '))
    # m = int(input('m = '))
    # matr = input_random_matr(n, m)
    matr = [[17, 14, 12],
            [9, 5, 11],
            [15, 7, 12],
            [13, 10, 8],
            [11, 16, 14]]
    print(step_1(matr))


if __name__ == '__main__':
    main()
