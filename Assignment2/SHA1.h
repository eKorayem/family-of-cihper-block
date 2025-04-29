//// sha1.h
//#ifndef SHA1_H
//#define SHA1_H
//
//#include <vector>
//#include <string>
//#include <cstdint>
//
//// SHA-1 implementation
//class SHA1 {
//private:
//    uint32_t h0, h1, h2, h3, h4;
//
//    void processBlock(const uint8_t* block);
//    static uint32_t leftRotate(uint32_t value, size_t count);
//
//public:
//    SHA1();
//    std::vector<uint8_t> hash(const std::vector<uint8_t>& message);
//    std::vector<uint8_t> hash(const std::string& message);
//};
//
//#endif // SHA1_H