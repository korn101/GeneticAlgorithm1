/* 
 * File:   Organism.h
 * Author: d-savant
 *
 * Created on 20 September 2013, 9:55 PM
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

#ifndef GENE_H
#define	GENE_H

#include "binaryNumber.h"
#include <string>
#include <cstdlib> //only for error handling.
#include <iostream> //ditto

const static char SEPERATOR = '-';

class Organism {
public:
    Organism();
    Organism(int, int); // initialize an organism with only 2 genes, pass integer values for each respective gene.
    Organism(int arr[]); // initalize an organisms genecode with an array of integers, each index representing a new gene.
    Organism(const Organism& other); // Copy constructor (with deep copy functionality)
    Organism(std::string geneCode); // initialise an organism with a genetic code in form of a string. Supports higher size noOfGenes than 2
    virtual ~Organism(); //destructor for dynamic memory cleanup.
    
    int getMaxFitness(); // simply returns an int representing the best possible fitness capable of the organisms chromosome.
    
    void mutate(); // force probability mutation of all genes
    void printChromosome() const; //prints the chromosome model. Seperated by SEPERATOR
    void printDetails() const; //print all info, not practical unless in debug situations really..
    
    friend void crossover(Organism& first, Organism& second); // perform a genetic crossover of first and second. WARNING first and second will CHANGE.    
    friend int compare(const Organism& first, const Organism& second); // comparison function returns an integer based on how close the two organisms are)
    friend void mate(Organism& first, Organism& second); //mate two organisms replacing them with their offspring. WARNING first and second will CHANGE.
    friend Organism reproduce(const Organism& first, const Organism& second); //mate two Organisms, mutate and return the child Organism.
    
    //overloaded operators:
    bool &operator[](int index); //subscript operator to return the actual gene bit at index from the 8 bit (4bit 2 part) chromosome
    const bool operator[](int index) const;
    Organism& operator=(const Organism& other);
    
    int getNoOfGenes(); //return noOfGenes
    
private:
    
    static int noOfGenes; //how many genes it contains. (can be an even number)
    const static float mutRate = 1; // represents percentage chance of mutation per bit. Good value seems to be 1% - 5%
    binaryNumber * chromosome; // dynamic array of binaryNumbers (genes) which represents the organisms chromosome.
    
    void error(std::string message) const //very basic exception handler.
    {
        std::cout << std::endl << "::Error: " << message << "::" << std::endl << "----" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    // NOTE: setting mutation rate too high seems to obscure the linearity of the evolution. ie. backward evolution
    // however; setting it too low means hardly any genetic diversity meaning almost NO evolution at all.
    // NOTE: mutRate may not be lower than 0.1, the algorithm only supports 1 decimal place right now, not two. eg. 0.01
    
};



#endif	/* GENE_H */

