#include <cmath>
#include <cstdlib>

#define random() ((double) rand() / (RAND_MAX))

class Annealing
{
  public:
    bool calcAcceptProb(int cEnergy, int pEnergy);
    bool cooling();
    double normal;
    Annealing(double pMax, double pMin, double change);
   
   
    double getCurrTemp()  { return currTemp; };
    double getMaxTemp()   { return maxTemp;  };
    double getMinTemp()   { return minTemp;  };
    double getTempChange(){ return tempChange; };
   
  private:
    double currTemp;
    double maxTemp, minTemp, tempChange;

};

Annealing::Annealing(double pMax, double pMin, double change)
{
   currTemp = pMax;
   maxTemp = pMax;
   minTemp = pMin;
   tempChange = change;
   normal = exp(1.0 / pMin);
}

bool Annealing::calcAcceptProb(int pEnergy, int cEnergy)
{
   if (cEnergy <= pEnergy)
      return true;
   
   double boltz = exp((pEnergy - cEnergy) / currTemp) / currTemp;
   
   if(boltz * normal > 1)
      normal = 1 / boltz;
   
   double temp = random();
   std::cerr << boltz * normal;
   std::cerr << " > " << temp << std::endl;
   return (boltz * normal) > temp;
}

bool Annealing::cooling()
{
   std::cout << "Temp: " << (currTemp = currTemp - tempChange) << std::endl;
   return currTemp > minTemp;
}
