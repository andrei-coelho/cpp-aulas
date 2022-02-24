#include <vector>
#include <string>
#include <bitset>

std::vector<std::bitset<32> > constants_bytes_values = { 
std::bitset<32>(0x428a2f98), std::bitset<32>(0x71374491), std::bitset<32>(0xb5c0fbcf), std::bitset<32>(0xe9b5dba5),
std::bitset<32>(0x3956c25b), std::bitset<32>(0x59f111f1), std::bitset<32>(0x923f82a4), std::bitset<32>(0xab1c5ed5),
std::bitset<32>(0xd807aa98), std::bitset<32>(0x12835b01), std::bitset<32>(0x243185be), std::bitset<32>(0x550c7dc3),
std::bitset<32>(0x72be5d74), std::bitset<32>(0x80deb1fe), std::bitset<32>(0x9bdc06a7), std::bitset<32>(0xc19bf174),
std::bitset<32>(0xe49b69c1), std::bitset<32>(0xefbe4786), std::bitset<32>(0x0fc19dc6), std::bitset<32>(0x240ca1cc),
std::bitset<32>(0x2de92c6f), std::bitset<32>(0x4a7484aa), std::bitset<32>(0x5cb0a9dc), std::bitset<32>(0x76f988da),
std::bitset<32>(0x983e5152), std::bitset<32>(0xa831c66d), std::bitset<32>(0xb00327c8), std::bitset<32>(0xbf597fc7),
std::bitset<32>(0xc6e00bf3), std::bitset<32>(0xd5a79147), std::bitset<32>(0x06ca6351), std::bitset<32>(0x14292967),
std::bitset<32>(0x27b70a85), std::bitset<32>(0x2e1b2138), std::bitset<32>(0x4d2c6dfc), std::bitset<32>(0x53380d13),
std::bitset<32>(0x650a7354), std::bitset<32>(0x766a0abb), std::bitset<32>(0x81c2c92e), std::bitset<32>(0x92722c85),
std::bitset<32>(0xa2bfe8a1), std::bitset<32>(0xa81a664b), std::bitset<32>(0xc24b8b70), std::bitset<32>(0xc76c51a3),
std::bitset<32>(0xd192e819), std::bitset<32>(0xd6990624), std::bitset<32>(0xf40e3585), std::bitset<32>(0x106aa070),
std::bitset<32>(0x19a4c116), std::bitset<32>(0x1e376c08), std::bitset<32>(0x2748774c), std::bitset<32>(0x34b0bcb5),
std::bitset<32>(0x391c0cb3), std::bitset<32>(0x4ed8aa4a), std::bitset<32>(0x5b9cca4f), std::bitset<32>(0x682e6ff3),
std::bitset<32>(0x748f82ee), std::bitset<32>(0x78a5636f), std::bitset<32>(0x84c87814), std::bitset<32>(0x8cc70208),
std::bitset<32>(0x90befffa), std::bitset<32>(0xa4506ceb), std::bitset<32>(0xbef9a3f7), std::bitset<32>(0xc67178f2) };

std::vector<std::bitset<32> > H = { 
std::bitset<32>(0x6a09e667), std::bitset<32>(0xbb67ae85),
std::bitset<32>(0x3c6ef372), std::bitset<32>(0xa54ff53a),
std::bitset<32>(0x510e527f), std::bitset<32>(0x9b05688c),
std::bitset<32>(0x1f83d9ab), std::bitset<32>(0x5be0cd19) };

