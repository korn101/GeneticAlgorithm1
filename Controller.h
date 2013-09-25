/* 
 * File:   Controller.h
 * Author: d-savant
 *
 * Created on 21 September 2013, 11:46 PM
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

