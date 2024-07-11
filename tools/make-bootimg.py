#!/bin/python3

import os
import sys;
import time;

# bootimg writer class
class bootimg:

    STRUCT_MAGIC = 0
    STRUCT_CRC32 = 8
    STRUCT_FLAGS = 12
    STRUCT_IMG_SIZE = 16
    STRUCT_ENTRY_OFFSET = 20
    STRUCT_TIMESTAMP = 24
    STRUCT_VERSION = 32
    STRUCT_KERNEL = 512

    _time = int(time.time() * 1000)

    def _get_time(self):
        return self._time.to_bytes(8, byteorder='little')

    def _get_version(self):

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
        ts = time.strftime("%y%m%d", time.localtime(self._time/1000))
        version = f"elkernel_build{ts}_{branch}_{tag}_{hash} \r\n{gcc}"
        return version.encode('utf-8')

    def _padding_write(self, file):
        self.fp.write(file)

        size = len(file)
        if size % 512 != 0:
            align = 512 - (size % 512)
            size += align
            self.fp.write(bytearray(align))
        return size

    def __init__(self, path):
        self.path = path
        self.fp = open(path, "wb")
        self.fp.seek(0)

        # write header
        self.fp.write(b"ELKERNEL")            # 0   magic
        self.fp.write(bytearray(4))           # 8   crc32
        self.fp.write(bytearray(4))           # 12  flags
        self.fp.write(bytearray(4))           # 16  image_size
        self.fp.write(bytearray(4))           # 20  entry_offset
        self.fp.write(self._get_time())       # 24  timestamp
        self.fp.write(self._get_version())    # 32  version
        self.fp.write(bytearray(352))         # 160 align
        # file content                        # 512 kernel

    def set_file(self, file):
        
        # calculate crc32
        crc = 0
        for i in range(0, len(file)):
            crc = crc ^ file[i]
            for j in range(0, 8):
                if crc & 1:
                    crc = (crc >> 1) ^ 0xEDB88320
                else:
                    crc = crc >> 1
        crc = crc ^ 0xFFFFFFFF

        # write crc32
        self.fp.seek(self.STRUCT_CRC32)
        self.fp.write(crc.to_bytes(4, byteorder='little'))
        
        # write file align 512
        self.fp.seek(self.STRUCT_KERNEL)
        size = self._padding_write(file)

        # write image size
        self.fp.seek(self.STRUCT_IMG_SIZE)
        self.fp.write(size.to_bytes(4, byteorder='little'))


    def close(self):

        self.fp.close()


def main():

    # open bootimg writer
    boot = bootimg(sys.argv[2])

    # open the file and read the bytes
    with open(sys.argv[1], "rb") as fp:
        file = fp.read()
        boot.set_file(file)
    
    boot.close()

    # # enumerate over the bytes and write to file
    # # limit to 128 bytes
    # with open(sys.argv[1] + "/ld_version.ld", "wt") as fp:
    #     i = 0
    #     for j in range(0, len(version)):
    #         fp.write(f"BYTE({hex(version[j])});\n")
    #         if i > 127: break
    #     fp.write(f"BYTE(0x00);\n")

pass

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: make-bootimg.py <input> <out bootim>")
        sys.exit(1)
    main()
