# tiAES-C
AES for the TI-89/90+ in C  

The _portable_ version compiles and works without error. The next step is for someone to port it to the TI platform with TIGCC.  

It is a very simple (simple minded?) implementation of AES, but produces FIPS
compliant output. It is not suitable for real world usage, but only serves as
an educational excercise.  

__STATUS__  

The program encyrpts and decrypts files of any size using CBC mode AES with PKCS padding.  

The KeyExpanson and Cypher routines produce FIPS-197 compliant output as verified with a block-by-block comparison to the "APPENDIX A - KEY EXPANSION EXAMPLES" and "APPENDIX B – CIPHER EXAMPLE" in the FIPS 197 documentation: https://csrc.nist.gov/files/pubs/fips/197/final/docs/fips-197.pdf  (See tiAES-C_version/portable/src/keyutils.c and tiAES-C_version/portable/src/encr.c)  

The portable version compiles cleanly with Clang 16.0.6 on FreeBSD, GCC 7.5.0 on NetBSD, and GCC 11.4.0 on Linux.




