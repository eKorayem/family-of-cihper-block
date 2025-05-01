#ifndef SHA1_H
#define SHA1_H

#include <iostream>
#include <cstring>

class SHA1 {
private:
    unsigned int h0, h1, h2, h3, h4;
    char hexChars[17] = "0123456789abcdef";

    unsigned int leftRotate(unsigned int value, unsigned int count);

public:
    SHA1();
    void compute(const char* message, unsigned int length, char output[41]);
};

#endif // SHA1_H
