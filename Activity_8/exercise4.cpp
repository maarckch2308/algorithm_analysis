
#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    static const int TABLE_SIZE = 11;
    int table[TABLE_SIZE];
    bool occupied[TABLE_SIZE];

    int hashFunction(int key) const {
        int index = key % TABLE_SIZE;

        // Handle negative keys
        if (index < 0) {
            index += TABLE_SIZE;
        }

        return index;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = 0;
            occupied[i] = false;
        }
    }

    bool insert(int key) {
        int index = hashFunction(key);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int position = (index + i) % TABLE_SIZE;

            if (occupied[position]) {
                if (table[position] == key) {
                    cout << "Key " << key
                         << " already exists.\n";
                    return false;
                }
            } else {
                table[position] = key;
                occupied[position] = true;

                cout << "Key " << key
                     << " inserted at index "
                     << position << ".\n";
                return true;
            }
        }

        cout << "Hash table is full. Cannot insert "
             << key << ".\n";
        return false;
    }

    bool search(int key) const {
        int index = hashFunction(key);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int position = (index + i) % TABLE_SIZE;

            if (!occupied[position]) {
                return false;
            }

            if (table[position] == key) {
                return true;
            }
        }

        return false;
    }

    void display() const {
        cout << "\nHash Table:\n";

        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "] ";

            if (occupied[i]) {
                cout << table[i];
            } else {
                cout << "EMPTY";
            }

            cout << "\n";
        }
    }
};

int main() {
    HashTable ht;
    int option, key;

    do {
        cout << "\n--- HASH TABLE MENU ---\n";
        cout << "1. Insert key\n";
        cout << "2. Search key\n";
        cout << "3. Display table\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";

        if (!(cin >> option)) {
            cout << "Invalid input.\n";
            return 1;
        }

        switch (option) {
        case 1:
            cout << "Enter key to insert: ";
            if (!(cin >> key)) {
                cout << "Invalid key.\n";
                return 1;
            }
            ht.insert(key);
            break;

        case 2:
            cout << "Enter key to search: ";
            if (!(cin >> key)) {
                cout << "Invalid key.\n";
                return 1;
            }

            if (ht.search(key)) {
                cout << "Key " << key << " found.\n";
            } else {
                cout << "Key " << key << " not found.\n";
            }
            break;

        case 3:
            ht.display();
            break;

        case 0:
            cout << "Program finished.\n";
            break;

        default:
            cout << "Invalid option.\n";
        }

    } while (option != 0);

    return 0;
}
