rm -f ethrand
gcc -O3 -I. ethrand.c sha3/sph_keccak.c -o ethrand -lsecp256k1 -lssl -lcrypto -march=native
