//
//  Timer.cpp
//  inquisitiveness
//
//  Created by Chris Vergaray on 2/6/14.
//  Copyright (c) 2014 cave_studios. All rights reserved.
//

#include "Timer.h"

/***********************************************************************
 * START
 * Saves the current time in the start time value. This
 ***********************************************************************/
void Timer::start()
{
   startTime = clock();    //Start benchmark timer
}

/***********************************************************************
 * STOP
 * Calculates the difference between the start time and the current time.
 ***********************************************************************/
double Timer::stop()
{
   //Calculate benchmark
   return elapsedTime = (double( clock() - startTime ) / (double)CLOCKS_PER_SEC);
}

/***********************************************************************
 * RESET
 * Resets all the values in the timer. This isn't really that necessary,
 * but can be used to create a cumulative timer.
 ***********************************************************************/
void Timer::reset()
{
   elapsedTime = 0;
   startTime = 0;
}

/***********************************************************************
 * DISPLAY STATS
 * Displays the Elapsed Calculation and Display times for benchmark testing.
 * Only after the calculation and display of a fibonacci number, will the
 * elapsed times be populated.
 ***********************************************************************/
void Timer::displayStats()
{
   std::cout.unsetf(std::ios::fixed);        //No scientific notation
   std::cout.unsetf(std::ios::showpoint);    //Always show the decimal
   std::cout.precision(6);
   
   std::cout << "Elapsed time: " << elapsedTime << "\t(S)" << std::endl;
}

double Timer::getTime()
{
   return elapsedTime;
}