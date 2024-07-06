#!/bin/python3

import io;
import os;
import sys;

def main():

    if sys.argv[1].index(':') == -1:
        print("Invalid symbol format, expected: <section>:<symbol>, got: " + sys.argv[1])
        sys.exit(1)
    
    split = sys.argv[1].split(':')
    symbol = split[0].encode(), split[1].encode()
    if len(symbol[1]) > len(symbol[0]):
        print("Renamed symbol is longer than the original symbol")
        sys.exit(1)

    input = sys.argv[2]
    output = sys.argv[3]

    with open(input, "rb") as coff:
        # search binary in the file
        data = coff.read()

        position = data.find(symbol[0])
        if position == -1:
            print("Symbol not found")
            sys.exit(1)

        # patch with align
        print("Patching " + split[0] + " at position: " + str(position))
        align = len(symbol[0]) - len(symbol[1])
        data = data[:position] + symbol[1] + bytearray(align) + data[position + len(symbol[0]):]

        # write
        with open(output, "wb") as out:
            out.write(data)

    pass

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage: patch-symbol.py <symbol> <input> <output>")
        sys.exit(1)
    main()
