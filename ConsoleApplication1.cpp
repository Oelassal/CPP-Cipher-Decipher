// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>

using namespace std;
ifstream inputFile;
int choice, choose, s, k, inp;
string ptr, text, keyenc, word;


////////////////// Helpers//////////////////////////////
void WelcomeScreen() {
    cout << "____    __    ____  _______  __        ______   ______  .___  ___. _______ " << endl;
    cout << "\\   \\  /  \\  /   / |   ____||  |      /      | /  __  \\ |   \\/   ||   ____|" << endl;
    cout << " \\   \\/    \\/   /  |  |__   |  |     |  ,----'|  |  |  ||  \\  /  ||  |__   " << endl;
    cout << "  \\            /   |   __|  |  |     |  |     |  |  |  ||  |\\/|  ||   __|  " << endl;
    cout << "   \\    /\\    /    |  |____ |  `----.|  `----.|  `--'  ||  |  |  ||  |____ " << endl;
    cout << "    \\__/  \\__/     |_______||_______| \\______| \\______/ |__|  |__||_______|" << endl;
    cout << "" << endl;
}

// input selector
string selector() {
    cout << "Please Select the input method:\n1)By Typing\n2)By FileName\nChoice:";
    cin >> inp;
    switch (inp) {
    case 1: {
        cout << "Please Type your text here:";
        cin >> text;
        break;
    }

    case 2: {
        cout << "Please Type your file name with it's extensions (e.g: WORD.txt)";
        cin >> word;
        inputFile.open(word);
        inputFile >> text;
        cout << "\nText is : " << text;
    }
    }
    return text;
}
//for affine cipher
int modInverse(int k) {
    for (int i = 0; i < 26; i++) {
        int flag = (i * k) % 26;
        if (flag == 1) {
            return i;
        }
    }
    return -1;
}
//simple vigenere key generator 
string generateKey(string str, string key)
{
    int x = str.size();

    for (int i = 0; ; i++)
    {
        if (x == i)
            i = 0;
        if (key.size() == str.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}
///////////////End of Helpers///////////////////////////

 string caesar_enc(string text, int s, string *test)
{
    
    string result = "";
    // traverse text
    for (int i=0;i < text.length();i++)
    {
        // apply transformation to each character
        // Encrypt Uppercase letters
        if (isupper(text[i]))
            result += char(int(text[i] + s - 65) % 26 + 65);
       
    //this is for symbols
        else if ((text[i]>= 91 && text[i] <= 96) || (text[i] >= 123 && text[i] <= 127) || text[i] <= 64){
            text[i] = text[i];
        result += text[i];
        }
 
    // Encrypt Lowercase letters
    else
        result += char(int(text[i]+s-97)%26 +97);
    }
    *test = result;
    // Return the resulting string
    ofstream outputFile;
    outputFile.open("encrypted.txt");
    outputFile << result << endl;
    return result;


}
 string affine_enc(string plain_text, int key1, int key2) {
     string cipher_text = "";
     for (int i = 0; i < plain_text.size(); i++) {
         if (isupper(plain_text[i])) {
             cipher_text += char((key1 * int(plain_text[i] - 65) + key2) % 26 + 65);
         }
         else if ((plain_text[i] >= 91 && plain_text[i] <= 96) || (plain_text[i] >= 123 && plain_text[i] <= 127) || plain_text[i] <= 64) {
             plain_text[i] = plain_text[i];
             cipher_text += plain_text[i];
         }
         else {
             cipher_text += char((key1 * int(plain_text[i] - 97) + key2) % 26 + 97);
         }
     }
     return cipher_text;
 }
 string vigenere_enc(string str, string key)
     {
         string cipher_text;

         for (int i = 0; i < str.size(); i++)
         {
             // converting in range 0-25
             int x = (str[i] + key[i]) % 26;

             // convert into alphabets(ASCII)
             x += 'A';

             cipher_text.push_back(x);
         }
         return cipher_text;
     }
void playfair_enc(string origin) {
     int i, j, k, n;
     string s;
     //Enter key for playfair cipher
     cout << "Enter the key:" << endl;
     string key;
     cin >> key;
     for (i = 0; i < origin.size(); i++) {
         if (origin[i] != ' ')
             s += origin[i];
     }
     vector<vector<char> > a(5, vector<char>(5, ' '));
     n = 5;
     map<char, int> mp;
     k = 0;
     int pi, pj;
     for (i = 0; i < n; i++) {
         for (j = 0; j < n; j++) {
             while (mp[key[k]] > 0 && k < key.size()) {
                 k++;
             }
             if (k < key.size()) {
                 a[i][j] = key[k];
                 mp[key[k]]++;
                 pi = i;
                 pj = j;
             }
             if (k == key.size())
                 break;
         }
         if (k == key.size())
             break;
     }
     k = 0;
     for (; i < n; i++) {
         for (; j < n; j++) {
             while (mp[char(k + 'a')] > 0 && k < 26) {
                 k++;
             }
             if (char(k + 'a') == 'j') {
                 j--;
                 k++;
                 continue;
             }
             if (k < 26) {
                 a[i][j] = char(k + 'a');
                 mp[char(k + 'a')]++;
             }
         }
         j = 0;
     }
     string ans;
     if (s.size() % 2 == 1)
         s += "x";
     for (i = 0; i < s.size() - 1; i++) {
         if (s[i] == s[i + 1])
             s[i + 1] = 'x';
     }
     map<char, pair<int, int> > mp2;
     for (i = 0; i < n; i++) {
         for (j = 0; j < n; j++) {
             mp2[a[i][j]] = make_pair(i, j);
         }
     }

     for (i = 0; i < s.size() - 1; i += 2) {
         int y1 = mp2[s[i]].first;
         int x1 = mp2[s[i]].second;
         int y2 = mp2[s[i + 1]].first;
         int x2 = mp2[s[i + 1]].second;
         if (y1 == y2) {
             ans += a[y1][(x1 + 1) % 5];
             ans += a[y1][(x2 + 1) % 5];
         }
         else if (x1 == x2) {
             ans += a[(y1 + 1) % 5][x1];
             ans += a[(y2 + 1) % 5][x2];
         }
         else {
             ans += a[y1][x2];
             ans += a[y2][x1];
         }
     }
     cout << "PlayFair Cipher For Text is: " << ans << endl;
   
 }
void rail_fence() {
     int t, n, m, i, j, k, sum = 0;
     string s;
    /* cout << "Enter the message" << '\n';
     cin >> s;*/
     cout <<"Text entered is:"<< text;
     cout << "\nEnter key:";
     cin >> n; 
     cout << "Rail Fence Cipher For Text is: ";
     vector<vector<char>> a(n, vector<char>(text.size(), ' '));
     j = 0;
     int flag = 0;
     char read;
     //cipher here
     for (i = 0; i < text.size(); i++) {
         a[j][i] = text[i];
         if (j == n - 1) {
             flag = 1;
         }
         else if (j == 0)
             flag = 0;
         if (flag == 0) {
             j++;
         }
         else j--;
     }
     //reading off
     for (i = 0; i < n; i++) {
         for (j = 0; j < text.size(); j++) {
             if (a[i][j] != ' '){
                 cout << a[i][j];
             }
         }
     }
     
 }
 ///////////////Decryption Functions///////////////////////////
    string caesar_dec(string text, int s) {
        string result = "";

        // traverse text
        for (int i = 0; i < text.length(); i++)
        {
            // apply transformation to each character
            // Encrypt Uppercase letters
            if (isupper(text[i]))
                result += char(int(text[i] - s - 65) % 26 + 65);

            //this is for symbols
            else if ((text[i] >= 91 && text[i] <= 96) || (text[i] >= 123 && text[i] <= 127) || text[i] <= 64) {
                text[i] = text[i];
                result += text[i];
            }

            // Encrypt Lowercase letters
            else
                result += char(int(text[i] - s - 97) % 26 + 97);
        }

        // Return the resulting string
        ofstream outputFile;
        outputFile.open("encrypted.txt");
        outputFile << result << endl;
        return result;
    }
    string affine_dec(string cipher_text, int key1, int key2)
    {
        string plain_text = "";
        int key_inverse = modInverse(key1);
        if (key_inverse == -1) {
            return "Not exist";
        }
        cout << "Key Inverse: " << key_inverse << endl;
        for (int i = 0; i < cipher_text.size(); i++) {
            if (isupper(cipher_text[i])) {
                plain_text += char(((((cipher_text[i] - 65 - key2) % 26 + 26) % 26) * key_inverse) % 26 + 65);
            }
            else if ((plain_text[i] >= 91 && plain_text[i] <= 96) || (plain_text[i] >= 123 && plain_text[i] <= 127) || plain_text[i] <= 64) {
                plain_text[i] = plain_text[i];
                cipher_text += plain_text[i];
            }
            else {
                plain_text += char(((((cipher_text[i] - 97 - key2) % 26 + 26) % 26) * key_inverse) % 26 + 97);
            }
        }
        return plain_text;
    }
    string vigenere_dec(string cipher_text, string key)
    {
        string orig_text;

        for (int i = 0; i < cipher_text.size(); i++)
        {
            // converting in range 0-25
            char x = (cipher_text[i] - key[i] + 26) % 26;

            // convert into alphabets(ASCII)
            x += 'A';
            orig_text.push_back(x);
        }
        return orig_text;
    }



    int main()
    {
       
        
        
        
        /// End Of General

       
       
       do {
           WelcomeScreen();
            cout << "Please choose Whether to Encrypt or Decrypt the File:\n1)Encrypt\n2)Decrypt\n3)Exit\nChoice:";
            cin >> choice;
            switch (choice) {
                
                //This Choice Is For Encryption 
            case 1:
            {
                selector();
                cout << "\nchoose the method :\n1.Ceasar (additive) cipher\n2.Affine cipher\n3.Simple shift vignere cipher" << endl;
                cout << "4.Fall vignere cipher.\n5.Playfair cipher\n6.Rail Fence cipher.\n7.S-box" << endl;
                cin >> choose;
                if (choose == 1) {
                    cout << "====================Caesar Encryption====================" << endl;
                    cout << "\nText : " << text;
                    cout << "\nShift: ";
                    cin >> s;
                    caesar_enc(text, s, &ptr);
                    cout << "\nCaesar Encryption : " << ptr << endl;
                    system("PAUSE");
                    system("CLS");
                }


                else if (choose == 2)
                {
                    cout << "\n====================Affine Encryption====================" << endl;
                    cout << "\nText : " << text;
                    //First key for affine cipher
                    cout << "\nPlease Enter The First Key:";
                    cin >> s;
                    //second key for affine cipher
                    cout << "\nPlease Enter The Second Key:";
                    cin >> k;
                    //cipher Text holds the result from caesar encryption by getting encrypted text from file and assigning it here
                    string cipher_text = affine_enc(text, s, k);
                    cout << "Affine Cipher For Text is: " << cipher_text << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else if (choose == 3)
                {
                    cout << "\n====================Simple vigenere Encryption====================" << endl;
                    cout << "\nText : " << text;
                    cout << "\nPlease Enter The Keyword:";
                    cin >> keyenc;
                    string key = generateKey(text,keyenc);
                    cout << "Simple Vigenere Cipher For Text is: " << vigenere_enc(text, key) << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else if (choose == 4)
                {
                    cout << "\n====================Fall vignere cipher Encryption====================" << endl;
                    cout << "\nText : " << text;
                  
                }
                else if (choose == 5)
                {
                    cout << "\n====================Playfair Encryption====================" << endl;
                    cout << "\nText : " << text << endl;
                     playfair_enc(text);
                    system("PAUSE");
                    system("CLS");
                }
                else if (choose == 6)
                {
                    cout << "\n====================Rail Fence Cipher Encryption===================="<<endl;
                    rail_fence();
                    cout << endl;
                    system("PAUSE");
                    system("CLS");
                }

                break;    }
        
                //This Choice Is For Decryption 
            case 2: {
                selector();
                cout << "\nchoose the method :\n1. Ceasar (additive) cipher\n2. Affine cipher\n3. Simple shift vignere cipher" << endl;
                cout << "4.Fall vignere cipher.\n5.Playfair cipher\n6.Unknown cipher.\n7.S - box" << endl;
                cin >> choose;
                if (choose == 1) {
                    cout << "\nText : " << text;
                    cout << "\nPlease enter the Shift (integers only): ";
                    cin >> s;
                    cout << "\nCaesar Decryption: " << caesar_dec(text, s);
                    system("PAUSE");
                    system("CLS");
                }
                else if (choose == 2)
                {
                    cout << "\n====================Affine Encryption====================";
                   
                    //First key for affine cipher
                    cout << "\nPlease Enter The First Key (integers only):";
                    cin >> s;
                    //second key for affine cipher
                    cout << "\nPlease Enter The Second Key:(integers only)";
                    cin >> k;
                    cout << "Affine Cipher For Text is: " << affine_dec(text, s, k) << endl;
                    system("PAUSE");
                    system("CLS");
                }
                break; }
                 
            case 3:
                break;
            default:
                cout << "Please Check your choice";


            }
         
        } while (choice != 3);
        return 0;
    }