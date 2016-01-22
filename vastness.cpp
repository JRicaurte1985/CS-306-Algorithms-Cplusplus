/*******************************************************************************
* Vastness
* Collaboration with Jeff Bickmore, Jordan Balls, Devin Lacrosse, Google
*******************************************************************************/
#include <iostream>
#include <NTL/RR.h>
#include <iomanip>
#include <algorithm>
#include <time.h>

NTL_CLIENT

using namespace NTL;
using namespace std;

const RR ZERO = to_RR(0);
const RR ONE  = to_RR(1);
const RR TWO  = to_RR(2);


/*
 * checks that the entire string is made out of
 * numbers
 */
bool isValid(string number)
{
   for (int i = 0; i < number.size(); i++)
   {
      if (!isdigit(number[i]))
         return false;
   }
   return true;
}

/*
 * prompt the user for the prefix number 
 * from the command line.  Converts to a 
 * rr number
 */
RR getNumber()
{
   RR prefix;
   string number;
   string instructions = "\nPlease enter a prefix for a number: ";
   cout << instructions;
   cin >> number;
   while (!isValid(number))
   {
      cin.clear();
      cin.ignore();
      cout << "Your input was not valid. " << instructions;
      cin >> number;
   }
   cout << "\n";
   prefix = to_RR(number.c_str());
   return prefix;
}

/*
 * request time to spend searching  
 */
 int requestTime(RR number)
 {
    int time;
    cout << "Using the proof: " << endl
         << "     log base 10 of num <= log base 10 of n - m < log base"
         << " 10 of num + 1 " << endl
         << "proves that there will always be a power of two that "
         << "begins with " << number << "." << endl;
    cout << "\nHow long are you willing to wait for an answer (in minutes)? ";
    cin >> time;
    
    while (cin.fail() || time < 0)
    {
      cin.clear();
      cin.ignore();
      cout << "Please enter only a useful number:\n>";
      cin  >> time;
    }
    return time;
 }
 
int main(int argc, char ** argv) 
{
   RR number = getNumber();
   int time = requestTime(number);
   
   long long timeToWait = time * CLOCKS_PER_SEC * 60;
   bool found = true;
      
   //create our checks, upper and lower bounds, and other variables.
   RR check1 = log10(number); 
   RR check2 = log10(number + ONE); 
   RR lowerCheck = (check1 - floor(check1));
   RR upperCheck = (check2 - floor(check2));
   RR closeEnough = to_RR(.000000000000000000000000000001);
      
      
   ZZ n = to_ZZ(ZERO);
   RR LogTwo = log10(TWO);
   RR mantissa = ZERO;
   RR base = ONE;
   RR absBase = ONE;

   ZZ zzZero = to_ZZ(0);
   ZZ addition = zzZero;

   //While the mantissa (fractional part... ie., the significand) of the
   // number is between the upper and lower bound, 
   // continue incrementing and recalculating.
   
   clock_t current = clock();
   long long closingTime = current + (((float)timeToWait));
   float timeElapsed;
   
   /*
   * to ensure that we actually stop at a resonable spot, the difference
   * needs to be compared to a really small number
   */
   while ( !(lowerCheck <= mantissa && mantissa < upperCheck) 
   && abs(mantissa - lowerCheck) > closeEnough)
   {
      if (closingTime - clock() < 0)
      {
         found = false;
         break;
      }
      
      n++;
      base = to_RR(n)*LogTwo;
      absBase = floor(base);
      mantissa = base - abs(absBase);
      clock_t end = (clock() - current);
      timeElapsed = end / CLOCKS_PER_SEC;
   
   }
   
   if (found)
      cout << "\nYour power of two is: "<< fixed << n << "   Total time taken: "
           << setprecision(2) << timeElapsed << " seconds" << endl;
   
   else
   {
      cout << "The program was unable to find your power of two in your"
           << " required time limit\n";
   }
   
   return 0;
}
