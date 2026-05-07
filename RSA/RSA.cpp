#include <iostream>
using namespace std;

// Prime Check
bool isPrime(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Modular Exponentiation
long long mod(long long base, long long exp, long long mod)
{
    long long res = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

// GCD
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

//  Modular inverse (Extended Euclidean Algorithm) or (Extended GCD)
long long modInvers(long long e, long long phi)
{
    long long org_phi = phi;
    long long y = 0, x = 1;
    long long a = e, b = phi;
    // just like the GCD func..
    while (b != 0)
    {
        long long q = a / b;

        long long temp_y = y;
        y = x - q * y;
        x = temp_y;

        long long temp_b = b;
        b = a - q * b;
        a = temp_b;
    }

    if (x < 0)
        x += org_phi;

    return x;
}

///////////////////////// MAIN ///////////////
int main()
{
    int choice = 1;

    long long old_p, old_q;

    while (choice != 0)
    {

        cout << "enter your choice : " << endl;
        cout << "0.exit" << endl;
        cout << "1.encrypt new message" << endl;
        cin >> choice;
        if (choice == 0)
            break;

        long long p, q, e, message;
        cout << "Enter Prime num p: ";
        cin >> p;
        cout << "Enter Prime num q: ";
        cin >> q;

        long long n = p * q;
        long long phi = (p - 1) * (q - 1);

        // check primes
        if (!isPrime(p) || !isPrime(q))
        {
            cout << "p and q must be prime\n";
            return 0;
        }

        cout << "Enter Plaintext (number): ";
        cin >> message;

        if (n <= message)
        {
            while (n <= message)
            { // 'message' mayenfa3sh tsawy aw teb2a akbar mn el 'n'

                cout << "message is equal to n" << endl;
                cout << "try another message : ";
                cin >> message;
            }
        }

        if (p == old_p && q == old_q)
        {
            cout << "el inputs mtkrra...";

            do
            {
                p++;
            } while (!isPrime(p)); // hanzawed l7ad ma n2abel el next prime

            do
            {
                q++;
            } while (!isPrime(q));

            cout << "(p,q) will be (" << p << "," << q << ")";
        }

        old_p = p;
        old_q = q;

        n = p * q;
        phi = (p - 1) * (q - 1);

        for (int i = 2; i < phi; i++)
        { // generate 'e'
            if (gcd(i, phi) == 1)
            {
                e = i;
                break;
            }
        }

        // check e
        if (gcd(e, phi) != 1)
        {
            cout << "e is not coprime with phi\n";
            return 0;
        }

        // get d
        long long d = modInvers(e, phi);

        // Encryption
        long long c = mod(message, e, n);

        // Decryption
        long long m = mod(c, d, n);

        // Output
        cout << "\n--- RSA Results ---\n";
        cout << "1. p = " << p << ", q = " << q << endl;
        cout << "2. n = " << n << endl;
        cout << "3. phi = " << phi << endl;
        cout << "4. Public Key (e, n) = (" << e << ", " << n << ")" << endl;
        cout << "5. Private Key (d, n) = (" << d << ", " << n << ")" << endl;
        cout << "6. Plaintext = " << message << endl;
        cout << "7. Ciphertext = " << c << endl;
        cout << "8. Decrypted Text = " << m << endl;
    }

    return 0;
}
