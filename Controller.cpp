/* 
 * File:   Controller.cpp
 * Author: d-savant
 * 
 * Created on 21 September 2013, 11:46 PM
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

#include "Controller.h"
#include <iostream>
#include <sstream>

using namespace std;

Controller::Controller(int popSize, Organism& target) : gSize(0)
{
    
    if (popSize <= 2)
        error("Initial Population must be greater than 2.");
    if (popSize % 2 != 0)
        error("Population size must be an EVEN integer value.");
    
    cout << "->Starting Evolution Controller..." << endl;
    
    populationSize = popSize;
    goalOrganism = target;
    population = new Organism[popSize]; // dynamic array allocation
    
    if (population == NULL)
    {
        error("Failed to Allocate memory for population");
    }    
    
    cout << "->Generating (random) Organisms.." << endl;
    
    for (int i = 0; i < popSize; i++)
        population[i] = Organism();
    
    cout << "->Evolution Controller Running..." << endl << "----" << endl;
}


Controller::~Controller() 
{

    if (population)
        delete[] population;
        
    populationSize = 0;

}

void Controller::printPopulation() const
{
    cout << "----" << endl;
    
    for (int i = 0; i < populationSize; i++)
    {
        if (population[i].getNoOfGenes() < 16)
        {    
            cout << "Organism " << i+1 << ": ";
            population[i].printChromosome();
            cout <<" Fitness: " << fitness(population[i]) << endl;
        }
        else // if it has really long chromosomes, then space them accordingly.
        {
            cout << "Organism " << i+1 << ": \n";
            population[i].printChromosome();
            cout <<"\nFitness: " << fitness(population[i]) << endl << "--" << endl;
        }
    }
    
    cout << "----" << endl;
    
}


void Controller::error(string message) const //very basic exception handler.
{
    cout << endl << "::Error: " << message << "::" << endl << "----" << endl;
    exit(EXIT_FAILURE);
}

int Controller::fitness(Organism& org) const
{
    binaryNumber temp;
    // count number of shared bits, and return result:
    int count = 0;
    
    for (int i = 0; i < org.getNoOfGenes()*temp.numBits; i++)
        if (org[i] == goalOrganism[i])
            count++;

    return count;
    
}

void Controller::step(int n) //do n number of evolutionary generations.
{
    // first evaluate current population, find fittest half. Discard unfit, replace the remaining empty population half with children.
    // mate fittest members of population.
    // replace other unfit slots with children (using reproduce function)
    // repeat for n generations
    
    gFitness = new int[n]; //array of highest fitnesses for each generation
    if (gFitness)
    {
        gSize = n;
    }
    else
    {
        error("Failed to allocate memory for fitness graph.");
    }
    
    for (int gen = 1; gen <= n; gen++) // loop through generations.
    {
        int bestFit = 0; // best fitness
        int iFitIndex = 0; //index of current fittest.
        int *fitnesses = new int[populationSize]; //use of dynamic memory allows for variable population size :)
        
        
        // this is the graphing code:
        
        // find the max fitness in new population, and save it to the graph of max fitness in generation number index.
        for (int i = 0; i < populationSize; i++)  
            if (fitness(population[i])  > bestFit)
                bestFit = fitness(population[i]);
            
        gFitness[gen-1] = bestFit;
        

        // load fitnesses into array.
        for (int i = 0; i < populationSize; i++)
            fitnesses[i] = fitness(population[i]); // tabulate fitnesses.
        
        
        //Organism *fittest = new Organism[populationSize/2]; //find the fittest half of the population and store them. These will be mated.
        Organism *fittest = new Organism[populationSize/2];
        //int fit1, fit2; //two fittest indexes.
        
        
        // find the fittest organisms. k being the index of fit0000111100001111test organisms.
        for (int k = 0; k < populationSize/2; k++)
        {
            bestFit = 0;
            iFitIndex = 0;
            
            for (int i = 0; i < populationSize; i++)
            {
                if (fitnesses[i] > bestFit) 
                {
                    bestFit = fitnesses[i];
                    iFitIndex = i;
                    
                }
            }
            fittest[k] = population[iFitIndex]; //store the fittest organsim in fittest[k]
            fitnesses[iFitIndex] = 0; // eliminate the fittest to find the second fittest
        
        }
        
        // at this point we have an array full of the fittest organisms.
        // we now need to mate them all, and acquire child organisms to fill the lost half of population.
        
        for (int i = 0; i < populationSize/2; i=i+2)
        {
            mate(fittest[i], fittest[i+1]);
        }
        // now we have a fully populated fittest array with the very fittest organisms only.
        // when using this function all we have to do is copy these fittest back into the population.
        
        // now place all fittest back into population.
        for (int i = 0; i < populationSize/2; i++)
            population[i] = fittest[i];
        
       
        
        // at this point we still only have half of the original population, so we need to repopulate:
        // we can take two approaches now, either reproduce with random parents or sequentially.
        // but for variety sake we will reproduce with random parents of the fittest.
      
        for (int i = (populationSize/2); i<populationSize; i++)
        {
            int parent1 = (rand() % (populationSize/2));
            int parent2 = (rand() % (populationSize/2));
            
            while (parent1 == parent2) // ensures that we do not mate the same organism with itself, lol
                parent2 = (rand() % (populationSize/2));
            
            population[i] = reproduce(population[parent1], population[parent2]);
            
        }
        
        
        // At this point we are done, half of the population is mated parents 
        // and the other half of the population is repopulated with fitter child organisms from reproduction
        if ((gen)%10 == 0) // set to gen%5 for every n generations to print.
        {
            cout << "Generation " << gen << endl;
            printPopulation();
        }
        // memory cleanup.
        if (fitnesses)
            delete[] fitnesses;
            
        if (fittest)
            delete[] fittest;
          
        for (int i = 0; i < populationSize; i++)
        {
            if (fitness(population[i]) == population[0].getMaxFitness())
            {   
                cout << "---" << endl << "Evolution Complete in " << gen << " generations" << endl;
                printPopulation();
                cout << endl;
                gSize = gen;
                gFitness[gen-1] = population[0].getMaxFitness();
                printFitGraph();
                exit(EXIT_SUCCESS);
            }
        }
           
       
    } // generation loop close.
    
    if (gFitness)
        delete[] gFitness;
}

void Controller::printFitGraph() const
{
    
    cout << "----" << endl << "Evolution of best fitnesses per generation: " << endl;

    for (int i = 0; i < gSize; i++)
    {
        cout << gFitness[i] << " ~> ";
    
   
    } 
    cout << "done";
    cout << endl << "----" << endl;
}