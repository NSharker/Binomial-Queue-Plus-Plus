/*****************************************************************************
Title:          BinomialNode.H
Author:         Nishad Sharker
******************************************************************************/
#ifndef BINOMIAL_NODE_H
#define BINOMIAL_NODE_H

#include <iostream>
#include <vector>
#include "dsexceptions.h"
using namespace std;

template<typename Comparable>
class BinomialNode
{
    public:
    Comparable    element;
    BinomialNode *leftChild;
    BinomialNode *nextSibling;
    BinomialNode *parent;

    BinomialNode( const Comparable & e, BinomialNode *lt, BinomialNode *rt, BinomialNode *pt )
      : element{ e }, leftChild{ lt }, nextSibling{ rt }, parent{ pt } { }

    BinomialNode( Comparable && e, BinomialNode *lt, BinomialNode *rt, BinomialNode *pt )
      : element{ std::move( e ) }, leftChild{ lt }, nextSibling{ rt }, parent{ pt } { }
};


#endif // BINOMIAL_NODE_H
