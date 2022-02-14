#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

template <size_t N1, size_t N2 >
bitset <N1 + N2> concat( const bitset <N1> & b1, const bitset <N2> & b2 ) {
    string s1 = b1.to_string();
    string s2 = b2.to_string();
    return bitset <N1 + N2>( s1 + s2 );
}

std::bitset<4> to_bin(char c){
    stringstream ss;
    ss << hex << c;
    unsigned n;
    ss >> n;
    bitset<4> b(n);
    return b;
}

std::string to_hex(std::string str){
    std::stringstream ss;
    for(int i=0; i<str.length(); ++i)
        ss << std::hex << (int)str[i];
    return ss.str();
}

std::string hex2ascii(std::string strhex){
    
    int len = strhex.length();
    std::string str;

    for(int i=0; i< len; i+=2){
        std::string byte = strhex.substr(i,2);
        char chr = (char) (int) strtoull(byte.c_str(), 0, 16);
        str.push_back(chr);
    }

    return str;
}

std::string bin_to_hex(std::bitset<8> charbyte){
    stringstream res;
    res << hex << uppercase << charbyte.to_ulong();
    std::string r = res.str();
    if(r.length() == 1) r = "0"+r;
    return r;
}

std::bitset<8> hex_to_bin(std::string strhex){
    stringstream ss;
    ss << hex << strhex;
    unsigned n;
    ss >> n;
    bitset<8> b(n);
    return b;
}

std::string vigenere_cipher_decrypt(std::string strhex, std::string key){
    
    std::string keyhex = to_hex(key);
    int maxLen = keyhex.length() -1;
    
    int x = 0;

    vector<std::bitset<8> > charbytes;
    vector<std::bitset<4> > charbits;

    for (int i = 0; i < strhex.length(); i++){
        if(x > maxLen) x = 0;
        
        std::bitset<4> res1 = to_bin(strhex[i]);
        std::bitset<4> res2 = to_bin(keyhex[x]);
        std::bitset<4> bitsres = res1 ^ res2;

        if(i > 0 && i % 2 != 0) {
            std::bitset<4> last = charbits[i-1];
            std::bitset<8> ress = concat(last, bitsres);
            charbytes.push_back(ress);
        }

        charbits.push_back(bitsres);
        x++;

    }
   
    std::string hexstr;
    for (size_t n = 0; n < charbytes.size(); n++){
        hexstr += bin_to_hex(charbytes[n]);
    }

    return hex2ascii(hexstr);

}

std::string vigenere_cipher_encrypt(std::string str, std::string key){
    
    std::string strhex = to_hex(str);
    std::string keyhex = to_hex(key);
    int maxLen = keyhex.length() -1;

    int x = 0;

    vector<std::bitset<8> > charbytes;
    vector<std::bitset<4> > charbits;

    for (int i = 0; i < strhex.length(); i++){
        if(x > maxLen) x = 0;
        
        std::bitset<4> res1 = to_bin(strhex[i]);
        std::bitset<4> res2 = to_bin(keyhex[x]);
        std::bitset<4> bitsres = res1 ^ res2;

        if(i > 0 && i % 2 != 0) {
            std::bitset<4> last = charbits[i-1];
            std::bitset<8> ress = concat(last, bitsres);
            charbytes.push_back(ress);
        }

        charbits.push_back(bitsres);
        x++;

    }
   
    std::string hexstr;
    for (size_t n = 0; n < charbytes.size(); n++){
        hexstr += bin_to_hex(charbytes[n]);
    }

    return hexstr;
}

int main()
{   
    std::string encrypt = vigenere_cipher_encrypt("Hello!", "key");
    cout << encrypt << "\n";
    std::string decrypt = vigenere_cipher_decrypt(encrypt, "key");
    cout << decrypt << "\n";
    return 0;
}
