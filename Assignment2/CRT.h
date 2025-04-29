#ifndef CTR_H
#define CTR_H

#include "CipherBlock.h"

/**
 * CTR (Counter) mode
 * In this mode, a counter is encrypted and then XORed with the plaintext to produce
 * the ciphertext. The counter is incremented for each block.
 *
 * Advantages:
 * - Parallelizable (does not depend on previous blocks)
 * - Random access to any block possible
 * - Does not require padding
 * - Self-synchronizing
 */
class CTR : public CipherBlock {
private:
    // Nonce combined with counter for generating keystream
    std::vector<unsigned char> nonce;

    /**
     * Generate the counter block for a given block index
     * @param blockIndex The index of the block
     * @return The counter block
     */
    std::vector<unsigned char> generateCounterBlock(size_t blockIndex) const;

public:
    /**
     * Constructor
     * @param key Encryption/decryption key
     * @param nonce Nonce value (must be smaller than block size)
     * @param blockSize Size of each block in bytes (default: 16)
     * @throws std::invalid_argument if nonce size is invalid
     */
    CTR(const std::vector<unsigned char>& key,
        const std::vector<unsigned char>& nonce,
        size_t blockSize = 16);

    /**
     * Encrypt data using CTR mode
     * @param data Data to encrypt
     * @return Encrypted data
     */
    std::vector<unsigned char> encrypt(const std::vector<unsigned char>& data) override;

    /**
     * Decrypt data using CTR mode
     * Note: In CTR mode, the encryption and decryption operations are identical
     * @param data Data to decrypt
     * @return Decrypted data
     */
    std::vector<unsigned char> decrypt(const std::vector<unsigned char>& data) override;
};

#endif // CTR_H