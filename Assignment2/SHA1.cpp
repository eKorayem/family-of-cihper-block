#include "SHA1.h"

SHA1::SHA1() {
    h0 = 0x67452301;
    h1 = 0xEFCDAB89;
    h2 = 0x98BADCFE;
    h3 = 0x10325476;
    h4 = 0xC3D2E1F0;
}

unsigned int SHA1::leftRotate(unsigned int value, unsigned int count) {
    return (value << count) | (value >> (32 - count));
}

void SHA1::compute(const char* message, unsigned int length, char output[41]) {
    unsigned char data[64] = { 0 };
    for (unsigned int i = 0; i < length; i++)
        data[i] = message[i];

    data[length] = 0x80;
    unsigned long long bitLength = length * 8;

    for (int i = 0; i < 8; i++)
        data[56 + i] = (bitLength >> (8 * (7 - i))) & 0xFF;

    unsigned int w[80];
    for (int i = 0; i < 16; i++) {
        w[i] = (data[i * 4] << 24) | (data[i * 4 + 1] << 16) |
            (data[i * 4 + 2] << 8) | data[i * 4 + 3];
    }

    for (int i = 16; i < 80; i++) {
        w[i] = leftRotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    }

    unsigned int a = h0, b = h1, c = h2, d = h3, e = h4;

    for (int i = 0; i < 80; i++) {
        unsigned int f, k;
        if (i < 20)
            f = (b & c) | (~b & d), k = 0x5A827999;
        else if (i < 40)
            f = b ^ c ^ d, k = 0x6ED9EBA1;
        else if (i < 60)
            f = (b & c) | (b & d) | (c & d), k = 0x8F1BBCDC;
        else
            f = b ^ c ^ d, k = 0xCA62C1D6;

        unsigned int temp = leftRotate(a, 5) + f + e + k + w[i];
        e = d;
        d = c;
        c = leftRotate(b, 30);
        b = a;
        a = temp;
    }

    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;

    unsigned int hashValues[] = { h0, h1, h2, h3, h4 };
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            output[i * 8 + j] = hexChars[(hashValues[i] >> (28 - j * 4)) & 0xF];
        }
    }

    output[40] = '\0';
}
