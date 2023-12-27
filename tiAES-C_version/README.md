# tiAES-C
AES for the TI-89/90+ in C  

This code is experimemntal and is not yet ready to be compiled with TIGCC.
It will first be beaten in to working with the _portable_ version before being
ported to the TI platform.  

It is a very simple (simple minded?) implementation of AES, but produces FIPS
compliant output. It is not suitable for real world usage, but only serves as
an educational excercise.  

STATUS  

The KeyExpanson and Cypher routines produce FIPS-197 compliant output as verified with a block-by-block comparison to the "APPENDIX A - KEY EXPANSION EXAMPLES" and "APPENDIX B – CIPHER EXAMPLE" in the FIPS 197 documentation: https://csrc.nist.gov/files/pubs/fips/197/final/docs/fips-197.pdf  (See tiAES-C_version/portable/src/keyutils.c and tiAES-C_version/portable/src/encr.c)  

Currently the InvCypher routine (tiAES-C_version/portable/src/decr.c) does not correctly decrypt. It compiles and runs without error, but the resulting binary does not match the original cleartext. Obviously some work is needed there.  

The portable version compiles cleanly with Clang 16.0.6 on FreeBSD, GCC 7.5.0 on NetBSD, and GCC 11.4.0 on Linux.

There is not yet a padding scheme in place. (See Issues)  


