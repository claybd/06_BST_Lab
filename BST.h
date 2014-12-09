/* This program was written by Ben Clay.  It may be used without the author's consent for non-profit puproses only. */

#include "SSet.h"
#include <iostream>

template <class Key, class T>
class Node {
public:
    Key k;
    T data;
    Node* left;
    Node* right;
    Node* parent;
    bool exists;
};

template <class Key, class T>
class BST : public SSet <Key,T> {
public:
    BST();
    ~BST();
    
    //Return the number of items currently in the SSet
    virtual unsigned long size();
    
    //Add a new item, x, with Key k.
    // If an item with Key k already exists, overwrite it
    virtual void add(Key k, T x);
    
    //Remove the item with Key k. If there is no such item, do nothing.
    virtual void remove(Key k);
    
    //Return the item with Key k.
    // If there is no such item, throw an exception.
    virtual T find(Key k);
    //Return true if there is an item with Key k in the table. If not,
    // return false
    virtual bool keyExists(Key k);
    
    //If there is a key in the set that is > k,
    // return the first such key. If not, return k
    virtual Key next(Key k);
    //If there is a key in the set that is < k,
    // return the first such key. If not, return k
    virtual Key prev(Key k);
    
private:
    Node<Key,T>* root;
    T* backingArray;
    
    virtual unsigned long size(Node<Key,T>* r);
    //These are the recursive versions of each of your methods.
    // You should return the address of the new root node, whether
    // or not the root node changes.
    virtual Node<Key,T>* add(Key k, T x, Node<Key,T>* r);
    virtual Node<Key,T>* remove(Key k, Node<Key,T>* r);
    
    //Find the item in the sub-tree rooted at r which has the smallest key
    virtual Node<Key,T>* min(Node<Key,T>* r);
    
    //Find the item in the sub-tree rooted at r which has the largest key
    virtual Node<Key,T>* max(Node<Key,T>* r);
    
    unsigned long arraySize;
    unsigned long numItems;
    
};

#define NULL 0
#include <string>

//***************************************************************************
template <class Key, class T>
BST<Key,T>::BST(){
    arraySize = 20;
    numItems = 0;
    root = new Node<Key,T>();
    root->exists = false;
    backingArray = new T[arraySize];
    
    for (int i = 0; i<20; i++)
        backingArray[i] = *new T;
}

//***************************************************************************
template <class Key, class T>
BST<Key,T>::~BST(){
    delete[] backingArray;
    backingArray = 0;
}

//***************************************************************************
//Return the number of items currently in the SSet
template <class Key, class T>
unsigned long BST<Key,T>::size(){
    return numItems;
}

//***************************************************************************
template <class Key, class T>
unsigned long BST<Key,T>::size(Node<Key,T>* r){
    //TODO
    return 0;
}

//***************************************************************************
//Add a new item, x, with Key k.
// If an item with Key k already exists, overwrite it
template <class Key, class T>
void BST<Key,T>::add(Key k, T x){
    if (keyExists(k))
        return;
    
    // Grow backingArray if needed.
    if (size() >= arraySize)
    {
        arraySize = arraySize*2;
        T* temp = new T[arraySize];
        
        for (int i = 0; i < arraySize/2; i++)
            temp[i] = backingArray[i];
        
        backingArray = temp;
    }
    
    // Create a root node if not already created.
    if (root->exists == false)
    {
        Node<Key,T> *n = new Node<Key,T>;
        n->k = k;
        n->data = x;
        n->exists = true;
        root = n;
        
        root->left = new Node<Key,T>();
        root->left->exists = false;
        root->left->parent = root;
        
        root->right = new Node<Key,T>();
        root->right->parent = root;
        root->right->exists = false;
        
        root->right->left = new Node<Key,T>();
        root->right->left->parent = root->right;
        root->right->left->exists = false;
        
        root->right->right = new Node<Key,T>();
        root->right->right->parent = root->right;
        root->right->right->exists = false;
        
        root->left->left = new Node<Key,T>();
        root->left->left->parent = root->left;
        root->left->left->exists = false;
        
        root->left->right = new Node<Key,T>();
        root->left->right->parent = root->left;
        root->left->right->exists = false;
        
        numItems++;
    }
    
    else
    {
        Node<Key,T> *holder;
        
        if (k == 0)
        {
            if (k == 0 && k > root->k && root->right->exists == false)
            {
                root->right->exists = true;
                root->right->data = x;
                
                holder = root->right;
            }
            
            else if (k == 0 && k < root->k && root->left->exists == false)
            {
                root->left->exists = true;
                root->left->data = x;
                
                holder = root->left;
            }
            
            holder->left = new Node<Key,T>();
            holder->left->parent = root->left;
            holder->left->exists = false;
            holder->right = new Node<Key,T>();
            holder->right->parent = root->left;
            holder->right->exists = false;
            
            numItems++;
        }
        
        else if (k > root->k)
        {
            if (root->right->exists == false)
            {
                root->right->k = k;
                root->right->data = x;
                root->right->exists = true;
            }
            else
                add(k, x, root->right);
            
            numItems++;
        }
        
        else if (k < root->k)
        {
            if (root->left->exists == false)
            {
                root->left->k = k;
                root->left->data = x;
                root->left->exists = true;
            }
            else
                add(k, x, root->left);
            
            numItems++;
        }
    }
}

//***************************************************************************
//Remove the item with Key k. If there is no such item, do nothing.
template <class Key, class T>
void BST<Key,T>::remove(Key k){
    if (!keyExists(k))
        return;
    
    Node<Key,T>* node = root;
    
    while (node->k != k)
    {
        if (k > node->k)
            node = node->right;
        else
            node = node->left;
    }
    
    // If the node being removed is a leaf...
    if (node->left->exists == false && node->right->exists == false)
    {
        node->exists = false;
        node->data = "";
        node->k = 0;
    }
    
    // If the node being removed has one branch/leaf...
    else if (node->left->exists == false && node->right->exists == true)
        node = node->right;
    else if (node->right->exists == false && node->left->exists == true)
        node = node->left;
    
    // If the node being removed has two branches/leaves...
    else if (node->left->exists == true && node->right->exists == true)
    {
        Node<Key,T> leftTraverse = *node->left;
        Node<Key,T> rightTraverse = *node->right;
        
        if (leftTraverse.k < node->right->k &&
            leftTraverse.left->exists == false &&
            leftTraverse.right->exists == false)
        {
            node = &leftTraverse;
        }
        else if (rightTraverse.k > node->right->k &&
                 rightTraverse.left->exists == false &&
                 rightTraverse.right->exists == false)
        {
            node = &rightTraverse;
        }
        else
        {
            while ((rightTraverse.right->exists == true || rightTraverse.left->exists == true) ||
                   (leftTraverse.right->exists == true && leftTraverse.left->exists == true))
            {
                if (rightTraverse.right->k > node->left->k &&
                    rightTraverse.right->k < node->right->k &&
                    rightTraverse.right->exists == true)
                {
                    rightTraverse = *rightTraverse.right;
                }
                else if (rightTraverse.left->k > node->left->k &&
                         rightTraverse.left->k < node->right->k &&
                         rightTraverse.left->exists == true)
                {
                    rightTraverse = *rightTraverse.left;
                }
                else if (leftTraverse.right->k > node->left->k &&
                         leftTraverse.right->k < node->right->k &&
                         leftTraverse.right->exists == true)
                {
                    leftTraverse = *rightTraverse.right;
                }
                else if (leftTraverse.left->k > node->left->k &&
                         leftTraverse.left->k < node->right->k &&
                         leftTraverse.left->exists == true)
                {
                    rightTraverse = *rightTraverse.left;
                }
                else
                    throw std::string("Something is wrong.");
            }
        }
        
    }
    else
        throw std::string("Something is wrong.");
    
}

//***************************************************************************
//Return the item with Key k.
// If there is no such item, throw an exception.
template <class Key, class T>
T BST<Key,T>::find(Key k){
    Node<Key,T>* holder = root;
    
    if (!keyExists(k))
        throw std::exception ();
    
    while (k != holder->k)
    {
        if (k > holder->k)
            holder = holder->right;
        else if (k < holder->k)
            holder = holder->left;
    }
    
    return holder->data;
}

//***************************************************************************
//Return true if there is an item with Key k in the table. If not,
// return false
template <class Key, class T>
bool BST<Key,T>::keyExists(Key k){
    Node<Key,T>* holder = root;
    if (root->exists == false)
        return false;
    
    while (holder->exists == true)
    {
        if (k > holder->k)
            holder = holder->right;
        else if (k < holder->k)
            holder = holder->left;
        else if (k == holder->k)
            return true;
    }
    
    return false;
}

//***************************************************************************
//If there is a key in the set that is > k,
// return the first such key. If not, return k
template <class Key, class T>
Key BST<Key,T>::next(Key k){
    Node<Key,T>* holder = root;
    
    while(holder->exists == true)
    {
        if (holder->k < k || holder->k == k)
            holder = holder->right;
        else if (holder->k > k)
        {
            if (holder->left->k > k && holder->left->exists == true)
                holder = holder->left;
            else
                return holder->k;
        }
    }
    
    return k;
}


//***************************************************************************
//If there is a key in the set that is < k,
// return the first such key. If not, return k
template <class Key, class T>
Key BST<Key,T>::prev(Key k)
{
    Node<Key,T>* holder = root;
    
    while(holder->exists == true)
    {
        if (holder->k > k || holder->k == k)
            holder = holder->left;
        else if (holder->k < k)
        {
            if (holder->right->k < k && holder->right->exists == true)
                holder = holder->right;
            else
                return holder->k;
        }
    }
    
    return k;
}


//***************************************************************************
template <class Key, class T>
Node<Key,T>* BST<Key,T>::add(Key k, T x, Node<Key,T>* r){
    Node<Key,T> holder = *r;
    
    if (k > holder.k && holder.right->exists == false)
    {
        holder.right->k = k;
        holder.right->parent = &holder;
        holder.right->data = x;
        holder.right->exists = true;
        
        holder.right->right = new Node<Key,T>;
        holder.right->left = new Node<Key,T>;
        holder.right->right->exists = false;
        holder.right->right->parent = holder.right;
        holder.right->left->exists = false;
        holder.right->left->parent = holder.right;
    }
    
    else if (k < holder.k && holder.left->exists == false)
    {
        holder.left->k = k;
        holder.left->parent = &holder;
        holder.left->data = x;
        holder.left->exists = true;
        
        holder.left->right = new Node<Key,T>;
        holder.left->left = new Node<Key,T>;
        holder.left->right->exists = false;
        holder.left->right->parent = holder.left;
        holder.left->left->exists = false;
        holder.left->left->parent = holder.left;
    }
    
    else if (k == 0 && holder.exists == false)
    {
        holder.data = x;
        holder.exists = true;
        
        holder.right = new Node<Key,T>;
        holder.left = new Node<Key,T>;
        holder.right->exists = false;
        holder.left->exists = false;
        holder.left->parent = &holder;
        holder.right->parent = &holder;
    }
    
    else if (k > holder.k && holder.right->exists == true)
        add(k, x, holder.right);
    
    else if (k < holder.k && holder.left->exists == true)
        add(k, x, holder.left);
    
    return root;
}

//***************************************************************************
template <class Key, class T>
Node<Key,T>* BST<Key,T>::remove(Key k, Node<Key,T>* r){
    //TODO
    return NULL;
}

//***************************************************************************
template <class Key, class T>
Node<Key,T>* BST<Key,T>::max(Node<Key,T>* r){
    //TODO
    return NULL;
}

//***************************************************************************
template <class Key, class T>
Node<Key,T>* BST<Key,T>::min(Node<Key,T>* r){
    //TODO
    return NULL;
}
