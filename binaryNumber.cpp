/* 
 * File:   binaryNumber.cpp
 * Author: d-savant
 * 
 * Created on 20 September 2013, 9:57 PM
 */

#include "binaryNumber.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

binaryNumber::binaryNumber() 
{
    //default constructor for binary number. Sets all bits to 0
    
    for (int i = 0; i < numBits; i++)
        bits[i] = 0;
    
}

binaryNumber::binaryNumber(int inp)
{
    //takes an int as input, checks if in range and allocates it accordingly.
    //default constructor for binary number.
    for (int i = 0; i < numBits; i++)
        bits[i] = 0;

    if (inp <= pow(2, numBits) - 1) //check if the value is actually representable with the given number of bits allowed.
    {
        int num = inp; // temp location.
        //convert input to binary:
        for (int i = 0; i < numBits; i++)
        {   
            if (num % 2 != 0)
                bits[(numBits-1)-i] = 1;
            num = num / 2;
            
        }
        
    }
    else
    {
        cout << "Error: Binary Number allocation fell out of range of the set number of bits" << endl;
        exit(EXIT_FAILURE);
    }
    
}

binaryNumber::binaryNumber(const binaryNumber& other) 
{

    for (int i = 0; i < other.numBits; i++)
        bits[i] = other.bits[i];    
    
}

binaryNumber::binaryNumber(string gene)
{
    
    if (gene.length() == numBits)
    {
        for (int i = 0; i < gene.length(); i++)
            bits[i] = (bool)gene[i];
        
    }
    else
    {
        cout << "Error: Specified Gene string does not match set gene bitlength" << endl;
        exit(EXIT_FAILURE);
    }
    
    
}


binaryNumber::~binaryNumber() 
{
}

void binaryNumber::print() const
{
    for (int i = 0; i < numBits; i++)
        cout << bits[i];
}

bool binaryNumber::operator[](int index) const
{
    return (bits[index]);
}

bool & binaryNumber::operator[](int index)
{
    return (bits[index]);
}

binaryNumber & binaryNumber::operator=(const binaryNumber& other)
{
    for (int i = 0; i < other.numBits; i++)
        bits[i] = other.bits[i];
}