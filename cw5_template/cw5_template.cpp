#include <iostream>
#include "Stack.h"
using namespace std;

int main( int argc, char* argv[] )
{
    Stack<char> cS;
    Stack<double> dS;
    try {
        char c = cS.top();
    }
    catch( StackException e )
    {
        cout << endl << "***" <<  e.getReason() << "***" << endl << endl;
    }

    dS.push( 1 );
    dS.push( 2 );
    dS.push( 3 );

    cS.push( 'A' );
    cS.push( 'B' );
    cS.push( 'C' );
    cout << endl;

    cout << dS.pop() << ' ';
    cout << dS.pop() << ' ';
    cout << dS.pop() << endl;

    try {
        if( cS.pop() == 'C' )
            if( cS.pop() == 'B' )
                if(cS.pop() == 'A')
                {
                    cout << "Char stack operations OK! " << endl;
                    cout << cS.pop();
                    return 0;
                }
    cout << endl << "--> No error in stack operations?!" << endl;
    }
    catch( StackException e )
    {
        cout << endl << "***" << e.getReason() << "***" << endl << endl;
    }
    return 0;
}
