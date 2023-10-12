#include <bits/stdc++.h>
using namespace std;
class TrieNode
{
public:
    int isEnd;
    TrieNode *children[26];
    TrieNode()
    {
        isEnd = 0;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};
class Trie
{
    TrieNode *root;

public:
    Trie() : root(new TrieNode()) {}
    void insert(string word)
    {
        TrieNode *curr = root;
        for (char ch : word)
        {
            if (curr->children[ch - 'a'] == NULL)
                curr->children[ch - 'a'] = new TrieNode();
            curr = curr->children[ch - 'a'];
        }
        curr->isEnd++;
    }
    bool search(string word)
    {
        TrieNode *curr = root;
        for (char ch : word)
        {
            if (curr->children[ch - 'a'] == NULL)
                return false;
            curr = curr->children[ch - 'a'];
        }
        return curr->isEnd;
    }
    bool startsWith(string prefix)
    {
        TrieNode *curr = root;
        for (char ch : prefix)
        {
            if (curr->children[ch - 'a'] == NULL)
                return false;
            curr = curr->children[ch - 'a'];
        }
        return true;
    }
    bool isJunc(TrieNode *curr)
    {
        for (int i = 0; i < 26; i++)
        {
            if (curr->children[i] != NULL)
                return true;
        }
        return false;
    }
    // 1 mane junction dlt kore ashse
    bool dlt(string s, int idx, TrieNode *curr)
    {
        if (idx >= s.size())
            return 0;
        if (idx == s.size() - 1)
        {
            if (isJunc(curr->children[s[idx] - 'a']))
            {
                curr->children[s[idx] - 'a']->isEnd = 0;
                return false;
            }
            else
            {
                delete curr->children[s[idx] - 'a'];
                curr->children[s[idx] - 'a'] = NULL;
                return true;
            }
        }
        bool res = dlt(s, idx + 1, curr->children[s[idx] - 'a']);
        if (res)
        {
            if (isJunc(curr->children[s[idx] - 'a']))
                return false;
            else if (!curr->children[s[idx] - 'a']->isEnd)
            {
                delete curr->children[s[idx] - 'a'];
                curr->children[s[idx] - 'a'] = NULL;
                return true;
            }
        }
        return false;
    }
    bool dlt(string s)
    {
        if (search(s))
        {
            dlt(s, 0, root);
            return true;
        }
        return false;
    }
    void print(string start, TrieNode *curr)
    {
        if (curr->isEnd)
            cout << start << endl;
        for (int i = 0; i < 26; i++)
        {
            if (curr->children[i] != NULL)
            {
                start.push_back(i + 'a');
                print(start, curr->children[i]);
                start.pop_back();
            }
        }
    }
    void print()
    {
        print("", root);
    }
};
int main()
{
    Trie t;
    t.insert("hello");
    t.insert("h");
    t.insert("hell");
    t.insert("helloworld");
    bool ans = t.dlt("helloworld");
    bool anss = t.search("hello");
    t.print();
}