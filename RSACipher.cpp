#include "Ciphers.h"
#include "ShowMenu.h"

#include <iostream>
#include <vector>

using namespace std;

vector<int> encrypt(string text, int publicKey1, int publicKey2)
{
    vector<int> encryptedText;
    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];
        int ascii = c;
        encryptedText.push_back(ascii);
    }

    vector<int> encryptedResult;
    for (int i = 0; i < encryptedText.size(); i++)
    {
        int s = encryptedText[i];
        for (int k = 0; k < (publicKey1 - 1); k++)
        {
            s = s * encryptedText[i] % publicKey2;
        }
        encryptedResult.push_back(s);
    }
    return encryptedResult;
}

string decrypt(vector<int> text, int privateKey, int modulus)
{
    string decryptedResult;
    for (int i = 0; i < text.size(); i++)
    {
        int s = text[i];
        for (int k = 0; k < privateKey - 1; k++)
        {
            s = s * text[i] % modulus;
        }
        char c = s;
        decryptedResult += c;
    }
    return decryptedResult;
}

void cipherRSA()
{
	showCipherMenu("RSA");
}