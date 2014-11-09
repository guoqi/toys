#!/usr/bin/python
#coding: utf-8
from random import randint


def getArray():
    r = [randint(1, 100000) for i in range(100000)]
    return r


if __name__ == '__main__':
    array = getArray()
    f = open('test.txt', 'w')
    for i in array:
        f.write(str(i))
        f.write('\n')
    f.close()
    f = open('result.txt', 'w')
    array.sort()
    for i in array:
        f.write(str(i))
        f.write('\n')
    f.close()
