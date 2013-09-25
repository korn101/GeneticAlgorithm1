/* 
 * File:   Organism.cpp
 * Author: d-savant
 * 
 * Created on 20 September 2013, 9:55 PM
 */

#include "Organism.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

//Background:
//An organism is an object which contains chromosomes, chromosomes are made of genes which determine traits.
//This organism only has one chromosome. But it is fairly easy to implement a chromosome object and use an array to have multiple.

int Organism::noOfGenes = 2; // set the DEFAULT chromosome length (how many genes it has).

Organism::Organism()
{
    //first initialize chromosome.
    //creation of an organisms chromosomes, assign genes to chromosome with genes being random integers of a seed.
    //for the sake of pseudo-randomness we use a seed. (set in the main)
    
    //allocate dynamic array of default chromosome length size.
    chromosome = new binaryNumber[noOfGenes];
    
    //determine number of possible integer values that can be represented:
    int iRange = pow(2, binaryNumber::numBits);
    
    //initialize genes to random values
    for (int i = 0; i < noOfGenes; i++)
        chromosome[i] = binaryNumber(rand() % iRange); // should be 10
    
    
}

Organism::Organism(int gene1, int gene2)
{
    noOfGenes = 2; // this constructor implies that only 2 genes exist, so set accordingly.
    chromosome = new binaryNumber[noOfGenes];
    
    //constructor that initializes an organism with the given integer representation of genes.
    chromosome[0] = binaryNumber(gene1);
    chromosome[1] = binaryNumber(gene2);
    
}

Organism::Organism(int arr[])
{
    int count = 0; // sizeof array.
    // count elements in array.
    for (int i = 0; &arr[i] != 0; i++)
        count++;
    
    noOfGenes = count;
    chromosome = new binaryNumber[noOfGenes];
    
    // now allocate genes:
    for (int i = 0; i < noOfGenes; i++)
        chromosome[i] = binaryNumber(arr[i]);
   
}

Organism::Organism(const Organism& other) 
{
    noOfGenes = other.noOfGenes;
    chromosome = new binaryNumber[noOfGenes];
    
    for (int i = 0; i < other.noOfGenes; i++)
        for (int k = 0; k < other.chromosome[0].numBits; k++)
            chromosome[i][k] = other.chromosome[i][k];
    
}

Organism::Organism(string geneCode) // initialise an organism with a genetic code in form of a string.
{ 
    //determine number of genes there are in the geneCode.
    binaryNumber temp; //create this temp just to get the numBits.
    noOfGenes = geneCode.length() / temp.numBits; 
    
    //allocate dynamic memory
    chromosome = new binaryNumber[noOfGenes];
    
    
    if (geneCode.length() == (noOfGenes*temp.numBits) && geneCode.length() % 2 == 0)
    {
        int geneSize = geneCode.length() / noOfGenes; //size of individual genes
    
        for (int i = 0 ; i<noOfGenes; i++)
                for (int k = 0; k<(geneSize); k++)
                {
                    bool bit = 0;
                    if (geneCode[k+(i*geneSize)] == '1')
                        bit = 1;
                    chromosome[i][k] = bit;
                }
                        
    
        // The above code loops through the string initializing the individual bits in the chromosome to those corresponding in the geneCode string
    }
    else
    {
        if (geneCode.length() % 2 != 0)
            cout << "Error: Trying to initialise an organism with an ODD bitlength genecode." << endl;
        
        if (geneCode.length() != (noOfGenes*temp.numBits))
            cout << "Error: Chromosome Genecode size mismatch" << endl;
        
        exit(EXIT_FAILURE);
    }
}

Organism::~Organism() 
{

    if (chromosome)
        delete[] chromosome;

}

int Organism::getNoOfGenes()
{
    return noOfGenes;
}
int Organism::getMaxFitness()
{
    // return the total length of the chromosome. ie. 8 if 2 * 4bit genes.
    return (chromosome[0].numBits * noOfGenes);
}

void Organism::mutate()
{
    if (mutRate < 0.1 || mutRate > 100)
        error("Organism mutation rate was set out of bounds");
    
    // this function forces chance mutation determined by a determined probability (declared in the Organism header)
    // iterate through the bits, generate a random number between 0-1000 and if it is 1, then perform a mutation/flip.
    for (int i = 0; i < noOfGenes; i++)
        for (int k = 0; k < chromosome[0].numBits; k++)
        {
            //check the probability:
            int random = (rand() % 1000); //produce a number between 0-999
            bool doMut = 0;
            if (random <= mutRate * 10) // high mutation rate is 10 = 1%, low would be 1 which is = 0.1%
                doMut = 1;
            
            if (doMut == 1) //if the generated number is within probability
            {
                chromosome[i][k] = !chromosome[i][k]; // flip the bit, yo
            }
            
        }
    
    
}

void Organism::printChromosome() const
{
    //iterate through genes and print them.
    for (int i = 0; i < noOfGenes-1; i++)
    {
        chromosome[i].print();
        cout << SEPERATOR;
    }
    chromosome[noOfGenes-1].print(); //simply prevents dangling '-' in print.
}

int compare(const Organism& first, const Organism& second)
{
    // count number of shared bits, and return result:
    int count = 0;
    
    //check that organisms are of same chromosome lengths:
    if (first.noOfGenes != second.noOfGenes)
    {
        cout << "Error: Invalid Comparison of differing organism chromosome lengths!" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
    
        for (int i = 0; i < first.noOfGenes; i++)
            for (int k = 0; k < first.chromosome[0].numBits; k++)
                if (first.chromosome[i][k] == second.chromosome[i][k])
                        ++count;
    }   
    
    return count;
    
}


void crossover(Organism& first, Organism& second)
{
    Organism temp(first);

    //Choose a random bit along the length of the chromosomes, and swap from that point.
    int crossPoint = rand() % (first.noOfGenes * first.chromosome[0].numBits);
    // note that crossPoint is an index! ie. 0-7 not 1-8.

    //loop through crossing over up till the crossover point.
    for (int i = 0; i <= crossPoint; i++) {
        bool temp;
        temp = first[i];
        first[i] = second[i];

        second[i] = temp;
    }

    // for the sake of diversity, say the crossover produces the same organism once again -> Then mutate it, just for diversity.
    if ((compare(temp, first) == (first.chromosome[0].numBits * first.noOfGenes))) {
        first.mutate();
    }
    
}

void mate(Organism& first, Organism& second)
{
    //the mate function mates two organisms.
    //first, a genetic crossover is applied with the crossover() function.
    //second, chance mutation is invoked with the mutate() function.
    //the result being a replacement of the two passed organisms with their offspring.
    crossover(first, second);
    first.mutate();
    second.mutate();
    
}

Organism reproduce(const Organism& first, const Organism& second)
{
    Organism temp1(first);
    Organism temp2(second);
    mate(temp1,temp2);
    
    int toRet = rand() % 2;
    
    if (toRet = 0)
    {
        return (temp1);
    }
    else
    {
        return temp2;
    }
}

bool& Organism::operator[](int index)
{ 
    if (index > (chromosome[0].numBits - 1))
    {   
        //if the index falls outside the scope of the first 4 bits of the chromosome.
        return (chromosome[1][index-chromosome[0].numBits]);
        
    }
    else
        return (chromosome[0][index]);
}

const bool Organism::operator[](int index) const
{
    if (index > (chromosome[0].numBits - 1))
    {   
        //if the index falls outside the scope of the first 4 bits of the chromosome.
        return (chromosome[1][index-chromosome[0].numBits]);
        
    }
    else
        return (chromosome[0][index]);
    
}

Organism& Organism::operator=(const Organism& other)
{
    
    for (int i = 0; i < other.noOfGenes; i++)
        chromosome[i] = other.chromosome[i];
    
}

void Organism::printDetails() const
{
    cout << "No. of Genes: " << noOfGenes << endl;
    cout << "Gene Size (bits): " << chromosome[0].numBits << endl;
    cout << "Chromosome size (bits): " << noOfGenes*chromosome[0].numBits << endl;
    cout << "Chromosome: ";
    //iterate through genes and print them.
    for (int i = 0; i < noOfGenes; i++)
        chromosome[i].print();
    
    cout << endl;
    
}