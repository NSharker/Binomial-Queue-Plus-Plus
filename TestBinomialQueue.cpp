#include "BinomialQueue.h"
#include "BinomialNode.h"
#include <iostream>
using namespace std;

int main( )
{
    int numItems = 100000;
    BinomialQueue<int> h;
    BinomialQueue<int> h1;
    BinomialQueue<int> h2;
    int i = 37;

    BinomialNode<int>* address;


    cout << "Begin test..." << endl;
    for( i = 37; i != 0; i = ( i + 37 ) % numItems )
        if( i % 2 == 0 )
        {
            address = h1.insert( i );
            cout << i << " is found at address: " << address << endl;
        }
        else
        {
            h.insert( i );
        }

    h.merge( h1 );
    h2 = h;



    for( i = 1; i < numItems; ++i )
    {

        int x;
        h2.deleteMin( x );
        if( x != i )
            cout << "Oops! " << i << endl;
    }

    if( !h1.isEmpty( ) )
        cout << "Oops! h1 should have been empty!" << endl;

    cout << "End of test... no output is good" << endl;

    return 0;
}
