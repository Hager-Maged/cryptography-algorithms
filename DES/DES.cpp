#include <iostream>
#include <string>
using namespace std;

// ======================= DES TABLES =======================

// Initial Permutation (IP)
int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

// Final Permutation (IP^-1) INVERSE
int IP_INV[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

// PC-1
int PC1[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

// PC-2
int PC2[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};

// Expansion Permutation
int E[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

// P-Permutation
int P[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25};

// Shift schedule
int SHIFT_TABLE[16] = {
    1, 1, 2, 2,
    2, 2, 2, 2,
    1, 2, 2, 2,
    2, 2, 2, 1};

// S-Boxes
int S_BOX[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

// =======================FUNCTIONS=======================

string permute(string input, int table[], int n)
{
    string output = "";
    for (int i = 0; i < n; i++)
    {
        output += input[table[i] - 1];
    }
    return output;
}

void splitIntoHalves(string input, string &left, string &right)
{
    int mid = input.length() / 2;
    left = input.substr(0, mid);
    right = input.substr(mid, mid);
}

string shiftLeft(string input, int shifts)
{
    for (int i = 0; i < shifts; i++)
    {
        input = input.substr(1) + input[0];
    }
    return input;
}

string xorBinary(string a, string b)
{
    string result = "";
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] == b[i])
            result += '0';
        else
            result += '1';
    }
    return result;
}

string decimalTo4BitBinary(int num)
{
    string result = "";
    for (int i = 3; i >= 0; i--)
    {
        if ((num >> i) & 1)
            result += '1';
        else
            result += '0';
    }
    return result;
}

char fourBitsToHexChar(string bits)
{
    int value = 0;

    if (bits[0] == '1')
        value += 8;
    if (bits[1] == '1')
        value += 4;
    if (bits[2] == '1')
        value += 2;
    if (bits[3] == '1')
        value += 1;

    if (value < 10)
        return char('0' + value);
    else
        return char('A' + (value - 10));
}

string binaryToHex(string binary)
{
    string hex = "";
    for (int i = 0; i < binary.length(); i += 4)
    {
        string nibble = binary.substr(i, 4);
        hex += fourBitsToHexChar(nibble);
    }
    return hex;
}

//================== DES MAIN FUNCTIONS ===================

string initialPermutation(string plaintext)
{
    return permute(plaintext, IP, 64);
}

string applyPC1(string key)
{
    return permute(key, PC1, 56);
}

string expansionPermutation(string right)
{
    return permute(right, E, 48);
}

string sBoxSubstitution(string input48)
{
    string output = "";

    for (int i = 0; i < 8; i++)
    {
        string block = input48.substr(i * 6, 6);

        int row = (block[0] - '0') * 2 + (block[5] - '0');
        int col = (block[1] - '0') * 8 +
                  (block[2] - '0') * 4 +
                  (block[3] - '0') * 2 +
                  (block[4] - '0');

        int value = S_BOX[i][row][col];
        output += decimalTo4BitBinary(value);
    }

    return output;
}

string pPermutation(string input32)
{
    return permute(input32, P, 32);
}

string roundFunction(string right, string roundKey)
{
    string expandedRight = expansionPermutation(right);
    string xored = xorBinary(expandedRight, roundKey);
    string sboxOutput = sBoxSubstitution(xored);
    string pOutput = pPermutation(sboxOutput);
    return pOutput;
}

void generateRoundKeys(string key, string roundKeys[16])
{
    string permutedKey = applyPC1(key);

    string C, D;
    splitIntoHalves(permutedKey, C, D);

    for (int i = 0; i < 16; i++)
    {
        C = shiftLeft(C, SHIFT_TABLE[i]);
        D = shiftLeft(D, SHIFT_TABLE[i]);

        string combinedKey = C + D;
        roundKeys[i] = permute(combinedKey, PC2, 48);
    }
}

string finalPermutation(string combined)
{
    return permute(combined, IP_INV, 64);
}

string desEncrypt(string plaintext, string key)
{
    cout << "Plaintext before IP:" << endl;
    cout << plaintext << endl;

    string permutedText = initialPermutation(plaintext);
    cout << "After Initial Permutation:" << endl;
    cout << permutedText << endl;

    string L, R;
    splitIntoHalves(permutedText, L, R);

    cout << "L0 = " << L << endl;
    cout << "R0 = " << R << endl;

    string roundKeys[16];
    generateRoundKeys(key, roundKeys);

    for (int i = 0; i < 16; i++)
    {
        string newL = R;
        string newR = xorBinary(L, roundFunction(R, roundKeys[i]));

        L = newL;
        R = newR;
    }

    string combined = R + L; // R16 + L16  (Swap)
    string ciphertext = finalPermutation(combined);

    return ciphertext;
}

int main()
{
    string plaintext, key;

    cout << "================ DES Encryption Program ================" << endl;
    cout << "Enter 64-bit plaintext:" << endl;
    cin >> plaintext;

    cout << "Enter 64-bit key:" << endl;
    cin >> key;

    string ciphertext = desEncrypt(plaintext, key);

    cout << "Final Ciphertext:" << endl;
    cout << ciphertext << endl;

    cout << "Ciphertext in Hex:" << endl;
    cout << binaryToHex(ciphertext) << endl;

    cout << "================ End of Program ================" << endl;

    return 0;
}
