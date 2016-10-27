/*****************************************************************************
Title:          QuadraticProbing.h
Author:         Nishad Sharker
******************************************************************************/
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

int nextPrime( int n );

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 );

    bool contains( const HashedObj & x ) const;

    void makeEmpty( );

    bool insert( const HashedObj & x );

    bool insert( HashedObj && x );

    bool remove( const HashedObj & x );

    //Returns the hashedObj, essential for returning structs pairs
    HashedObj getItem(const HashedObj & x) const;

    enum EntryType { ACTIVE, EMPTY, DELETED };

    //Merges the hashtable h2 with current hashtable by inserting all
    //   the elements from h2 one by one into this hashtable
    void merge(HashTable & h2);

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }

        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const;

    int findPos( const HashedObj & x ) const;

    void rehash( );

    size_t myhash( const HashedObj & x ) const;
};

#include "QuadraticProbing.cpp"

#endif
