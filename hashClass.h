//
//  hashClass.h
//  goodness
//
//  Created by Chris Vergaray on 3/18/14.
//  Copyright (c) 2014 cave_studios. All rights reserved.
//

#ifndef __goodness__hashClass__
#define __goodness__hashClass__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cstdlib>

class HashClass
{
private:
   short shiftA;
   short shiftB;
   short shiftC;
   short shiftD;
   short limit;
   int collisions;
   std::vector<unsigned int> * words;
   std::map<int, int> mymap;
   
public:
   inline short getShiftA()      {return shiftA;      };
   inline short getShiftB()      {return shiftB;      };
   inline short getShiftC()      {return shiftC;      };
   inline short getShiftD()      {return shiftD;      };
   inline short getLimit()       {return limit;       };
   
   int getCollisions()
   {
      if(collisions < 0)
      {
         collisions = 0;
         checkCollisions();
      }
      
      return collisions;
   };
   
   //Constructors
   HashClass(HashClass const &otherHash, short pLimit)
   {
      words = otherHash.words;
      limit = pLimit;
      
      shiftA = otherHash.shiftA + (rand() % limit) - (limit / 2);
      boundsChecking(shiftA);
      
      shiftB = otherHash.shiftB + (rand() % limit) - (limit / 2);
      boundsChecking(shiftB);
      
      shiftC = otherHash.shiftC + (rand() % limit) - (limit / 2);
      boundsChecking(shiftC);

      shiftD = otherHash.shiftD + (rand() % limit) - (limit / 2);
      boundsChecking(shiftD);
      
      collisions = -1;
   }
   
   void boundsChecking(short &shift)
   {
      shift = shift < 0  ? -shift : shift;
      shift = shift > 31 ? 62 - shift : shift;
   }
   
   HashClass(std::string pFileName)
   {
      collisions = -1;
      words = new std::vector<unsigned int>;
      shiftA = shiftB = shiftC = shiftD = 15;
      
      std::ifstream infile(pFileName.c_str());
      std::string word;
      
      while (getline(infile, word))
      {
         words->push_back(hashCode(word));
      }
   }
   
   ~HashClass()
   {
      //There is a potential memory leak because we are intentionally not deleting
      //the vector of words. It must be deleted later when we are done with it
      //using removeList()
   }
   
   void removeList() { delete words; };
   
   HashClass operator = (HashClass other)
   {
      this->limit = other.limit;
      this->words = other.words;
      this->shiftA = other.shiftA;
      this->shiftB = other.shiftB;
      this->shiftC = other.shiftC;
      this->shiftD = other.shiftD;
      this->collisions = other.collisions;
      return *this;
   }
   
   //Setters
   inline void setShiftA(short pShift) { shiftA = pShift; };
   inline void setShiftB(short pShift) { shiftB = pShift; };
   inline void setShiftC(short pShift) { shiftC = pShift; };
   inline void setShiftD(short pShift) { shiftD = pShift; };
   
   /****************************************************************
    * HASH CODE
    *  Converts strings into an unsigned integer hashcode. This code
    *  is used as seed for the hash function which converts hash codes
    *  into hashes.
    ****************************************************************/
   unsigned int hashCode(std::string word)
   {
      unsigned int h = 1;
      
      for (int i = 0; i < word.length(); i++)
      {
         h = 31 * h + word[i];
      }
      
      return h;
   };
   
   /****************************************************************
    * MY HASH
    *  Generates a hashed version of the passed integer based on the
    *  shift values defined in the class.
    ****************************************************************/
   int myHash(int h)
   {
      h +=  ~(h << this->shiftA);
      h ^=   (h >> this->shiftB);
      h +=   (h << this->shiftC);
      h ^=   (h >> this->shiftD);
      return h;
   }

   void display()
   {
      std::cout  << "Shift A:    " << shiftA << std::endl
                 << "Shift B:    " << shiftB << std::endl
                 << "Shift C:    " << shiftC << std::endl
                 << "Shift D:    " << shiftD << std::endl
                 << "Collisions: " << collisions << std::endl;
   }
   
   /****************************************************************
    * RUN SIMULATION
    * This function accepts a vector of values which have been pregenerated using
    * the hashcode function. The ints in this list represent the words
    * from the dictionary file. These values are hashed and then sent
    * to the add to map function.
    ****************************************************************/
   void checkCollisions()
   {
      int temp;
      for (std::vector<unsigned int>::iterator it = words->begin(); it != words->end(); ++it)
      {
         temp = myHash(*it);
         
         if (mymap.count(temp) > 0)
         {
            mymap[temp]++;
            collisions++;
         }
         else
         {
            mymap.insert(std::make_pair(temp, 1));
         }
      }
   };
   
};


#endif /* defined(__goodness__hashClass__) */
