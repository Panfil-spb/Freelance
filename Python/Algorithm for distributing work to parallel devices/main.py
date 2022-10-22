import math
import random


def input_random_matr(n: int = 8) -> list:
    return [[random.randint(1, 100) for i in range(n)] for j in range(n)]


def s_calculation(matr: list) -> int:
    max_elem = max([max(i) for i in matr])
    a = max_elem - 1
    s = math.ceil(math.log10(2) / math.log10(max_elem - math.log10(a))) + 1
    return s


def matr_increment(matr: list, s: int) -> list:
    res = [line[-1] ** s - line[0] ** s for line in matr]
    return res


def matr_permutation(matr: list, incr: list) -> None:
    N = len(incr)
    for i in range(N - 1):
        for j in range(N - i - 1):
            if incr[j] < incr[j + 1]:
                incr[j], incr[j + 1] = incr[j + 1], incr[j]
                matr[j], matr[j + 1] = matr[j + 1], matr[j]


def step_2(matr: list):
    l = len(matr)
    if l % 2 == 0:
        matr_1 = [line[:(l // 2)] for line in matr[:(l // 2)]]

        matr_4 = [line[(l // 2):] for line in matr[(l // 2):]]
    else:
        matr_1 = [line[:(l + 1 // 2)] for line in matr[:(l + 1 // 2)]]

        matr_4 = [line[(l - 1 // 2):] for line in matr[(l - 1 // 2):]]
    return [matr_1, matr_4]


def step_1(matr: list, s: int) -> list:
    incr = matr_increment(matr, s)
    matr_permutation(matr, incr)
    if len(matr) <= 3:
        return [matr[i][i] for i in range(len(matr))]
    matrs = step_2(matr)
    res = []
    return step_1(matrs[0], s) + step_1(matrs[1], s)


def main():
    n = int(input('Введи разиерность матрицы n * n\n n = '))
    matr = input_random_matr(n)
    # matr = [[9, 5, 7, 6, 1, 6, 8, 7],
    #         [8, 10, 3, 9, 3, 4, 10, 7],
    #         [6, 5, 4, 1, 3, 7, 8, 7],
    #         [5, 7, 6, 10, 6, 7, 3, 1],
    #         [5, 1, 3, 4, 7, 9, 2, 10],
    #         [7, 8, 3, 5, 6, 9, 4, 8],
    #         [8, 5, 6, 7, 5, 4, 3, 10],
    #         [6, 3, 4, 4, 8, 6, 5, 2]]
    s = s_calculation(matr)
    res = step_1(matr, s)
    print(max(res))


if __name__ == '__main__':
    main()
