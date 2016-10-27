/*****************************************************************************
Title:          BinomialQueuePlusPlus.h
Author:         Nishad Sharker
******************************************************************************/
#ifndef BINOMIAL_QUEUE_PLUS_PLUS
#define BINOMIAL_QUEUE_PLUS_PLUS

#include "BinomialQueue.h"
#include "QuadraticProbing.h"
#include "BinomialNode.h"
using namespace std;


template <typename Comparable>
class BinomialQueuePlusPlus
{
    public:
/*
    BinomialQueuePlusPlus( );

    //BinomialQueuePlusPlus( const Comparable & item );

    //BinomialQueuePlusPlus( const BinomialQueuePlusPlus & rhs );

    //BinomialQueuePlusPlus( BinomialQueuePlusPlus && rhs );
*/
    ~BinomialQueuePlusPlus( );



    /**
     * Deep copy.
     */
    BinomialQueuePlusPlus & operator=( const BinomialQueuePlusPlus & rhs );

    /**
     * Move.
     */
    BinomialQueuePlusPlus & operator=( BinomialQueuePlusPlus && rhs );

    /**
     * Return true if empty; false otherwise.
     */
    bool isEmpty( ) const;

    /**
     * Returns minimum item.
     * Throws UnderflowException if empty.
     */
    const Comparable & findMin( ) const;

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( const Comparable & x );

    /**
     * Insert item x into the priority queue; allows duplicates.
     */
    void insert( Comparable && x );

    /**
     * Remove the smallest item from the priority queue.
     * Throws UnderflowException if empty.
     */
    void deleteMin( );

    /**
     * Remove the minimum item and place it in minItem.
     * Throws UnderflowException if empty.
     */
    void deleteMin( Comparable & minItem );

    /**
     * Make the priority queue logically empty.
     */
    void makeEmpty( );

    /**
     * Merge rhs into the priority queue.
     * rhs becomes empty. rhs must be different from this.
     * Exercise 6.35 needed to make this operation more efficient.
     */
    void merge( BinomialQueuePlusPlus & rhs );

    int getAssignCounter();

    int getComparisonCounter();

    //This calls our private find(key) function
    //Returns false if find(key) returns a nullptr
    //  which means the key was not found
    //Returns true if find(key) retuns a pointer that is not the nullptr
    bool findNode(const Comparable & key);



    //Changes the x to decrease, Decrease should be smaller than X
    //Once x is changed to the decreased value, it will percolate to the correct position
    void decreaseKey(const Comparable & x, const Comparable & decrease);

    //This will remove the given X from the queue
    //This essenitally replaces x with the empty string
    void remove(const Comparable & x);




private:
    struct hashObj
    {
        Comparable key;
        BinomialNode<Comparable> * ptrnode;

        hashObj(){};
        hashObj(const hashObj & p)
        {
            key = p.key;
            ptrnode = p.ptrnode;
        };

        hashObj & operator=(const hashObj & p)
        {
            key = p.key;
            ptrnode = p.ptrnode;
            return *this;
        };

        bool operator!=(const hashObj & p) const
        {
            return key != p.key;
        }


        hashObj(const Comparable & k, BinomialNode<Comparable> *p)
            : key{ k }, ptrnode{ p } { }

        hashObj(Comparable && k, BinomialNode<Comparable> *p)
            : key{ std::move(k) }, ptrnode{ p } { }



    };

    HashTable<hashObj> hash1;
    BinomialQueue<Comparable> binomQue;

    void percolateUp(BinomialNode <Comparable> * t);

     // Private function that returns a pointer to a BinomialNode that has the Key value
    BinomialNode<Comparable> * find(const Comparable & key);
















};

#include "BinomialQueuePlusPlus.cpp"

#endif
