#ifndef __BST_IMPLEMENTATION_H__
#define __BST_IMPLEMENTATION_H__

#include "BST.h"
#include "BSTNode.h"
#include "LinkedList.h"

// TODO: Task 3.1
template <typename K>
const BST<K>* BST<K>::find(K key) const {
    if(isEmpty()){
        return nullptr;
    }
    
    if(key == root->key){
        return this;
    }
    else if(key < root->key){
        return root->left.find(key);
    }
    else{
        return root->right.find(key);
    }
}

// TODO: Task 3.2
template <typename K>
bool BST<K>::contains(K key, const Student* student) const {
    const BST<K>* node = find(key);
    if(node == nullptr){
        return false;  
    }
    return node->root->value.contains(student);
}

// TODO: Task 3.3
template <typename K>
int BST<K>::size() const{
    if(isEmpty()){
        return 0;  
    }
    return (root->value.getSize() + root->left.size() + root->right.size());
}

// TODO: Task 3.4
template <typename K>
void BST<K>::add(K key, Student* student){
    if(isEmpty()){
        root = new BSTNode<K>(key, student); 
        return;
    }
    if(key == root->key){
        root->value.add(student); 
    } 
    else if(key < root->key){
        root->left.add(key, student); 
    } 
    else{
        root->right.add(key, student);
    }
}

// TODO: Task 3.5
template <typename K>
LinkedList BST<K>::getAllValues() const {
    LinkedList result;
    if(root){
        result.add(root->right.getAllValues());   
        result.add(root->value);
        result.add(root->left.getAllValues());
    }
    
    return result;
}


// TODO: Task 3.6
template <typename K>
const BST<K>* BST<K>::kthLargest(int k) const {

    if(root == nullptr || k > size()){
        return nullptr;
    }
    int rSize = root->right.size();
    if(rSize + 1 == k){
        return this;
    }
    else if(k <= rSize){
        return root->right.kthLargest(k);
    }
    else{
        return root->left.kthLargest(k-rSize-1);
    }

}


// TODO: Task 3.7
template <typename K>
void BST<K>::remove(K key) {
    if(isEmpty())
        return;
    if(key < root->key){
        root->left.remove(key);
    }
    else if(key > root->key){
        root->right.remove(key);
    }
    else if(root->left.root && root->right.root){
        root->key = root->left.kthLargest(1)->getKey();
        root->left.remove(root->key);
    }
    else{
        BSTNode<K>* deleting_node = root;
        root = (root->right.isEmpty())? root->left.root : root->right.root;

        deleting_node->right.root = deleting_node->left.root = nullptr;
        delete deleting_node;
    }
}

// TODO: Task 3.8
template <typename K>
void BST<K>::remove(K key, const Student* student) {
    const BST<K>* temp = find(key);
    if(temp == nullptr){
        return;
    }
    if(temp->getValue().getSize() == 1){
        remove(key);
    }
    else if(temp){
        temp->root->value.remove(student);
    }
}

#endif
