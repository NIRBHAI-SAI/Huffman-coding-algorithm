#include <bits/stdc++.h>
using namespace std;

class huff_node
{
public:
    huff_node *left;
    huff_node *right;
    char ch;
    int fq;
    huff_node(huff_node *l, huff_node *r, char tx, int frequency)
    {
        left = l;
        right = r;
        ch = tx;
        fq = frequency;
    }
};

class cmp
{
public:
    bool operator()(huff_node *a, huff_node *b)
    {
        return a->fq > b->fq;
    }
};

int main()
{

    ifstream file;
    file.open("input.txt");

    unordered_map<char, int> mpp;
    string inp = "";
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            inp += line;
            for (auto it : line)
            {
                mpp[it]++;
            }
        }
    }

    priority_queue<huff_node *, vector<huff_node *>, cmp> pq;

    for (auto it : mpp)
    {
        huff_node *node = new huff_node(NULL, NULL, it.first, it.second);
        pq.push(node);
    }

    while (pq.size() != 1)
    {
        huff_node *lf1 = pq.top();
        pq.pop();
        huff_node *lf2 = pq.top();
        pq.pop();
        huff_node *node1 = new huff_node(lf1, lf2, '*', lf1->fq + lf2->fq);
        pq.push(node1);
    }

    // encoding
    ofstream out("codewords.txt");

    huff_node *root = pq.top();

    stack<pair<huff_node *, string>> stk;

    stk.push({root, ""});

    unordered_map<char, string> codes;

    while (!stk.empty())
    {
        auto p = stk.top();
        stk.pop();
        huff_node *a = p.first;
        if (a->left == NULL && a->right == NULL)
        {
            out << a->ch << " " << p.second << endl;
            codes[a->ch] = p.second;
        }
        if (a->right != NULL)
        {
            stk.push({a->right, p.second + '1'});
        }
        if (a->left != NULL)
        {
            stk.push({a->left, p.second + '0'});
        }
    }
    ofstream en("encoded_string.txt");
    for (auto it : inp)
    {
        en << codes[it];
    }

    cout << "codewords.txt is created and that contains character -> code word" << endl;
    cout << "also encoded_string.txt is genrated it contains the encoded strings";
}