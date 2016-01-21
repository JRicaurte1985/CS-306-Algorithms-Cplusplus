#include <iostream>
#include <cstdlib>
using namespace std;

int pow(int aBase, int aExponent);

int main(int argc, char*argv[])
{
   if (argc != 3)
   {
      cout << "USAGE: BASE, POWER";
      return 1;
   }
   
   int result = pow(atoi(argv[1]), atoi(argv[2]));
   cout << argv[1] << " to the " << argv[2] << " power equals "
        << result << endl;
   
   return 0;
}

int pow(int aBase, int aExponent)
{
   // if (aExponent == 0)
   // return 1;

   return aBase * pow(aBase, aExponent - 1);
}
