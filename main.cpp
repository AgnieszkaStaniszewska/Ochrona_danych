#include <iostream>
#include <cmath>
#include <iostream>
#include <cmath>
using namespace std;

long long* fnum_gen(long long& nfnum, long long num_in) {
    long long nmax = sqrt(num_in) + 1;
    long long* fnum_in = new long long[nmax];
    long long n = 0;

    for (long long i = 2; i < nmax; i++)
        fnum_in[i - 2] = i;

    for (long long i = 0; i < nmax; i++) {
        n = i + 1;
        for (long long j = i + 1; j < nmax; j++) {
            if (fnum_in[j] % fnum_in[i]) {
                fnum_in[n] = fnum_in[j];
                n++;
            }
        }
        nmax = n;
    }
    nfnum = nmax;

    long long* fnum = new long long[nfnum];
    for (long long i = 0; i < n; i++)
        fnum[i] = fnum_in[i];
    delete[] fnum_in;
    return fnum;
}

long long* mersenne_gen(long long& nmer, long long* fnum, const long long pmax) {
    nmer = 0;
    while (fnum[nmer] <= pmax)
        nmer++;
    long long* mernum = new long long[nmer];

    for (long long i = 0; i < nmer; i++)
        mernum[i] = pow(2ll, fnum[i]) - 1ll;

    return mernum;
}

bool is_first_direct(long long* fnum, long long nfnum, long long number) {
    for (long long i = 0; i < nfnum; i++) {
        if ((number != fnum[i]) && !(number % fnum[i])) {
            return false;
        }
    }
    return true;
}

bool is_first_LL(long long mer_in, long long p_in) {
    unsigned long long S = 4;
    int p = 1;

    while (p <= p_in - 2) {
        S = (S * S - 2ll) % mer_in;
        p++;
    }

    if (!(S % mer_in))
        return true;
    else
        return false;
}

bool isPrime(long long n) {
    if (n <= 1) {
        return false;
    }

    long long nfnum;
    long long* fnum = fnum_gen(nfnum, n);

    if (!is_first_direct(fnum, nfnum, n)) {
        delete[] fnum;
        return false;
    }

    long long nmer;
    long long* mernum = mersenne_gen(nmer, fnum, n);

    for (long long i = 0; i < nmer; i++) {
        if (is_first_LL(mernum[i], n)) {
            delete[] fnum;
            delete[] mernum;
            return true;
        }
    }

    delete[] fnum;
    delete[] mernum;

    return false;
}
int powmod(int a, int b, int n) {
    long long x = 1, y = a;
    while (b > 0) {
        if (b % 2 == 1) {
            x = (x * y) % n; // multiplying with base
        }
        y = (y * y) % n; // squaring the base
        b /= 2;
    }
    return x % n;
}


int main() {

    //tutaj mamy przyklad; prosze sprawdzic takze te z wprowadzenia do zajec
    cout<<"(123 pow 456) % 789 = "<<powmod(123, 456, 789)<<endl;
    cout<<"(19 pow 1) % 23 = "<<powmod(19, 1, 23)<<endl;
    cout<<"(256 pow 40) % 100 = "<<powmod(256, 40, 100)<<endl;
    cout<<"(4321 pow 5678) % 9876 = "<<powmod(4321, 5678, 9876)<<endl;
    cout<<endl;

    int p, g, a, b;

    cout << "Podaj p: ";
    cin >> p;

    if (!isPrime(p) || p < 1000) {
        cout << "p nie jest liczba pierwsza lub nie ma co najmniej 4 cyfr.\n";
        return 0;
    }


    cout << "Podaj g: ";
    cin >> g;
    if (g < 1000) {
        cout << "g nie ma co najmniej 4 cyfr." << endl;
        return 0;
    }
    cout<<endl;

    cout << "Podaj a: ";
    cin >> a;
    if (a < 1000) {
        cout << "a nie ma co najmniej 4 cyfr." << endl;
        return 0;
    }

    cout << "Podaj b: ";
    cin >> b;
    if (b < 1000) {
        cout << "b nie ma co najmniej 4 cyfr." << endl;
        return 0;
    }

    int A = powmod(g, a, p);
    int B = powmod(g, b, p);

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;

    int k_a = powmod(B, a, p);
    int k_b = powmod(A, b, p);

    cout << "klucz dla A = " << k_a << endl;
    cout << "klucz dla B = " << k_b << endl;

    return 0;
}
