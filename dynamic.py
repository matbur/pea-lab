import itertools
import re

from collections import OrderedDict
from glob import glob
from time import time


def combinations(dim, r):
    l = []
    pool = range(1, dim)
    indices = list(range(r))
    l.append(tuple(pool[i] for i in indices))
    while True:
        for i in range(r - 1, -1, -1):
            a = i + dim - 1 - r
            if indices[i] != a:
                break

        else:
            return tuple(l)
        indices[i] += 1
        for j in range(i + 1, r):
            indices[j] = indices[j - 1] + 1

        l.append(tuple(pool[i] for i in indices))


def get_set(n, r):
    return itertools.combinations(range(1, n), r)


def generate_subsets(matrix):
    odict = OrderedDict()
    len_ = len(matrix)

    for i in range(len_):
        for j in get_set(len_, i):
            for k in range(1, len_):
                if k in j:
                    continue
                odict[(k, *j)] = None
    odict[tuple(range(len_))] = None
    return odict


def fill_dict(matrix, odict):
    for item in odict:
        city = item[0]
        if len(item) == 1:
            odict[item] = matrix[0][city], 0
            continue

        set_ = item[1:]

        first = set_[0]
        min_ = odict[set_][0] + matrix[first][city], first

        for i in range(len(set_)):
            temp = list(set_)
            temp[0], temp[i] = temp[i], temp[0]

            temp = (temp[0], *sorted(temp[1:]))
            first = temp[0]

            temp = odict[temp][0] + matrix[first][city], first
            min_ = min(min_, temp)

        odict[item] = min_

    return odict


def get_distance(odict):
    return next(reversed(odict.items()))[1][0]


def load_matrix(filename):
    with open(filename) as f:
        matrix = f.readlines()

    return [[int(i) for i in j.split()] for j in matrix[1:]]


def key(x):
    return [int(i) for i in re.findall(r'\d+', x)]


if __name__ == '__main__':

    for i in sorted(glob('data/*/*_0.tsp'), key=key):
        matrix = load_matrix(i)
        odict = generate_subsets(matrix)

        t = time()
        odict = fill_dict(matrix, odict)
        t2 = time()

        print(i, get_distance(odict), t2 - t)
