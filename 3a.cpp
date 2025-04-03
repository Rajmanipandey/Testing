#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Function to compute gcd using Extended Euclidean Algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int eulerTotient(int p, int q) {
    int n = p * q;
    return (p - 1) * (q - 1);
}

// Function to count numbers that are relatively prime to n
int countRelativelyPrimeNumbers(int n) {
    int count = 0;
    for (int i = 1; i < n; i++) {
        if (gcd(i, n) == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    int P, Q;
    cout << "Enter two prime numbers P and Q: ";
    cin >> P >> Q;

    int N = P * Q;
    int phiN = eulerTotient(P, Q);
    int relativePrimeCount = countRelativelyPrimeNumbers(N);

    cout << "N = " << N << endl;
    cout << "Euler's Totient Function ϕ(N) = " << phiN << endl;
    cout << "Count of relatively prime numbers to N = " << relativePrimeCount << endl;
    
    if (phiN == relativePrimeCount) {
        cout << "Verification successful: ϕ(N) matches the count of relatively prime numbers." << endl;
    } else {
        cout << "Verification failed: Mismatch in computed values." << endl;
    }
    
    // Store results in file
    ofstream outputFile("Rollnumber_IT352P3a.txt");
    if (outputFile.is_open()) {
        outputFile << "N = " << N << endl;
        outputFile << "Euler's Totient Function ϕ(N) = " << phiN << endl;
        outputFile << "Count of relatively prime numbers to N = " << relativePrimeCount << endl;
        if (phiN == relativePrimeCount) {
            outputFile << "Verification successful: ϕ(N) matches the count of relatively prime numbers." << endl;
        } else {
            outputFile << "Verification failed: Mismatch in computed values." << endl;
        }
        outputFile.close();
    } else {
        cout << "Error opening file for writing." << endl;
    }
    
    return 0;
}
