#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
using namespace std;

#define sizeTable 12000
int random(int size)
{
    return rand() % (size - 0 + 0) + 0;
}
struct info
{
    string Keys;
    string Value;
};
int sizeFileInput(fstream &fsInFile)
{
    int size = 0;
    while (!fsInFile.eof())
    {
        string temp;
        getline(fsInFile, temp);
        size++;
    }
    return size;
}
void input(fstream &fsInFile)
{
    fstream fsTest("Keys.txt", ios::in);
    int size = sizeFileInput(fsTest);
    fsTest.close();
    if (size < 10)
    {
        fstream fs1("Keys.txt", ios::out);
        fstream fs2("Value.txt", ios::out);
        while (!fsInFile.eof())
        {
            string line;
            getline(fsInFile, line);
            if (line.size() > 3)
            {
                string Keys;
                string Value;
                stringstream ss(line);
                getline(ss, Keys, ' ');
                getline(ss, Value, '\n');
                fs1 << Keys << endl;
                fs2 << Value << endl;
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
        if (arr[mid].Keys == x)
        {
            fsTime << "binarySearch ";
            end = clock();
            double duration = (double)(end - start);
            fsTime << " Time total:" << duration << "ms" << endl;
            fsTime.close();
            return mid;
        }
        else if (arr[mid].Keys > x)
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
    string Keys;
    for (i = 1; i < n; i++)
    {
        Keys = arr[i].Keys;
        j = i - 1;
        while (j >= 0 && arr[j].Keys > Keys)
        {
            swap(arr[j], arr[j + 1]);
            j = j - 1;
        }
        arr[j + 1].Keys = Keys;
    }
    end = clock();
    double duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    fsTime.close();
    return arr;
}
void search(info *arr, int size)
{
    cout << " Enter Keys search :";
    string x;
    cin >> x;
    int temp = binarySearch(arr, 0, size - 1, x);
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << "Search : " << endl;
    fs3 << x << " : ";
    if (temp > 0)
    {
        cout << arr[temp].Value << endl;
        fs3 << arr[temp].Value << endl;
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
    ofstream ofs1("Keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("Value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1("Keys.txt", ios::out);
    fstream fs2("Value.txt", ios::out);
    for (int i = 0; i < size; i++)
    {
        fs1 << arrFinal[i].Keys << endl;
        fs2 << arrFinal[i].Value << endl;
    }
    fs1.close();
    fs2.close();
}
info *inputArr(info *arr, int size)
{
    fstream fs1("Keys.txt", ios::in);
    fstream fs2("Value.txt", ios::in);
    int i = 0;
    while (!fs1.eof())
    {
        string temp1;
        string temp2;
        getline(fs1, temp1);
        getline(fs2, temp2);
        if (temp1.length() > 0)
        {
            arr[i].Keys = temp1;
            arr[i].Value = temp2;
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
    cout << " Enter Keys: ";
    cin.ignore();
    getline(cin, temp1);
    cout << "Enter Value: ";
    getline(cin, temp2);
    cout << endl;
    fstream fs1("Keys.txt", ios::out | ios::app);
    fstream fs2("Value.txt", ios::in | ios::app);
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
    fstream fs("Keys.txt", ios::in);
    cout << " Enter Keys: ";
    size = sizeFileInput(fs);
    cin.ignore();
    getline(cin, temp1);
    fs3 << temp1 << " : ";
    info *arr = new info[size];
    arr = inputArr(arr, size);
    int mid = binarySearch(arr, 0, size - 1, temp1);
    if (mid >= 0)
    {
        fs3 << arr[mid].Value << endl;
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
    fstream fs1("Keys.txt", ios::in);
    size = sizeFileInput(fs1);
    fs1.close();
    info *arrTemp = new info[size];
    arrTemp = inputArr(arrTemp, size);
    arrTemp = insertionSort(arrTemp, size);
    cout << " Enter Keys: ";
    cin.ignore();
    cin >> temp1;
    fs3 << temp1 << " : " << endl;
    int mid = binarySearch(arrTemp, 0, size - 1, temp1);
    if (mid >= 0)
    {
        fs3 << " prev Value: " << arrTemp[mid].Value << endl;
        cout << "Enter Value: ";
        cin.ignore();
        getline(cin, temp2);
        fs3 << " New Value: " << temp2 << endl;
        arrTemp[mid].Value = temp2;
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
        fstream fsTemp("Keys.txt", ios::in);
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
        fstream fsFinals("Keys.txt", ios::in);
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
    int num = hashKeys(table.Keys);
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
    while (p != NULL && p->table.Keys != temp)
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
    fstream fs1("Keys.txt", ios::in);
    fstream fs2("Value.txt", ios::in);
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
    cout << "Enter Keys: ";
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
        cout << find->table.Value << endl;
        fsH << temp << " : " << find->table.Value << endl;
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
    cout << "Enter Keys: ";
    cin.ignore();
    getline(cin, temp1);
    cout << "Enter value: ";
    getline(cin, temp2);
    table.Keys = temp1;
    table.Value = temp2;
    fs3 << temp1 << " : " << temp2 << endl;
    addNode(H, table);
}
void deleteDataHash(hashtable &H)
{
    fstream fs3("History.txt", ios::out | ios::app);
    fs3 << " Deleted Data " << endl;
    node *deleteData;
    string temp1;
    cout << "Enter Keys: ";
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
    cout << "Enter Keys: ";
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
        cout << "Enter Value: ";
        string temp2;
        getline(cin, temp2);
        fs3 << " prev Value: " << editDataHash->table.Value << endl;
        editDataHash->table.Value = temp2;
        fs3 << " New Value: " << temp2 << endl;
    }
}
void saveDataHash(hashtable &H)
{
    ofstream ofs1("Keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("Value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1("Keys.txt", ios::out);
    fstream fs2("Value.txt", ios::out);
    for (int i = 0; i < sizeTable; i++)
    {
        node *temp = H[i];
        while (temp != NULL)
        {
            if (temp->table.Keys.length() > 1)
            {
                fs1 << temp->table.Keys << endl;
                fs2 << temp->table.Value << endl;
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

Node *CreateNode(string Keys, string value)
{
    Node *p = new Node;
    p->Data.Keys = Keys;
    p->Data.Value = value;
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
        if (node->Data.Keys <= root->Data.Keys)
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

Node *FindNode(Tree root, string Keys)
{
    if (root)
    {
        if (root->Data.Keys == Keys)
        {
            return root;
        }
        if (Keys < root->Data.Keys)
        {
            return FindNode(root->left, Keys);
        }
        return FindNode(root->right, Keys);
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

    fs1 << root->Data.Keys << endl;
    fs2 << root->Data.Value << endl;

    saveDataTree(root->right, fs1, fs2);
}
void FindAndReplace(Tree &p, Tree &tree)
{
    if (tree->left)
        FindAndReplace(p, tree->left);
    else
    {
        p->Data.Keys = tree->Data.Keys;
        p = tree;
        tree = tree->right;
    }
}

void DeleteNode(Tree &root, string x)
{
    if (root)
    {
        if (x > root->Data.Keys)
        {
            DeleteNode(root->right, x);
        }
        else if (x < root->Data.Keys)
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
            fsH << find->Data.Value << endl;
            cout << endl
                 << find->Data.Keys << " : " << find->Data.Value << endl;
        }
    }
    else if (seletc == 2)
    {
        string Keys;
        string value;
        fsH << "Add : ";
        cout << "Enter Keys:";
        cin.ignore();
        cin >> Keys;
        fsH << Keys << " : ";
        cout << endl
             << " Enter value: ";
        cin.ignore();
        getline(cin, value);
        fsH << value << endl;
        start = clock();
        AddNode(t, CreateNode(Keys, value));
        end = clock();
        duration = (double)(end - start);
        fsTime << "Add: "
               << " Time total:" << duration << "ms" << endl;
    }
    else if (seletc == 3)
    {
        fsH << "Edit : ";
        cout << endl
             << "Enter Keys delete ";
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
                 << " prev Data : " << find->Data.Value << endl;
            fsH << endl
                << " prev Data : " << find->Data.Value << endl;
            string Value;
            cout << "Enter new Data ";
            cin.ignore();
            getline(cin, Value);
            fsH << "New Value: " << Value << endl;
            find->Data.Value = Value;
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

    fstream fsKeys("Keys.txt", ios::in);
    fstream fsValue("Value.txt", ios::in);
    int count = 0;

    while (!fsKeys.eof())
    {
        string Keys;
        string Value;
        getline(fsKeys, Keys);
        getline(fsValue, Value);
        AddNode(t, CreateNode(Keys, Value));
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
    ofstream ofs1("Keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("Value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1("Keys.txt", ios::out);
    fstream fs2("Value.txt", ios::out);
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

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *createNodeAvl(info Data)
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
        return createNodeAvl(Data);

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
void addKeys(Node *N)
{
    string key;
    string value;
    cout << "Enter new Keys:";
    cin >> key;
    cout << "Enter new Value:";
    cin.ignore();
    getline(cin, value);
    info Data;
    Data.Keys = key;
    Data.Value = value;
    N = insertNode(N, Data);
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
void rightBalance(info *D, int &size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (D[j].Value == D[i].Value)
            {
                D[j].Keys = D[size - 1].Keys;
                D[j].Value = D[size - 1].Value;
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
void load(Node *&N)
{
    fstream fsTime("Time.txt", ios::out | ios::app);
    clock_t start, end;
    double duration;
    start = clock();
    string s;
    fstream fsInFile("Keys.txt", ios::in);
    int size = sizeFileInput(fsInFile);
    fsInFile.close();
    info *Data = new info[size];
    int count = 0;
    fstream fs1("Keys.txt", ios::in);
    fstream fs2("Value.txt", ios::in);
    while (!fs1.eof())
    {
        string keys;
        string values;
        getline(fs1, keys);
        getline(fs2, values);
        Data[count].Keys = keys;
        Data[count].Value = values;
        count++;
    }
    count = count - 1;
    rightBalance(Data, count);
    for (int i = 0; i <= count; i++)
    {
        N = insertNode(N, Data[i]);
    }

    delete[] Data;
    fsTime << "Load : ";
    end = clock();
    duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
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
    fstream fsH("History.txt", ios::out | ios::app);
    fstream fsTime("Time.txt", ios::out | ios::app);
    string key;
    fsH << "SEARCH: " << endl;
    fsTime << "SEARCH: ";
    cout << "Enter a Keys to translate Value: ";
    cin.ignore();
    getline(cin, key);
    clock_t start, end;
    double duration;
    start = clock();
    Node *p = find(N, key);
    if (p != NULL)
    {
        cout << p->Data.Keys + ": " + p->Data.Value + "\n";
        fsH << p->Data.Keys + ": " + p->Data.Value + "\n";
    }
    else
    {
        cout << "Can't find the Keys.\n";
        fsH << key << " : Can't find the Keys.\n";
    }
    end = clock();
    duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
}

void addNewKeys(Node *N)
{
    fstream fsH("History.txt", ios::out | ios::app);
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsH << "Add: " << endl;
    fsTime << "Add: ";
    info D;
    cout << "Enter the Keys for adding: ";
    cin.ignore();
    getline(cin, D.Keys);
    cout << "Enter the Value of word: ";
    getline(cin, D.Value);
    fsH << "key: " << endl;
    clock_t start, end;
    double duration;
    start = clock();
    N = insertNode(N, D);
    end = clock();
    duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    cout << "Successfully added...\n";
}
void delAWord(Node *N)
{
    fstream fsH("History.txt", ios::out | ios::app);
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsH << "Delete: " << endl;
    fsTime << "Delete: ";
    string key;
    cout << "Enter a word to delete: ";
    cin.ignore();
    getline(cin, key);
    fsH << key;
    clock_t start, end;
    double duration;
    start = clock();
    N = deleteNode(N, key);
    end = clock();
    duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    if (N == NULL)
    {
        cout << "Can't find the word.\n";
        fsH << "Can't find the word.\n";
        return;
    }
    else
    {
        fsH << "Done" << endl;
    }
    cout << "Successfully deleted...\n";
}
void editValue(Node *N)
{
    fstream fsH("History.txt", ios::out | ios::app);
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsH << "Edit: " << endl;
    fsTime << "Edit: ";
    string key;
    Node *result;
    cout << "Enter a word to edit Value: ";
    cin.ignore();
    getline(cin, key);
    fsH << key << " : ";
    clock_t start, end;
    double duration;
    start = clock();
    result = find(N, key);
    end = clock();
    duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    if (result == NULL)
    {
        cout << "Can't find the word.\n";
        fsH << "Can't find the word.\n";
    }
    else
    {
        cout << result->Data.Keys + ": " + result->Data.Value + '\n';
        fsH << result->Data.Value << endl;
        cout << "Enter new Value for editing: ";
        fsH << "New Value for editing: ";
        getline(cin, key);
        fsH << key << endl;
        result->Data.Value = key;
        cout << result->Data.Keys + ": " + result->Data.Value + "\n";
    }
}
void outputTree(Node *N, fstream &fs1, fstream &fs2)
{
    if (N == NULL)
        return;
    outputTree(N->left, fs1, fs2);
    fs1 << N->Data.Keys << endl;
    fs2 << N->Data.Value << endl;
    outputTree(N->right, fs1, fs2);
}
void save(Node *N)
{
    ofstream ofs1("Keys.txt", std::ofstream::out);
    ofs1.close();
    ofstream ofs2("Value.txt", std::ofstream::out);
    ofs2.close();
    fstream fs1;
    fs1.open("Keys.txt", ios::out | ios::app);
    fstream fs2;
    fs2.open("Value.txt", ios::out | ios::app);
    outputTree(N, fs1, fs2);
}
void selectionAvl(Node *N)
{
    load(N);
    int temp = 5;
    bool flag = true;

    cout << " AvlTree " << endl;
    cout << "1. SEARCH" << endl;
    cout << "2. ADD Data" << endl;
    cout << "3. DELETE Data" << endl;
    cout << "4. EDIT Data" << endl;
    cout << " Choose your choice : ";
    cin >> temp;
    cout << endl;
    if (temp == 1)
    {
        search(N);
    }
    else if (temp == 2)
    {
        addNewKeys(N);
    }
    else if (temp == 3)
    {
        delAWord(N);
    }
    else if (temp == 4)
    {
        editValue(N);
    }
    fstream fsTime("Time.txt", ios::out | ios::app);
    fsTime << "save: ";
    clock_t start, end;
    double duration;
    start = clock();
    save(N);
    end = clock();
    duration = (double)(end - start);
    fsTime << " Time total:" << duration << "ms" << endl;
    system("pause");
}

int avlTree()
{
    Node *N = NULL;
    cout << "Loading..." << endl;
    selectionAvl(N);

    return 0;
}
int main()
{
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
        cout << "3. Run with  Binary Tree " << endl;
        cout << "4. Run with avlTree " << endl;
        cout << "5.    Show History        " << endl;
        cout << "6.       EXIT        " << endl;
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
            fsH << "Run with AVL tree" << endl;
            fsTime << "Run with AVL tree" << endl;
            avlTree();
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
        fsTime.close();
        fsH.close();
    }
    return 0;
}