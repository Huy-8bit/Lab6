#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <windows.h>
using namespace std;
#define sizeTable 12000
int random(int size)
{
    return rand() % (size - 0 + 0) + 0;
}
struct info
{
    string keys;
    string value;
};
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
void input(fstream &fsInFile)
{
    fstream fsTest("keys.txt", ios::in);
    int size = sizeFileInput(fsTest);
    fsTest.close();
    if (size < 10)
    {
        fstream fs1("keys.txt", ios::out);
        fstream fs2("value.txt", ios::out);
        while (!fsInFile.eof())
        {
            string line;
            getline(fsInFile, line);
            if (line.size() > 3)
            {
                string keys;
                string value;
                stringstream ss(line);
                getline(ss, keys, ' ');
                getline(ss, value, '\n');
                fs1 << keys << endl;
                fs2 << value << endl;
            }
        }

        fs1.clear();
        fs2.clear();
    }
}

int binarySearch(info *arr, int l, int r, string x)
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    clock_t start, end;
    start = clock();
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid].keys == x)
        {
            fsTime << "binarySearch ";
            end = clock();
            double duration = (double)(end - start);
            fsTime << " Time total:" << duration << "ms" << endl;
            fsTime.close();
            return mid;
        }
        else if (arr[mid].keys > x)
        {
            return binarySearch(arr, l, mid - 1, x);
        }
        return binarySearch(arr, mid + 1, r, x);
    }
    fsTime << "binarySearch ";
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
    return -1;
}
info *insertionSort(info *arr, int n)
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsTime << "Sort array: ";
    clock_t start, end;
    start = clock();
    cout << "Loading..." << endl;
    int i, j;
    string keys;
    for (i = 1; i < n; i++)
    {
        keys = arr[i].keys;
        j = i - 1;
        while (j >= 0 && arr[j].keys > keys)
        {
            swap(arr[j], arr[j + 1]);
            j = j - 1;
        }
        arr[j + 1].keys = keys;
    }
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
    return arr;
}
void search(info *arr, int size)
{
    cout << " Enter keys search :";
    string x;
    cin >> x;
    int temp = binarySearch(arr, 0, size - 1, x);
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << "Search : " << endl;
    fs3 << x << " : ";
    if (temp > 0)
    {
        cout << arr[temp].value << endl;
        fs3 << arr[temp].value << endl;
    }
    else
    {
        cout << " Don't see it" << endl;
        fs3 << " Don't see it" << endl;
    }
    fs3.close();
}
void saveFileArray(info *arrFinal, int &size)
{
    ofstream ofs1("keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1("keys.txt", ios::out);
    fstream fs2("value.txt", ios::out);
    for (int i = 0; i < size; i++)
    {
        fs1 << arrFinal[i].keys << endl;
        fs2 << arrFinal[i].value << endl;
    }
    fs1.close();
    fs2.close();
}
info *inputArr(info *arr, int size)
{
    fstream fs1("keys.txt", ios::in);
    fstream fs2("value.txt", ios::in);
    int i = 0;
    while (!fs1.eof())
    {
        string temp1;
        string temp2;
        getline(fs1, temp1);
        getline(fs2, temp2);
        if (temp1.length() > 0)
        {
            arr[i].keys = temp1;
            arr[i].value = temp2;
            i++;
        }
    }
    fs1.clear();
    fs2.clear();
    fs1.close();
    fs2.close();
    return arr;
}
void addData()
{
    int size;
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << "ADD Data:" << endl;
    cout << " ADD Data" << endl;
    string temp1;
    string temp2;
    cout << " Enter keys: ";
    cin.ignore();
    getline(cin, temp1);
    cout << "Enter value: ";
    getline(cin, temp2);
    cout << endl;
    fstream fs1("keys.txt", ios::out | ios::app);
    fstream fs2("value.txt", ios::in | ios::app);
    fs1 << temp1 << endl;
    fs2 << temp2 << endl;
    fs3 << temp1 << " : " << temp2 << endl;
    fs1.close();
    fs2.close();
    fs3.close();
}
void deleteData()
{
    fstream fs3("History.txt", ios::out | ios::app);
    int size;
    cout << " Deleted Data " << endl;
    fs3 << " Deleted Data " << endl;
    string temp1;
    fstream fs("keys.txt", ios::in);
    cout << " Enter keys: ";
    size = sizeFileInput(fs);
    cin.ignore();
    getline(cin, temp1);
    fs3 << temp1 << " : ";
    info *arr = new info[size];
    arr = inputArr(arr, size);
    int mid = binarySearch(arr, 0, size - 1, temp1);
    if (mid >= 0)
    {
        fs3 << arr[mid].value << endl;
        swap(arr[mid], arr[size - 1]);
        size--;
        saveFileArray(arr, size);
    }
    else if (mid == -1)
    {
        cout << "Not found" << endl;
        fs3 << "Not found" << endl;
    }
    fs3.close();
    delete[] arr;
}
void editData()
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << " EDIT Data" << endl;
    cout << " EDIT Data" << endl;
    int size;
    string temp1;
    string temp2;
    fstream fs1("keys.txt", ios::in);
    size = sizeFileInput(fs1);
    fs1.close();
    info *arrTemp = new info[size];
    arrTemp = inputArr(arrTemp, size);
    arrTemp = insertionSort(arrTemp, size);
    cout << " Enter keys: ";
    cin.ignore();
    cin >> temp1;
    fs3 << temp1 << " : " << endl;
    int mid = binarySearch(arrTemp, 0, size - 1, temp1);
    if (mid >= 0)
    {
        fs3 << " prev value: " << arrTemp[mid].value << endl;
        cout << "Enter value: ";
        cin.ignore();
        getline(cin, temp2);
        fs3 << " New value: " << temp2 << endl;
        arrTemp[mid].value = temp2;
        saveFileArray(arrTemp, size);
    }
    else
    {
        cout << " Not found " << endl;
        fs3 << " Not found" << endl;
    }
    fs3.close();
    delete[] arrTemp;
}
void process(int seletc)
{
    int size;
    if (seletc == 1)
    {
        fstream fsTemp("keys.txt", ios::in);
        size = sizeFileInput(fsTemp);
        fsTemp.close();
        info *arr = new info[size];
        arr = inputArr(arr, size);
        arr = insertionSort(arr, size);
        search(arr, size);
        delete[] arr;
    }
    else if (seletc == 2)
    {
        addData();
    }
    else if (seletc == 3)
    {
        deleteData();
    }
    else if (seletc == 4)
    {
        editData();
    }
    if (seletc != 1)
    {
        fstream fsFinals("keys.txt", ios::in);
        size = sizeFileInput(fsFinals);
        fsFinals.close();
        info *arrFinal = new info[size];
        arrFinal = inputArr(arrFinal, size);
        arrFinal = insertionSort(arrFinal, size);
        saveFileArray(arrFinal, size);
        delete[] arrFinal;
    }
}
void selection()
{
    cout << " ARRAY " << endl;
    cout << "1. SEARCH" << endl;
    cout << "2. ADD Data" << endl;
    cout << "3. DELETE Data" << endl;
    cout << "4. EDIT Data" << endl;
    cout << "5. EXIT " << endl;
    cout << " Choose your choice : ";
    int seletc;
    cin >> seletc;
    if (seletc < 5)
    {
        process(seletc);
    }
}
struct node
{
    info table;
    node *next;
};
typedef node *hashtable[sizeTable];
void tableInitialization(hashtable &H)
{
    for (int i = 0; i < sizeTable; i++)
    {
        H[i] = NULL;
    }
}
int hashKeys(string str)
{

    long sum = 0, mul = 1;
    for (int i = 0; i < str.length(); i++)
    {
        mul = (i % 4 == 0) ? 1 : mul * 256;
        sum += str.at(i) * mul;
    }
    return (int)(abs(sum) % sizeTable);
}
void addNode(hashtable &H, info table)
{
    node *p = new node{table, NULL};
    int num = hashKeys(table.keys);
    if (H[num] == NULL)
    {
        H[num] = p;
    }
    else
    {
        node *q = H[num];
        while (q->next != NULL)
        {
            q = q->next;
        }
        q->next = p;
    }
}
node *find_node(hashtable &H, string temp)
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsTime << "find_node ";
    clock_t start, end;
    start = clock();
    int num = hashKeys(temp);
    node *p = H[num];
    while (p != NULL && p->table.keys != temp)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        end = clock();
        double duration = (double)(end - start);
        fsTime << " Time total:" << duration << "ms" << endl;
        fsTime.close();
        return NULL;
    }
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
    return p;
}
void loadFile(hashtable &H)
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsTime << "loadFile ";
    clock_t start, end;
    start = clock();
    fstream fs1("keys.txt", ios::in);
    fstream fs2("value.txt", ios::in);
    while (!fs1.eof())
    {
        string temp1;
        string temp2;
        getline(fs1, temp1);
        getline(fs2, temp2);
        info table{temp1, temp2};
        addNode(H, table);
    }
    fs1.close();
    fs2.close();
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
}
void searchHash(hashtable &H)
{
    fstream fsH("History.txt", ios::out | ios::app);
    fsH << "ADD Data" << endl;
    node *find;
    string temp;
    cout << "Enter keys: ";
    cin.ignore();
    getline(cin, temp);
    find = find_node(H, temp);
    if (find == NULL)
    {
        cout << "Not found" << endl;
        fsH << temp << " : "
            << "Not found" << endl;
    }
    else
    {
        cout << find->table.value << endl;
        fsH << temp << " : " << find->table.value << endl;
    }
    fsH.close();
}
void addDataHash(hashtable &H)
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << "ADD Data:" << endl;
    info table;
    string temp1;
    string temp2;
    cout << "Enter keys: ";
    cin.ignore();
    getline(cin, temp1);
    cout << "Enter value: ";
    getline(cin, temp2);
    table.keys = temp1;
    table.value = temp2;
    fs3 << temp1 << " : " << temp2 << endl;
    addNode(H, table);
}
void deleteDataHash(hashtable &H)
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << " Deleted Data " << endl;
    node *deleteData;
    string temp1;
    cout << "Enter keys: ";
    cin.ignore();
    getline(cin, temp1);
    int index = hashKeys(temp1);
    deleteData = find_node(H, temp1);
    if (deleteData == NULL)
    {
        cout << "Don't see" << endl
             << endl;
    }
    else if (deleteData == H[index])
    {
        H[index] = H[index]->next;
        delete deleteData;
    }
    else
    {
        node *q = H[index];
        q->next = deleteData->next;
        delete deleteData;
    }
}
void editDataHash(hashtable &H)
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << " EDIT Data" << endl;
    node *editDataHash;
    string temp1;
    cout << "Enter keys: ";
    cin.ignore();
    getline(cin, temp1);
    fs3 << temp1 << " : " << endl;
    editDataHash = find_node(H, temp1);
    if (editDataHash == NULL)
    {
        cout << "Not found" << endl
             << endl;
        fs3 << " Not found" << endl;
    }
    else
    {
        cout << "Enter value: ";
        string temp2;
        getline(cin, temp2);
        fs3 << " prev value: " << editDataHash->table.value << endl;
        editDataHash->table.value = temp2;
        fs3 << " New value: " << temp2 << endl;
    }
}
void saveDataHash(hashtable &H)
{
    ofstream ofs1("keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1("keys.txt", ios::out);
    fstream fs2("value.txt", ios::out);
    for (int i = 0; i < sizeTable; i++)
    {
        node *temp = H[i];
        while (temp != NULL)
        {
            if (temp->table.keys.length() > 1)
            {
                fs1 << temp->table.keys << endl;
                fs2 << temp->table.value << endl;
            }
            temp = temp->next;
        }
        delete[] temp;
    }
    fs1.close();
    fs2.close();
}
void selectionHash(hashtable &H)
{
    cout << " HASH TABLE " << endl;
    cout << "1. SEARCH" << endl;
    cout << "2. ADD Data" << endl;
    cout << "3. DELETE Data" << endl;
    cout << "4. EDIT Data" << endl;
    cout << " Choose your choice : ";
    int seletc;
    cin >> seletc;
    if (seletc == 1)
    {
        searchHash(H);
    }
    else if (seletc == 2)
    {
        addDataHash(H);
    }
    else if (seletc == 3)
    {
        deleteDataHash(H);
    }
    else if (seletc == 4)
    {
        editDataHash(H);
    }
    saveDataHash(H);
}
struct Node
{
    info Data;
    Node *left;
    Node *right;
    int height;
};

typedef Node *Tree;

Node *CreateNode(string keys, string value)
{
    Node *p = new Node;
    p->Data.keys = keys;
    p->Data.value = value;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void CreateTree(Tree &root)
{
    root = NULL;
}

void DestroyTree(Tree &root)
{
    if (root)
    {
        DestroyTree(root->left);
        DestroyTree(root->right);
        delete root;
    }
}

void AddNode(Tree &root, Node *node)
{
    if (root)
    {
        if (node->Data.keys <= root->Data.keys)
        {
            AddNode(root->left, node);
        }
        else
        {
            AddNode(root->right, node);
        }
    }
    else
    {
        root = node;
    }
}

Node *FindNode(Tree root, string keys)
{
    if (root)
    {
        if (root->Data.keys == keys)
        {
            return root;
        }
        if (keys < root->Data.keys)
        {
            return FindNode(root->left, keys);
        }
        return FindNode(root->right, keys);
    }
    return NULL;
}

void saveDataTree(Tree root, fstream &fs1, fstream &fs2)
{
    if (root == NULL)
    {
        return;
    }
    saveDataTree(root->left, fs1, fs2);

    fs1 << root->Data.keys << endl;
    fs2 << root->Data.value << endl;

    saveDataTree(root->right, fs1, fs2);
}
void FindAndReplace(Tree &p, Tree &tree)
{
    if (tree->left)
        FindAndReplace(p, tree->left);
    else
    {
        p->Data.keys = tree->Data.keys;
        p = tree;
        tree = tree->right;
    }
}

void DeleteNode(Tree &root, string x)
{
    if (root)
    {
        if (x > root->Data.keys)
        {
            DeleteNode(root->right, x);
        }
        else if (x < root->Data.keys)
        {
            DeleteNode(root->left, x);
        }
        else
        {
            Node *p = root;
            if (!root->left)
            {
                root = root->right;
            }
            else if (!root->right)
            {
                root = root->left;
            }
            else
            {
                FindAndReplace(p, root->right);
            }
            delete p;
        }
    }
    else
    {
        cout << endl
             << "Not found!\n";
    }
}

void processTree(Tree t, int seletc)
{
    fstream fsH("History.txt", ios::out | ios::app);
    fstream fsTime("Time.txt", ios::out | ios::app);
    string temps;
    clock_t start, end;
    double duration;

    if (seletc == 1)
    {
        fsH << "Search: ";
        cout << endl
             << "Input Data to search: ";
        cin >> temps;
        fsH << temps << " : ";
        start = clock();
        Node *find = FindNode(t, temps);
        end = clock();
        duration = (double)(end - start);
        fsTime << "Search:"
               << " Time total:" << duration << "ms" << endl;
        if (find == NULL)
        {
            fsH << "Not found" << endl;
            cout << endl
                 << "Not find" << endl;
        }
        else
        {
            fsH << find->Data.value << endl;
            cout << endl
                 << find->Data.keys << " : " << find->Data.value << endl;
        }
    }
    else if (seletc == 2)
    {
        string keys;
        string value;
        fsH << "Add : ";
        cout << "Enter keys:";
        cin.ignore();
        cin >> keys;
        fsH << keys << " : ";
        cout << endl
             << " Enter value: ";
        cin.ignore();
        getline(cin, value);
        fsH << value << endl;
        start = clock();
        AddNode(t, CreateNode(keys, value));
        end = clock();
        duration = (double)(end - start);
        fsTime << "Add: "
               << " Time total:" << duration << "ms" << endl;
    }
    else if (seletc == 3)
    {
        fsH << "Edit : ";
        cout << endl
             << "Enter keys delete ";
        cin >> temps;
        fsH << temps << endl;
        start = clock();
        DeleteNode(t, temps);
        end = clock();
        duration = (double)(end - start);
        fsTime << "Delete: "
               << " Time total:" << duration << "ms" << endl;
    }
    else if (seletc == 4)
    {
        fsH << "Edit : ";
        cout << endl
             << "Input Data to Edit: ";
        cin >> temps;
        fsH << temps << " : ";
        start = clock();
        Node *find = FindNode(t, temps);
        if (find == NULL)
        {
            fsH << "Not find" << endl;
            cout << endl
                 << "Not find" << endl;
        }
        else
        {

            cout << endl
                 << " prev Data : " << find->Data.value << endl;
            fsH << endl
                << " prev Data : " << find->Data.value << endl;
            string value;
            cout << "Enter new Data ";
            cin.ignore();
            getline(cin, value);
            fsH << "New value: " << value << endl;
            find->Data.value = value;
        }
        end = clock();
        duration = (double)(end - start);
        fsTime << "Edit: "
               << " Time total:" << duration << "ms" << endl;
    }
    fsTime.close();
}

void selectionTree(Tree t)
{

    fstream fsKeys("keys.txt", ios::in);
    fstream fsValue("value.txt", ios::in);
    int count = 0;

    while (!fsKeys.eof())
    {
        string keys;
        string value;
        getline(fsKeys, keys);
        getline(fsValue, value);
        AddNode(t, CreateNode(keys, value));
    }

    fsKeys.close();
    fsValue.close();
    cout << " AVL TREE " << endl;
    cout << "1. SEARCH" << endl;
    cout << "2. ADD Data" << endl;
    cout << "3. DELETE Data" << endl;
    cout << "4. EDIT Data" << endl;
    cout << " Choose your choice : ";
    int seletc;
    cin >> seletc;
    processTree(t, seletc);
    cout << "Save File" << endl;
    ofstream ofs1("keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1("keys.txt", ios::out);
    fstream fs2("value.txt", ios::out);
    saveDataTree(t, fs1, fs2);
    fs1.close();
    fs2.close();
}
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
int findMax(int a, int b)
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
    N->height = findMax(height(N->left), height(N->right)) + 1;
    Nl->height = findMax(height(Nl->left), height(Nl->right)) + 1;
    return Nl;
}
Node *leftRotate(Node *N)
{
    Node *Nr = N->right;
    Node *Nrl = Nr->left;

    Nr->left = N;
    N->right = Nrl;

    N->height = findMax(height(N->left), height(N->right)) + 1;
    Nr->height = findMax(height(Nr->left), height(Nr->right)) + 1;

    return Nr;
}
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return (height(N->left) - height(N->right));
}

Node *insertNodeTree(Node *N, info Data)
{
    if (N == NULL)
        return createNode(Data);

    if (Data.keys < N->Data.keys)
        N->left = insertNodeTree(N->left, Data);
    else if (Data.keys > N->Data.keys)
        N->right = insertNodeTree(N->right, Data);
    else
        return N;

    N->height = findMax(height(N->left), height(N->right)) + 1;

    int balance = getBalance(N);

    // LL & RR
    if (balance > 1 && Data.keys < N->Data.keys)
        return rightRotate(N);
    if (balance < -1 && Data.keys > N->Data.keys)
        return leftRotate(N);

    // LR & RL
    if (balance > 1 && Data.keys > N->Data.keys)
    {
        N->left = leftRotate(N->left);
        return rightRotate(N);
    }
    if (balance < -1 && Data.keys < N->Data.keys)
    {
        N->right = rightRotate(N->right);
        return leftRotate(N);
    }

    return N;
}
void addKeys(Node *N)
{
    string key;
    string value;
    cout << "Enter new keys:";
    cin >> key;
    cout << "Enter new value:";
    cin.ignore();
    getline(cin, value);
    info Data;
    Data.keys = key;
    Data.value = value;
    N = insertNodeTree(N, Data);
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

    if (s < N->Data.keys)
        N->left = deleteNode(N->left, s);
    else if (s > N->Data.keys)
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
            N->right = deleteNode(N->right, p->Data.keys);
        }
    }

    if (N == NULL)
        return N;

    N->height = findMax(height(N->left), height(N->right)) + 1;

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
        if (D[i].keys == "Usage")
        {
            if (D[i].value[0] != 'n' || D[i].value[1] != '.')
            {
                D[i - 1].value += " " + D[i].keys + ": " + D[i].value;
                D[i].keys = D[size - 1].keys;
                D[i].value = D[size - 1].value;
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
            if (D[j].value == D[i].value)
            {
                D[j].keys = D[size - 1].keys;
                D[j].value = D[size - 1].value;
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

    string s = D[(l + r) / 2].keys;

    int i = l;
    int j = r;

    while (i <= j)
    {
        while (D[i].keys < s)
            ++i;
        while (D[j].keys > s)
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
// int sizeFileInput(fstream &fsInFile)
// {
//     int size = 0;
//     while (!fsInFile.eof())
//     {
//         string temp;
//         getline(fsInFile, temp);
//         if (temp.length() > 1)
//         {
//             size++;
//         }
//     }
//     return size;
// }
void load(Node *&N)
{
    cout << "Load Data ... " << endl;

    string s;
    fstream fsInFile("keys.txt", ios::in);
    int size = sizeFileInput(fsInFile);
    fsInFile.close();
    info *Data = new info[size];
    int count = 0;
    fstream fsKeys("keys.txt", ios::in);
    fstream fsValue("value.txt", ios::in);
    while (!fsKeys.eof())
    {
        string keys;
        string value;
        getline(fsKeys, keys);
        getline(fsValue, value);
        Data[count].keys = keys;
        Data[count].value = value;
        count++;
    }
    fsKeys.close();
    fsValue.close();
    rightBalance(Data, count);
    for (int i = 0; i < count; ++i)
    {
        N = insertNodeTree(N, Data[i]);
    }

    delete[] Data;
}

Node *find(Node *N, string s)
{
    if (N == NULL)
        return NULL;

    if (N->Data.keys == s)
        return N;

    if (N->Data.keys > s)
        return find(N->left, s);
    return find(N->right, s);
}
void search(Node *N)
{
    string key;

    cout << "Enter a keys to translate value: ";
    getline(cin, key);
    if (key[0] >= 'a' && key[0] <= 'z')
        key[0] -= 32;

    Node *p = find(N, key);
    if (p != NULL)
        cout << p->Data.keys + ": " + p->Data.value + "\n";
    else
        cout << "Can't find the keys.\n";
}

void addNewKeys(Node *N)
{
    info D;

    cout << "Enter the keys for adding: ";
    getline(cin, D.keys);
    if (D.keys[0] >= 'a' && D.keys[0] <= 'z')
        D.keys[0] -= 32;
    cout << "Enter the value of word: ";
    getline(cin, D.value);

    N = insertNodeTree(N, D);
    cout << "Successfully added...\n";
}
void delAWord(Node *N)
{
    string key;
    cout << "Enter a word to delete: ";
    getline(cin, key);
    N = deleteNode(N, key);
    if (N == NULL)
    {
        cout << "Can't find the word.\n";
        return;
    }
    cout << "Successfully deleted...\n";
}
void editvalue(Node *N)
{
    string key;
    Node *result;
    cout << "Enter a word to edit value: ";
    getline(cin, key);
    if (key[0] >= 'a' && key[0] <= 'z')
        key[0] -= 32;
    result = find(N, key);
    if (result == NULL)
        cout << "Can't find the word.\n";
    else
    {
        cout << result->Data.keys + ": " + result->Data.value + '\n';
        cout << "Enter new value for editing: ";
        getline(cin, key);
        result->Data.value = key;
        cout << result->Data.keys + ": " + result->Data.value + "\n";
    }
}
void outputTree(Node *N, fstream &fsKeys, fstream &fsValue)
{
    if (N == NULL)
        return;
    outputTree(N->left, fsKeys, fsValue);
    fsKeys << N->Data.keys << endl;
    fsValue << N->Data.value << endl;
    outputTree(N->right, fsKeys, fsValue);
}
void save(Node *N)
{
    fstream fsKeys("keys.txt", ios::out);
    fstream fsValue("keys.txt", ios::out);
    outputTree(N, fsKeys, fsValue);
}
void selectionAvl(Node *N)
{
    load(N);
    int temp = 5;
    bool flag = true;

    while (temp > 0)
    {
        cout << " AVL tree" << endl;
        cout << "1. SEARCH" << endl;
        cout << "2. ADD Data" << endl;
        cout << "3. DELETE Data" << endl;
        cout << "4. EDIT Data" << endl;
        cout << "5. EXIT " << endl;
        cout << " Choose your choice : ";
        cin >> temp;
        cin.ignore();
        cout << endl;
        if (temp == 0)
        {
            break;
        }
        else if (temp == 1)
        {
            search(N);
        }
        else if (temp == 2)
        {
            addKeys(N);
        }
        else if (temp == 3)
        {
            delAWord(N);
        }
        else if (temp == 4)
        {
            editvalue(N);
        }

        system("pause");
    }
}
void AVLTree()
{
    Node *N = NULL;
    selectionAvl(N);
}
int main()
{
    //system("color 80");
    cout << "RUN..." << endl;
    srand(time(NULL));
    int Select = 0;
    fstream fsInFile("Oxford English Dictionary.txt", ios::in);
    input(fsInFile);
    fsInFile.close();
    while (Select <= 5 && Select >= 0)
    {
        system("cls");
        fstream fsTime("Time.txt", ios::out | ios::app);
        fstream fsH("History.txt", ios::out | ios::app);
        cout << "LAB5_20127185_Nguyen Gia Huy" << endl;
        cout << "1. Run with array" << endl;
        cout << "2. Run with  Hash Table " << endl;
        cout << "3. Run with  Tree " << endl;
        cout << "4. Run with AVLTree        " << endl;
        cout << "5. Show History        " << endl;
        cout << "6.   EXIT     " << endl;
        cout << " Enter your choice: ";
        cin >> Select;
        if (Select == 1)
        {
            fsH << "Run with array" << endl;
            fsTime << "Run with array" << endl;
            selection();
            system("pause");
        }
        else if (Select == 2)
        {
            fsH << "Run with Hash Table" << endl;
            fsTime << "Run with Hash Table" << endl;
            cout << "Loading..." << endl;
            hashtable H;
            tableInitialization(H);
            loadFile(H);
            selectionHash(H);
            system("pause");
        }
        else if (Select == 3)
        {

            fsH << "Run with Binary tree" << endl;
            fsTime << "Run with Binary tree" << endl;
            Tree t;
            CreateTree(t);
            cout << "Loading..." << endl;
            selectionTree(t);
            system("pause");
        }
        else if (Select == 4)
        {
            AVLTree();
        }
        else if (Select == 5)
        {
            fstream History("History.txt", ios::in);
            while (!History.eof())
            {
                string temp;
                getline(History, temp);
                cout << temp << endl;
            }
            system("pause");
        }
        else
        {
            Beep(523, 1000);
        }
        fsTime.close();
        fsH.close();
    }
    return 0;
}
