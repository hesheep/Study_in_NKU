#include <iostream>
#include <cmath>
using namespace std;

// 快速幂 (a^b mod q)
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
// 计算 (a * b) % mod，防止溢出
long long modMul(long long a, long long b, long long mod) {
    return (a % mod) * (b % mod) % mod;
}
//// 求模逆元 (a^(-1) mod q)，使用扩展欧几里得算法
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
// 求模逆元 (a^(-1) mod q)，使用扩展欧几里得算法，处理 a 为负的情况
long long modInverse(long long a, long long q) {
    a = (a % q + q) % q; // 确保 a 为正数 (处理负数情况)
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

    // 确保 x 为正数
    if (x < 0) x += m0;
    return x;
}

// 椭圆曲线加法：P + Q = R
void pointAdd(long long x1, long long y1, long long x2, long long y2,
    long long& x3, long long& y3, long long a, long long p) {
    long long lambda;
    if (x1 == x2 && y1 == y2) { // 点倍增
        lambda = modMul(3 * x1 * x1 + a, modInverse(2 * y1, p), p);
        //cout << "lambda=" << lambda << endl;
        x3 = (lambda * lambda - 2 * x1) % p;
        //cout << "x3=" << endl;
    }
    else { // 普通加法
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
// 计算 kA，返回 k 倍的点 (u, v)
void scalarMultiply(long long x0, long long y0, long long k,
    long long a, long long p, long long& u, long long& v) {
    u = x0; v = y0; // 初始化为 A
    long long x_temp = x0, y_temp = y0;

    for (long long i = 1; i < k; i++) { // 循环计算点加法
        pointAdd(u, v, x_temp, y_temp, u, v, a, p);
        //cout<<"i="<<i << "  u=" << u << ",v=" << v << endl;
    }
}

// 主函数：椭圆曲线数字签名
int main() {
    // 输入椭圆曲线参数
    long long x0, y0; // 点A的坐标
    long long m, x, k; // 私钥m, 消息x, 随机数k
    const long long q = 13, p = 11; // 椭圆曲线的阶 q = 13

    cin >> x0 >> y0; // 输入非零远点A坐标 (x0, y0)
    cin >> m >> x >> k; // 输入私钥m, 消息x, 随机数k

    // 计算 kA = (u, v)，其中 u 是 x 坐标 mod q
    long long u, v;
    int a = 1, b = 1, c = 6;
    scalarMultiply(x0, y0, k, a, p, u, v);
    //cout << "u=" << u << endl << "v=" << v << endl;
    //long long u = (k * x0) % q; // 由于是简单实现，计算椭圆曲线点的倍数简化为 k * x0
    long long r = u % q; // r = u mod q
    //cout << "r=" << r << endl;
    if (r == 0) {
        cout << "Error: r cannot be 0, choose another k" << endl;
        return 0;
    }

    // 计算 s = k^(-1) * (Hash(x) + m * r) mod q
    long long hash_x = modPow(2, x, q); // Hash(x) = 2^x mod q
    long long s = modInverse(k, q) * (hash_x + m * r) % q;

    if (s == 0) {
        cout << "Error: s cannot be 0, choose another k" << endl;
        return 0;
    }

    // 输出结果 (r, s)
    cout << r << " " << s ;
    return 0;
}
