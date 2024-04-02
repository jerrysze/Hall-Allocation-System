#include <climits>
#include "HashTable.h"
#include "Student.h"

using namespace std;

// TODO: Task 4.1
HashTable::HashTable(int size): size(size) {
    table = new LinkedList[size];
    for(int i = 0; i < size; i++){
        table[i] = LinkedList();
    }
}

// TODO: Task 4.2
HashTable::~HashTable() {
    delete[] table;
}

// TODO: Task 4.3
int HashTable::hash(int sid) {
    int hashValue = 0;
    long long product = static_cast<long long>(sid) * sid;
    hashValue = product % INT_MAX;
    return hashValue;
}

// TODO: Task 4.4
void HashTable::add(Student* student) {
    table[hash(student->getSid()) % size].add(student);
}

// TODO: Task 4.5
Student* HashTable::get(int sid) const {
    LLNode* curr = table[hash(sid) % size].getHead();
    while (curr != nullptr) {
        if (*(curr->getData()) == sid){
            return curr->getData();
        }
        curr = curr->getNext();
    }
    return nullptr;
}

// TODO: Task 4.6
void HashTable::remove(const Student* student) {
    table[hash(student->getSid()) % size].remove(student);
}

// GIVEN: DO NOT EDIT
void HashTable::printTable() const {
    for (int i = 0; i < size; i++) {
        cout << "table[" << i << "] = " << table[i] << endl;
    }
}