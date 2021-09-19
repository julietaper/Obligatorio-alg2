#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class Hash
{
public:
    Hash(int expectedElements)
    {
        table = new HashNode *[expectedElements];
        elements = expectedElements;
        actualElements = 0;
        for (int i = 0; i < elements; i++)
        {
            table[i] = NULL;
        }
    }
    int hashFunction(string data)
    {
        long hash = 0;
        long long position = 0;
        for (int i = 0; i < data.length(); i++)
        {
            hash += data[i] * pow(31, i);
        }
        position = hash % elements;
        return position;
    }
    void insert(string data)
    {
        int position = hashFunction(data);
        insert(table[position], data);
        actualElements++;
    }
    int twoEqualElements()
    {
        int count = 0;
        for (int i = 0; i < elements; i++)
        {
            if (table[i] != NULL)
            {
                count += dobleElementsInNode(table[i]);
            }
        }
        return count;
    }

private:
    struct HashNode
    {
        string data;
        int elements;
        HashNode *next;
    };
    HashNode **table;
    int actualElements;
    int elements;

    void insert(HashNode *&node, string data)
    {
        if (node == NULL)
        {
            node = new HashNode();
            node->data = data;
            node->elements = 1;
            node->next = NULL;
            return;
        }
        if (equalWords(node->data, data))
        {
            node->elements++;
        }
        else
        {
            insert(node->next, data);
        }
    }

    bool equalWords(string str1, string str2)
    {
        int length1 = str1.length();
        int length2 = str2.length();
        if (length1 > length2 || length1 < length2)
            return false;
        for (int i = 0; i < length1; i++)
        {
            if (str1[i] != str2[i])
            {
                return false;
            }
        }
        return true;
    }
    int dobleElementsInNode(HashNode *node)
    {
        int count = 0;
        while (node != NULL)
        {
            if (node->elements == 2)
            {
                count++;
            }
            node = node->next;
        }
        return count;
    }
};

int main()
{
    int elements;
    cin >> elements;
    Hash hash = Hash(elements);
    for (int i = 0; i < elements; i++)
    {
        string word;
        cin >> word;
        hash.insert(word);
    }
    cout << hash.twoEqualElements() << endl;
}