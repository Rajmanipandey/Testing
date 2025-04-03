#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Function to compute gcd using Euclidean Algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to check if a number is a primitive root of P
bool isPrimitiveRoot(int g, int P) {
    vector<bool> seen(P - 1, false);
    int value = 1;
    for (int i = 0; i < P - 1; i++) {
        value = (value * g) % P;
        if (seen[value - 1]) return false;
        seen[value - 1] = true;
    }
    return true;
}

// Function to find all primitive roots of P
vector<int> findPrimitiveRoots(int P) {
    vector<int> roots;
    for (int g = 2; g < P; g++) {
        if (isPrimitiveRoot(g, P)) {
            roots.push_back(g);
        }
    }
    return roots;
}

// Function for modular exponentiation (base^exp % mod)
int modExp(int base, int exp, int mod) {
    int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    srand(time(0));
   
    int P;
    cout << "Enter a large prime number P: ";
    cin >> P;
   
    vector<int> primitiveRoots = findPrimitiveRoots(P);
    if (primitiveRoots.empty()) {
        cout << "No primitive roots found for P." << endl;
        return 1;
    }
   
    int G = primitiveRoots[0]; // Select the first primitive root
    int privateKey = rand() % (P - 2) + 1; // Private key: random from 1 to P-2
    int publicKey = modExp(G, privateKey, P); // Public key = G^privateKey % P
   
    cout << "Primitive root G: " << G << endl;
    cout << "Private Key: " << privateKey << endl;
    cout << "Public Key: " << publicKey << endl;
   
    // Encryption
    string message;
    cout << "Enter an alphanumeric message: ";
    cin >> message;
    vector<int> encryptedMessage;
    int k = rand() % (P - 2) + 1; // Random k
    int K = modExp(publicKey, k, P); // Shared key
    int C1 = modExp(G, k, P); // First part of ciphertext
   
    for (char c : message) {
        encryptedMessage.push_back((int(c) * K) % P);
    }
   
    cout << "Encrypted Message: ";
    for (int c : encryptedMessage) {
        cout << c << " ";
    }
    cout << endl;
   
    // Decryption
    int K_inv = modExp(C1, P - 1 - privateKey, P); // Compute inverse of shared key
    string decryptedMessage = "";
    for (int c : encryptedMessage) {
        decryptedMessage += char((c * K_inv) % P);
    }
   
    cout << "Decrypted Message: " << decryptedMessage << endl;
   
    // Store results in file
    ofstream outputFile("Rollnumber_IT352P3b.txt");
    if (outputFile.is_open()) {
        outputFile << "Primitive root G: " << G << endl;
        outputFile << "Private Key: " << privateKey << endl;
        outputFile << "Public Key: " << publicKey << endl;
        outputFile << "Encrypted Message: ";
        for (int c : encryptedMessage) {
            outputFile << c << " ";
        }
        outputFile << endl;
        outputFile << "Decrypted Message: " << decryptedMessage << endl;
        outputFile.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }
   
    return 0;
}