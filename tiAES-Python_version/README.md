# tiAES-Python
tiAES: AES for the TI nSpire CX II  

ABOUT  

tiAES software was developed as and educational tool for the purposes of demonstrating and teaching the basic principles of AES cryptography.   

tiAES is free and open source software released under the 2-clause BSD license. The purpose of this licensing is to provide attribution to the author(s), while giving the code to the world as a gift. I hope you enjoy it!  

USAGE  

Other than the standard Python libraries, you will need NumPy installed.  

    pip3 install numpy  
or  

    pip3 install -r requrirements.txt  

To run:  

    ./tiAES.py [-h, --help]

for options.  

To encrypt a file:  

    ./tiAES.py -e <filename>  

which will write a file called filename.enc.  

The decrypt will look for the file extension '.enc'. To decrypt:  

    ./tiAES.py -d <filename>.enc  

which will write the file filename.dec. Thus, your original file will never be overwritten.  

STATUS  

This version is fully functional and produces FIPS 197 compliant output. It uses CBC mode  block-chaining. The initialization vector is calculated by the KeyExpansion algorithm as one extra block in the key schedule. The key is a 16-, 24- or, 32-character passphrase. The length of the key phrase will determine 128, 192, or 256 bit encrypton.  

This implementation tries to by fully compliant with the FIPS 197 Advanced Encryption
Standard, even using the exact function names from the standard:  
https://csrc.nist.gov/files/pubs/fips/197/final/docs/fips-197.pdf  

While it works, we cannot make any claims as to how secure the coding is nor is it very fast on large files. Do not use this code for anything other that personal education and enjoyment.  

Notes on reading and writing blocks  

We use numpy.fromfile() to read bytes into a byte array: We will read blocks of 16 in
to a vector, then use reshape(4,4,order='F') to create a new state block, which then is
encr|decr, flattened, then written to outfile. Order 'F' loads the bytes into a block by column.

We track the offset i with outfile.tell() to load 16 bytes from the byte array  
 for each block:  
 
     sv = bpd[i:i+16]
     st = sv.reshape(4, 4, order='F')  
(where bpd is the padded byte array from the input file).  
``` 
                                                                          [01 05 09 13]  
bpd[i:i+16]->[01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16].reshape()->[02 06 10 14]  
                                                                          [03 07 11 15]  
                                                                          [04 08 12 16]
```

To write out state blocks, we call sv = st.flatten(order='F') on each block, then write the bytes from each flattened block sv in to the open outfile, tracking the byte position with outfile.tell().  
``` 
[01 05 09 13]  
[02 06 10 14].flatten()->[01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16]-> of.write()  
[03 07 11 15]   
[04 08 12 16]
```

Notes on block padding  

    padding_bytes = block_size - (message_length % block_size)  
    where block_size = 16  
    
Padding bytes are appended to the file's byte array _before_ encryption. The value of the added bytes = padding_bytes.  
After decryption, the last byte is read and assigned to padding_bytes, which is the number of bytes to be truncated.  
https://www.ibm.com/docs/en/zos/3.1.0?topic=rules-pkcs-padding-method  

Notes on using the ulab library in place of numpy in MicroPython  

Use of ulab in place of numpy in MicroPython supplies a good amount of numpy functionality however, two important methods are currently missing: fromfile() and append(), both of which are used here. This matters to the author in as much as it was hoped that this code could run on the TI nSpire cx calculators using ulab.  

If/when the ulab library supports these methods, it should be a 'drop in' replacement for numpy using:  
```python
from ulab import numpy as np  
```
In the mean time, the existing code can be reworked to get around the use of fromfile() and append().    

TUTORIAL  

I have outlined a tutorial which will eventually end up here.
