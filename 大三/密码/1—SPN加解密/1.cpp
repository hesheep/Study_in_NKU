#include<iostream>
#include<string>
using namespace std;
const int l=4;
const int m=4;
const int Nr=4;

string xor(string a,string b)  //异或
{
    if(a.length()!=b.length())
    {
        cout<<"Error";
        return "Error";
    }
    else
    {
        string xor_result;
        for(int i=0;i<a.length();i++)
        {
            xor_result[i]=((a[i]==b[i])?'0':'1');
        }
        return xor_result;
    }
}
string SPN(string x,string k)
{
    string y;
    return y;
}
int main()
{
    string x,k,y;
    cin>>x>>k;
    y=SPN(x,k);
    cout<<y;
    return 0;
}