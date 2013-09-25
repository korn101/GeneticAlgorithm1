/* 
 * File:   binaryNumber.h
 * Author: d-savant
 *
 * Created on 20 September 2013, 9:57 PM
 */

#ifndef BINARYNUMBER_H
#define	BINARYNUMBER_H

#include <string>

class binaryNumber {
public:
    binaryNumber();
    binaryNumber(int);
    binaryNumber(const binaryNumber& other);
    binaryNumber(std::string gene); // initialise a binaryNumber with a gene in form of a string
    virtual ~binaryNumber();
    void print() const;
    const static int numBits = 4; // genesize. VARIABLE but only in pre-compile
    bool operator[](int index) const;
    bool &operator[](int index);
    binaryNumber & operator=(const binaryNumber& other);
private:
    bool bits[numBits]; // numBits bit size binary number.

    
};

#endif	/* BINARYNUMBER_H */

