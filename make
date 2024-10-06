rm -f ethrand
gcc -O2 -g -I. ethrand.c sha3/sph_keccak.c -o ethrand -lsecp256k1 -lssl -lcrypto
