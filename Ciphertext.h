/*
The Ciphertext class contains various methods for decrypting a given ciphertext that was encoded using Caesar cipher (cc), 
linear cipher (lc), monoalphabetic substitution cipher (msc) or Vigenere cipher (vc). The methods that decrypt cc, lc, msc
are not automatic, meaning that the keys/parameters must be determined before decoding the ciphertext. The method vc is
automatic and works by bruteforce search of keys in text files containing different length keys. The ciphertext's
corresponding plaintext and key is found when the first five words of the decrypted ciphertext are valid words.
*/

#include <iostream>
#include <cctype>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_set> // unordered_set for faster lookups

using namespace std;

class Ciphertext {
    private:
        string cText; // ciphertext
        string pText; // plaintext
        
        int* kTextDigits; // keyedText represented as digits 0-25 (part of letterToDigits)
        int* cTextDigits; // cText represented as digits 0-25 (part of letterToDigits)
        int* result; // cTextDigits - kTextDigits (part of letterToDigits)
        unordered_set<string> dictionary;
        string keyFileName;
        string dictionaryFileName;

        void reset() {
            pText = "";
        }

        // helper function for lcDecoder
        int modInverse(int A, int M) {
            for (int X = 1; X < M; X++)
                if (((A % M) * (X % M)) % M == 1) {
                    return X;
                }
                return -1;
        }

        string tolowerStr(string str) {
            for (int i = 0; i < str.size(); i++) {
                if (isalpha(str[i])) {
                    str[i] = tolower(str[i]);
                }
            }
            return str;
        }

        // helper function for mscDecoder1
        void substituteLetter(string &cipherText, char ctLetter, char substitution) {
            for (int i = 0; i < cipherText.size(); i++) {
                if (cipherText[i] == toupper(ctLetter)) {
                    cipherText[i] = substitution;
                }
            }
            cout << cipherText << endl;
        }

        //// helper functions for vcDecoder ////
        // 1. creates a new string that contains the key/keyword placed in sections of the ciphertext containing letters
        /* e.g., if key is ok, then      cipherText: bcde, felwa. 
                                         keyedText:  okok, okoko. */
        string keyedText(string key) {
            reset();
            string keyLower = tolowerStr(key);
            string result = cText; // create a copy of cText
            int j = 0; // counter that keeps track of key length
            for (int i = 0; i < cText.size(); i++) {
                if (isalpha(result[i])) {   // if character encountered is a letter, replace it with something
                    if (j < keyLower.size()) {       // if keyword hasn't fully been copied
                        result[i] = key[j];     // replace ciphertext letter with keyword letter
                    }
                    else {                      // if the keyword has fully been copied
                        j = 0;                  // start over at the first letter of the keyword
                        result[i] = keyLower[j];     // begin replacement with the letters at the start of the keyword
                    }
                    j++;                    // increment j here to maintain the current letter of the keyword
                }
                                            // if character isn't a letter don't do anything
            }
            return result;
        }
        // 2. creates numeric arrays representing keyedText and  cText with letters as 0-25, also creates results array
        void letterToDigits(string keyedTxt) {
            // loop for constructing kTextDigits and cTextDigits arrays
            string cTextLower = tolowerStr(cText);
            for (int i = 0; i < keyedTxt.size(); i++) {
                if (isalpha(keyedTxt[i]) && isalpha(cTextLower[i])) {
                    kTextDigits[i] = (int)keyedTxt[i] - 97; 
                    cTextDigits[i] = (int)cTextLower[i] - 97;
                }
                else { // -1 is used as a placeholder for non-letter characters
                    kTextDigits[i] = -1;
                    cTextDigits[i] = -1;
                }
            }
            // loop for constructing result array
            for (int i = 0; i < keyedTxt.size(); i++) {
                result[i] = (((cTextDigits[i] - kTextDigits[i]) + 26) % 26) + 97; // + 26 to handle negative mod, % 26 to wrap around, + 97 to conert to proper ascii for conversion to letter later on
                if (kTextDigits[i] == -1) { // only need to check for one of the arrays as non-letter characters are in the same position
                    result[i] = -1;
                } 
            }
        }
        // 3. constructs the potential plaintext from the results array
        void getPPText() {
            for (int i = 0; i < cText.size(); i++) {
                if (result[i] >= 0) {
                    pText = pText + (char)result[i];
                }
                else {
                    pText = pText + cText[i];
                }
            }
        }
        // 4. checks if first five words of the decrypted ciphertext are valid words
        bool areConsecutiveWordsValid() {
            istringstream iss(pText);
            string word;
            int consecutiveValidCount = 0;
            while (iss >> word) {
                if (dictionary.count(word)) {
                    consecutiveValidCount++;
                    if (consecutiveValidCount == 5) {   // can modify the 5
                        return true;
                    }
                } else {
                    consecutiveValidCount = 0;
                }
            }
            return false;
        }
        
        unordered_set<string> loadDictionary(const string& dictionaryFile) {
            unordered_set<string> dictionary;
            ifstream file(dictionaryFile);
            if (file.is_open()) {
                string word;
                while (getline(file, word)) {
                    dictionary.insert(word);
                }
                file.close();
            } 
            else {
                cerr << "Error opening dictionary file!\n";
            }
            return dictionary;
        }


    public:
        Ciphertext(string cText) {  // constructor for other ciphers
            this->cText = cText;
            pText = "";
        }

        Ciphertext(string cText, string keyFileName, string dictionaryFileName) { // constructor for vigenere cipher
            this->cText = cText;
            pText = "";
            kTextDigits = new int[cText.size()];
            cTextDigits = new int[cText.size()];
            result = new int[cText.size()];
            this->dictionaryFileName = dictionaryFileName;
            this->keyFileName = keyFileName;
            this->dictionary = loadDictionary(dictionaryFileName);
            
        }

        ~Ciphertext() {
            delete[] kTextDigits;
            delete[] cTextDigits;
            delete[] result; 
        }

        void display() {
            cout << pText << endl;
        }

        // manual decoder for Caesar cipher, where shift is determined by calculating mostFreqEngLetter - mostFreqCTLetter 
        void ccDecoder(int shift) {
            reset();
            int length = cText.size();
            char* result = new char[length];
            for (int i = 0; i < length; i++) {
                if (isalpha(cText[i])) {
                    result[i] = (int(tolower(cText[i]) - 97 - shift + 26)) % 26 ;
                    result[i] = char(result[i] + 97);
                }
                else {
                    result[i] = cText[i];
                }
            }      
            for (int i = 0; i < length; i++) {
                pText += result[i];
            }
            delete[] result;
        }

        // manual decoder for linear cipher
        void lcDecoder(int a, int b) {
            reset();
            string cTextLower = tolowerStr(cText); 
            for (int i = 0; i < cTextLower.size(); i++) {
                if (isalpha(cTextLower[i])) {
                    char decodedChar = (char)(((modInverse(a, 26) * ((cTextLower[i] - 'a' - b + 26) % 26)) + 26) % 26 + 'a');
                    pText = pText + decodedChar;
                }
                else {
                    pText += cText[i];
                }
            }
        }
        // manual decoder for monoalphabetic substitution cipher that decrypts cText from user input of individual letters
        void mscDecoder1() {
            reset();
            cout << cText << endl << endl;
            //tolowerStr(cipherText); commented out due to letters being replaced more than once; need uppercase (non-replaced) to distinguish from lowercase (replaced)
            string ctCopy = cText;
            char ctLetter; 
            char substitution;
            while (substitution != '0') {
                cout << "Enter ciphertext letter: ";
                cin >> ctLetter;
                cout << "Enter letter to substitute (0 to exit): ";
                cin >> substitution;
                substituteLetter(cText, ctLetter, substitution);
                cout << endl;
            }
            pText = cText;
        }

        // alternative manual decoder for monoalphabetic substitution cipher that decrypts cText from user input of the permutation
        void mscDecoder2(string substitution) {
            reset();
            string cTextLower = tolowerStr(cText);
            string subsLower = tolowerStr(substitution);
            map<char, char> substitutionMap;
            if (substitution.length() != 26) {
                cerr << "Error: Substitution string must be of length 26." << endl;
                exit(1);
            }
            /* this loop causes incorrect decoding, commented out as a reminder of improper assignment
            int i = 0;
            for (char letter = 'a'; letter <= 'z'; letter++) {
                substitutionMap[letter] = substitution[i];
                i++;
            }
            */
            
            char start = 'a';
            for (int i = 0; i < subsLower.size(); i++) {
                substitutionMap[subsLower[i]] = start;
                start = char(start + 1);
            }     

            string decodedText = cTextLower;
            for (int i = 0; i < decodedText.size(); i++) {
                if (isalpha(decodedText[i])) {
                    decodedText[i] = substitutionMap[decodedText[i]];
                }
                else {
                    decodedText[i] = cTextLower[i];
                }
            }
            pText = decodedText;
        }

        void vcDecoder() {
            // create an instance of filestream class
            ifstream keysFile;
            // open the file
            keysFile.open(keyFileName);

            // error check
            if (keysFile.fail()) {
                cerr << "Error opening file!" << endl;
                exit(1);
            }

            string key;
            // read file until end is reached
            while (!keysFile.eof()) {
                keysFile >> key;
                string keyedTxt = keyedText(key);
                letterToDigits(keyedTxt);
                getPPText();
                if (areConsecutiveWordsValid()) {
                    cout << key << ": ";
                    display();
                    break; // remove this line if further decrypting is needed
                }
                else {
                    cout << key << ": ";
                }
                cout << endl;
            }
            keysFile.close();
        }


};