# ethaddr

calculate a new ethereum address (with private key) with the lowest pow value.

```
root@loderunner:~/ethaddr# ./ethrand 
62066030af04b03d827e694711da1ef8c84bbce8ce07b2ebc1aa5a7a634c3f90 0a483a521d1bfdd090c955eb34a71c8f07101fab (1 leading zeroes)
47a6943045c36bf14f951911ec5a5428627c801bd3bf62401dbf2b1d8c8de93e 00c72915d8b082d4f8a2c7da9526816851d88afc (2 leading zeroes)
f095c7688390d41113dd975a767bc9ac9814f02dfb47680a539dc48f85080dd3 0004fdd2ce509c155400fe0811f8e29c94f16909 (3 leading zeroes)
b227b79aaa84103b7062fe671c615428bf3315e933f8cc7932e68cf2731c9ad4 0000ea0b3dbeb37196dfdfa341a430e5a804b4db (4 leading zeroes)
3cc195b56fffb413cee64aba3646aa77b0dc754a220f4ff05f7dbef8029aa419 00000d5f8791e3d0bc3af877667ec36e260f6419 (5 leading zeroes)
ab4d0f4f019054b8be5d30ea731d781d385600c2872de4a6ca4878ed1c81755a 000000b4d4a455b94071408481c90ca3a2f5dbce (6 leading zeroes)
```

```
to build:

./make

requires libsecp256k1-dev and libssl-dev
```
