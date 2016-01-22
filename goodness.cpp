//
//  hashClass.cpp
//  goodness
//
//  Created by Chris Vergaray on 3/18/14.
//  Copyright (c) 2014 cave_studios. All rights reserved.
//

#include "hashClass.h"
#include "annealing.h"
#include <cmath>

using namespace std;

class Run
{
private:
	HashClass *oldHash;
	HashClass *newHash;
	Annealing *anneal;
   
public:
	Run (double maxTemp, double minTemp, double tempChange, string filename)
	{
           anneal = new Annealing(maxTemp,minTemp,tempChange);
	   oldHash = new HashClass(filename);
	   newHash = new HashClass(*oldHash, 16.0);
	}
   
	void run()
	{
           do
	   {
              std::cerr << "Old collisions: " << oldHash->getCollisions() << endl;
              std::cerr << "New collisions: " << newHash->getCollisions() << endl;
              
              if (anneal->calcAcceptProb(oldHash->getCollisions(), newHash->getCollisions()))
              {
                 delete oldHash;
                 oldHash = newHash;
              }
              
              newHash = new HashClass(*oldHash, ceil(16 * anneal->getCurrTemp() / anneal->getMaxTemp()));
           }
           
           while(anneal->cooling());
           oldHash->display();
           oldHash->removeList();
	}
};

int main(int argc, const char * argv[])
{
   srand(clock());
   //Run runClass(730.0, 727.0, .1, "/usr/share/dict/words");
   //Run runClass(730.0, 722.0, .001, "/usr/share/dict/words");
   Run runClass(100.0, 1.0, 1, "/usr/share/dict/words");
   runClass.run();
}
