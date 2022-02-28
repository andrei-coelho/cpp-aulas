/**
 * 
 * @file sha256.cpp
 * @author Andrei Coelho
 * @version 0.1
 * @date 2022-02-23
 * 
 * @details
 *      Este é um código que eu criei do algorítmo 
 *      SHA-256 para fins de estudo.
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

std::bitset<32> bitsetAdd(std::bitset<32> x, std::bitset<32> y)
{
    bool carry = false;
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
 * @brief  função para expandir o bloco de 15 palavras para 64 palavras
 *         usando a seguinte formula
 *         t0 = (w[i-15] >>  7) xor (w[i-15] >> 18) xor (w[i-15] >>>  3)
 *         t1 = (w[i-2]  >> 17) xor (w[i-2]  >> 19) xor (w[i-2]  >>> 10)
 *         w[i] = w[i-16] + w[i-7] + t0 + t1
 * @param  bloc 
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


/**
 * @brief função para gerar um bloco da mensagem
 * 
 * @param part_message 
 * @param last_block 
 * @param endBytes 
 * @return std::vector<std::bitset<32> > 
 */
std::vector<std::bitset<32> > gen_block(std:: string part_message, bool last_block = false, std::bitset<32> endBytes = std::bitset<32> (0x00)){
    
    std::bitset<8>  oneByte  = std::bitset<8> (0x80);
    std::bitset<8>  zeroByte = std::bitset<8> (0x00);
    size_t msg_size = part_message.length();


    size_t max_words = last_block ? 14 : 16;
    std::vector<std::bitset<8> > words;
    std::vector<std::bitset<32> > bloc;

    for (size_t i = 0; i < msg_size; i++)
    {
       if(words.size() == 4){
            // gera a palavra de 32 bits e insere no bloco
            // zera o bloco
            std::bitset<32> _word = concat_bytes(concat_bytes(words[0], words[1]), concat_bytes(words[2], words[3]));
            bloc.push_back(_word);
            words.clear();
       }

        words.push_back(char_to_byte(part_message[i]));
    }
    
    bool init = true;

    if(words.size() != 0){
        for (size_t i = 0; i < words.size(); i++)
        {
            if(words.size() == 4){
                std::bitset<32> _word = concat_bytes(concat_bytes(words[0], words[1]), concat_bytes(words[2], words[3]));
                bloc.push_back(_word);
                words.clear();
            }
            words.push_back((init ? oneByte : zeroByte));
            init = false;
        }
        
    }

    while (bloc.size() <= max_words)
    {
        std::bitset<32> _word_32 = init ? 
            concat_bytes(concat_bytes(oneByte , zeroByte), concat_bytes(zeroByte, zeroByte)) :
            concat_bytes(concat_bytes(zeroByte, zeroByte), concat_bytes(zeroByte, zeroByte)) ;

        init = false;
        bloc.push_back(_word_32);
    }
    
    if(last_block) bloc.push_back(endBytes);
    return bloc;
}


/**
 * @brief função para gerar a lista de blocos da mensagem
 * 
 * @param message 
 * @return const std::vector<std::vector<std::bitset<32> > > 
 */
std::vector<std::vector<std::bitset<32> > > pre_processing_message(std::string message){
    
    std::vector<std::vector<std::bitset<32> > > blocs;
    std::vector<std::string> message_parts;
    size_t max_char_bloc = 55;
    size_t siz_char_bloc = 64;
    size_t msg_size = message.length();
    std::bitset<32> endBytes = std::bitset<32>(msg_size * 8);

    if(msg_size > max_char_bloc){
        size_t i = 0;
        while (msg_size > i) {
            std::string part = message.substr(i, max_char_bloc);
            message_parts.push_back(part);
            i += max_char_bloc;
        }
    } else {
        message_parts.push_back(message);
    }

    std::vector<std::bitset<32> > lastBlock = gen_block(message_parts[message_parts.size()-1], true, endBytes);
    size_t max_blocs = message_parts.size()-1;
    for (size_t i = 0; i < max_blocs; i++) blocs.push_back(gen_block(message_parts[i]));
    blocs.push_back(lastBlock);

    return blocs;

}

/**
 * @brief gera o hash da mensagem
 * 
 * @param message 
 * @return std::string 
 */
std::string sha256(std::string message){
    
    initialize_H();

    std::vector<std::vector<std::bitset<32> > > blocs = pre_processing_message(message);

    for (size_t i = 0; i < blocs.size(); i++){
       
        std::bitset<32> a = H[0];
        std::bitset<32> b = H[1];
        std::bitset<32> c = H[2];
        std::bitset<32> d = H[3];
        std::bitset<32> e = H[4];
        std::bitset<32> f = H[5];
        std::bitset<32> g = H[6];
        std::bitset<32> h = H[7];
        
        std::vector<std::bitset<32> > blocs_ex = bloc_expansion(blocs[i]);

        for (size_t y = 0; y < blocs_ex.size(); y++)
        {
            std::bitset<32> s1 = rotate(e, 6) ^ rotate(e, 11) ^ rotate(e, 25);
            std::bitset<32> ch = (e & f) ^ (~e & g);
            std::bitset<32> t1 = bitsetAdd(bitsetAdd(bitsetAdd(h,s1), bitsetAdd(ch, K[y])),blocs_ex[y]);

            std::bitset<32> s0 = rotate(a, 2) ^ rotate(a, 13) ^ rotate(a, 22);
            std::bitset<32> mj = (a & b) ^ (a & c) ^ (b & c);
            std::bitset<32> t2 = bitsetAdd(s0, mj);

            h = g; g = f; f = e; e = bitsetAdd(d, t1); d = c; c = b; b = a; a = bitsetAdd(t1,t2);
        }

        H[0] = bitsetAdd(H[0], a);
        H[1] = bitsetAdd(H[1], b);
        H[2] = bitsetAdd(H[2], c);
        H[3] = bitsetAdd(H[3], d);
        H[4] = bitsetAdd(H[4], e);
        H[5] = bitsetAdd(H[5], f);
        H[6] = bitsetAdd(H[6], g);
        H[7] = bitsetAdd(H[7], h);
   
    }

    std::string res = bytes_to_hex(H);
    H.clear();

    return res;
}


int main()
{
    std::string res = sha256("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    std::cout << res << "\n";
    system("pause");
    return 0;
}
