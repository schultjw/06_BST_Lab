//DO NOT CHANGE THIS FILE
//Author: Bo Brinkman
//Date: 2013/10/01

#include "SSet.h"

template <class Key, class T>
class Node {
public:
  Key k;
  T data;
  Node* left;
  Node* right;
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

  virtual unsigned long size(Node<Key,T>* r);
  //These are the recursive versions of each of your methods.
  // You should return the address of the new root node, whether
  // or not the root node changes.
  virtual Node<Key,T>* add(Key k, T x, Node<Key,T>* r);
  virtual Node<Key,T>* remove(Key k, Node<Key,T>* r);

  //This one returns the address of the found node, NULL
  // if not found
  virtual Node<Key,T>* find(Key k, Node<Key,T>* r);

  //Find the item in the sub-tree rooted at r which has the smallest key
  virtual Node<Key,T>* min(Node<Key,T>* r);

  //Find the item in the sub-tree rooted at r which has the largest key
  virtual Node<Key,T>* max(Node<Key,T>* r);

  //Find the next/prev node, and return its address
  virtual Node<Key,T>* next(Key k, Node<Key,T>* r);
  virtual Node<Key,T>* prev(Key k, Node<Key,T>* r);

};

#define NULL 0
#include <string>

template <class Key, class T>
BST<Key,T>::BST(){
  root = NULL;
}

template <class Key, class T>
BST<Key,T>::~BST(){
	while(root != NULL){
		root = remove(root->k, root);
	}
	root = NULL;
}
  
//Return the number of items currently in the SSet
template <class Key, class T>
unsigned long BST<Key,T>::size(){
    return size(root); //using the other size(Node) method, return size of whole tree.
}

template <class Key, class T>
unsigned long BST<Key,T>::size(Node<Key,T>* r){

	if(r == NULL) //if this node is NULL, there is also nothing lower than it
	{
		return 0;
	}

    return 1 + size(r->right) + size(r->left); //return 1 plus the size of both subtrees
}

//Add a new item, x, with Key k.
// If an item with Key k already exists, overwrite it
template <class Key, class T>
void BST<Key,T>::add(Key k, T x){
	if(root = NULL)
	{
		root = add(k, x, root);
	}

}

//Remove the item with Key k. If there is no such item, do nothing.
template <class Key, class T>
void BST<Key,T>::remove(Key k){
  root = remove(k, root);
}

//Return the item with Key k. 
// If there is no such item, throw an exception.
template <class Key, class T>
T BST<Key,T>::find(Key k){
	Node<Key, T>* node = find(k, root);

	if(node = NULL)
		throw new std::string("Error: No such item to find");

	return node->data;
}

//Return true if there is an item with Key k in the table. If not,
// return false
template <class Key, class T>
bool BST<Key,T>::keyExists(Key k){
	return find(k, root) != NULL;
}

//If there is a key in the set that is > k,
// return the first such key. If not, return k
template <class Key, class T>
Key BST<Key,T>::next(Key k){
	Node<Key, T>* n = next(k, root);
	if(n == NULL)
		return k;
	return n->k;
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::next(Key k, Node<Key,T>* r){
	if(r == NULL){
		return NULL;
	}else if(r->k < k) //search right tree
		return next(k, r->right);
	else if(r->k > k){ //search left tree		
		if(next(k, r->left) != NULL)
			return r;
		else
			return next(k, r->left);
	}else { //r->k == k
		if(r->right != NULL)
			return next(k, r->right);
		else
			return NULL;
	}
}

//If there is a key in the set that is < k,
// return the first such key. If not, return k
template <class Key, class T>
Key BST<Key,T>::prev(Key k){
	Node<Key, T>* n = prev(k, root);
	if(n == NULL)
		return k;
	return n->k;
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::prev(Key k, Node<Key,T>* r){
	if(r == NULL)
		return NULL;
	else if(r->k < k){ // right tree
		if(prev(k, r->right) == NULL)
			return r;
		else
			return prev(k, r->right);
	}
	else if(r->k > k){ // left tree
		return prev(k, r->left);
	}else{//r->k == k
		if(r->left != NULL)
			return prev(k, r->left);
		else return NULL;
	}
}


template <class Key, class T>
Node<Key,T>* BST<Key,T>::add(Key k, T x, Node<Key,T>* r){
  if( r == NULL )
  {
	  r = new Node<Key, T>();
	  r->k = k;
	  r->data = x;
	  r->left = NULL;
	  r->right = NULL;
  }else if(r->k == k)
  {
	  r->data = x;
  } else if( r->k > k) 
  {
	  r->left = add(k, x, r->left);
  } else
  {
	  r->right = add(k, x, r->right);
  }
  return r;
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::remove(Key k, Node<Key,T>* r){
	if(r == NULL)
	{
		return NULL;
	}

	Node<Key, T>* n; //replacement node for the one to be deleted. Chosen from among the children of the target node.

	if(r->k == k) //found node
	{

		if(r->left == NULL && r->right == NULL) //no children, done.
		{
			delete r;
			r = NULL;
			return NULL;
		}
		
		//find replacement node
		if(r->left != NULL)
		{
			n = max(r->left);
		} else {
			n = min(r->right);
		}

		//store the important info about the replacement node
		Node<Key, T> temp;
		temp.k = n->k;
		temp.data= n->data;

		//then delete the replacement
		remove(n->k, r);

		//now change the current node to the replacement
		r->k = temp.k;
		r->data = temp.data;
		
		return r;
	}

	if(r->k < k) //check to the right
	{
		n = remove(k, r->right);
		r->right = n;
	} else { //check to the left
		n = remove(k, r->left);
		r->left = n;
	}
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::find(Key k, Node<Key,T>* r){
	if(r == NULL)
		return NULL;
	
	if(r->k == k) //found it
	{
		return r;
	}
	else if(r->k < k) //k is on right tree
	{
		return find(k, r->right);
	}
	else if(r->k > k) //k is on left tree
	{
		return find(k, r->left);
	}
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::max(Node<Key,T>* r){
	if(r == NULL){
		throw std::string("Error: r is null");
	}else if(r->right == NULL){
		return r;
	}else 
		return max(r->right);
	return NULL;
}

template <class Key, class T>
Node<Key,T>* BST<Key,T>::min(Node<Key,T>* r){
	if(r == NULL)
		throw std::string("Error: r is null");
	else if(r->left == NULL)
		return r;
	else
		return min(r->left);
	return NULL;
}