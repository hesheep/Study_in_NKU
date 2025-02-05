#include <iostream>
#include <cmath>
using namespace std;

// ������ (a^b mod q)
long long modPow(long long a, long long b, long long q) {
    long long res = 1;
    a = a % q;
    while (b > 0) {
        if (b % 2 == 1) res = (res * a) % q;
        b = b / 2;
        a = (a * a) % q;
    }
    return res;
}
// ���� (a * b) % mod����ֹ���
long long modMul(long long a, long long b, long long mod) {
    return (a % mod) * (b % mod) % mod;
}
//// ��ģ��Ԫ (a^(-1) mod q)��ʹ����չŷ������㷨
//long long modInverse(long long a, long long q) {
//    long long m0 = q, t, y = 0, x = 1;
//    if (q == 1) return 0;
//    while (a > 1) {
//        long long q1 = a / q;
//        t = q;
//        q = a % q, a = t;
//        t = y;
//        y = x - q1 * y;
//        x = t;
//    }
//    if (x < 0) x += m0;
//    return x;
//}
// ��ģ��Ԫ (a^(-1) mod q)��ʹ����չŷ������㷨������ a Ϊ�������
long long modInverse(long long a, long long q) {
    a = (a % q + q) % q; // ȷ�� a Ϊ���� (���������)
    long long m0 = q, t, y = 0, x = 1;
    if (q == 1) return 0;

    while (a > 1) {
        long long q1 = a / q;
        t = q;
        q = a % q, a = t;
        t = y;
        y = x - q1 * y;
        x = t;
    }

    // ȷ�� x Ϊ����
    if (x < 0) x += m0;
    return x;
}

// ��Բ���߼ӷ���P + Q = R
void pointAdd(long long x1, long long y1, long long x2, long long y2,
    long long& x3, long long& y3, long long a, long long p) {
    long long lambda;
    if (x1 == x2 && y1 == y2) { // �㱶��
        lambda = modMul(3 * x1 * x1 + a, modInverse(2 * y1, p), p);
        //cout << "lambda=" << lambda << endl;
        x3 = (lambda * lambda - 2 * x1) % p;
        //cout << "x3=" << endl;
    }
    else { // ��ͨ�ӷ�
        //cout << "y2-y1=" << (y2 - y1) << endl;
        //cout << "x2-x1=" << (x2 - x1) << endl;
        //cout << "modInverse(x2 - x1, p)="<<modInverse(x2 - x1, p) << endl;
        lambda = modMul(y2 - y1, modInverse(x2 - x1, p), p);
        //cout << "lambda=" << lambda << endl;
        x3 = (lambda * lambda - x1 - x2) % p;
        //cout << "x3=" << endl;
    }
    if (x3 < 0) x3 += p;
    y3 = (lambda * (x1 - x3) - y1) % p;
    if (y3 < 0) y3 += p;
    //cout << "x3=" << x3 << ",y3=" << y3 << endl;
}
// ���� kA������ k ���ĵ� (u, v)
void scalarMultiply(long long x0, long long y0, long long k,
    long long a, long long p, long long& u, long long& v) {
    u = x0; v = y0; // ��ʼ��Ϊ A
    long long x_temp = x0, y_temp = y0;

    for (long long i = 1; i < k; i++) { // ѭ�������ӷ�
        pointAdd(u, v, x_temp, y_temp, u, v, a, p);
        //cout<<"i="<<i << "  u=" << u << ",v=" << v << endl;
    }
}

// ����������Բ��������ǩ��
int main() {
    // ������Բ���߲���
    long long x0, y0; // ��A������
    long long m, x, k; // ˽Կm, ��Ϣx, �����k
    const long long q = 13, p = 11; // ��Բ���ߵĽ� q = 13

    cin >> x0 >> y0; // �������Զ��A���� (x0, y0)
    cin >> m >> x >> k; // ����˽Կm, ��Ϣx, �����k

    // ���� kA = (u, v)������ u �� x ���� mod q
    long long u, v;
    int a = 1, b = 1, c = 6;
    scalarMultiply(x0, y0, k, a, p, u, v);
    //cout << "u=" << u << endl << "v=" << v << endl;
    //long long u = (k * x0) % q; // �����Ǽ�ʵ�֣�������Բ���ߵ�ı�����Ϊ k * x0
    long long r = u % q; // r = u mod q
    //cout << "r=" << r << endl;
    if (r == 0) {
        cout << "Error: r cannot be 0, choose another k" << endl;
        return 0;
    }

    // ���� s = k^(-1) * (Hash(x) + m * r) mod q
    long long hash_x = modPow(2, x, q); // Hash(x) = 2^x mod q
    long long s = modInverse(k, q) * (hash_x + m * r) % q;

    if (s == 0) {
        cout << "Error: s cannot be 0, choose another k" << endl;
        return 0;
    }

    // ������ (r, s)
    cout << r << " " << s ;
    return 0;
}
