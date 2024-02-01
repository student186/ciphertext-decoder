# ciphertext-decoder
A C++ Ciphertext class that contains methods for manually and automatically decrypting ciphertext encoded by Caesar, linear, monoalphabetic substitution and Vigenere ciphers.

## Files
- Ciphertext.h: A class containing methods for manual and automatic decryption  <br>
- main.cpp: Program to test the methods from Ciphertext.h <br>
- keys.txt: Text file containing ~150,000 words (keys of different length) <br>
- dictionary.txt: Text file for checking if words of decrypted ciphertext are valid for the Vigenere Cipher <br>

## Demo
Testing Caesar cipher decryption (with known shift of 7):
```
// main.cpp
Ciphertext c1 = Ciphertext("Aopz pz alzapun aol jhlzhy jpwoly. Pm aol tlzzhnl pz ylhkhisl aolu aol jpwolyalea ohz illu zbjjlzzmbssf kljyfwalk.");
c1.ccDecoder(7);
c1.display();
```
```
...\ciphertext-decoder> g++ main.cpp
...\ciphertext-decoder> ./a
this is testing the caesar cipher. if the message is readable then the ciphertext has been successfully decrypted.
```
<br>

Testing linear cipher decryption (with known parameters a = 3, b = 4): 
```
// main.cpp
Ciphertext c2 = Ciphertext("kadh dh krhkdsx kar mdsrfe ldyare. du kar prhhfxr dh erfofimr kars kar ldyarekrwk afh irrs hnllrhhunmmz orlezykro.");
c2.lcDecoder(3,5);
c2.display();
```
```
...\ciphertext-decoder> g++ main.cpp
...\ciphertext-decoder> ./a
this is testing the linear cipher. if the message is readable then the ciphertext has been successfully decrypted.
```
<br/>

Testing monoalphabetic substitution cipher decryption (with known substitution):
```
// main.cpp
Ciphertext c3 = Ciphertext("BIOK OK BVKBODH BIV CXDXPGWIPUVBOE KZUKBOBZBOXD EOWIVJ. OS BIV CVKKPHV OK JVPQPUGV BIVD BIV EOWIVJBVNB IPK UVVD KZEEVKKSZGGL QVEJLWBVQ.");
c3.mscDecoder2("PUEQVSHIORFGCDXWTJKBZYANLM");
c3.display();
```

```
...\ciphertext-decoder> g++ main.cpp
...\ciphertext-decoder> ./a
this is testing the monoalphabetic substitution cipher. if the message is readable then the ciphertext has been successfully decrypted.
```
<br>

Testing Vigenere cipher (automatic decryption by brute force of ~150,000 keys):
```
// main.cpp
Ciphertext c4 = Ciphertext("Zf lri'dv lbryueg srf drnqra brrnjfmghf, bcg'me praq ko gks dzguw dxrcr. Zvqe a edbpfm jrfp fr n uozuoz vszkeafs ujn'g tiuke rqcgxh, gks zvxg ocszcno gfvp vv ha wiag o drnqra brrnjfmgh. Jh qdvaghr fye Edbpfm Cdfmxrnsv Svnruoffr jlht poh lb yznq. Wvq grbfsej if tiuke flabce. Pkcaje gks zlmohf aw rnqrad pnuosiackg kfu'q owwv tb vsq rnq fzutk gks nltgrb. Kfue fvajea qiysee rt brrnjfmghf zwxc iavhmetyb obgenu.", "keys.txt", "dictionary.txt");
c4.vcDecoder();
```

```
...\ciphertext-decoder> g++ main.cpp
...\ciphertext-decoder> ./a
.
.
.
.
.
.
.
sarcasm:
random: if you're looking for random paragraphs, you've come to the right place. when a random word or a random sentence isn't quite enough, the next logical step is to find a random paragraph. we created the random paragraph generator with you in mind. the process is quite simple. choose the number of random paragraphs you'd like to see and click the button. your chosen number of paragraphs will instantly appear.
```
