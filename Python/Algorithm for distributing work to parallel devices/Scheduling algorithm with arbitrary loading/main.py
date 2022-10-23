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


def print_matr(matr: list) -> None:
    for line in matr:
        print(line)


def step_2(matr: list) -> list:
    sums = [0 for _ in matr[0]]

    for i in range(len(matr)):

        min_index, min_num = min(list(enumerate(matr[i])), key=lambda x: x[1] + sums[x[0]])

        sums[min_index] += min_num - sums[min_index]
        if i + 1 < len(matr):
            for j in range(i + 1, len(matr)):
                matr[j][min_index] += min_num

    return sums


def step_1(matr: list) -> int:
    incr = matr_increment(matr)
    matr_permutation(matr, incr)
    res = step_2(matr)
    print(f'res: {" ".join(str(i) for i in res)}')
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
