/* 
 * File:   main.cpp
 * Author: d-savant
 *
 * Created on 20 September 2013, 9:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <sys/time.h>
#include <iomanip>
#include "Controller.h"
#include "binaryNumber.h"

using namespace std;

int main(int argc, char** argv) {
   
    //prerequired directives:
    int seed;
    timeval t1;
    gettimeofday(&t1, NULL);
    seed = t1.tv_usec * t1.tv_sec;
    srand(seed);
    //end of required start of main:
    
    int pop = 4;
    string input;
    
    string sSep = ":::::::::::::::::::::::::\n";
    string geneCode = "11111111";
    
    cout << sSep;
    cout << setfill(':') <<  setw(25) << left << ":::Genetic Algorithm 1" << endl;
    cout << setfill(':') <<  setw(25) << left << ":::::by Jaime Fouche" << endl;
    cout << sSep;
    cout << "A time seed is used for " << endl;
    cout << "random gene association" << endl;
    cout << sSep;
    
    cout << "Enter an initial population size (type help for help): ";
    cin >> input;
    
    for (int i = 0; i < input.length(); i++)
        input[i] = toupper(input[i]);
    
    if ((input) == ("HELP") || input[0] == 'H')
    {
        //help code
        cout << "----" << endl;
        cout << "Help: " << endl;
        cout << "----" << endl;
    }
    else
    {
        pop = atoi(input.c_str());
        while ((pop % 4 != 0) && (pop <= 0))
        {
        cout << "Invalid population size. Pop. Size must be a factor of 4." << endl;
        cout << "Enter an initial population size (type help for help): ";
        cin >> pop;
        }
    }
    cout << "Enter a target genotype: ";
    cin >> geneCode;
    while (geneCode.length() % binaryNumber::numBits != 0)
    {
        cout << "Invalid genecode entered, must be of " << binaryNumber::numBits << "bit factor" << endl;
        cout << "Enter a target genotype: ";
        cin >> geneCode; 
    }
    
    //create the goal organism:
    Organism orgDef(geneCode); //target organism to evolve. Genecode as string.
    
    
    cout << "The target/goal organism: " << endl << sSep;
    orgDef.printDetails();
    
    cout << "----" << endl;
    Controller controller(pop, orgDef);
    controller.printPopulation();
    
    cout << "Running evolution for some generations..." << endl;
    controller.step(1000);
    
    controller.printFitGraph();
    
    return 0;
}

