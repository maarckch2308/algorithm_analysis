
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>

using namespace std;

struct Node {
    char symbol;
    double frequency;
    Node* left;
    Node* right;

    Node(char s, double f)
        : symbol(s), frequency(f), left(nullptr), right(nullptr) {}

    Node(Node* l, Node* r)
        : symbol('\0'),
          frequency(l->frequency + r->frequency),
          left(l), right(r) {}
};

struct Compare {
    bool operator()(const Node* a, const Node* b) const {
        if (a->frequency != b->frequency) {
            return a->frequency > b->frequency;
        }

        return a->symbol > b->symbol;
    }
};

void generateCodes(Node* root,
                   const string& prefix,
                   unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    // A leaf represents one symbol.
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->symbol] = prefix.empty() ? "0" : prefix;
        return;
    }

    generateCodes(root->left, prefix + "0", codes);
    generateCodes(root->right, prefix + "1", codes);
}

Node* buildHuffmanTree(
    const vector<pair<char, double>>& frequencies) {

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& entry : frequencies) {
        pq.push(new Node(entry.first, entry.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        pq.push(new Node(left, right));
    }

    return pq.empty() ? nullptr : pq.top();
}

string encode(const string& text,
              const unordered_map<char, string>& codes) {
    string encoded;

    for (char symbol : text) {
        auto it = codes.find(symbol);

        if (it == codes.end()) {
            return "ERROR: symbol not found in Huffman table";
        }

        encoded += it->second;
    }

    return encoded;
}

string decode(const string& bits, Node* root) {
    if (root == nullptr) {
        return "ERROR: empty Huffman tree";
    }

    string decoded;
    Node* current = root;

    for (char bit : bits) {
        if (bit != '0' && bit != '1') {
            return "ERROR: input must contain only 0 and 1";
        }

        current = (bit == '0') ? current->left : current->right;

        if (current == nullptr) {
            return "ERROR: invalid bit sequence";
        }

        // When a leaf is reached, output its symbol.
        if (current->left == nullptr && current->right == nullptr) {
            decoded += current->symbol;
            current = root;
        }
    }

    if (current != root) {
        return "ERROR: incomplete Huffman code at the end";
    }

    return decoded;
}

void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Frequencies given in Exercise 5.1.
    vector<pair<char, double>> frequencies = {
        {'A', 0.40},
        {'B', 0.10},
        {'C', 0.20},
        {'D', 0.15},
        {'_', 0.15}
    };

    string originalText = "ABACABAD";
    string bitsToDecode = "100010111001010";

    Node* root = buildHuffmanTree(frequencies);

    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "====================================\n";
    cout << "          HUFFMAN CODING\n";
    cout << "====================================\n";

    cout << "\n5.1 Huffman code table\n";
    cout << left
         << setw(12) << "Symbol"
         << setw(15) << "Frequency"
         << "Code\n";

    cout << "------------------------------------\n";

    // Print in the order given in the assignment.
    for (const auto& entry : frequencies) {
        cout << left
             << setw(12) << entry.first
             << setw(15) << fixed << setprecision(2)
             << entry.second
             << codes.at(entry.first) << '\n';
    }

    cout << "\n5.2 Encoding\n";
    cout << "Original text: " << originalText << '\n';

    string encoded = encode(originalText, codes);

    cout << "Encoded text:  " << encoded << '\n';
    cout << "Encoded length: " << encoded.size() << " bits\n";

    cout << "\n5.3 Decoding\n";
    cout << "Input bits:    " << bitsToDecode << '\n';

    string decoded = decode(bitsToDecode, root);
    cout << "Decoded text:  " << decoded << '\n';

    deleteTree(root);

    return 0;
}
