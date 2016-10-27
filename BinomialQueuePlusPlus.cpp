/*****************************************************************************
Title:          BinomialQueuePlusPlus.cpp
Author:         Nishad Sharker
******************************************************************************/
#include "BinomialQueuePlusPlus.h"
#include "BinomialQueue.h"
#include "QuadraticProbing.h"
#include "BinomialNode.h"
using namespace std;
/*
template <typename Comparable>
BinomialQueuePlusPlus<Comparable> :: BinomialQueuePlusPlus( )
{
//Do we add the two objects constructors for hash1 and binomQue?
    cout << "We are in BQ++" << endl;
    HashTable<hashObj> hash1();
    BinomialQueue<Comparable> binomQue();
    cout << "We are leaving BQ++" << endl;

}

    //BinomialQueuePlusPlus( const ComparablePlusPlus & item );

    //BinomialQueuePlusPlus( const BinomialQueuePlusPlus & rhs );

    //BinomialQueuePlusPlus( BinomialQueuePlusPlus && rhs );


*/
template <typename Comparable>
BinomialQueuePlusPlus<Comparable> :: ~BinomialQueuePlusPlus( )
{
    makeEmpty();
}


/**
 * Deep copy.
 */

template <typename Comparable>
BinomialQueuePlusPlus<Comparable> & BinomialQueuePlusPlus<Comparable> ::  operator=( const BinomialQueuePlusPlus & rhs )
{
    BinomialQueuePlusPlus copy = rhs;
    std::swap( *this, copy );
    return *this;

}

/**
 * Move.
 */
template <typename Comparable>
BinomialQueuePlusPlus<Comparable> & BinomialQueuePlusPlus<Comparable> :: operator=( BinomialQueuePlusPlus && rhs )
{
    std::swap(hash1, rhs.hash1);
    std::swap(binomQue, rhs.binomQue);
    return *this;
}

/**
 * Return true if empty; false otherwise.
 */
template <typename Comparable>
bool BinomialQueuePlusPlus<Comparable> :: isEmpty( ) const
{
    return binomQue.isEmpty();
}

/**
 * Returns minimum item.
 * Throws UnderflowException if empty.
 */
template <typename Comparable>
const Comparable & BinomialQueuePlusPlus<Comparable> :: findMin( ) const
{
    return binomQue.findMin();
}

/**
 * Insert item x into the priority queue; allows duplicates.
 */
template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> ::insert( const Comparable & x )
{


    //bnptr = call insert bq X
    BinomialNode<Comparable>* loc = binomQue.insert(x);
    //make a hashobj using X and bnptr
    hashObj pair(x, loc);
    //insert the hasobj in to the table
    hash1.insert(pair);

}


/**
 * Insert item x into the priority queue; allows duplicates.
 */
template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> :: insert( Comparable && x )
{

    //bnptr = call insert bq X
    BinomialNode<Comparable>* loc = binomQue.insert(x);
    //make a hashobj using X and bnptr
    hashObj pair(x, loc);
    //insert the hasobj in to the table
    hash1.insert(pair);
}

/**
 * Remove the smallest item from the priority queue.
 * Throws UnderflowException if empty.
 */
template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> :: deleteMin( )
{
    //FindMin
    auto foundMin = binomQue.findMin();
    hashObj nodeToDelete{foundMin,nullptr};
    //Remove from Hashtable
    hash1.remove(nodeToDelete);
    //Remove from queue
    binomQue.deleteMin();

}

/**
 * Remove the minimum item and place it in minItem.
 * Throws UnderflowException if empty.
 */
template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> :: deleteMin( Comparable & minItem )
{
    //FindMin
    auto foundMin = binomQue.findMin();
    hashObj nodeToDelete{foundMin,nullptr};
    //Remove from Hashtable
    hash1.remove(nodeToDelete);
    //Remove from queue
    binomQue.deleteMin();
    minItem = foundMin;
}

/**
 * Make the priority queue logically empty.
 */
template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> ::  makeEmpty( )
{
    hash1.makeEmpty();
    binomQue.makeEmpty();
}

/**
 * Merge rhs into the priority queue.
 * rhs becomes empty. rhs must be different from this.
 * Exercise 6.35 needed to make this operation more efficient.
 */
template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> ::  merge( BinomialQueuePlusPlus & rhs )
{
    binomQue.merge(rhs.binomQue);
    hash1.merge(rhs.hash1);

}

template <typename Comparable>
BinomialNode<Comparable> * BinomialQueuePlusPlus<Comparable> :: find(const Comparable & key)
{

    BinomialNode<Comparable> * elem = nullptr;
    hashObj locateElem(key, elem);
    return hash1.getItem(locateElem).ptrnode;
}

template <typename Comparable>
int BinomialQueuePlusPlus<Comparable> :: getAssignCounter()
{
    return binomQue.getAssignCounter();
}


template <typename Comparable>
int BinomialQueuePlusPlus<Comparable> :: getComparisonCounter()
{
    return binomQue.getComparisonCounter();
}

template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> :: decreaseKey(const Comparable & x,const Comparable & decrease)
{

    //find x in hashtable
    BinomialNode<Comparable> * searchPTR = nullptr;

    hashObj tempPair(x,searchPTR);
    hashObj val = hash1.getItem(tempPair);

    BinomialNode<Comparable> * nodePTR = val.ptrnode;

    if (nodePTR != nullptr)
    {
        //Remove the X from the hash table before we change it to decrease
        hashObj remX(nodePTR->element, nullptr);
        hash1.remove(remX);


        nodePTR->element = decrease;

        //PercolateUp so that the tree is in proper order.
        percolateUp(nodePTR);

    }

    //if X is found then execute code
        //change x.key = to decrease
        //percolate upwards

}

template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> :: percolateUp(BinomialNode <Comparable> * t)
{
    BinomialNode<Comparable> *parPTR = t->parent;

    if (t->parent != nullptr && t->element < parPTR->element)
    {
        //remove t-> element and parPTR -> element from hash
        hashObj remT(t->element, nullptr);
        hash1.remove(remT);

        hashObj remPar(parPTR->element,nullptr);
        hash1.remove(remPar);

        //Swap t->element and parPTR->element
        auto temp = t->element;
        t->element = parPTR->element;
        parPTR->element = temp;

        //INSERT t->element and partPTR->element with new pointers into hash
        hashObj newT(t->element,t);
        hashObj newPar(parPTR->element, parPTR);
        hash1.insert(newT);
        hash1.insert(newPar);
        //percolateUp the parent node becuase the parent node is where we need to search next.
        //percolateUP(THE NEW VARIABLE THAT POINTS TO PARENT)
        percolateUp(parPTR);

    }

}

template <typename Comparable>
void BinomialQueuePlusPlus<Comparable> :: remove(const Comparable & x)
{
    decreaseKey(x,"");
    deleteMin();
}

template <typename Comparable>
bool BinomialQueuePlusPlus<Comparable> :: findNode(const Comparable & key)
{
    bool found;
    if (find(key) == nullptr)
    {
        found = false;
    }
    else
    {
        found = true;
    }

    return found;
}
