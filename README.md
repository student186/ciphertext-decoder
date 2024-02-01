# ciphertext-decoder
A C++ Ciphertext class that contains methods for manually and automatically decrypting ciphertext encoded by Caesar, linear, monoalphabetic substitution and Vigenere ciphers.

## Files
- Ciphertext.h: A class containing methods for manual and automatic decryption.  <br>
- main.cpp: Program to test the methods from Ciphertext.h <br>

## Demo
Testing Caesar cipher decryption (with known shift of 7):
```
Ciphertext c1 = Ciphertext("Aopz pz alzapun aol jhlzhy jpwoly. Pm aol tlzzhnl pz ylhkhisl aolu aol jpwolyalea ohz illu zbjjlzzmbssf kljyfwalk.");
c1.ccDecoder(7);
c1.display();
```
```
...\ciphertext-decoder>
```
\
Testing linear cipher decryption (with known parameters a = 3, b = 4): 
```

```
\
Testing monoalphabetic substitution cipher decryption (with known substitution):
```

```
\
Testing Vigenere cipher (automatic decryption by brute force of ~150,000 keys)
```

```
