// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Created by OMAR ALASSAL https://github.com/Oelassal
/*_________________________________________________________________________________
|Please Notice that playfair encryptionand decryption are still under development. |
|Feel free to improve this code by forking, or pulling the code into you workspace.|
|Please Don't Use this code business wise unless referred to the owner of the code.|
|                                                                                  |
|**ALERT** : This Version of the application doesn't accept space between words.   |
|_________________________________________________________________________________*/

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>

using namespace std;


////////////////// Identifiers and Selection Function/////////
void WelcomeScreen() {
    cout << "____    __    ____  _______  __        ______   ______  .___  ___. _______ " << endl;
    cout << "\\   \\  /  \\  /   / |   ____||  |      /      | /  __  \\ |   \\/   ||   ____|" << endl;
    cout << " \\   \\/    \\/   /  |  |__   |  |     |  ,----'|  |  |  ||  \\  /  ||  |__   " << endl;
    cout << "  \\            /   |   __|  |  |     |  |     |  |  |  ||  |\\/|  ||   __|  " << endl;
    cout << "   \\    /\\    /    |  |____ |  `----.|  `----.|  `--'  ||  |  |  ||  |____ " << endl;
    cout << "    \\__/  \\__/     |_______||_______| \\______| \\______/ |__|  |__||_______|" << endl;
    cout << "" << endl;
}
ifstream inputFile;
int choice, choose, s, k, inp;
string ptr, text, keyenc, word;
/// End Of General
//defining arrays, integers and inputs for playfair
//bool alpha[200];
//char table[6][6];
//int dcpKey[105], n;
//int A, B, key, prIdx, x1, x2, y1, y2;
//string pairing, mPlay, kPlay, decTxt = "", encTxt = "";
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
//Playfair cipher table constructor
//void constructTable() {
//    string kPlay;
//    cout << "Enter The playfair Key:" << endl;
//    getline(cin, kPlay);
//
//    int keyIdx = 0;
//    int i, j;
//    for (i = 0; i < 5 && keyIdx < kPlay.size();) {
//        for (j = 0; j < 5 && keyIdx < kPlay.size();) {
//            kPlay[keyIdx] = tolower(kPlay[keyIdx]);
//            while (keyIdx < kPlay.size() && (!isalpha(kPlay[keyIdx]) || alpha[kPlay[keyIdx]])) keyIdx++;
//            if (keyIdx >= kPlay.size())break;
//            if (kPlay[keyIdx] == 'i' || kPlay[keyIdx] == 'j') {
//                table[i][j] = 'i';
//                alpha['i'] = alpha['j'] = 1;
//            }
//            else {
//                table[i][j] = kPlay[keyIdx];
//                alpha[kPlay[keyIdx]] = 1;
//            }
//            keyIdx++;
//            j++;
//        }
//        if (keyIdx < kPlay.size()) i++;
//    }
//
//    for (char ch = 'a'; ch <= 'z'; ch++) {
//        if (!alpha[ch]) {
//            if (ch == 'i' || ch == 'j') {
//                if (alpha[i] || alpha[j]) continue;
//                else {
//                    table[i][j] = 'i';
//                    alpha['i'] = alpha['j'] = 1;
//                }
//            }
//            else table[i][j] = ch;
//
//            alpha[ch] = 1;
//            if (j >= 4) j = 0, i++;
//            else j++;
//
//        }
//    }
//
//    for (i = 0; i < 5; i++) {
//        for (j = 0; j < 5; j++) {
//            cout << table[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
////playfair constructing pairs
//void constructPairs(){
//prIdx = 0;
//for (int i = 0; i < mPlay.size(); i++) {
//    if (!isalpha(mPlay[i])) continue;
//    if ((i == mPlay.size() - 1 && prIdx % 2 == 0) || mPlay[i] == mPlay[i + 1]) {
//        pairing[prIdx] = mPlay[i];
//        prIdx++;
//        pairing[prIdx] = 'x';
//        prIdx++;
//    }
//    else pairing[prIdx++] = mPlay[i];
//}
//pairing[prIdx] = '\0';
//cout << pairing << endl;
//}
////find elements in table (playfair)
//void findInTableEN(){
//for (int idx = 0; idx < prIdx; idx++) {
//    bool fnd = 0;
//    for (int i = 0; i < 5; i++) {
//        for (int j = 0; j < 5; j++) {
//            if (pairing[idx] == table[i][j]) {
//                x1 = i;
//                y1 = j;
//                fnd = 1;
//            }
//            else if ((pairing[prIdx] == 'i' || pairing[prIdx] == 'j') && table[i][j] == 'i') {
//                x1 = i;
//                y1 = j;
//                fnd = 1;
//            }
//        }
//        if (fnd) break;
//    }
//
//    fnd = 0; idx++;
//    for (int i = 0; i < 5; i++) {
//        for (int j = 0; j < 5; j++) {
//            if (pairing[idx] == table[i][j]) {
//                x2 = i;
//                y2 = j;
//                fnd = 1;
//            }
//            else if ((pairing[prIdx] == 'i' || pairing[prIdx] == 'j') && table[i][j] == 'i') {
//                x2 = i;
//                y2 = j;
//                fnd = 1;
//            }
//        }
//        if (fnd) break;
//    }
//    encrypt();
//}
//}
//void findInTableDE() {
//    for (int idx = 0; idx < prIdx; idx++) {
//        bool fnd = 0;
//        for (int i = 0; i < 5; i++) {
//            for (int j = 0; j < 5; j++) {
//                if (pairing[idx] == table[i][j]) {
//                    x1 = i;
//                    y1 = j;
//                    fnd = 1;
//                }
//                else if ((pairing[prIdx] == 'i' || pairing[prIdx] == 'j') && table[i][j] == 'i') {
//                    x1 = i;
//                    y1 = j;
//                    fnd = 1;
//                }
//            }
//            if (fnd) break;
//        }
//
//        fnd = 0; idx++;
//        for (int i = 0; i < 5; i++) {
//            for (int j = 0; j < 5; j++) {
//                if (pairing[idx] == table[i][j]) {
//                    x2 = i;
//                    y2 = j;
//                    fnd = 1;
//                }
//                else if ((pairing[prIdx] == 'i' || pairing[prIdx] == 'j') && table[i][j] == 'i') {
//                    x2 = i;
//                    y2 = j;
//                    fnd = 1;
//                }
//            }
//            if (fnd) break;
//        }
//        decrypt();
//    }
//}
//void constructPairs() {
//    prIdx = 0;
//    for (int i = 0; i < mPlay.size(); i++) {
//        if (!isalpha(mPlay[i])) continue;
//        if ((i == mPlay.size() - 1 && prIdx % 2 == 0) || mPlay[i] == mPlay[i + 1]) {
//            pairing[prIdx] = mPlay[i];
//            prIdx++;
//            pairing[prIdx] = 'x';
//            prIdx++;
//        }
//        else pairing[prIdx++] = mPlay[i];
//    }
//    pairing[prIdx] = '\0';
//    cout << pairing << endl;
//}
//////////////////input selector//////////////////////////////
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
 ////playfair encrypt
 //void encrypt() {
 //    if (x1 == x2) {
 //        encTxt += table[x1][(y1 + 1) % 5];
 //        encTxt += table[x2][(y2 + 1) % 5];
 //    }
 //    else if (y1 == y2) {
 //        encTxt += table[(x1 + 1) % 5][y1];
 //        encTxt += table[(x2 + 1) % 5][y2];
 //    }
 //    else {
 //        encTxt += table[x1][y2];
 //        encTxt += table[x2][y1];
//    }
 //}
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
void sbox_enc(int(&x)[8], int a, int(&k)[3]) 
{    
   /*///////////////////////THE RULE///////////////////\ 
   |P = X1 X2 X3 X4   .......key = k1 k2 k3             |
   |E(X1 X2 X3 X4, K1 K2 K3) = X3 X4 U1 U2              |
   |U1 U2 = X1 X2 (+) T1 T2                             |
   |T1 T2 = S(X3 X4 X3 (+)  K1 K2 K3) ----> MAIN KEY    |
   ////////////////////////////////////////////////////*/
    
    
    //int a is the divisor
    //Collecting Values of S-Box text in array determined in integers;
    int temp[3], temps = 0; 
    int t[2];
    int u[2];
    int resu[4]; //Resu is an array of integers with 4-bit (To Store 0,1 of an integer)
     //X3 and X4 are preserved at first
    resu[0] = x[(5 - a)]; 
    resu[1] = x[(4 - a)];
    //Temps (values of S-Box) = Values of Inserted Text Raised To The Power Of binary Values of S-box 
    temp[0] = resu[0] ^ k[2];  
    temp[1] = resu[1] ^ k[1];
    temp[2] = resu[0] ^ k[0];
    for (int j = 0; j < 3; j++)
    {
        if (temp[j] == 1)
            temps += pow(2, j);
    }
    //Switch Case for temps determining T1 and T2 values (Temp Text1 & Temp Text2)
    switch (temps) 
    {
    case (0):
    {
        u[0] = 1;
        u[1] = 1;
        break;
    }
    case(1):
    {
        u[0] = 0;
        u[1] = 1;
        break;
    }
    case(2):
    {
        u[0] = 0, u[1] = 0;
        break;
    }
    case(3):
    {
        u[0] = 1, u[1] = 0;
        break;
    }
    case(4):
    {
        u[0] = 0, u[1] = 1;
        break;
    }
    case(5):
    {
        u[0] = 0, u[1] = 0;
        break;
    }
    case(6):
    {
        u[0] = 1, u[1] = 1;
        break;
    }
    case(7):
    {
        u[0] = 1, u[1] = 0;
        break;
    }
    }
    t[0] = x[7 - a] ^ u[0];
    t[1] = x[6 - a] ^ u[1];
    resu[2] = t[0];
    resu[3] = t[1];
    for (int j = 0; j < 4; j++)
    {
        x[(7 - j) - a] = resu[j];
    }
    return;

}
///////////////////////////////////////////////////////////////
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
            char x = ((cipher_text[i] - key[i] + 26) % 26);

            // convert into alphabets(ASCII)
            x += 'A';

            orig_text.push_back(x);
        }
        return orig_text;
    }
    void sbox_dec(int(&x)[8], int a, int(&k)[3])
    {
        int temp[3], temps = 0;
        int t[2];
        int u[2];
        int resu[4];
        resu[2] = x[(7 - a)];
        resu[3] = x[(6 - a)];
        temp[0] = resu[2] ^ k[2];
        temp[1] = resu[3] ^ k[1];
        temp[2] = resu[2] ^ k[0];
        for (int j = 0; j < 3; j++)
        {
            if (temp[j] == 1)
                temps += pow(2, j);
        }
        switch (temps)
        {
        case (0):
        {
            u[0] = 1;
            u[1] = 1;
            break;
        }
        case(1):
        {
            u[0] = 0;
            u[1] = 1;
            break;
        }
        case(2):
        {
            u[0] = 0, u[1] = 0;
            break;
        }
        case(3):
        {
            u[0] = 1, u[1] = 0;
            break;
        }
        case(4):
        {
            u[0] = 0, u[1] = 1;
            break;
        }
        case(5):
        {
            u[0] = 0, u[1] = 0;
            break;
        }
        case(6):
        {
            u[0] = 1, u[1] = 1;
            break;
        }
        case(7):
        {
            u[0] = 1, u[1] = 0;
            break;
        }
        }
        t[0] = x[5 - a];
        t[1] = x[4 - a];
        resu[0] = t[0] ^ u[0];
        resu[1] = t[1] ^ u[1];
        for (int j = 0; j < 4; j++)
        {
            x[(7 - j) - a] = resu[j];
        }
        return;
    }
    ////playfair decryption
    //void decrypt() {
    //    if (x1 == x2) {
    //        decTxt += table[x1][(y1 - 1 + 5) % 5];
    //        decTxt += table[x2][(y2 - 1 + 5) % 5];
    //    }
    //    else if (y1 == y2) {
    //        decTxt += table[(x1 - 1 + 5) % 5][y1];
    //        decTxt += table[(x2 - 1 + 5) % 5][y2];
    //    }
    //    else {
    //        decTxt += table[x1][y2];
    //        decTxt += table[x2][y1];
    //    }
    //}
    void rail_fence_dec() {
        int t, n, m, i, j, k, sum = 0;
        string s;
        /* cout << "Enter the message" << '\n';
         cin >> s;*/
        cout << "Text entered is:" << text;
        cout << "\nEnter key:";
        cin >> n;
        cout << "Rail Fence Cipher For Text is: ";
        vector<vector<char>> a(n, vector<char>(s.size(), ' '));
        j = 0;
        int flag = 0;
        for (i = 0; i < s.size(); i++) {
            a[j][i] = '0';
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
        int temp = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < s.size(); j++) {
                if (a[i][j] == '0')
                    a[i][j] = s[temp++];
            }
        }
        flag = 0;
        j = 0;
        for (i = 0; i < s.size(); i++) {
            cout << a[j][i];
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
    }

    int main()
    {
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
                    string key = generateKey(text, keyenc);
                    cout << "Simple Vigenere Cipher For Text is: " << vigenere_enc(text, key) << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else if (choose == 4)
                {
                    cout << "\n====================Full vignere cipher Encryption====================" << endl;
                    cout << "\nText : " << text;
                    cout << "\nPlease Enter The Keyword:";
                    cin >> keyenc;
                    string key = generateKey(text, keyenc);
                    cout << "Simple Vigenere Cipher For Text is: " << vigenere_enc(text, key) << endl;
                    system("PAUSE");
                    system("CLS");
                  
                }
                /*else if (choose == 5)
                {
                    cout << "\n====================Playfair Encryption====================" << endl;
                    for (int i = 0; i < mPlay.length(); i++)
                    {
                        mPlay[i] = tolower(mPlay[i]);
                    }
                    pairing = mPlay;
                    constructTable();
                    constructPairs();
                    findInTableEN();
                    cout << "Play_Fair Cipher Encryption:  " << encTxt << endl;
                }*/
                else if (choose == 6)
                {
                    cout << "\n====================Rail Fence Cipher Encryption===================="<<endl;
                    rail_fence();
                    cout << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else if (choose == 7)
                {
                    cout << "\n====================S-Box Cipher Encryption====================" << endl;
                    vector<int>arr;
                    int  biarr[8] = { 0,0,0,0,0,0,0,0 }, i, result = 0, temp, n, z;
                    int key[3];
                    bool en = false;
                    string s, rei;
                    s = text;
                    rei = text;
                    cout << "Please Enter three keys: ";
                    for (int j = 0; j < 3; j++)
                    {
                        cin >> key[j];
                    }

                    for (int l = 0; l < s.length(); l++)
                    {
                        result = 0;
                        int n = int(s[l]);
                        int orp = n;
                        for (i = 0; n > 0; i++)
                        {
                            biarr[i] = n % 2;
                            n /= 2;
                        }
                        sbox_enc(biarr, 0, key); //mara zeo we mara 4 
                        sbox_enc(biarr, 4, key);
                        for (int i = 7; i >= 0; i--) //ba7awel mn binary le decimal tany 
                        {
                            if (biarr[i] == 1)
                                result += pow(2, i);
                        }
                        rei[l] = ((result - 97) % 26) + 97;

                        cout << s[l];
                        cout << " " << orp << "  -> " << rei[l] << " " << result << endl;
                    }
                    cout << s << " -> " << rei;
                    system("PAUSE");
                    system("CLS");
                }

                break;    
}
        
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
                else if (choose == 3)
                {
                    cout << "\n====================Simple vigenere Decryption====================" << endl;
                    cout << "\nText : " << text;
                    cout << "\nPlease Enter The Keyword:";
                    cin >> keyenc;
                    string keydec = generateKey(text, keyenc);
                    cout << "Simple Vigenere Decipher For Text is: " << vigenere_dec(text, keydec) << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else if (choose == 4)
                {
                    cout << "\n====================Full vigenere Decryption====================" << endl;
                    cout << "\nText : " << text;
                    cout << "\nPlease Enter The Keyword:";
                    cin >> keyenc;
                    string keydec = generateKey(text, keyenc);
                    cout << "Simple Vigenere Decipher For Text is: " << vigenere_dec(text, keydec) << endl;
                    system("PAUSE");
                    system("CLS");
                }
              /*  else if (choose == 5)
                {
                    cout << "\n====================Playfair Encryption====================" << endl;
                }*/
                else if (choose == 6)
                {
                    cout << "\n====================Rail Fence Cipher Encryption====================" << endl;
                    rail_fence_dec();
                    cout << endl;
                    system("PAUSE");
                    system("CLS");
                }
                else if (choose == 7)
                {
                    /*Decrypt S-box*/
                    //cout << "\n====================Playfair Encryption====================" << endl;
                }
                break; }
                 
            default:
                cout << "Please Check your choice";


            }
         
        } while (choice != 3);
        return 0;
    }
