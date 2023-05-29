#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int array_max_size = 50;

int arrayDef[array_max_size], arrayDefSupport[array_max_size], arrayDefTree[array_max_size], k, v;
bool fail;
vector<int> keys(array_max_size);

const int array_range = 100;

int random(int range_min, int range_max) {
    return rand() % (range_max - range_min + 1) + range_min;
}

void merge(int arrayDef[], int arrayDefSupport[], int low, int mid, int high) {
    int k = low, i = low, j = mid + 1;

    while (i <= mid && j <= high) {
        if (arrayDef[i] <= arrayDef[j]) {
            arrayDefSupport[k++] = arrayDef[i++];
        } else {
            arrayDefSupport[k++] = arrayDef[j++];
        }
    }

    while (i <= mid) {
        arrayDefSupport[k++] = arrayDef[i++];
    }

    for (int i = low; i <= high; i++) {
        arrayDef[i] = arrayDefSupport[i];
    }
}

void mergesort(int arrayDef[], int arrayDefSupport[], int startRange, int endRange) {
    if (endRange <= startRange) {
        return;
    }

    int centre = (startRange + ((endRange - startRange) >> 1));
    mergesort(arrayDef, arrayDefSupport, startRange, centre);
    mergesort(arrayDef, arrayDefSupport, centre + 1, endRange);

    merge(arrayDef, arrayDefSupport, startRange, centre, endRange);
}

struct Node {
    int data;
    Node* left = nullptr, *right = nullptr;

    Node() {}
    Node(int data): data(data) {}
};

void inorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorder(root->left);
    if (root->data > 0) {
        cout << root->data << " ";
    }
    inorder(root->right);
}

Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }

    if (key < root->data) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }

    return root;
}

void convert(vector<int> const &keys, int low, int high, Node* &root){
    if (low > high) {
        return;
    }
    int mid = (low + high) / 2;
    root = new Node(keys[mid]);

    convert(keys, low, mid - 1, root->left);

    convert(keys, mid + 1, high, root->right);
}

Node* convert(vector<int> keys) {
    sort(keys.begin(), keys.end());

    Node* root = nullptr;
    convert(keys, 0, keys.size() - 1, root);

    return root;
}
int main() {
    setlocale(LC_ALL, "Russian");

    srand(static_cast<unsigned int>(time(NULL)));


    do {
        fail = false;
        cout << "Введите размерность массива и количество ключеё дерева,\n"
                "число k и v (число k и v в диапазоне 0 < k,v < " << array_max_size << " ):";
        cout << endl << "Введите k := ";
        cin >> k;
        cout << "Введите v := ";
        cin >> v;
        if ((k <= 0 || k >= array_max_size)) {
            cout << "*** Введены некорректное значения. Повторите ввод." << endl;
            fail = true;
        }
    } while (fail);

    for (int i = 0; i < k; i++) {
        arrayDefSupport[i] = arrayDef[i] = random(-array_range, array_range);
    }

    cout << "Элементы массива:" << endl;
    for (int i = 0; i < k; i++) {
        cout << arrayDef[i] << ", ";
    }

    mergesort(arrayDef, arrayDefSupport, 0, k - 1);

    cout << endl << "Отсортированный массив слиянием:" << endl;
    for (int i = 0; i < k; i++) {
        cout << arrayDef[i] << ", ";
    }


    for (int i = 0; i < v; i++) {
        keys[i] = random(1, array_range);
    }

    cout << endl << "Ключи дерева:" << endl;
    for (int i = 0; i < v; i++) {
        cout << keys[i] << ", ";
    }

    Node *root = convert(keys);

    cout << endl << "Построенное дерево BST:" << endl;
    inorder(root);

    return 0;
}
