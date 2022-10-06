#!/usr/bin/python
from cffi import FFI
import os
import sys

ffi = FFI()

ffi.cdef("""
    void encrypt(const char *);
    void decrypt(const char *);
""")

#encryptor = ffi.dlopen("lib_name.so"/"lib_name.dll") # dll или so зависит от ОС, на Windows dll, на *nix so

def cipher(lib, path):
    def cipher_iter(d):
        for item in os.listdir(d):
            f = os.path.join(d, item)
            if os.path.isdir(f):
                cipher_iter(f)
            else:
                lib.encrypt(f.encode('utf-8'))
            

if __name__ == "__main__":
    if len(sys.argv) <= 2:
        print("Usage: cipher <path> <algo>")
        sys.exit(-1)
    path, lib = input().split()
    match lib:
        case 'aes':
            lib = 'lib/libaes.so'
        case 'magma':
            lib = 'lib/magma-cipher.so'
        case 'module':
            lib = 'lib/libmodule.so'
        case _:
            lib = lib
        encryptor = ffi.dlopen(lib)
        cipher(lib, path)
