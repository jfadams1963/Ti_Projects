# tiAES-BASIC
tiAES: AES for the TI-89/90+ written in TI-89 BASIC  

__ABOUT__  

tiAES software was developed as and educational tool for the purposes of demonstrating and teaching the basic principles of AES cryptography. This BASIC version of tiAES uses character strings as input and output and does not operate directly on bytes.  

tiAES is free and open source software released under the 2-clause BSD license. The purpose of this licensing is to provide attribution to the author(s), while giving the code to the world as a gift. I hope you enjoy it!  

__STATUS__  

This version is fully functional and produces FIPS 197 compliant output. It implements a simple CBC mode of block-chaining. The Initialization Vector (IV) randomly generated for each encrypt. The key is a 16-, 24- or, 32-character passphrase. The length of the key phrase will determine 128, 192, or 256 bit encrypton.

End block padding is "automatic" in as much as each block starts as a 4x4 matrix of zeros. If the last block has fewer than 16 byte-values, the remaining zeros are encrypted as part of the block. When the block is decrypted and the byte-values converted to characters, the zeros are NULL characters and are thus not part of the decrypted string.

__TUTORIAL__  

I have outlined a tutorial which will eventually end up here.
