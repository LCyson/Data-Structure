#include <iostream>
#include <exception>
#include <cstdlib>
#include <string>
#include "bst.h"

template <class KeyType, class ValueType>
class SplayTree : public BinarySearchTree<KeyType, ValueType>
{
private:
  void Splay (Node<KeyType, ValueType>* node);
  void rightRotate_Zig ( Node<KeyType, ValueType>* node );
  void leftRotate_Zig ( Node<KeyType, ValueType>* node );
  void rightRotate_Zag ( Node<KeyType, ValueType>* node );
  void leftRotate_Zag ( Node<KeyType, ValueType>* node );
  void rightRotate_ZigZig ( Node<KeyType, ValueType>* node );
  void leftRotate_ZigZig ( Node<KeyType, ValueType>* node );
  Node<KeyType, ValueType>* insertInTree(Node<KeyType, ValueType>* node, Node<KeyType, ValueType>* Parent_node, const std::pair<const KeyType, ValueType>& new_item);


public:
  void insert (const std::pair<const KeyType, ValueType>& new_item);
  typename BinarySearchTree<KeyType, ValueType>::iterator& find ( const KeyType& object );
};


template <class KeyType, class ValueType>
typename BinarySearchTree<KeyType, ValueType>::iterator& SplayTree<KeyType, ValueType>::find ( const KeyType& object )
{
  Node<KeyType, ValueType>* target = this->internalFind( object );
  if ( target && target != this->root ){
    Splay( target );    
  } 
  typename BinarySearchTree<KeyType, ValueType>::iterator* it = new typename BinarySearchTree<KeyType, ValueType>::iterator(target);
  // if ( target == NULL) std::cout<< "DEBUG" <<std::endl;
  return *it;
}


template <class KeyType, class ValueType>
void SplayTree<KeyType, ValueType>::insert (const std::pair<const KeyType, ValueType>& new_item)
{
  this->root = insertInTree(this->root, NULL, new_item );
  Node<KeyType, ValueType>* fix_node = this->internalFind( new_item.first );
  if ( fix_node == this->root ) return;
  Splay( fix_node );
}

template <class KeyType, class ValueType>
void SplayTree<KeyType, ValueType>::Splay ( Node<KeyType, ValueType>* node )
{
  Node<KeyType, ValueType>* parent = node->getParent();

  if ( parent == this->root && parent->getLeft() == node )
  { rightRotate_Zig( parent ); }
  else if ( parent == this->root && parent->getRight() == node )
  { leftRotate_Zig( parent ); }
  else if ( parent->getLeft() == node && parent->getParent()->getLeft() == parent ) 
  { rightRotate_ZigZig( parent ); }
  else if ( parent->getRight() == node && parent->getParent()->getRight() == parent ) 
  { leftRotate_ZigZig( parent ); }
  else if ( parent->getRight() == node && parent->getParent()->getLeft() == parent ) 
  { leftRotate_Zag( parent ); }
  else if ( parent->getLeft() == node && parent->getParent()->getRight() == parent ) 
  { rightRotate_Zag( parent ); }

  if ( node != this->root && node != NULL ) {
    Splay( node );
  }
}


template <class KeyType, class ValueType>
void SplayTree<KeyType, ValueType>::rightRotate_Zig ( Node<KeyType, ValueType>* node )
{
  Node<KeyType, ValueType>* X = node->getLeft();
  Node<KeyType, ValueType>* R = node;

  R->setLeft( X->getRight() );
  if ( X->getRight() ) X->getRight()->setParent( R );

  if ( R == this->root ) this->root = X;
  X->setParent( R->getParent() );
  X->setRight( R );
  R->setParent( X );
}


template <class KeyType, class ValueType>
void SplayTree<KeyType, ValueType>::leftRotate_Zig ( Node<KeyType, ValueType>* node )
{
  Node<KeyType, ValueType>* X = node->getRight();
  Node<KeyType, ValueType>* R = node;

  R->setRight( X->getLeft() );
  if ( X->getLeft() ) X->getLeft()->setParent( R );

  if ( R == this->root ) this->root = X;
  X->setParent( R->getParent() );
  X->setLeft( R );
  R->setParent( X );
}

template <class KeyType, class ValueType>
void SplayTree<KeyType, ValueType>::leftRotate_Zag ( Node<KeyType, ValueType>* node )
{
  Node<KeyType, ValueType>* X = node->getRight();
  Node<KeyType, ValueType>* P = node;
  Node<KeyType, ValueType>* G = P->getParent();

  P->setRight( X->getLeft() );
  if ( X->getLeft() ) X->getLeft()->setParent( P );
  X->setLeft( P );
  P->setParent( X );
  G->setLeft( X );
  X->setParent( G );

  G->setLeft( X->getRight() );
  if ( X->getRight() ) X->getRight()->setParent( G );

  if ( G == this->root ){
    this->root = X;
  }
  else if( G->getParent()->getLeft() == G ){
    G->getParent()->setLeft( X );
  }
  else{
    G->getParent()->setRight( X );
  }
  X->setParent( G->getParent() );
  G->setParent( X );
  X->setRight( G );
}

template <class KeyType, class ValueType>
void SplayTree<KeyType, ValueType>::rightRotate_Zag ( Node<KeyType, ValueType>* node )
{
  Node<KeyType, ValueType>* X = node->getLeft();
  Node<KeyType, ValueType>* P = node;
  Node<KeyType, ValueType>* G = P->getParent();

  P->setLeft( X->getRight() );
  if ( X->getRight() ) X->getRight()->setParent( P );
  X->setRight( P );
  P->setParent( X );
  G->setRight( X );
  X->setParent( G );

  G->setRight( X->getLeft() );
  if ( X->getLeft() ) X->getLeft()->setParent( G );

  if ( G == this->root ){
    this->root = X;
  }
  else if( G->getParent()->getLeft() == G ){
    G->getParent()->setLeft( X );
  }
  else{
    G->getParent()->setRight( X );
  }
  X->setParent( G->getParent() );
  G->setParent( X );
  X->setLeft( G );
}

template <class KeyType, class ValueType>
void SplayTree<KeyType, ValueType>::rightRotate_ZigZig ( Node<KeyType, ValueType>* node )
{
  Node<KeyType, ValueType>* X = node->getLeft();
  Node<KeyType, ValueType>* P = node;
  Node<KeyType, ValueType>* G = P->getParent();

  G->setLeft( P->getRight() );
  if ( P->getRight() ) P->getRight()->setParent( G );
  P->setLeft( X->getRight() );
  if ( X->getRight() ) X->getRight()->setParent( P );
  X->setRight( P );
  P->setParent( X );

  if ( G == this->root ){
    this->root = X;
  }
  else if ( G->getParent()->getLeft() == G ){
    G->getParent()->setLeft( X );
  } 
  else{
    G->getParent()->setRight( X );
  }
  X->setParent( G->getParent() );
  P->setRight( G );
  G->setParent( P );
}

template <class KeyType, class ValueType>
void SplayTree<KeyType, ValueType>::leftRotate_ZigZig ( Node<KeyType, ValueType>* node )
{
  Node<KeyType, ValueType>* G = node->getRight();
  Node<KeyType, ValueType>* P = node;
  Node<KeyType, ValueType>* X = P->getParent();

  X->setRight( P->getLeft() );
  if ( P->getLeft() ) P->getLeft()->setParent( X );
  P->setRight( G->getLeft() );
  if ( G->getLeft() ) G->getLeft()->setParent( P );
  G->setLeft( P );
  P->setParent( G );

  if ( X == this->root ){
    this->root = G;
  }
  else if ( X->getParent()->getLeft() == X ){
    X->getParent()->setLeft( G );
  } 
  else{
    X->getParent()->setRight( G );
  }
  G->setParent( X->getParent() );
  P->setLeft( X );
  X->setParent( P );
}

template <class KeyType, class ValueType>
Node<KeyType, ValueType>* SplayTree<KeyType, ValueType>::insertInTree(Node<KeyType, ValueType>* node,
  Node<KeyType, ValueType>* Parent_node, const std::pair<const KeyType, ValueType>& new_item)
{
  if(node == NULL) {
    Node<KeyType, ValueType>* temp = new Node<KeyType, ValueType>( new_item.first, new_item.second, Parent_node);
    return temp;
  }
  if( new_item.first < node->getKey() ) { node->setLeft( insertInTree(node->getLeft(), node, new_item) ); }
  else if( new_item.first > node->getKey() ) node->setRight( insertInTree(node->getRight(), node, new_item) );
  else if( new_item.first == node->getKey() ){
    node->setValue( new_item.second );
  }

  return node;
}