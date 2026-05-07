#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
using namespace std;

// ================= S-Box =================
unsigned char Sbox[256] = { // SBox [16][16]
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16};

// ================= Random constant =================
unsigned char Rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

// ================ converting from text to state ==========
void textToState(string text, unsigned char state[4][4])
{
    int k = 0;
    for (int col = 0; col < 4; col++)
    {
        for (int row = 0; row < 4; row++)
        {
            state[row][col] = (unsigned char)text[k];
            k++;
        }
    }
}
// ================= PRINTT FUNCTIONNNN =================
void print(unsigned char s[4][4], bool hexMode = true, bool line = false)
{
    for (int c = 0; c < 4; c++)
    {
        for (int r = 0; r < 4; r++)
        {
            if (line)
            {
                if (hexMode)
                    cout << hex << setw(2) << setfill('0') << (int)s[r][c] << " ";
                else
                    cout << bitset<8>(s[r][c]) << " "; // binary mood
            }
        }
        if (!line)
        {
            for (int j = 0; j < 4; j++)
            {
                if (hexMode)
                    cout << hex << setw(2) << setfill('0') << (int)s[c][j] << " ";
                else
                    cout << bitset<8>(s[c][j]) << " "; // binary mood
            }
            cout << endl;
        }
    }
    cout << dec << endl;
}
// ================= AddRoundKey =================
void AddRoundKey(unsigned char state[4][4], unsigned char roundKey[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] ^= roundKey[i][j];
        }
    }
}
// ================= SubBytes =================
void SubBytes(unsigned char state[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = Sbox[state[i][j]];
        }
    }
}
// ================= ShiftRows =================
void ShiftRows(unsigned char state[4][4])
{
    unsigned char temp[4];

    // row 0 mesh bn3mlo shift
    for (int i = 0; i < 4; i++)
        temp[i] = state[1][i];
    state[1][0] = temp[1];
    state[1][1] = temp[2];
    state[1][2] = temp[3];
    state[1][3] = temp[0];

    for (int i = 0; i < 4; i++)
        temp[i] = state[2][i];
    state[2][0] = temp[2];
    state[2][1] = temp[3];
    state[2][2] = temp[0];
    state[2][3] = temp[1];

    for (int i = 0; i < 4; i++)
        temp[i] = state[3][i];
    state[3][0] = temp[3];
    state[3][1] = temp[0];
    state[3][2] = temp[1];
    state[3][3] = temp[2];
}
// ================= GF(2^8) =================
unsigned char mul2(unsigned char x)
{
    if (x >= 128)
        return (x << 1) ^ 0x1B;
    else
        return x << 1;
}

unsigned char mul3(unsigned char x)
{
    return mul2(x) ^ x;
}

// ================= MixColumns =================
void MixColumns(unsigned char state[4][4])
{
    unsigned char temp[4];

    for (int col = 0; col < 4; col++)
    {
        temp[0] = state[0][col];
        temp[1] = state[1][col];
        temp[2] = state[2][col];
        temp[3] = state[3][col];

        state[0][col] = mul2(temp[0]) ^ mul3(temp[1]) ^ temp[2] ^ temp[3];
        state[1][col] = temp[0] ^ mul2(temp[1]) ^ mul3(temp[2]) ^ temp[3];
        state[2][col] = temp[0] ^ temp[1] ^ mul2(temp[2]) ^ mul3(temp[3]);
        state[3][col] = mul3(temp[0]) ^ temp[1] ^ temp[2] ^ mul2(temp[3]);
    }
}
// =============== Key Expansionn =================
void KeyExpansion(unsigned char key[4][4], unsigned char roundKeys[11][4][4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            roundKeys[0][i][j] = key[i][j];

    for (int r = 1; r <= 10; r++)
    {
        unsigned char temp[4];

        // 1) Last Word (col)
        for (int i = 0; i < 4; i++)
            temp[i] = roundKeys[r - 1][i][3];
        // 2) Rotate
        unsigned char t = temp[0];
        for (int i = 0; i < 3; i++)
            temp[i] = temp[i + 1];
        temp[3] = t;

        // 3) SubBytes
        for (int i = 0; i < 4; i++)
            temp[i] = Sbox[temp[i]];

        // 4) W0 XOR Rcon
        temp[0] ^= Rcon[r - 1];

        // 5) First Word (col/W0)
        for (int i = 0; i < 4; i++)
            roundKeys[r][i][0] = roundKeys[r - 1][i][0] ^ temp[i];

        // 6) ba2y el Words (cols)
        for (int col = 1; col < 4; col++)
        {
            for (int row = 0; row < 4; row++)
            {
                // EL RULE =>    K[r]:W[i]    =        K[r-1]:W[i]         ^       K[r]:W[i-1]
                roundKeys[r][row][col] = roundKeys[r - 1][row][col] ^ roundKeys[r][row][col - 1];
            }
        }
    }
}
// ================= AES Encryption =================
void AES(unsigned char state[4][4], unsigned char roundKeys[11][4][4])
{
    cout << "Round 0 (Initial AddRoundKey):" << endl;
    AddRoundKey(state, roundKeys[0]);
    print(state, true, false);

    for (int round = 1; round <= 9; round++)
    {
        cout << "Round " << round << ":" << endl;

        SubBytes(state);
        cout << "After SubBytes:" << endl;
        print(state, true, false);

        ShiftRows(state); // shift
        cout << "After ShiftRows:" << endl;
        print(state, true, false);

        MixColumns(state); // Mix Columns
        cout << "After MixColumns:" << endl;
        print(state, true, false);

        AddRoundKey(state, roundKeys[round]); // State XOR RoundKey
        cout << "After AddRoundKey:" << endl;
        print(state, true, false);
    }

    cout << "Round 10:" << endl;
    SubBytes(state);
    cout << "After SubBytes:" << endl;
    print(state, true, false);

    ShiftRows(state);
    cout << "After ShiftRows:" << endl;
    print(state, true, false);

    AddRoundKey(state, roundKeys[10]);
    cout << "After AddRoundKey:" << endl;
    print(state, true, false);
}

// ================= MAINNNNN =================
int main()
{
    string plaintext, keyText;

    cout << "Enter Plaintext (16 chars): ";
    getline(cin, plaintext);

    cout << "Enter Key (16 chars): ";
    getline(cin, keyText);

    if (plaintext.length() != 16 || keyText.length() != 16)
    {
        cout << "Error: plaintext and key must be exactly 16 characters." << endl;
        return 0;
    }

    unsigned char state[4][4];
    unsigned char key[4][4];
    unsigned char roundKeys[11][4][4];

    cout << endl;
    cout << "Plaintext before encryption:" << endl;
    cout << plaintext << endl
         << endl;

    textToState(plaintext, state);
    textToState(keyText, key);

    cout << "Plaintext after initial state formation (State Matrix):" << endl;
    print(state, true, false); // hexa matrix

    KeyExpansion(key, roundKeys);
    AES(state, roundKeys);

    cout << "Final Ciphertext (Binary):" << endl;
    print(state, false, true); // binary line
    cout << endl;

    cout << "Final Ciphertext (Hexadecimal):" << endl;
    print(state, true, true); // hexa line

    return 0;
}
