#!/usr/bin/env python3
# tiAES.py
# (c) 2024 J. Adams jfa63@duck.com
# Released under the 2-clause BSD Licence

"""
  This implementation tries to by fully compliant with the FIPS 197 Advanced Encryption
Standard:
https://csrc.nist.gov/files/pubs/fips/197/final/docs/fips-197.pdf
  While it works, we cannot make any claims as to how secure the coding is nor is it very
fast on large files. Do not use this code for anything other that personal education and
enjoyment.
"""

import os
import gc
import sys
import hashlib
import argparse
import traceback
import numpy as np
from getpass import getpass
from aes_tables import *


## Functions

def KeyExpansion(key: np.ndarray) -> np.ndarray:
    """
    Implements FIPS 197 KeyExpansion() routine
    Parameters:
    - key: 16-byte (128-bit) input key as a NumPy 1D array
    - key: 24-byte (192-bit) input key as a NumPy 1D array
    - key: 32-byte (256-bit) input key as a NumPy 1D array
    Returns:
    - key_sched: expanded key schedule as a NumPy 2D array of shape:
      (NB*(nr+1))words x 4bytes
    Verified FIPS compliant output 20231220
    """
    # Constants defined in FIPS 197
    nk = len(key)//4
    nr = nk + 6
    wl = NB * (nr + 1) + 4 # We add 4 rows to w length for the CBC IV block
    
    # Round key constants as row vectors
    rcons = np.array([
        0x01, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00,
        0x04, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00,
        0x10, 0x00, 0x00, 0x00,
        0x20, 0x00, 0x00, 0x00,
        0x40, 0x00, 0x00, 0x00,
        0x80, 0x00, 0x00, 0x00,
        0x1b, 0x00, 0x00, 0x00,
        0x36, 0x00, 0x00, 0x00,
        0x6c, 0x00, 0x00, 0x00,
        0xd8, 0x00, 0x00, 0x00
    ], dtype=np.uint8).reshape(-1, 4)
    
    w = np.zeros((wl, 4), dtype=np.uint8)
    
    # Copy the original key into the first nk words of w
    w[:nk] = key.reshape(-1, 4)
    
    # Expand key schedule
    for i in range(nk, wl):
        temp = w[i-1]
        
        if i % nk == 0:
            temp = np.roll(temp, -1)
            temp = np.array([sbox[val] for val in temp], dtype=np.uint8)
            temp ^= rcons[i//nk - 1]
        
        elif nk > 6 and i % nk == 4:
            temp = np.array([sbox[val] for val in temp], dtype=np.uint8)
        
        w[i] = w[i-nk] ^ temp

    del key, temp
    gc.collect()
    return w
# End KeyExpansion


def AddRoundKey(st: np.ndarray, w: np.ndarray, rnd: int) -> np.ndarray:
    """
    Implements the FIPS 197 AddRoundKey() routine.
    Array st is the state.
    Array w is the key schedule.
    Integer rnd is the round.
    AddRoundkey() xors columns of state with rows
    of key material.
    """

    for c in range(4):
        wd = w[((rnd * 4) + c), :]
        st[:, c] ^= wd
    
    return st
# End AddRoundKey


def SubBytes(st: np.ndarray) -> np.ndarray:
    """
    Implements the FIPS 197 SubBytes() routine.
    Array st is the state.
    Substitues values in state from the sbox.
    """
    for r in range(4):
        for c in range(4):
            st[r, c] = sbox[st[r, c]]

    return st
# End SubBytes


def InvSubBytes(st: np.ndarray) -> np.ndarray:
    """
    Implements the FIPS 197 InvSubBytes() routine.
    Array st is the state.
    Substitues values in state from the inverse sbox.
    """
    for r in range(4):
        for c in range(4):
            st[r, c] = sboxinv[st[r, c]]

    return st
# End InvSubBytes


def ShiftRows(st: np.ndarray) -> np.ndarray:
    """
    Implements the FIPS 197 ShiftRows() routine.
    Array st is the state.
    Shift values left (-) in rows 2, 3 and 4 of st
    by -1, -2 and -3 places, respectively.
    """
    st[1, :] = np.roll(st[1, :], -1)
    st[2, :] = np.roll(st[2, :], -2)
    st[3, :] = np.roll(st[3, :], -3)

    return st
# End ShiftRows


def InvShiftRows(st: np.ndarray) -> np.ndarray:
    """
    Implements the FIPS 197 InvShiftRows() routine.
    Array st is the state.
    Shift values right (+) in rows 2, 3 and 4 of st
    by 1, 2 and 3 places, respectively.
    """
    st[1, :] = np.roll(st[1, :], 1)
    st[2, :] = np.roll(st[2, :], 2)
    st[3, :] = np.roll(st[3, :], 3)
    
    return st
# End InvShiftRows


def MixColumns(st: np.ndarray) -> np.ndarray:
    """
    Implements the FIPS 197 MixColums() routine.
    Array st is the state.
    Performs GF(256) matrix muliplication mcem*st, where
    mcem = [ 02  03  01  01 ]
           [ 01  02  03  01 ]
           [ 01  01  02  03 ]
           [ 03  01  01  02 ]
    """
    nst = st.copy()
    for c in range(4):
        nst[0, c] = m2[st[0, c]] ^ m3[st[1, c]] ^ st[2, c] ^ st[3, c]
        nst[1, c] = st[0, c] ^ m2[st[1, c]] ^ m3[st[2, c]] ^ st[3, c]
        nst[2, c] = st[0, c] ^ st[1, c] ^ m2[st[2, c]] ^ m3[st[3, c]]
        nst[3, c] = m3[st[0, c]] ^ st[1, c] ^ st[2, c] ^ m2[st[3, c]]

    return nst
# End MixColumns


def InvMixColumns(st: np.ndarray) -> np.ndarray:
    """
    Implements the FIPS 197 InvMixColums() routine.
    Array st is the state.
    Performs GF(256) matrix muliplication mcdm*st, where
    mcdm = [ 14  11  13  9  ]
           [ 9   14  11  13 ]
           [ 13  9   14  11 ]
           [ 11  13  9   14 ]
    """
    nst = st.copy()
    for c in range(4):
        nst[0, c] = m14[st[0, c]] ^ m11[st[1, c]] ^ m13[st[2, c]] ^ m9[st[3, c]]
        nst[1, c] = m9[st[0, c]] ^ m14[st[1, c]] ^ m11[st[2, c]] ^ m13[st[3, c]]
        nst[2, c] = m13[st[0, c]] ^ m9[st[1, c]] ^ m14[st[2, c]] ^ m11[st[3, c]]
        nst[3, c] = m11[st[0, c]] ^ m13[st[1, c]] ^ m9[st[2, c]] ^ m14[st[3, c]]

    return nst
# End InvMixColumns


def Cipher(st: np.ndarray, w: np.ndarray) -> np.ndarray:
    """
    Encrypts one block with AES
    Calculates number of rounds, nr, by dividing the
    number of rows in the key schedule, w, by 4.
    Notice that we subtract 4 from the row count to 
    account for the extra block used for the CBC IV.
    """
    nr = (np.shape(w)[0]-4)//4 - 1

    # Round 0 whitening
    s = AddRoundKey(st, w, 0)

    # Rounds 1 -> nr-1
    for r in range(1, nr):
        s = SubBytes(s)
        s = ShiftRows(s)
        s = MixColumns(s)
        s = AddRoundKey(s, w, r)

    # Round nr
    s = SubBytes(s)
    s = ShiftRows(s)
    s = AddRoundKey(s, w, nr)

    return s
# End Cipher


def InvCipher(st: np.ndarray, w: np.ndarray) -> np.ndarray:
    """
    Decrypts one block with AES
    See above note on number of rounds.
    """
    nr = (np.shape(w)[0]-4)//4 - 1

    # Round nr
    s = AddRoundKey(st, w, nr)
    s = InvShiftRows(s)
    s = InvSubBytes(s)
    
    # Rounds nr-1 -> 1
    for r in range(nr-1, 0, -1):
        s = AddRoundKey(s, w, r)
        s = InvMixColumns(s)
        s = InvShiftRows(s)
        s = InvSubBytes(s)

    # Round 0 whitening
    s = AddRoundKey(s, w, 0)

    return s
# End InvCipher


# Encrpyt in CBC mode
def cbcencr(fname: str, key: np.ndarray):
    """
    Encrypts in CBC mode.
    Saves output as fname.enc
    """

    # create an outfile name
    outfile = fname + '.enc'
    
    # Get last 4 rows of w for CBC IV
    s = np.shape(key)[0] - 4
    r = 0
    iv = np.zeros((4,4), dtype=np.uint8)
    for i in range(s, s+4):
        for j in range(4):
            iv[r,j] = key[i,j]
        r += 1

    # Open input file for reading
    infile = open(fname, 'r')

    # infile size
    fsz = os.path.getsize(fname)

    # Padding so num of bytes is a multiple of 16
    # as per the PKCS padding scheme.
    pad = 16 - (fsz % 16)
    # If the file size is already a multiple of 16,
    # add one block of 0x10 bytes
    if pad == 0:
        pad = 0x10

    # get a numpy byte array
    barr = np.fromfile(fname, dtype=np.uint8)
    infile.close()

    # pad the byte array
    pv = np.uint8(pad)
    padding = [pv for x in range(pad)]
    # This is a byte array of the input file
    # plus the padding:
    bpd = np.append(barr, padding)
    del pv, padding, barr
    gc.collect()

    try:
        with open(outfile, 'w+b') as of:
            ## Do CBC mode encr ##
            # We need to iterate through pbd 16 bytes
            # at a time, load them into a 4x4 state block
            # array (stb) encrypt, flatten (fst) then write
            # to outfile each time.
            # Note that we do state xor IV _before_ we encrypt.
            # The new state becomes the IV for the next CBC round.

            i = 0
            while i < fsz:
                # Get next 16 bytes from bpd
                st = bpd[i:i+16]
                # Reshape into block by column
                stb = st.reshape(4, 4, order='F')
                # xor state and IV
                stb ^= iv 
                # Call Cipher()
                stb = Cipher(stb, key)
                # Copy state to new IV 
                iv = stb.copy()
                # Flatten state by column
                fst = stb.flatten(order='F')
                # This writes the flattend blocks to file
                for b in range(16):
                    of.seek(b+i)
                    of.write(np.uint8(fst[b]))
                # Set i
                i = of.tell()
            # End while
        # End with, automatic of.close()
    except Exception as e:
        traceback.print_exc()
    finally:
        del bpd, st, stb, iv, fst
        gc.collect()
# End cbcencr


# Decrytp in CBC mode
def cbcdecr(fname: str, key: np.ndarray):
    """
    Decrypts in CBC mode.
    Saves output as fname.dec
    """
    # Strip off .enc extension
    # create an outfile name
    outfile = os.path.splitext(fname)[0] + '.dec'
    
    # Get last 4 rows of w for CBC IV
    s = np.shape(key)[0] - 4
    r = 0
    iv = np.zeros((4,4), dtype=np.uint8)
    for i in range(s, s+4):
        for j in range(4):
            iv[r,j] = key[i,j]
        r += 1

    # Open input file for reading
    infile = open(fname, 'r')

    # infile size
    fsz = os.path.getsize(fname)

    # get a numpy byte array
    barr = np.fromfile(fname, dtype=np.uint8)
    infile.close()

    try:
        with open(outfile, 'w+b') as of:
            ## Do CBC mode decr ##
            # We need to iterate through pbd 16 bytes
            # at a time, load them into a 4x4 state block
            # array (stb) decrypt, flatten (fst) then write
            # to outfile each time.
            # Note that we do stat xor IV _after_ we decrypt.
            # The new state becomes the IV for the next CBC round.

            i = 0
            while i < fsz:
                # Get next 16 bytes from byte array
                st = barr[i:i+16]
                # Reshape into block by column
                stb = st.reshape(4, 4, order='F')
                # Copy state to a temp block
                tb = stb.copy()
                # Call Cipher()
                stb = InvCipher(stb, key)
                # xor state and IV
                stb ^= iv 
                # Copy tmp block (old state) to new IV 
                iv = tb.copy()
                # Flatten state by column
                fst = stb.flatten(order='F')
                # This writes the flattend blocks to file
                for b in range(16):
                    of.seek(b+i)
                    of.write(np.uint8(fst[b]))
                # Set i
                i = of.tell()
            # Get last byte value = padding bytes
            of.seek(-1, 2)
            pv = int.from_bytes(of.read(1), "little")
            # Seek to cut-off point
            of.seek(-pv, 2)
            # Remove padding
            of.truncate()
        # End with, automatic of.close()
    except Exception as e:
        traceback.print_exc()
    finally:
        del fsz, st, stb, tb, iv, fst
        gc.collect()
# End cbcdecr


def main():
    do_encr = None
    
    # Handle args
    parser = argparse.ArgumentParser()
    parser.add_argument('-e', '--encrypt', help='Encrypt <filename>',
                        action='store_true')
    parser.add_argument('-d', '--decrypt', help='Decrypt <filename>',
                        action='store_true')
    parser.add_argument('filename', type=str,
                        help='Filename to encrypt or decrypt')
    args = parser.parse_args()

    if args.encrypt:
        print('Encrypt', args.filename)
        do_encr = True
    elif args.decrypt:
        fsplit = os.path.splitext(args.filename)
        if fsplit[1] == '.enc':
            print('Decrypt', args.filename)
        else:
            print('The file does not have the .enc extension.')
            print("We don't know if it was actually encrypted with PyAES.")
            sys.exit()
        do_encr = False
    else:
        sys.exit()

    # Make sure pwd is 16 characters min
    plen = 1
    while plen < 16:
        pstr = getpass()
        plen = len(pstr)

    # The actual key is a hash of the passphrase
    # We're basically enforcing 256bit encryption
    # since the hash is always 32bytes/256bits
    phsh = hashlib.sha256(str.encode(pstr)).digest()
    pwd = np.zeros(32, dtype=np.uint8)
    for i, b in enumerate(phsh):
        pwd[i] = b
    del phsh, pstr, plen
    gc.collect()

    key = KeyExpansion(pwd)

    if do_encr is True:
        print('We will now encrypt', args.filename, 'to '+args.filename+'.enc')
        cbcencr(args.filename, key)
        del pwd, key
        gc.collect()
    elif do_encr is False:
        fstrp = fsplit[0]
        print('We will now decrypt', args.filename, 'to '+fstrp+'.dec')
        cbcdecr(args.filename, key)
        del pwd, key
        gc.collect()
    else:
        sys.exit()

# End main


if __name__ == '__main__':
    main()


