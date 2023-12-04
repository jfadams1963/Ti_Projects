# tiAES
tiAES: AES for the TI-89/90+ written in TI-89 BASIC  

ABOUT  

tiAES software was developed as and educational tool for the purposes of demonstrating and teaching the principles of AES cryptography. This BASIC version of tiAES uses character strings as input and output and does not operate directly on bytes.  
&nbsp;  

tiAES is free and open source software released under the 2-clause BSD license. The purpose of this licensing is to provide attribution to the author(s), while giving the code to the world as a gift.  
&nbsp;  

STATUS  

This version is fully functional and produces FIPS 197 compliant output. It implements a simple CBC mode of block-chaining. The initialization vector is calculated by the KeyExpansion algorithm as one extra block in the key schedule. The key is a 32-character passphrase.
