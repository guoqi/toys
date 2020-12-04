#!/usr/bin/python
# coding: utf-8

import re
import sys


def decode(s):
    result = bytearray()
    r = re.compile("\\\\[0-7]{3}")
    m = r.findall(s)
    for t in m:
        result.append((int(t[1:], 8)))
    print(bytes(result).decode("utf-8"))


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: {0} [string]".format(sys.argv[0]))
        exit(1)
    decode(sys.argv[1])
