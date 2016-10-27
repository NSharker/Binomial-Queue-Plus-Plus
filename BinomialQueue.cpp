/*****************************************************************************
Title:          BinomialQueue.cpp
Author:         Nishad Sharker
******************************************************************************/

#include <iostream>
#include <vector>
#include "dsexceptions.h"
#include "BinomialQueue.h"
#include "BinomialNode.h"
using namespace std;

// Binomial queue class
//
// CONSTRUCTION: with no parameters
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( )           --> Return and remove smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void merge( rhs )      --> Absorb rhs into this heap
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
BinomialQueue<Comparable> :: BinomialQueue( ) : theTrees( DEFAULT_TREES )
{
    for( auto & root : theTrees )
        root = nullptr;
    currentSize = 0;
    assignCounter = 0;
    comparisonCounter = 0;
    //cout << "BQ constructor was called." << endl;
}

template <typename Comparable>
BinomialQueue<Comparable> :: BinomialQueue( const Comparable & item ) : theTrees( 1 ), currentSize{ 1 }
{
    theTrees[ 0 ] = new BinomialNode<Comparable> { item, nullptr, nullptr, nullptr };
    assignCounter = 1;
    comparisonCounter = 0;

}

template <typename Comparable>
BinomialQueue<Comparable> :: BinomialQueue( const BinomialQueue & rhs )
      : theTrees( rhs.theTrees.size( ) ),currentSize{ rhs.currentSize }
{
    for( int i = 0; i < rhs.theTrees.size( ); ++i )
        theTrees[ i ] = clone( rhs.theTrees[ i ] );

    assignCounter = rhs.assignCounter;
    comparisonCounter = rhs.comparisonCounter;
}

template <typename Comparable>
BinomialQueue<Comparable> :: BinomialQueue( BinomialQueue && rhs )
      : theTrees{ std::move( rhs.theTrees ) }, currentSize{ rhs.currentSize }
{
    assignCounter = rhs.assignCounter;
    comparisonCounter = rhs.comparisonCounter;
}

template <typename Comparable>
BinomialQueue<Comparable> :: ~BinomialQueue( )
      { makeEmpty( ); }


/**
 * Deep copy.
 */
template <typename Comparable>
BinomialQueue<Comparable> & BinomialQueue<Comparable> :: operator=( const BinomialQueue & rhs )
{
    BinomialQueue copy = rhs;
    std::swap( *this, copy );
    return *this;
}

/**
 * Move.
 */
template <typename Comparable>
BinomialQueue<Comparable> & BinomialQueue<Comparable> :: operator=( BinomialQueue && rhs )
{
    std::swap( currentSize, rhs.currentSize );
    std::swap( theTrees, rhs.theTrees );

    return *this;
}

/**
 * Return true if empty; false otherwise.
 */
template <typename Comparable>
bool BinomialQueue<Comparable> :: isEmpty( ) const
{
    return currentSize == 0;
}

/**
 * Returns minimum item.
 * Throws UnderflowException if empty.
 */
template <typename Comparable>
const Comparable & BinomialQueue<Comparable> ::findMin( ) const
{
    if( isEmpty( ) )
        throw UnderflowException{ };

    return theTrees[ findMinIndex( ) ]->element;
}

/**
 * Insert item x into the priority queue; allows duplicates.
 */
template <typename Comparable>
BinomialNode<Comparable> * BinomialQueue<Comparable> :: insert( const Comparable & x )
{
    BinomialQueue oneItem{ x };
    BinomialNode<Comparable> * location = oneItem.theTrees[0];
    merge( oneItem );
    return location;
}

/**
 * Insert item x into the priority queue; allows duplicates.
 */
template <typename Comparable>
BinomialNode<Comparable> * BinomialQueue<Comparable> :: insert( Comparable && x )
{
    BinomialQueue oneItem{ std::move( x ) };
    BinomialNode<Comparable> * location = oneItem.theTrees[0];
    merge( oneItem );
    return location;
}

/**
 * Remove the smallest item from the priority queue.
 * Throws UnderflowException if empty.
 */
template <typename Comparable>
void BinomialQueue<Comparable> :: deleteMin( )
{
    Comparable x;
    deleteMin( x );
}

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
template <typename Comparable>
void BinomialQueue<Comparable> :: deleteMin( Comparable & minItem )
{
    if( isEmpty( ) )
        throw UnderflowException{ };

    int minIndex = findMinIndex( );
    minItem = theTrees[ minIndex ]->element;

    BinomialNode<Comparable> *oldRoot = theTrees[ minIndex ];
    BinomialNode<Comparable> *deletedTree = oldRoot->leftChild;
    delete oldRoot;

    // Construct H''
    BinomialQueue deletedQueue;
    deletedQueue.theTrees.resize( minIndex + 1 );
    deletedQueue.currentSize = ( 1 << minIndex ) - 1;
    for( int j = minIndex - 1; j >= 0; --j )
    {
        deletedQueue.theTrees[ j ] = deletedTree;
        deletedQueue.theTrees[ j ]->parent = nullptr;
        deletedTree = deletedTree->nextSibling;
        deletedQueue.theTrees[ j ]->nextSibling = nullptr;
    }

    // Construct H'
    theTrees[ minIndex ] = nullptr;
    currentSize -= deletedQueue.currentSize + 1;

    merge( deletedQueue );
}

/**
 * Make the priority queue logically empty.
 */
template <typename Comparable>
void BinomialQueue<Comparable> :: makeEmpty( )
{
    currentSize = 0;
    for( auto & root : theTrees )
        makeEmpty( root );
}

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
template <typename Comparable>
void BinomialQueue<Comparable> :: merge( BinomialQueue & rhs )
{
    assignCounter += rhs.assignCounter;
    comparisonCounter += rhs.comparisonCounter;

    comparisonCounter++;
    if( this == &rhs )    // Avoid aliasing problems
        return;

    assignCounter++;
    currentSize += rhs.currentSize;

    comparisonCounter++;
    if( currentSize > capacity( ) )
    {
        assignCounter += 3;
        int oldNumTrees = theTrees.size( );
        int newNumTrees = max( theTrees.size( ), rhs.theTrees.size( ) ) + 1;
        theTrees.resize( newNumTrees );
        for( int i = oldNumTrees; i < newNumTrees; ++i )
        {
            comparisonCounter++;
            assignCounter++;
            theTrees[ i ] = nullptr;
        }
        comparisonCounter++;
    }

    assignCounter +=3;
    BinomialNode<Comparable> *carry = nullptr;
    for( int i = 0, j = 1; j <= currentSize; ++i, j *= 2 )
    {
        //assignCounter increases for ++i and j*=2
        assignCounter +=4;
        comparisonCounter++;
        BinomialNode<Comparable> *t1 = theTrees[ i ];
        BinomialNode<Comparable> *t2 = i < rhs.theTrees.size( ) ? rhs.theTrees[ i ] : nullptr;

        assignCounter +=3;
        comparisonCounter +=3;
        int whichCase = t1 == nullptr ? 0 : 1;
        whichCase += t2 == nullptr ? 0 : 2;
        whichCase += carry == nullptr ? 0 : 4;

        switch( whichCase )
        {
          case 0: /* No trees */
          case 1: /* Only this */
            break;
          case 2: /* Only rhs */
              assignCounter += 2;
            theTrees[ i ] = t2;
            rhs.theTrees[ i ] = nullptr;
            break;
          case 4: /* Only carry */
              assignCounter += 2;
            theTrees[ i ] = carry;
            carry = nullptr;
            break;
          case 3: /* this and rhs */
              assignCounter += 3;
            carry = combineTrees( t1, t2 );
            theTrees[ i ] = rhs.theTrees[ i ] = nullptr;
            break;
          case 5: /* this and carry */
              assignCounter += 2;
            carry = combineTrees( t1, carry );
            theTrees[ i ] = nullptr;
            break;
          case 6: /* rhs and carry */
              assignCounter += 2;
            carry = combineTrees( t2, carry );
            rhs.theTrees[ i ] = nullptr;
            break;
          case 7: /* All three */
              assignCounter += 3;
            theTrees[ i ] = carry;
            carry = combineTrees( t1, t2 );
            rhs.theTrees[ i ] = nullptr;
            break;
        }
    }

    for( auto & root : rhs.theTrees )
    {
        assignCounter++;
        root = nullptr;
    }
    assignCounter++;
    rhs.currentSize = 0;
}

/**
 * Find index of tree containing the smallest item in the priority queue.
 * The priority queue must not be empty.
 * Return the index of tree containing the smallest item.
 */
template <typename Comparable>
int BinomialQueue<Comparable> :: findMinIndex( ) const
{
    int i;
    int minIndex;

    for( i = 0; theTrees[ i ] == nullptr; ++i )
        ;

    for( minIndex = i; i < theTrees.size( ); ++i )
        if( theTrees[ i ] != nullptr &&
            theTrees[ i ]->element < theTrees[ minIndex ]->element )
            minIndex = i;

    return minIndex;
}

/**
 * Return the capacity.
 */
template <typename Comparable>
int BinomialQueue<Comparable> :: capacity( ) const
{
    return ( 1 << theTrees.size( ) ) - 1;
}

/**
 * Return the result of merging equal-sized t1 and t2.
 * typename BinomialQueue<Comparable> :: BinomialNode * BinomialQueue<Comparable> :: combineTrees( BinomialNode *t1, BinomialNode *t2 )
 */
template <typename Comparable>
BinomialNode<Comparable> * BinomialQueue<Comparable> :: combineTrees( BinomialNode<Comparable> *t1, BinomialNode<Comparable> *t2 )
{
    //Place a variable counter here for comparison
    comparisonCounter++;
    if( t2->element < t1->element )
        return combineTrees( t2, t1 );

    assignCounter += 2;
    t2->nextSibling = t1->leftChild;
    t1->leftChild = t2;
    //t2 is a left child of t1, therefore t1 is a parent of t2
    t2->parent = t1;
    return t1;
}

/**
 * Make a binomial tree logically empty, and free memory.
 */
template <typename Comparable>
void BinomialQueue<Comparable> :: makeEmpty( BinomialNode<Comparable> * & t )
{
    if( t != nullptr )
    {
        makeEmpty( t->leftChild );
        makeEmpty( t->nextSibling );
        delete t;
        t = nullptr;
    }
}

/**
 * Internal method to clone subtree.
 */
template <typename Comparable>
BinomialNode<Comparable> * BinomialQueue<Comparable> ::  clone( BinomialNode<Comparable> * t ) const
{
    if( t == nullptr )
        return nullptr;
    else
        return new BinomialNode<Comparable>{ t->element, clone( t->leftChild ), clone( t->nextSibling ) };
}

template <typename Comparable>
int BinomialQueue<Comparable> :: getAssignCounter()
{
    return assignCounter;
}


template <typename Comparable>
int BinomialQueue<Comparable> :: getComparisonCounter()
{
    return comparisonCounter;
}



