#ifndef ECB_H
#define ECB_H

#include "CipherBlock.h"

/**
 * ECB (Electronic Codebook) mode
 * In this mode, each block is encrypted independently.
 * Note: This mode is generally not recommended for secure applications
 * as identical plaintext blocks will generate identical ciphertext blocks.
 */
class ECB : public CipherBlock {
public:
    /**
     * Constructor
     * @param key Encryption/decryption key
     * @param blockSize Size of each block in bytes (default: 16)
     */
    ECB(const std::vector<unsigned char>& key, size_t blockSize = 16);

    /**
     * Encrypt data using ECB mode
     * @param data Data to encrypt
     * @return Encrypted data
     */
    std::vector<unsigned char> encrypt(const std::vector<unsigned char>& data) override;

    /**
     * Decrypt data using ECB mode
     * @param data Data to decrypt
     * @return Decrypted data
     */
    std::vector<unsigned char> decrypt(const std::vector<unsigned char>& data) override;
};

#endif // ECB_H