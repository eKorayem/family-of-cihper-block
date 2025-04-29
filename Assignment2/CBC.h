#ifndef CBC_H
#define CBC_H

#include "CipherBlock.h"

/**
 * CBC (Cipher Block Chaining) mode
 * In this mode, each block is XORed with the previous ciphertext block
 * before being encrypted. For the first block, an Initialization Vector (IV)
 * is used as the previous block.
 */
class CBC : public CipherBlock {
private:
    // Initialization Vector
    vector<unsigned char> iv;

public:
    /**
     * Constructor
     * @param key Encryption/decryption key
     * @param iv Initialization Vector (must be the same size as the block size)
     * @param blockSize Size of each block in bytes (default: 16)
     * @throws std::invalid_argument if IV size doesn't match block size
     */
    CBC(const vector<unsigned char>& key, const vector<unsigned char>& iv, size_t blockSize = 16);

    /**
     * Encrypt data using CBC mode
     * @param data Data to encrypt
     * @return Encrypted data
     */
    vector<unsigned char> encrypt(const vector<unsigned char>& data) override;

    /**
     * Decrypt data using CBC mode
     * @param data Data to decrypt
     * @return Decrypted data
     */
    vector<unsigned char> decrypt(const vector<unsigned char>& data) override;
};

#endif // CBC_H