#include<iostream>
#include<string>
#include<vector>
#include<bitset>
using namespace std;
const int l = 4;
const int m = 4;
const int Nr = 4;
const int a[16] = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 };
const int b[16] = { 1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16 };

string xor_1 (string a, string b)  //异或
{
    if (a.length() != b.length())
    {
        cout << "Error";
        return "Error";
    }
    else
    {
        string xor_result="";
        for (int i = 0; i < a.length(); i++)
        {
            xor_result += ((a[i] == b[i]) ? '0' : '1');
        }
        return xor_result;
    }
}
string S(string& u)
{
    string v="";
    string u_i;
    for (int i = 0; i < m; i++)
    {
        u_i = u.substr(i * 4, 4);
        //cout <<"i=" << i<<" " << u_i << endl;
        int j = stoi(u_i, nullptr, 2);
        //cout << j << endl;
        int n = a[j];
        //cout << n << endl;
        string binary = bitset<4>(n).to_string();
        //cout << binary << endl;
        v += binary;
        //cout << v;
    }
    return v;
}
string P(string& v)
{
    string w="";
    for (int i = 0; i < v.length(); i++)
    {
        w += v[b[i] - 1];
    }
    //cout << w << endl;
    return w;
}

string SPN(string x, string k)
{
    //cout << k.length() << endl;
    vector<string> keys;
    for (int i = 0; i <= Nr; i++)
    {
        keys.push_back(k.substr(i * 4, 16));
        //cout << i << " " << keys[i] << endl;
    }
    string w = x;
    string u, v, y;
    for (int i = 0; i < Nr - 1; i++)
    {
        u = xor_1(w, keys[i]);
        v = S(u);
        w = P(v);
    }
    u = xor_1(w, keys[Nr - 1]);
    v = S(u);
    y = xor_1(v, keys[Nr]);
    return y;
}
int main()
{
    string x, k, y;
    cin >> x >> k;
    y = SPN(x, k);
    cout << y;
    /*string x;
    cin >> x;
    P(x);*/

    return 0;
}