#include <iostream>
#include "LinkedList.h"
#include "Student.h"

// TODO: Task 2.2
LinkedList::LinkedList(const LinkedList& ll) : head(nullptr), tail(nullptr), size(0) {  
    LLNode* curr = ll.head;
    while (curr != nullptr) {
        add((curr->getData()));
        curr = curr->getNext();
    }
    
}

// TODO: Task 2.1
bool LinkedList::contains(const Student* data) const {
    LLNode* curr = head;
    while (curr != nullptr) {
        if (*(curr->getData()) == data->getSid()){
            return true;
        }
        curr = curr->getNext();
    }
    return false;
}

// TODO: Task 2.3
LinkedList& LinkedList::operator=(const LinkedList& ll) {
    if (this == &ll) {  
        return *this;
    }
    clear();  
    LLNode* curr = ll.head;
    while (curr != nullptr) {
        add(curr->getData());
        curr = curr->getNext();
    }
    return *this;
}
