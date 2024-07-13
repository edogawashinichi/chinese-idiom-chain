#!/usr/bin/python3

import sys

if __name__ == "__main__":
    fname = sys.argv[1] if len(sys.argv) > 1 else "result.txt";
    with open(fname, 'r') as f:
        lines = f.readlines()
        if len(lines) == 2:
            idioms = lines[1].split("->")
            if len(idioms[-1]) < 3:
                idioms = idioms[:-1]
            idioms_set = set(idioms)
            all_connect = True
            for i in range(len(idioms)-1):
                if idioms[i][-1] != idioms[i+1][0]:
                    print(idioms[i] + " is not adjacent to " + idioms[i+1])
                    all_connect = False
                    break
            if all_connect:
                print("all connections ok!")
            if len(idioms) == len(idioms_set):
                print("no duplicate with size: " + str(len(idioms)))
                print("start: " + idioms[0] + "    end: " + idioms[-1])
            else:
                print("idioms size: " + str(len(idioms)))
                print("duplicate size: " + str(len(idioms) - len(idioms_set)))
        else:
            print(fname + " format invalid!")
