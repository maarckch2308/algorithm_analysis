#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class BinaryTree {
private:
    struct Node {
        T value;
        Node *left;
        Node *right;
        Node(const T &v) : value(v), left(nullptr), right(nullptr) {}
    };

    Node *root;

    Node* insertRec(Node *node, const T &value) {
        if (node == nullptr) {
            return new Node(value); 
        }
        if (value < node->value) {
            node->left = insertRec(node->left, value);
        } else if (value > node->value) {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    void inOrderRec(Node *node, vector<T> &result) const {
        if (node == nullptr) return;
        inOrderRec(node->left, result);
        result.push_back(node->value);
        inOrderRec(node->right, result);
    }

    int heightRec(Node *node) const {
        if (node == nullptr) return -1;
        return 1 + max(heightRec(node->left), heightRec(node->right));
    }

    void destroyRec(Node *node) {
        if (node == nullptr) return;
        destroyRec(node->left);
        destroyRec(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree() { destroyRec(root); }

    void insert(const T &value) {
        root = insertRec(root, value);
    }

    vector<T> inOrder() const {
        vector<T> result;
        inOrderRec(root, result);
        return result;
    }

    int height() const {
        return heightRec(root);
    }

    bool empty() const {
        return root == nullptr;
    }
};

int main() {
    BinaryTree<int> tree;
    vector<int> valuesToInsert = { 50, 30, 70, 20, 40, 60, 80, 10, 25 };

    cout << "Inserting values: ";
    for (int v : valuesToInsert) cout << v << " ";
    cout << "\n\n";

    for (int v : valuesToInsert) {
        tree.insert(v);
    }

    cout << "In-order traversal (should be sorted): ";
    for (int v : tree.inOrder()) cout << v << " ";
    cout << "\n";

    cout << "Tree height: " << tree.height() << "\n";

    return 0;
}