#include "HallAllocationSystem.h"
#include "BST.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Student.h"

// TODO: Task 5.1
HallAllocationSystem::HallAllocationSystem(int totalHallAvailable): totalHallAvailable(totalHallAvailable) {
    studentTable = new HashTable(193);
    studentQueue = new BST<int>();
}

// TODO: Task 5.2
HallAllocationSystem::~HallAllocationSystem() {
    delete studentTable;
    delete studentQueue;
}

// TODO: Task 5.3
void HallAllocationSystem::allocateHall() {
    if(!studentPendingList.isEmpty()){
        return;
    }
    LinkedList temp;
    while(totalHallAvailable > 0 && !studentQueue->isEmpty()){
        const BST<int>* largest = studentQueue->kthLargest(1);
        temp.add(largest->getValue());
        LLNode* curr = temp.getHead();
        while (curr != nullptr) {
            curr->getData()->setStatus(PENDING_ACTION);
            curr = curr->getNext();
        }
        totalHallAvailable -= (largest->getValue().getSize());
        studentQueue->remove(largest->getKey());
    }

    if(totalHallAvailable < 0){
        totalHallAvailable = 0;
    }
    studentPendingList.add(temp);
}

// TODO: Task 5.4
void HallAllocationSystem::addStudent(Student* student) {
    if (student->getStatus() != QUEUEING) {
        return;
    }
    studentTable->add(student);
    studentQueue->add(student->getTotalHallPoints(), student);
}

// TODO: Task 5.5
void HallAllocationSystem::removeStudent(const Student* student) {
    if(studentTable->get(student->getSid()) == nullptr){
        return;
    }
    studentTable->remove(student);
    studentQueue->remove(student->getTotalHallPoints(), student);
    studentPendingList.remove(student);
}

// TODO: Task 5.6
bool HallAllocationSystem::predict(const Student* student) const {
    if(studentQueue->contains(student->getTotalHallPoints(), student) == false || totalHallAvailable <= 0){
        return false;
    }

    int largest = studentQueue->kthLargest(totalHallAvailable)->getKey();

    if(student->getTotalHallPoints() >= largest){
        return true;
    }
    return false;
}

// TODO: Task 5.7
void HallAllocationSystem::acceptOffer(Student* student) {
    if(!studentPendingList.contains(student)){
        return;
    }
    studentPendingList.remove(student);
    student->setStatus(ACCEPTED);
}

// TODO: Task 5.8
void HallAllocationSystem::rejectOffer(Student* student) {
    if(!studentPendingList.contains(student)){
        return;
    }
    studentPendingList.remove(student);
    student->setStatus(REJECTED);
    totalHallAvailable++;
}

// TODO: Task 5.9
void HallAllocationSystem::acceptAllOffers() {
    LLNode* curr = studentPendingList.getHead();

    while (curr != nullptr) {
        Student* student = curr->getData();
        acceptOffer(student);
        curr = studentPendingList.getHead();
    }
}

// TODO: Task 5.10
void HallAllocationSystem::rejectAllOffers() {
    LLNode* curr = studentPendingList.getHead();

    while (curr != nullptr) {
        Student* student = curr->getData();
        rejectOffer(student);
        curr = studentPendingList.getHead();
    }
}