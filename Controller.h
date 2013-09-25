/* 
 * File:   Controller.h
 * Author: d-savant
 *
 * Created on 21 September 2013, 11:46 PM
 * 
 * The MIT License (MIT)

Copyright (c) 2013 korn101

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include "Organism.h"
#include <cstdlib>

class Controller 
{
public:
    Controller(int popSize, Organism& target);
    virtual ~Controller();
    
    
    void printPopulation() const;
    void step(int n); //do n number of evolutionary generations.
    int fitness(Organism& org) const; //fintess function.
    void printFitGraph() const;
    
    
private:
    void error(std::string message) const;
    int populationSize; //the variable size of the population.
    Organism * population; //dynamic array of organisms to represent population.
    Organism goalOrganism;
    const static int chromosomeLen = 8 ; // VARIABLE this should reflect binaryNumber.numBits * Organism.noOfGenes
    int * gFitness; // graph of fitness where index represents the generation. ie. gen 0 is the starting highest fitness.
    int gSize; //gSize, the size of the gFitness graph - defined as the number of evolutionary steps.
    
};

#endif	/* CONTROLLER_H */

