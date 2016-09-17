#include <iostream>
#include "smathparser.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    SMathParser p;
    cout << p.run( " 1 + 5 * ( 6 + 5 ) + 6 " ) << endl;
    return 0;
}
