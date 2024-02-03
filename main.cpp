#include "Ciphertext.h"
#include "Plaintext.h"
#include <iostream>

using namespace std;

int main() {
    //// c1,c2,c3 are for manual decryption. c4 is automatic decryption. ////    
    //Ciphertext c1 = Ciphertext("Aopz pz alzapun aol jhlzhy jpwoly. Pm aol tlzzhnl pz ylhkhisl aolu aol jpwolyalea ohz illu zbjjlzzmbssf kljyfwalk.");
    //Ciphertext c2 = Ciphertext("wz");
    //Ciphertext c3 = Ciphertext("bdactfgehjiklonmpqsruvxwy");
    //Ciphertext c4 = Ciphertext("Zf lri'dv lbryueg srf drnqra brrnjfmghf, bcg'me praq ko gks dzguw dxrcr. Zvqe a edbpfm jrfp fr n uozuoz vszkeafs ujn'g tiuke rqcgxh, gks zvxg ocszcno gfvp vv ha wiag o drnqra brrnjfmgh. Jh qdvaghr fye Edbpfm Cdfmxrnsv Svnruoffr jlht poh lb yznq. Wvq grbfsej if tiuke flabce. Pkcaje gks zlmohf aw rnqrad pnuosiackg kfu'q owwv tb vsq rnq fzutk gks nltgrb. Kfue fvajea qiysee rt brrnjfmghf zwxc iavhmetyb obgenu.", "keys.txt", "dictionary.txt");


    // Caesar cipher decryption (with known shift of 7)
   // c1.ccDecoder(7);
   // c1.display();
   // cout << endl;


    // linear cipher decryption (with known parameters a = 3, b = 4)
    //c2.lcDecoder(3,5);
    //c2.display();
    //cout << endl;    


    // monoalphabetic substitution cipher decryption (with known substitution)
                  //ABCDEFGHIJKLMNOPQRSTUVWXYZ  
    //c3.mscDecoder2("bdactfgehjiklonmpqsruvxwyz");
    //c3.display();
    //cout << endl;

    
    // Vigenere cipher (automatic decryption by brute force of ~150,000 keys)
    //c4.vcDecoder();

    Plaintext p1("Hello, my name is Bob and I like to swim!");
    //p1.lcEncoder(1,2);
    //p1.display();
    //p1.ccEncoder(1);
    //p1.display();
    p1.vcEncoder("key");
    p1.display();
    
    return 0;
}
