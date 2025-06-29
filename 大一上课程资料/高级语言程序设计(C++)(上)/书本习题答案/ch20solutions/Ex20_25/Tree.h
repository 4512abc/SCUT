// Exercise 20.25 Solution: Tree.h
// Template Tree class definition.
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <new>
#include "Treenode.h"
using namespace std;

// Tree class-template definition
template< typename NODETYPE > class Tree
{
public:
   Tree(); // constructor
   void insertNode( const NODETYPE & );
   void preOrderTraversal() const;
   void inOrderTraversal() const;
   void postOrderTraversal() const;
   void outputTree() const;
private:
   TreeNode< NODETYPE > *rootPtr;

   // utility functions
   void insertNodeHelper( TreeNode< NODETYPE > **, const NODETYPE & );
   void preOrderHelper( TreeNode< NODETYPE > * ) const;
   void inOrderHelper( TreeNode< NODETYPE > * ) const;
   void postOrderHelper( TreeNode< NODETYPE > * ) const;
   void outputTreeHelper( TreeNode< NODETYPE > *, int ) const;
}; // end class Tree

// constructor
template< typename NODETYPE >
Tree< NODETYPE >::Tree() 
{ 
   rootPtr = 0; // indicate tree is initially empty 
} // end Tree constructor

// insert node in Tree
template< typename NODETYPE >
void Tree< NODETYPE >::insertNode( const NODETYPE &value )
{ 
   insertNodeHelper( &rootPtr, value ); 
} // end function insertNode

// utility function called by insertNode; receives a pointer
// to a pointer so that the function can modify pointer's value
template< typename NODETYPE >
void Tree< NODETYPE >::insertNodeHelper( 
   TreeNode< NODETYPE > **ptr, const NODETYPE &value )
{
   // subtree is empty; create new TreeNode containing value
   if ( *ptr == 0 )  
      *ptr = new TreeNode< NODETYPE >( value );
   else // subtree is not empty
   {
      // data to insert is less than data in current node
      if ( value < ( *ptr )->data )
         insertNodeHelper( &( ( *ptr )->leftPtr ), value );
      else
      {
         // data to insert is greater than data in current node
         if ( value > ( *ptr )->data )
            insertNodeHelper( &( ( *ptr )->rightPtr ), value );
         else // duplicate data value ignored
            cout << value << " dup" << endl;
      } // end else
   } // end else
} // end function insertNodeHelper

// begin preorder traversal of Tree
template< typename NODETYPE > 
void Tree< NODETYPE >::preOrderTraversal() const
{ 
   preOrderHelper( rootPtr ); 
} // end function preOrderTraversal

// utility function to perform preorder traversal of Tree
template< typename NODETYPE >
void Tree< NODETYPE >::preOrderHelper( TreeNode< NODETYPE > *ptr ) const
{
   if ( ptr != 0 ) 
   {
      cout << ptr->data << ' '; // process node          
      preOrderHelper( ptr->leftPtr ); // traverse left subtree 
      preOrderHelper( ptr->rightPtr ); // traverse right subtree
   } // end if
} // end function preOrderHelper

// begin inorder traversal of Tree
template< typename NODETYPE >
void Tree< NODETYPE >::inOrderTraversal() const
{ 
   inOrderHelper( rootPtr ); 
} // end function inOrderTraversal

// utility function to perform inorder traversal of Tree
template< typename NODETYPE >
void Tree< NODETYPE >::inOrderHelper( TreeNode< NODETYPE > *ptr ) const
{
   if ( ptr != 0 ) 
   {
      inOrderHelper( ptr->leftPtr ); // traverse left subtree  
      cout << ptr->data << ' '; // process node                
      inOrderHelper( ptr->rightPtr ); // traverse right subtree
   } // end if
} // end function inOrderHelper

// begin postorder traversal of Tree
template< typename NODETYPE >
void Tree< NODETYPE >::postOrderTraversal() const
{ 
   postOrderHelper( rootPtr ); 
} // end function postOrderTraversal

// utility function to perform postorder traversal of Tree
template< typename NODETYPE >
void Tree< NODETYPE >::postOrderHelper( 
   TreeNode< NODETYPE > *ptr ) const
{
   if ( ptr != 0 ) 
   {
      postOrderHelper( ptr->leftPtr ); // traverse left subtree  
      postOrderHelper( ptr->rightPtr ); // traverse right subtree
      cout << ptr->data << ' '; // process node                  
   } // end if
} // end function postOrderHelper

// print the tree
template< typename NODETYPE >
void Tree< NODETYPE >::outputTree() const 
{ 
   outputTreeHelper( rootPtr, 0 ); 
} // end function outputTree

// utility function to print the tree
template< typename NODETYPE >
void Tree< NODETYPE >::outputTreeHelper( TreeNode< NODETYPE > *ptr,
   int totalSpaces ) const
{
   if ( ptr != 0 ) 
   {
      outputTreeHelper( ptr->rightPtr, totalSpaces + 5 );

      for ( int i = 1; i <= totalSpaces; i++ )
         cout << ' ';
         
      cout << ptr->data << '\n';
      outputTreeHelper( ptr->leftPtr, totalSpaces + 5 );
   } // end if
} // end function outputTreeHelper

#endif


/**************************************************************************
 * (C) Copyright 1992-2010 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
