/**
 * 
 * @file sha256.cpp
 * @author Andrei Coelho
 * @version 0.1
 * @date 2022-02-23
 * 
 * @details
 *      Este é um código que eu criei do algorítmo 
 *      SHA-256 para fins de estudo do tutorial:
 * 
 *      https://www.youtube.com/watch?v=ElugJOU5XyQ&list=PLqLkgoa8tYcU0NI9WVvX-Qm6Bzh-wvBgE&index=1
 * 
 *      Apesar de funcionar corretamente, eu não recomendo
 *      substituir este código por bibliotecas já consagradas
 * 
 * 
 * Be happy =)
 *  
 *      to compile > g++ sha256.cpp -o sha256.exe -std=c++0x
 * 
 */

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <bitset>
#include <cstdlib>

std::vector<std::bitset<32> > K = { 
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

std::vector<std::bitset<32> > H;

template <size_t N1, size_t N2 >
std::bitset <N1 + N2> concat_bytes( const std::bitset <N1> & b1, const std::bitset <N2> & b2 ) {
    return std::bitset <N1 + N2>( b1.to_string() + b2.to_string() );
}

template <std::size_t N> 
std::bitset<N> rotate(std::bitset<N> b, unsigned m) { 
   b = b >> m | b << (N-m); 
   return b;
}

bool fullAdder(bool b1, bool b2, bool& carry)
{
    bool sum = (b1 ^ b2) ^ carry;
    carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
    return sum;
}
// Function to add two bitsets
std::bitset<32> bitsetAdd(std::bitset<32> x, std::bitset<32> y)
{
    bool carry = false;
    // bitset to store the sum of the two bitsets
    std::bitset<32> ans;
    for (int i = 0; i < 32; i++) {
        ans[i] = fullAdder(x[i], y[i], carry);
    }
    return ans;
}

std::bitset<8> char_to_byte(char c){
    std::stringstream ss;
    ss << std::hex << (int)c;
    unsigned n;
    ss >> n;
    std::bitset<8> b(n);
    return b;
}

void initialize_H(){
    H.push_back(std::bitset<32>(0x6a09e667));
    H.push_back(std::bitset<32>(0xbb67ae85));
    H.push_back(std::bitset<32>(0x3c6ef372));
    H.push_back(std::bitset<32>(0xa54ff53a));
    H.push_back(std::bitset<32>(0x510e527f));
    H.push_back(std::bitset<32>(0x9b05688c));
    H.push_back(std::bitset<32>(0x1f83d9ab));
    H.push_back(std::bitset<32>(0x5be0cd19));
}

std::string bytes_to_hex(std::vector<std::bitset<32> > msg_bytes){

    size_t size = msg_bytes.size();
    std::string rfinal;

    for (size_t i = 0; i < size; i++){   
        
        std::bitset<32> msg_byte = msg_bytes[i];
        std::stringstream res;
        std::string r;
        
        res << std::hex << msg_byte.to_ulong();
        r = res.str();
        rfinal += r;
    }
    
    return rfinal;
}

/**
 * @brief função para gerar os blocos da mensagem 
 * 
 * @param message 
 * @return const std::vector<std::vector<std::bitset<32> > > 
 */
const std::vector<std::vector<std::bitset<32> > > message_blocs(std::string message){
    
    std::vector<std::vector<std::bitset<32> > > blocs;
    std::vector<std::string> message_parts;
    
    size_t max_size = 56;
    size_t msg_size = message.length();
    std::bitset<32> msg_len_bits = std::bitset<32>(msg_size * 8);
    
    if(msg_size > max_size){
        size_t i = 0;
        while (msg_size > i) {
            std::string part = message.substr(i, max_size);
            message_parts.push_back(part);
            i += max_size;
        }
    } else {
        message_parts.push_back(message);
    }

    size_t msg_parts_size = message_parts.size();
    for (size_t y = 0; y < msg_parts_size; y++) {
        
        std::vector<std::bitset<32> > bloc;
        std::string msg_part = message_parts[y];
        size_t msg_part_len = msg_part.length();
        
        std::vector<std::bitset<8> > word; // 4 bytes -> 32 bits

        for (size_t w = 0; w < msg_part_len; w++) {
            
            word.push_back(char_to_byte(msg_part[w]));

            if(word.size() == 4){
                std::bitset<32> _word = concat_bytes(concat_bytes(word[0], word[1]), concat_bytes(word[2], word[3]));
                bloc.push_back(_word);
                word.clear();
            }

        }

        bool one_bit = true;

        if(word.size() > 0){
            
            size_t maxR  =  4 - word.size();
            for (size_t i = 0; i < maxR; i++){
                if(one_bit){
                    word.push_back(std::bitset<8>(0x80));
                    one_bit = false;
                    continue;
                }
                word.push_back(std::bitset<8>(0x0));
            }

            std::bitset<32> _word = concat_bytes(concat_bytes(word[0], word[1]), concat_bytes(word[2], word[3]));
            bloc.push_back(_word);
            word.clear();
        }

        while (bloc.size() < 14) {
            
            if(one_bit){
                bloc.push_back(std::bitset<32>(0x80000000));
                one_bit = false;
                continue;
            }

            bloc.push_back(std::bitset<32>(0x0));
        }
        
        bloc.push_back(std::bitset<32>(0x0));
        bloc.push_back(msg_len_bits);
        blocs.push_back(bloc);
    }
    
    return blocs;
    
}

/**
 * @brief função para expandir o bloco de 15 palavras para 64 palavras
 *        usando a seguinte formula
 *        t0 = (w[i-15] >>  7) xor (w[i-15] >> 18) xor (w[i-15] >>>  3)
 *        t1 = (w[i-2]  >> 17) xor (w[i-2]  >> 19) xor (w[i-2]  >>> 10)
 *        w[i] = w[i-16] + w[i-7] + t0 + t1
 * @param bloc 
 * @return std::vector<std::bitset<32> > 
 */
std::vector<std::bitset<32> > bloc_expansion(std::vector<std::bitset<32> > bloc){

    for(size_t i = 16; i < 64; i++){
        
        std::bitset<32> t0 = rotate(bloc[i-15], 7) ^ rotate(bloc[i-15], 18) ^ (bloc[i-15] >>  3);
        std::bitset<32> t1 = rotate(bloc[i-2], 17) ^ rotate(bloc[i-2],  19) ^ (bloc[i-2] >>  10);
        bloc.push_back(bitsetAdd(bitsetAdd(t0, t1), bitsetAdd(bloc[i-16], bloc[i-7])));

    }

    return bloc;
}

std::string hash256(std::string message){
    
    initialize_H();

    std::vector<std::vector<std::bitset<32> > > blocs = message_blocs(message);

    for (size_t i = 0; i < blocs.size(); i++){
        
        std::vector<std::bitset<32> > blocs_ex = bloc_expansion(blocs[i]);

        for (size_t y = 0; y < blocs_ex.size(); y++)
        {
            std::bitset<32> a = H[0];
            std::bitset<32> b = H[1];
            std::bitset<32> c = H[2];
            std::bitset<32> d = H[3];
            std::bitset<32> e = H[4];
            std::bitset<32> f = H[5];
            std::bitset<32> g = H[6];
            std::bitset<32> h = H[7];
            
            std::bitset<32> s1 = rotate(e, 6) ^ rotate(e, 11) ^ rotate(e, 25);
            std::bitset<32> ch = (e & f) ^ (~e & g);
            std::bitset<32> t1 = bitsetAdd(bitsetAdd(bitsetAdd(h,s1), bitsetAdd(ch, K[y])),blocs_ex[y]);

            std::bitset<32> s0 = rotate(a, 2) ^ rotate(a, 13) ^ rotate(a, 22);
            std::bitset<32> mj = (a & b) ^ (a & c) ^ (b & c);
            std::bitset<32> t2 = bitsetAdd(s0, mj);

            h = g; g = f; f = e; e = bitsetAdd(d, t1); d = c; c = b; b = a; a = bitsetAdd(t1,t2);

            H[0] = bitsetAdd(H[0], a);
            H[1] = bitsetAdd(H[1], b);
            H[2] = bitsetAdd(H[2], c);
            H[3] = bitsetAdd(H[3], d);
            H[4] = bitsetAdd(H[4], e);
            H[5] = bitsetAdd(H[5], f);
            H[6] = bitsetAdd(H[6], g);
            H[7] = bitsetAdd(H[7], h);

        }
        

    }

    

    std::string res = bytes_to_hex(H);
    H.clear();
    return res;
}

int main()
{
    std::string res = hash256("string mnbsdamn,bdsn,mabf kjhdfjhasdifhklajshfkjlashfjksda kjhadsfjkhasfkjhasdf kjhdasfjkashdf");
    // 473287f8298dba7163a897908958f7c0eae733e25d2e027992ea2edc9bed2fa8
    // 473287f8298dba7163a897908958f7c0eae733e25d2e027992ea2edc9bed2fa8
    std::cout << res << "\n";
    system("pause");
    return 0;
}
