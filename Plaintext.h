/*
The Plaintext class contains methods for encrypting a given plaintext using Caesar cipher (cc), 
linear cipher (lc), monoalphabetic substitution cipher (msc) or Vigenere cipher (vc). The purpose
of this class is to check the correctness of methods in the Ciphertext class.
*/

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Plaintext {
    private: 
        string cText; // ciphertext
        string pText; // plaintext  
        int pLength; 
        // converts the plaintext to lowercase
        string tolowerStr(string str) {
            for (int i = 0; i < str.size(); i++) {
                if (isalpha(str[i])) {
                    str[i] = tolower(str[i]);
                }
            }
            return str;
        }
        // resets the ciphertext in case multiple methods are called with the same object (would concatenate previous strings)
        void reset() {
            cText = "";
        }

    public:
        Plaintext(string pText) {
            this->pText = tolowerStr(pText); // convert pText to lowercase when Plaintext instance is created
            pLength = pText.size();
            cText = "";
        } 
        void display() {
            cout << cText << endl;
        }
        string getCText() {
            return cText;
        }
        void ccEncoder(int shift) {
            reset();
            int* temp = new int[pLength]; // temporary array that holds the numbers representing letters a-z
            for (int i = 0; i < pLength; i++) {
                if (isalpha(pText[i])) {
                    temp[i] = (((int)pText[i] - 97 + shift) % 26) + 97;
                    cText = cText + (char)temp[i];
                }
                else {
                    temp[i] = -1; // -1 to represent non-letter characters (this line could be removed)
                    cText = cText + pText[i];
                }
            }
            delete[] temp;
        }
        void lcEncoder(int a, int b) {
            reset();
            int* temp = new int[pLength];
            for (int i = 0; i < pLength; i++) {
                if (isalpha(pText[i])) {
                    temp[i] = ((((int)pText[i] - 97)*a + b) % 26) + 97; // -97 converts 97-122 to 0-25, *a + b is E alg., %26 to wrap around, +97 converts back to 97-122
                    cText = cText + (char)temp[i];
                }
                else {
                    cText = cText + pText[i];
                }
            }
            delete[] temp;
        }
        void mscEncoder(string substitution) {
            reset();
            map<char, char> substitutionMap;
            if (substitution.length() != 26) {
                cerr << "Error: Substitution string must be of length 26." << endl;
                exit(1);
            }
            int i = 0;
            for (char letter = 'a'; letter <= 'z'; letter++) {
                substitutionMap[letter] = substitution[i];
                i++;
            }
            for (int j = 0; j < pLength; j++) {
                if (isalpha(pText[j])) {
                    cText = cText + substitutionMap[pText[j]];
                }
                else {
                    cText = cText + pText[j];
                }
            }
        }
        // keyword needs to be a valid word (in dictionary.txt) if vcDecoder is used after vcEncoder
        void vcEncoder(string keyword) {
            reset();
            string keyLower = tolowerStr(keyword);
            int* temp1 = new int[keyword.size()]; // temporary array1 to hold the shifts 0-25 of each letter in the keyword
            int* temp2 = new int[pLength]; // temporary array2 to hold the numbers 0-25 representing the pText
            // find all shifts of the keyword
            for (int i = 0; i < keyword.size(); i++) {
                temp1[i] = (int)keyLower[i] - 97;
            }
            // construct temporary array2
            for (int i = 0; i < pLength; i++) {
                if (isalpha(pText[i])) {
                    temp2[i] = (int)pText[i] - 97;
                }
                else {
                    temp2[i] = -1;
                }
            }
            // construct numbers representing cText while constructing the final cText
            int j = 0; // counter to keep track of key length
            for (int i = 0; i < pLength; i++) {
                if (temp2[i] >= 0) {
                    if (j < keyword.size()) {
                        temp2[i] = ((temp2[i] + temp1[j]) % 26) + 97;
                        cText = cText + (char)temp2[i];
                    }
                    else {
                        j = 0;
                        temp2[i] = ((temp2[i] + temp1[j]) % 26) + 97;
                        cText = cText + (char)temp2[i];
                    }
                    j++;
                }
                else { // temp2[i] < 0 (non-letter character)
                    cText = cText + pText[i];
                }
            }
            delete[] temp1;
            delete[] temp2;
        }

};