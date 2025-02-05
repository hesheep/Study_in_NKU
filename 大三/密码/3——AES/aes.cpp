#include<iostream>
#include<string>
#include<vector>
#include<bitset>
#include <sstream>
#include <iomanip>
using namespace std;
vector<string> w(44);
vector<vector<string>> AES_SBox = {
        {"63", "7c", "77", "7b", "f2", "6b", "6f", "c5", "30", "01", "67", "2b", "fe", "d7", "ab", "76"},
        {"ca", "82", "c9", "7d", "fa", "59", "47", "f0", "ad", "d4", "a2", "af", "9c", "a4", "72", "c0"},
        {"b7", "fd", "93", "26", "36", "3f", "f7", "cc", "34", "a5", "e5", "f1", "71", "d8", "31", "15"},
        {"04", "c7", "23", "c3", "18", "96", "05", "9a", "07", "12", "80", "e2", "eb", "27", "b2", "75"},
        {"09", "83", "2c", "1a", "1b", "6e", "5a", "a0", "52", "3b", "d6", "b3", "29", "e3", "2f", "84"},
        {"53", "d1", "00", "ed", "20", "fc", "b1", "5b", "6a", "cb", "be", "39", "4a", "4c", "58", "cf"},
        {"d0", "ef", "aa", "fb", "43", "4d", "33", "85", "45", "f9", "02", "7f", "50", "3c", "9f", "a8"},
        {"51", "a3", "40", "8f", "92", "9d", "38", "f5", "bc", "b6", "da", "21", "10", "ff", "f3", "d2"},
        {"cd", "0c", "13", "ec", "5f", "97", "44", "17", "c4", "a7", "7e", "3d", "64", "5d", "19", "73"},
        {"60", "81", "4f", "dc", "22", "2a", "90", "88", "46", "ee", "b8", "14", "de", "5e", "0b", "db"},
        {"e0", "32", "3a", "0a", "49", "06", "24", "5c", "c2", "d3", "ac", "62", "91", "95", "e4", "79"},
        {"e7", "c8", "37", "6d", "8d", "d5", "4e", "a9", "6c", "56", "f4", "ea", "65", "7a", "ae", "08"},
        {"ba", "78", "25", "2e", "1c", "a6", "b4", "c6", "e8", "dd", "74", "1f", "4b", "bd", "8b", "8a"},
        {"70", "3e", "b5", "66", "48", "03", "f6", "0e", "61", "35", "57", "b9", "86", "c1", "1d", "9e"},
        {"e1", "f8", "98", "11", "69", "d9", "8e", "94", "9b", "1e", "87", "e9", "ce", "55", "28", "df"},
        {"8c", "a1", "89", "0d", "bf", "e6", "42", "68", "41", "99", "2d", "0f", "b0", "54", "bb", "16"}
};
string xor_1(string a, string b)  //异或
{
    if (a.length() != b.length())
    {
        cout << "Error";
        return "Error";
    }
    else
    {
        string xor_result = "";
        for (int i = 0; i < a.length(); i++)
        {
            xor_result += ((a[i] == b[i]) ? '0' : '1');
        }
        return xor_result;
    }
}
string hexToBinary(const string& hex) 
{
    string binary;
    for (char c : hex) {
        // 将每个十六进制字符转换为对应的整数
        int value = (c >= '0' && c <= '9') ? c - '0' :
            (c >= 'A' && c <= 'F') ? c - 'A' + 10 :
            (c >= 'a' && c <= 'f') ? c - 'a' + 10 : 0;

        // 将整数转换为二进制字符串，填充到4位
        binary += bitset<4>(value).to_string();
    }
    // 确保最终结果是128位
    //while (binary.size() < 128) {
    //    binary = '0' + binary;  // 在前面补零
    //}
    return binary;
}
string binaryToHex(const string& binary) 
{
    string hex;
    int len = binary.length();

    // 确保长度是4的倍数，不足时补零
    int padding = (4 - len % 4) % 4;
    string paddedBinary = string(padding, '0') + binary;

    // 将每4位二进制转换为1位十六进制
    for (size_t i = 0; i < paddedBinary.length(); i += 4) {
        string fourBits = paddedBinary.substr(i, 4);
        hex += (fourBits == "0000") ? '0' :
            (fourBits == "0001") ? '1' :
            (fourBits == "0010") ? '2' :
            (fourBits == "0011") ? '3' :
            (fourBits == "0100") ? '4' :
            (fourBits == "0101") ? '5' :
            (fourBits == "0110") ? '6' :
            (fourBits == "0111") ? '7' :
            (fourBits == "1000") ? '8' :
            (fourBits == "1001") ? '9' :
            (fourBits == "1010") ? 'a' :
            (fourBits == "1011") ? 'b' :
            (fourBits == "1100") ? 'c' :
            (fourBits == "1101") ? 'd' :
            (fourBits == "1110") ? 'e' :
            (fourBits == "1111") ? 'f' : '?';
    }

    return hex;
}
string convertHexString(const string& hexStr) 
{
    string result;
    for (char ch : hexStr) {
        if (isdigit(ch)) {
            result += ch; // 保留数字
        }
        else if (islower(ch)) {
            result += toupper(ch); // 转换小写字母为大写
        }
        else {
            result += ch; // 其他字符保留
        }
    }
    return result;
}
string RotWord(string temp)//temp是四个字节，循环移位
{
    string s1 = temp.substr(0, 2);
    temp = temp.substr(2) + s1;
    //cout << temp;
    return temp;
}
string Find_S(string w)//w是长度为2的十六进制字符串
{
    string w11 = w.substr(0, 1);
    int f = stoi(w11, nullptr, 16);
    string w12 = w.substr(1, 1);
    int s = stoi(w12, nullptr, 16);
    string w_1 = AES_SBox[f][s];
    //cout << w_1 << endl;
    return w_1;
}
string SubWord(string w)//w是长度为8的十六进制字符串
{
    string w1, w2, w3, w4;
    string w1_1, w2_1, w3_1, w4_1;
    w1 = w.substr(0, 2);
    //cout << w1 << endl;
    w1_1 = Find_S(w1);
    //cout << w1_1 << endl;
    w2 = w.substr(2, 2);
    w2_1 = Find_S(w2);

    w3 = w.substr(4, 2);
    w3_1 = Find_S(w3);

    w4 = w.substr(6, 2); 
    w4_1 = Find_S(w4);

    string w_1;
    w_1 = w1_1 + w2_1 + w3_1 + w4_1;
    //cout << w_1 << endl;
    return w_1;
}
vector<string> keyexpansinon(string k)//k是字节数组k[16],k[0]=2个十六进制
{
    //vector<string> w(44);
    vector<string> RCon(11);
    RCon[1] = "01000000";
    RCon[2] = "02000000";
    RCon[3] = "04000000";
    RCon[4] = "08000000";
    RCon[5] = "10000000";
    RCon[6] = "20000000";
    RCon[7] = "40000000";
    RCon[8] = "80000000";
    RCon[9] = "1B000000";
    RCon[10] = "36000000";
    for (int i = 0; i < 4; i++)
    {
        w[i] = k.substr(8 * i, 8); //十六进制字符串
        //cout << "w[" << i << "]=" << w[i] << endl;
    }
    for (int i = 4; i < 44; i++)
    {
        //cout <<i<< endl;
        string temp = w[i - 1];
        //cout << "temp=" << temp << endl;
        if (i % 4 == 0)
        {
            //string m, n;
            //m = RotWord(temp);
            //cout << "After RobWord():" << m << endl;
            ////m = hexToBinary(m);
            //n = xor_1(hexToBinary(m), hexToBinary(RCon[i / 4]));//n现在是二进制字符串,应该是32位
            ////cout << n << endl;
            //n = binaryToHex(n);
            ////cout << n << endl;
            //temp = SubWord(n);
            //cout << "After SubWord():" << temp << endl;
            //cout << "Rcon[i/4]=Rcon[" << i / 4 << "]=" << RCon[i / 4] << endl;

            string m, n;
            m = RotWord(temp);
            //cout << "After RobWord():" << m << endl;
            //m = hexToBinary(m);
            n = SubWord(m);
            //cout << "After SubWord():" << n << endl;
            //cout << "Rcon[i/4]=Rcon[" << i / 4 << "]=" << RCon[i / 4] << endl;
            temp = xor_1(hexToBinary(n), hexToBinary(RCon[i / 4]));//n现在是二进制字符串,应该是32位
            //cout << n << endl;
            temp = binaryToHex(temp);
            //cout << n << endl;
            //cout << "After XOR with RCon" << temp;
            
        }
        //cout << "temp=" << temp << "   " << "w[i-4]=w[" << i - 4 << "]=" << w[i - 4] << endl;
        w[i] = binaryToHex(xor_1(hexToBinary(w[i - 4]), hexToBinary(temp)));
        //cout << "w[" << i << "]=" << w[i] << endl;
    }
    return w;
}

// 将两个字节进行乘法运算
static string Multiply(string a, int b)
{
    // 将输入的十六进制字符串转换为整数
    int aInt = stoi(a, nullptr, 16);
    int result = 0;

    // 使用GF(2^8)的乘法规则
    for (int i = 0; i < 8; ++i) {
        if (b & 1) {
            result ^= aInt; // 异或运算
        }
        bool high_bit_set = aInt & 0x80; // 检查高位是否为1
        aInt <<= 1; // 左移1位
        if (high_bit_set) {
            aInt ^= 0x1B; // 在GF(2^8)中进行减法，使用生成多项式x^8 + x^4 + x^3 + x + 1
        }
        b >>= 1; // 右移1位
    }

    // 返回乘法结果的十六进制字符串
    stringstream ss;
    ss << hex << setw(2) << setfill('0') << (result & 0xFF);
    return ss.str();
}

string SubBytes(string m)
{
    string n;
    vector<string> s(16);
    for (int i = 0; i < 16; i++)
    {
        s[i] = m.substr(i * 2, 2);
        //cout << "s[" << i << "]=" << s[i] << " ";
        s[i] = Find_S(s[i]);
        //cout << "Find_S()=" << s[i] << endl;
        n += s[i];
    }
    return n;
}
string ShiftRows(string m)
{
    string n;
    vector<string> s(16);
    for (int i = 0; i < 16; i++)
    {
        s[i] = m.substr(i * 2, 2);
    }
    vector<string> sn(16);
    sn[0] = s[0];
    sn[1] = s[5];
    sn[2] = s[10];
    sn[3] = s[15];
    sn[4] = s[4];
    sn[5] = s[9];
    sn[6] = s[14];
    sn[7] = s[3];
    sn[8] = s[8];
    sn[9] = s[13];
    sn[10] = s[2];
    sn[11] = s[7];
    sn[12] = s[12];
    sn[13] = s[1];
    sn[14] = s[6];
    sn[15] = s[11];
    for (int i = 0; i < 16; i++)
    {
        n += sn[i];
    }
    return n;
}
string MixColumns(string m)
{
    // 初始化一个新的字符串，用于存储混合后的列
    string n;
    vector<string> s(16);

    // 将输入的16字节字符串分割成字节
    for (int i = 0; i < 16; i++)
    {
        s[i] = m.substr(i * 2, 2); // 每个字节由两个十六进制字符表示
    }

    // 进行列混合
    for (int i = 0; i < 16; i += 4) // 每列处理4个字节
    {
        // 提取当前列的字节
        string col[4] = { s[i], s[i + 1], s[i + 2], s[i + 3] };

        // 计算新的字节
        string newCol[4];
        newCol[0] = xor_1(xor_1(xor_1(hexToBinary(Multiply(col[0], 2)),
            hexToBinary(Multiply(col[1], 3))) ,
            hexToBinary(col[2])) ,
            hexToBinary(col[3]));

        newCol[1] = xor_1(xor_1(xor_1(hexToBinary(col[0]),
            hexToBinary(Multiply(col[1], 2))),
            hexToBinary(Multiply(col[2], 3))),
            hexToBinary(col[3]));

        newCol[2] = xor_1(xor_1(xor_1(hexToBinary(col[0]),
            hexToBinary(col[1])),
            hexToBinary(Multiply(col[2], 2))),
            hexToBinary(Multiply(col[3], 3)));

        newCol[3] = xor_1(xor_1(xor_1(hexToBinary(Multiply(col[0], 3)),
            hexToBinary(col[1])),
            hexToBinary(col[2])),
            hexToBinary(Multiply(col[3], 2)));

        // 将新列的字节加入到结果字符串中
        for (int j = 0; j < 4; j++)
        {
            n += binaryToHex(newCol[j]); // 转换回十六进制并添加到结果
        }
    }

    return n; // 返回混合后的字符串
}


string Encryption(string p, string k)
{
    keyexpansinon(k);
    string c,x;
    //cout << "p=" << p << endl << "k=" << k << endl;
    //cout << "hexToBinary(p)=" << hexToBinary(p) << endl;
    //cout << "hexToBinary(p)=" << hexToBinary(k) << endl;
    x = xor_1(hexToBinary(p), hexToBinary(k));
    //cout << "x=" << x << endl;
    for (int i = 1; i < 10; i++)
    {
        //cout << "i=" << i << endl << "x=" << binaryToHex(x) << endl;
        x = binaryToHex(x);
        x = SubBytes(x);
        //cout << "After SubBytes=" << x << endl;
        x = ShiftRows(x);
        //cout << "After ShiftRows=" << x << endl;
        x = MixColumns(x);
        //cout << "After MixColumns=" << x << endl;
        string k_i = w[4 * i] + w[4 * i + 1] + w[4 * i + 2] + w[4 * i + 3];
        //cout << "Round Key Value=" << k_i << endl;
        x = xor_1(hexToBinary(x), hexToBinary(k_i));
    }
    x = binaryToHex(x);
    //cout << "i=" << 10 << endl << "x=" << x << endl;
    x = SubBytes(x);
    //cout << "After SubBytes=" << x << endl;
    x = ShiftRows(x);
    //cout << "After ShiftRows=" << x << endl;
    string k_10 = w[40] + w[41] + w[42] + w[43];
    //cout << "Round Key Value=" << k_10 << endl;
    x = xor_1(hexToBinary(x), hexToBinary(k_10));
    //cout << "x=" << x << endl;
    c = binaryToHex(x);
    c = convertHexString(c);
    return c;
}
int main()
{
    string p, k;
    cin >> k>>p ;
    cout << Encryption(p, k) << endl;


    //cin >> k;
    /*vector<string> s(16);
    for (int i = 0; i < 16; i++)
    {
        s[i] = p.substr(i * 2, 2);
        cout << "s[" << i << "]=" << s[i] << endl;
    }*/

    //cout << SubBytes(p);
    //cout << ShiftRows(p);
    //cout << hexToBinary(p);
    //cin >> k;
   // cout << k[0]<<" " << k[31] << endl;
    //keyexpansinon(k);
    //string temp = "0c0d0e0f";
    //RotWord(temp);
    //string a = "1111000100101110";
    //cout << binaryToHex(a) << endl;
    //string h = "ff";
    //Find_S(h);
	return 0;
}
// k:000102030405060708090a0b0c0d0e0f 
// K: 2b7e151628aed2a6abf7158809cf4f3c
 
// p:00112233445566778899aabbccddeeff
// P:3243f6a8885a308d313198a2e0370734
 

