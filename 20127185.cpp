#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct info
{
    string Keys;
    string Values;
};

struct Node
{
    info Data;
    Node *left;
    Node *right;
    int height;
};

int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *createNode(info Data)
{
    Node *p = new Node;
    p->Data = Data;
    p->left = NULL;
    p->right = NULL;
    p->height = 1;
    return p;
}

Node *rightRotate(Node *N)
{
    Node *Nl = N->left;
    Node *Nlr = Nl->right;

    Nl->right = N;
    N->left = Nlr;

    N->height = max(height(N->left), height(N->right)) + 1;
    Nl->height = max(height(Nl->left), height(Nl->right)) + 1;

    return Nl;
}

Node *leftRotate(Node *N)
{
    Node *Nr = N->right;
    Node *Nrl = Nr->left;

    Nr->left = N;
    N->right = Nrl;

    N->height = max(height(N->left), height(N->right)) + 1;
    Nr->height = max(height(Nr->left), height(Nr->right)) + 1;

    return Nr;
}

int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return (height(N->left) - height(N->right));
}

Node *insertNode(Node *N, info Data)
{
    if (N == NULL)
        return createNode(Data);

    if (Data.Keys < N->Data.Keys)
        N->left = insertNode(N->left, Data);
    else if (Data.Keys > N->Data.Keys)
        N->right = insertNode(N->right, Data);
    else
        return N;

    N->height = max(height(N->left), height(N->right)) + 1;

    int balance = getBalance(N);

    // LL & RR
    if (balance > 1 && Data.Keys < N->Data.Keys)
        return rightRotate(N);
    if (balance < -1 && Data.Keys > N->Data.Keys)
        return leftRotate(N);

    // LR & RL
    if (balance > 1 && Data.Keys > N->Data.Keys)
    {
        N->left = leftRotate(N->left);
        return rightRotate(N);
    }
    if (balance < -1 && Data.Keys < N->Data.Keys)
    {
        N->right = rightRotate(N->right);
        return leftRotate(N);
    }

    return N;
}

Node *minValueNode(Node *N)
{
    Node *p = N;

    while (p->left != NULL)
        p = p->left;
    return p;
}
Node *deleteNode(Node *N, string s)
{
    if (N == NULL)
        return N;

    if (s < N->Data.Keys)
        N->left = deleteNode(N->left, s);
    else if (s > N->Data.Keys)
        N->right = deleteNode(N->right, s);
    else
    {
        if (N->left == NULL || N->right == NULL)
        {
            Node *p = N->left ? N->left : N->right;
            if (p == NULL)
            {
                p = N;
                N = NULL;
            }
            else
                N->Data = p->Data;
            delete p;
        }
        else
        {
            Node *p = minValueNode(N->right);
            N->Data = p->Data;
            N->right = deleteNode(N->right, p->Data.Keys);
        }
    }

    if (N == NULL)
        return N;

    N->height = max(height(N->left), height(N->right)) + 1;

    int balance = getBalance(N);

    if (balance > 1 && getBalance(N->left) >= 0)
        return rightRotate(N);
    if (balance < -1 && getBalance(N->right) <= 0)
        return leftRotate(N);

    if (balance > 1 && getBalance(N->left) < 0)
    {
        N->left = leftRotate(N->left);
        N = rightRotate(N);
    }
    if (balance < -1 && getBalance(N->right) > 0)
    {
        N->right = rightRotate(N->right);
        N = leftRotate(N);
    }

    return N;
}

void processingUsage(info *D, int &size)
{
    for (int i = 0; i < size; ++i)
    {
        if (D[i].Keys == "Usage")
        {
            if (D[i].Values[0] != 'n' || D[i].Values[1] != '.')
            {
                D[i - 1].Values += " " + D[i].Keys + ": " + D[i].Values;
                D[i].Keys = D[size - 1].Keys;
                D[i].Values = D[size - 1].Values;
                --size;
            }
        }
    }
}
void rightBalance(info *D, int &size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (D[j].Values == D[i].Values)
            {
                D[j].Keys = D[size - 1].Keys;
                D[j].Values = D[size - 1].Values;
                --size;
                break;
            }
        }
    }
}
void quickSort(info *D, int l, int r)
{
    if (l > r)
        return;

    string s = D[(l + r) / 2].Keys;

    int i = l;
    int j = r;

    while (i <= j)
    {
        while (D[i].Keys < s)
            ++i;
        while (D[j].Keys > s)
            --j;

        if (i <= j)
        {
            swap(D[i], D[j]);
            ++i;
            --j;
        }
    }

    if (l < j)
        quickSort(D, l, j);
    if (r > i)
        quickSort(D, i, r);
}
int sizeFileInput(fstream &fsInFile)
{
    int size = 0;
    while (!fsInFile.eof())
    {
        string temp;
        getline(fsInFile, temp);
        if (temp.length() > 1)
        {
            size++;
        }
    }
    return size;
}
void load(Node *&N)
{
    cout << "Load Data ... " << endl;

    string s;
    fstream fsInFile("Oxford English Dictionary.txt", ios::in);
    int size = sizeFileInput(fsInFile);
    fsInFile.close();
    fstream fs("Oxford English Dictionary.txt", ios::in);
    info *Data = new info[size];
    int count = 0;
    while (!fs.eof())
    {
        string line;
        getline(fs, line);
        if (line.size() > 3)
        {
            string keys;
            string values;
            stringstream ss(line);
            getline(ss, keys, ' ');
            getline(ss, values, '\n');
            Data[count].Keys = keys;
            Data[count].Values = values;
            count++;
        }
    }
    fs.close();
    rightBalance(Data, count);
    for (int i = 0; i < count; ++i)
    {
        N = insertNode(N, Data[i]);
    }

    delete[] Data;
}

Node *find(Node *N, string s)
{
    if (N == NULL)
        return NULL;

    if (N->Data.Keys == s)
        return N;

    if (N->Data.Keys > s)
        return find(N->left, s);
    return find(N->right, s);
}
void search(Node *N)
{
    string key;

    cout << "Enter a Keys to translate Values: ";
    getline(cin, key);
    if (key[0] >= 'a' && key[0] <= 'z')
        key[0] -= 32;

    Node *p = find(N, key);
    if (p != NULL)
        cout << p->Data.Keys + ": " + p->Data.Values + "\n";
    else
        cout << "Can't find the Keys.\n";
}

void addNewKeys(Node *N)
{
    info D;

    cout << "Enter the Keys for adding: ";
    getline(cin, D.Keys);
    if (D.Keys[0] >= 'a' && D.Keys[0] <= 'z')
        D.Keys[0] -= 32;
    cout << "Enter the Values of word: ";
    getline(cin, D.Values);

    N = insertNode(N, D);
    cout << "Successfully added...\n";
}

void selection(Node *N)
{
    load(N);
    int temp = 5;
    bool flag = true;

    while (temp > 0)
    {
        system("cls");
        cout << "1. Search" << endl;
        cout << "0. Exit" << endl;
        cout << "Your choice: ";
        cin >> temp;
        cin.ignore();
        cout << endl;

        if (temp = 1)
        {
            search(N);
        }
        system("pause");
    }
}

int main()
{
    Node *N = NULL;
    cout << "RUN..." << endl;
    selection(N);

    return 0;
}