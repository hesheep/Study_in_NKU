#include <iostream>
#include <cmath>
using namespace std;

long long int gcd(long long int a, long long int b) {
    while (b != 0) {
        long long int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

bool isPrime(long long int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (long long int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}
//计算最大公因子
long long int extendedGCD(long long int a, long long int b, long long int& x, long long int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long int x1, y1;
    long long int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}
//计算逆元
long long int modularInverse(long long int e, long long int z) {
    long long int x, y;
    long long int gcd = extendedGCD(e, z, x, y);
    //long long int gcd = gcd(e, z);
    if (gcd != 1) {
        // cout << "没有模反元素，gcd(e, z) = " << gcd << endl;
        return -1;
    }
    else {
        return (x % z + z) % z;
    }
}
//计算模运算
long long int fastModularExponentiation(long long int c, long long int d, long long int n) {
//__int128 fastModularExponentiation(long long int c, long long int d, long long int n) {
    //long long int result = 1;
    __int128 result = 1;
    //long long int result = 1;
    __int128 c1 = c;
    c1 = c1 % n;
    while (d > 0) {
        if (d % 2 == 1) {
            result = (result * c1) % n;
        }
        c1 = (c1 * c1) % n;
        d /= 2;
    }
    return result;
}

long long int RSA(long long int p, long long int q, long long int e, long long int c) {
//__int128 RSA(long long int p, long long int q, long long int e, long long int c) {
    long long int n, z, d;
    //__int128 m;
    long long int m;
    if (isPrime(p) && isPrime(q)) {
        n = p * q;
        //cout << "n=p*q=" << n << endl;
        z = (p - 1) * (q - 1);
        //cout << "z=(p-1)*(q-1)=" << z << endl;
        d = modularInverse(e, z);
        //cout << "d=" << d << endl;
        m = fastModularExponentiation(c, d, n);
        //return fastModularExponentiation(c, d, n);
        return m;
    }
    else {
        return 0;
    }
}

int main() {
    long long int p, q, e, c;
    cin >> p >> q >> e >> c;
    //if (p < (1LL << 31) && q < (1LL << 31) && gcd(e, (p - 1) * (q - 1)) == 1) {
    if ( gcd(e, (p - 1) * (q - 1)) == 1) {

        //__int128 m;
        //long long int m;
        //m = RSA(p, q, e, c);
        //cout << m;
        cout<< RSA(p, q, e, c);
    }
    return 0;
}