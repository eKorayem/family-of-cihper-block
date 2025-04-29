#ifndef CIPHER_BLOCK_H
#define CIPHER_BLOCK_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

/**
 * CipherBlock - Base class for block cipher modes
 * Provides an interface for encryption and decryption operations
*/

class CipherBlock {
protected:
    // Block size in bytes
    const size_t blockSize;

    // Key for encryption/decryption
    vector<unsigned char> key;

    /**
     * Encrypt a single block using the cipher algorithm
     * @param block Block to encrypt
     * @return Encrypted block
     */
    virtual vector<unsigned char> encryptBlock(const vector<unsigned char>& block) const;

    /**
     * Decrypt a single block using the cipher algorithm
     * @param block Block to decrypt
     * @return Decrypted block
     */
    virtual std::vector<unsigned char> decryptBlock(const std::vector<unsigned char>& block) const;

    /**
     * Split the input data into blocks of blockSize
     * @param data Data to be split
     * @return Vector of data blocks
     */
    std::vector<vector<unsigned char>> splitIntoBlocks(const std::vector<unsigned char>& data) const;

public:
    /**
     * Constructor
     * @param key Encryption/decryption key
     * @param blockSize Size of each block in bytes (default: 16)
     * @throws std::invalid_argument if key is empty
     */
    CipherBlock(const vector<unsigned char>& key, size_t blockSize = 16);

    /**
     * Virtual destructor
     */
    virtual ~CipherBlock();

    /**
     * Encrypt data using the specific cipher mode
     * @param data Data to encrypt
     * @return Encrypted data
     */
    virtual std::vector<unsigned char> encrypt(const std::vector<unsigned char>& data) = 0;

    /**
     * Decrypt data using the specific cipher mode
     * @param data Data to decrypt
     * @return Decrypted data
     */
    virtual std::vector<unsigned char> decrypt(const std::vector<unsigned char>& data) = 0;

    /**
     * Convenience function to encrypt a string
     * @param str String to encrypt
     * @return Encrypted string
     */
    std::string encryptString(const std::string& str);

    /**
     * Convenience function to decrypt a string
     * @param str String to decrypt
     * @return Decrypted string
     */
    std::string decryptString(const std::string& str);

    static void print_hexa(string str);
};

#endif // CIPHER_BLOCK_H