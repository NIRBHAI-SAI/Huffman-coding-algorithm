#include <bits/stdc++.h>
using namespace std;
int decode(int idx, unordered_map<string, char> mpp, string str)
{

    int len = 1;
    while (mpp.find(str.substr(idx, len)) == mpp.end())
    {
        len++;
    }
    return len;
}
int main()
{
    ifstream file;
    file.open("codewords.txt");
    unordered_map<string, char> mpp;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            mpp[line.substr(2, line.length() - 2)] = line[0];
        }
    }

    string str;
    ifstream en("encoded_string.txt");
    en >> str;
    int idx = 0;

    ofstream de("decoded_string.txt");
    while (idx < str.length())
    {
        int len = decode(idx, mpp, str);
        de << mpp[str.substr(idx, len)];
        idx = idx + len;
    }
}