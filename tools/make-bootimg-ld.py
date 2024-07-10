#!/bin/python3

import os
import sys;
import time;

def main():

    # get timespan from local system
    unixtime = int(time.time() * 1000)
    parts = unixtime & 0xFFFFFFFF, (unixtime >> 32) & 0xFFFFFFFF

    # write to file
    with open(sys.argv[1] + "/ld_date.ld", "wt") as fp:
        fp.write(f"LONG({hex(parts[1])});")
        fp.write(f"LONG({hex(parts[0])});")

    # get git commit hash
    tag = os.popen("git describe --tags").read().strip()
    hash = os.popen("git describe --always").read().strip()
    branch = os.popen("git rev-parse --abbrev-ref HEAD").read().strip()
    # get gcc version
    gcc = os.popen("gcc --version | head -n1").read().strip()
    tag = tag.replace("v", "").replace("-", "_")
    if tag == "":
        tag = "v0.0.0"

    # convert ts to yymmdd
    ts = time.strftime("%y%m%d", time.localtime(unixtime/1000))
    version = f"elkernel_build{ts}_{branch}_{tag}_{hash} # {gcc}"
    version = version.encode('utf-8')

    # enumerate over the bytes and write to file
    # limit to 128 bytes
    with open(sys.argv[1] + "/ld_version.ld", "wt") as fp:
        i = 0
        for j in range(0, len(version)):
            fp.write(f"BYTE({hex(version[j])});\n")
            if i > 127: break
        fp.write(f"BYTE(0x00);\n")

pass

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: make-ld-params.py <output dir>")
        sys.exit(1)
    main()
