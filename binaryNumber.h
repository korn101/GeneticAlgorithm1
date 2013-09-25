/* 
 * File:   binaryNumber.h
 * Author: d-savant
 *
 * Created on 20 September 2013, 9:57 PM
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

