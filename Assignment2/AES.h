// AES.h
#ifndef AES_H
#define AES_H

#include <vector>
#include <array>

class AES {
private:
    static const size_t BLOCK_SIZE = 16; // AES always uses 16-byte blocks
    size_t keySize;
    std::vector<unsigned char> key;
    std::vector<std::vector<unsigned char>> roundKeys;

    // AES internal functions
    void keyExpansion();
    void addRoundKey(std::vector<unsigned char>& state, size_t round);
    void subBytes(std::vector<unsigned char>& state);
    void shiftRows(std::vector<unsigned char>& state);
    void mixColumns(std::vector<unsigned char>& state);
    void invSubBytes(std::vector<unsigned char>& state);
    void invShiftRows(std::vector<unsigned char>& state);
    void invMixColumns(std::vector<unsigned char>& state);

public:
    enum KeySize {
        AES_128 = 16,
        AES_192 = 24,
        AES_256 = 32
    };

    AES(const std::vector<unsigned char>& key);
    std::vector<unsigned char> encryptBlock(const std::vector<unsigned char>& block);
    std::vector<unsigned char> decryptBlock(const std::vector<unsigned char>& block);
    static size_t getBlockSize() { return BLOCK_SIZE; }
};

#endif // AES_H