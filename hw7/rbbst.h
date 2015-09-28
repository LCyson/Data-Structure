/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include <string>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
private:
  void fixTree (RedBlackNode<KeyType, ValueType>* node);
  RedBlackNode<KeyType, ValueType>* insertInTree(RedBlackNode<KeyType, ValueType>* node,
        RedBlackNode<KeyType, ValueType>* Parent_node, const std::pair<const KeyType, ValueType>& new_item);

public:
  void printRoot (RedBlackNode<KeyType, ValueType>* r) const;
  void print () const;
  void insert (const std::pair<const KeyType, ValueType>& new_item);
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree
     (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */   
};


template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::insert (const std::pair<const KeyType, ValueType>& new_item)
{
  this->root = insertInTree( (RedBlackNode<KeyType, ValueType>*)(this->root), NULL, new_item );
  RedBlackNode<KeyType, ValueType>* fix_node = (RedBlackNode<KeyType, ValueType>*)( this->internalFind( new_item.first ) );
  fixTree( fix_node );
}

template <class KeyType, class ValueType>
void RedBlackTree<KeyType, ValueType>::fixTree (RedBlackNode<KeyType, ValueType>* node)
{
  if ( node->getParent() == NULL )
  {
    node->setColor(black);
    return;
  }
  if ( (node->getParent())->getParent() == NULL || (node->getParent())->getColor() == black )
  {
    return;
  }

  char rotate = 'R';
  char NeedRotate = 'N';
  RedBlackNode<KeyType, ValueType>* parent = node->getParent();
  RedBlackNode<KeyType, ValueType>* parentLeft = parent->getLeft();
  RedBlackNode<KeyType, ValueType>* parentRight = parent->getRight();
  RedBlackNode<KeyType, ValueType>* graParent = parent->getParent();
  RedBlackNode<KeyType, ValueType>*  Uncle = graParent->getRight();
  if ( Uncle == parent )
  {
    // std::cout<< node->getKey() << " "<< std::endl;
    Uncle = graParent->getLeft();
    rotate = 'L';
  }
  if ( parent->getRight() == node && graParent->getLeft() == parent )
  {
    NeedRotate = 'L';
  }
  if ( parent->getLeft() == node && graParent->getRight() == parent )
  {
    NeedRotate = 'R';
  }


  if ( Uncle != NULL && Uncle->getColor() == red )
  {   
    // std::cout<< node->getKey() << " "<< parent->getKey() << " "<< Uncle->getKey()<< std::endl;
    parent->setColor(black);
    Uncle->setColor(black);
    graParent->setColor(red);
    node = graParent;
    fixTree( node );
  }
  else if ( Uncle == NULL || Uncle->getColor() == black )
  {

  if ( NeedRotate != 'N' && parent->getColor() == red )
  {
    // std::cout<< node->getKey() << " "<< std::endl;
    if ( NeedRotate == 'L' )
    {
      graParent->setLeft(node);
      node->setParent(graParent);
      parent->setRight(NULL);
      parent->setParent(node);
      node->setLeft(parent);
  std::cout<< parent->getKey()<< std::endl;
      fixTree( parent );
      return;
    }
    if ( NeedRotate == 'R' )
    {
      graParent->setRight(node);
      node->setParent(graParent);
      parent->setLeft(NULL);
      parent->setParent(node);
      node->setRight(parent);
      fixTree( parent );
      return;
    }    
  }

  // std::cout<< node->getKey()<< std::endl;
    RedBlackNode<KeyType, ValueType>* rootParent = graParent->getParent();

    if ( rootParent == NULL )
    {
  // std::cout<< node->getKey()<< std::endl;
      this->root = parent;
      parent->setParent( NULL );
    }
    else{
      if ( rootParent->getRight() == graParent )
      {
        rootParent->setRight( parent );      
      }
      else{
        rootParent->setLeft( parent );
      }
      parent->setParent(rootParent);
    }


    if ( rotate == 'R' )
     {
       if ( parentRight != NULL )
       {
        graParent->setLeft(parentRight);
        parentRight->setParent(graParent);
       }
       else{
        graParent->setLeft(NULL);
       }
       graParent->setParent(parent);
       parent->setRight(graParent);
       parent->setColor(black);
       graParent->setColor(red);
     }
    if ( rotate == 'L' )
     {
       if ( parentLeft != NULL )
       {
        graParent->setRight(parentLeft);
        parentLeft->setParent(graParent);
       }
       else{
        graParent->setRight(NULL);
      }
        graParent->setParent(parent);
        parent->setLeft(graParent);
        parent->setColor(black);
        graParent->setColor(red);
     }      
  }
  
}

template <class KeyType, class ValueType>
RedBlackNode<KeyType, ValueType>* RedBlackTree<KeyType, ValueType>::insertInTree(RedBlackNode<KeyType, ValueType>* node,
  RedBlackNode<KeyType, ValueType>* Parent_node, const std::pair<const KeyType, ValueType>& new_item)
{
  if(node == NULL) {
    RedBlackNode<KeyType, ValueType>* temp = new RedBlackNode<KeyType, ValueType>( new_item.first, new_item.second, Parent_node);
    return temp;
  }
  if( new_item.first < node->getKey() ) { node->setLeft( insertInTree(node->getLeft(), node, new_item) ); }
  else if( new_item.first > node->getKey() ) node->setRight( insertInTree(node->getRight(), node, new_item) );
  else if( new_item.first == node->getKey() ){
    node->setValue( new_item.second );
  }

  return node;
}

template <class KeyType, class ValueType>
  void RedBlackTree<KeyType, ValueType>::printRoot (RedBlackNode<KeyType, ValueType> *r) const
  {
    if (r != NULL)
      {
  std::cout << "[";
  printRoot (r->getLeft());
  std::cout << " (" << r->getKey() << ", " << r->getColor() << ") ";
  printRoot (r->getRight());
  std::cout << "]";
      }
  }

template <class KeyType, class ValueType>
  void RedBlackTree<KeyType, ValueType>::print () const
  { 
    printRoot ( (RedBlackNode<KeyType, ValueType>*)this->root);
    std::cout << "\n";
  }