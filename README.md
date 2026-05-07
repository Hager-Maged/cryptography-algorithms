#  Cryptography Algorithms (AES, DES, RSA)

##  Overview

This repository contains implementations of three fundamental cryptographic algorithms:

* 🔸 AES (Advanced Encryption Standard)
* 🔸 DES (Data Encryption Standard)
* 🔸 RSA (Rivest–Shamir–Adleman)

These implementations were developed to understand the internal structure and working principles of encryption techniques.

---

##  Authors

* **Hager Maged**
* **Ziad Mohamed**

---

##  Project Info

This project was developed as part of a university cryptography course.

---

##  Repository Structure

```
cryptography-algorithms/
│
├── AES/
│   └── aes.cpp
│
├── DES/
│   └── des.cpp
│
├── RSA/
│   └── rsa.cpp
│
└── README.md
```

---

##  Features

###  AES

* Full encryption process
* Includes:

  * SubBytes
  * ShiftRows
  * MixColumns
  * AddRoundKey
  * Key Expansion
* Step-by-step round output for learning

---

###  DES

* Complete DES encryption implementation
* Includes:

  * Initial & Final Permutation
  * Key generation (16 rounds)
  * Expansion, S-box, P-permutation
* Binary and Hexadecimal output

---

###  RSA

* Key generation using prime numbers
* Encryption & Decryption
* Includes:

  * Prime checking
  * GCD
  * Modular inverse (Extended Euclidean Algorithm)
  * Fast modular exponentiation

---

##  How to Run

Make sure you have a C++ compiler installed.

### Compile:

```
g++ file_name.cpp -o output
```

### Run:

```
./output
```

### Example:

```
g++ aes.cpp -o aes
./aes
```

---

##  Disclaimer

These implementations are **for educational purposes only**.

They are NOT secure and should NOT be used in real-world applications.

---

##  Notes

* All implementations are written in C++
* Focus is on understanding how algorithms work internally
* Code includes step-by-step outputs for clarity

---

##  Future Improvements

* Add decryption for AES
* Improve code structure (modular design)
* Add test cases
* Enhance documentation

---

