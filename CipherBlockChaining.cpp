#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <time.h>
#include <cstdlib>


char chars[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
std::vector<std::vector<std::bitset<8> > > messages;


std::vector<int> rand_numbers(int max_char){
    
    srand(time(NULL));
    if(max_char == 0) max_char = rand() % 20;
    
    std::vector<int> indexes;
    int max_index = sizeof(chars) - 1;

    for (size_t i = 0; i < max_char; i++){   
        int number = rand() % max_index;
        indexes.push_back(number);
    }
    
    return indexes;
}


std::string gen_random_IV(int len){
    
    std::vector<int> indexes = rand_numbers(len);
    std::string text;
    
    for (size_t i = 0; i < indexes.size(); i++){
        text += chars[indexes[i]];
    }

    return text;
}


std::bitset<8> char_to_byte(char c){
    std::stringstream ss;
    ss << std::hex << (int)c;
    unsigned n;
    ss >> n;
    std::bitset<8> b(n);
    return b;
}


std::vector<std::bitset<8> > string_to_bytes(std::string s){
    
    std::vector<std::bitset<8> > vec;
    
    for (size_t i = 0; i < s.length(); i++)
        vec.push_back(char_to_byte(s[i]));
    
    return vec;
}


std::vector<std::bitset<8> > xroring_message(std::vector<std::bitset<8> > a, std::vector<std::bitset<8> >b){
    
    std::vector<std::bitset<8> > c;
    size_t sizeMsg = a.size();
    int diference = sizeMsg - b.size();
    
    if (diference < 0){
        // erro
    }

    if (diference > 0){
        // gerar e adicionar bytes ao vetor b
    }

    for (size_t i = 0; i < sizeMsg; i++) c.push_back(a[i] ^ b[i]);
    return c;
    
}


std::string bytes_to_hex(std::vector<std::bitset<8> > msg_bytes){

    size_t size = msg_bytes.size();
    std::string rfinal;

    for (size_t i = 0; i < size; i++){   
        
        std::bitset<8> msg_byte = msg_bytes[i];
        std::stringstream res;
        std::string r;
        
        res << std::hex << msg_byte.to_ulong();
        r = res.str();
        if(r.length() == 1) r = "0"+r;
        rfinal += r;
    }
    
    return rfinal;
}


std::vector<std::bitset<8> > hex_to_bytes(std::string h){
    
    std::vector<std::bitset<8> > vec;
    size_t size = h.length();
    
    for (size_t i = 0; i < size; i+=2){
        
        std::string charhex;
        charhex.push_back(h[i]);
        charhex.push_back(h[i+1]);
        
        std::stringstream ss;
        ss << std::hex << charhex;
        unsigned n;
        ss >> n;
        
        std::bitset<8> b(n);
        vec.push_back(b);
    }

    return vec;
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

std::string CBC_encrypt(std::string message, std::string key1, std::string key2){
    
    unsigned int sizeMsg = messages.size();

    if(sizeMsg == 0) {
        std::string IV = gen_random_IV(8);
        std::cout << "IV:   " << IV << "\n\n";
        messages.push_back(string_to_bytes(IV));
        sizeMsg++;
    }

    std::vector<std::bitset<8> > lastMessage  = messages[sizeMsg-1];
    std::vector<std::bitset<8> > encMessPart1 = xroring_message(lastMessage, string_to_bytes(message));
    std::vector<std::bitset<8> > encMessageC  = xroring_message(encMessPart1, string_to_bytes(key1));
    std::vector<std::bitset<8> > encMessCheck = xroring_message(encMessageC, string_to_bytes(key2));

    std::string encMessage = bytes_to_hex(encMessageC) + bytes_to_hex(encMessCheck);

    messages.push_back(encMessageC);

    return encMessage;

}


std::string CBC_decrypt(std::string hex, std::string key1, std::string key2){

    std::vector<std::bitset<8> > lastMessage = messages[messages.size()-2];
    std::vector<std::bitset<8> > messagBytes = hex_to_bytes(hex.substr(0,16));
    std::vector<std::bitset<8> > checkBytes  = xroring_message(hex_to_bytes(hex.substr(16,16)), string_to_bytes(key2));
    std::vector<std::bitset<8> > decMessPart = xroring_message(messagBytes, string_to_bytes(key1));
    std::vector<std::bitset<8> > decMesFinal = xroring_message(decMessPart, lastMessage);

    if(bytes_to_hex(messagBytes) == bytes_to_hex(checkBytes)) {
        std::cout << "VALID: TRUE" << "\n";
    } else {
        std::cout << "VALID: FALSE" << "\n";
    }

    return hex2ascii(bytes_to_hex(decMesFinal));
}


int main(){ 
    
    std::string key1 = "chave000";
    std::string key2 = "000chave";
    std::string m1   = "send $01";
    std::string m2   = "send $02";
    std::string m3   = "send $03";

    std::cout << "---------------------------------------" << "\n";

    std::cout << "KEY1: " <<  key1 << "\n";
    std::cout << "KEY2: " <<  key2 << "\n";

    std::cout << "--------------------------------------" << "\n";

    std::cout << "MSG1: " << m1 << "\n\n";
    std::string m1c = CBC_encrypt(m1, key1, key2);
    std::cout << "ENC1: " << m1c << "\n";
    std::string m1d = CBC_decrypt(m1c, key1, key2);
    std::cout << "DEC1: " << m1d << "\n";
    std::cout << "--------------------------------------" << "\n";

    std::cout << "MSG2: " << m2 << "\n\n";
    std::string m2c = CBC_encrypt(m2, key1, key2);
    std::cout << "ENC2: " << m2c << "\n";
    std::string m2d = CBC_decrypt(m2c, key1, key2);
    std::cout << "DEC2: " << m2d << "\n";
    std::cout << "--------------------------------------" << "\n";

    std::cout << "MSG2: " << m3 << "\n\n";
    std::string m3c = CBC_encrypt(m3, key1, key2);
    std::cout << "ENC2: " << m3c << "\n";
    m3c = m3c.substr(0,15) + "0" + m3c.substr(8,16);
    std::cout << "ATACK:" << m3c << "\n";
    std::string m3d = CBC_decrypt(m3c, key1, key2);
    std::cout << "DEC2: " << m3d << "\n";
    std::cout << "--------------------------------------" << "\n";

    return 0;
}
