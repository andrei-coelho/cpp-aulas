#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <map>
#include <cstddef>
#include "vigenere_cipher.cpp"


char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int  key_len = 3;
int  max_char_indx = sizeof(alfabeto) - 1;
vector<int> indx;


std::string brute_force_gen_key(){
    
    std::string str;
    
    for (size_t i = 0; i < key_len; i++){
        str += alfabeto[indx[i]];
    }

    int n = indx.size() - 1;
    indx[n]++;

    while(n > 0) {
        if(indx[n] > max_char_indx){
            indx[n] = 0;
            int x = n - 1;
            if(x >= 0) indx[x]++;
        }
        n--; 
    }

    return str;
}


bool is_word_in_text(std::string text){
    
    int count = 0;
    int tlen = text.length(); 
    // caracteres mais presentes na lingua portuguesa
    // cerca de 3/4
    char chars[] = {'a', 'e', 'i', 'o', 'u', 's', 'r', 'n', 'd', 'm'};
    int  sizec   = sizeof(chars);
    // a porcentagem pode ser alterada para diminuir ou aumentar a precisão
    int  percent = 55; 

    for (size_t i = 0; i < tlen; i++)
        for (size_t j = 0; j < sizec; j++)
            if(chars[j] == tolower(text[i])) count++;
                
    return (count * 100 / tlen) > percent;
}


bool test_key(std::string test_key, std::string enc_cipher){

    std::string keyhex = to_hex(test_key);
    int maxLen = keyhex.length() -1;

    int x = 0;

    vector<std::bitset<8> > charbytes;
    vector<std::bitset<4> > charbits;

    for (int i = 0; i < enc_cipher.length(); i++){
        
        if(x > maxLen) x = 0;
        
        std::bitset<4> res1 = to_bin(enc_cipher[i]);
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

    for (size_t y = 0; y < hexstr.length(); y++){
        if(y % 2 == 0){
            std::string hexpart(1,hexstr[y]);
            hexpart += hexstr[y+1];
            int z;
            std::stringstream stream; 
            stream << hexpart;
            stream >> std::hex >> z;
            if(z < 32 || z > 127) return false;
        }
    }

    std::string teststr = hex2ascii(hexstr);
    return is_word_in_text(teststr);
}


std::string cracking(std::string enc_cipher){
    
    for (size_t i = 0; i < key_len; i++) indx.push_back(0);

    while (true) {
        if(indx[0] > max_char_indx) return "";
        std::string key = brute_force_gen_key(); 
        if(test_key(key, enc_cipher)) return key;
    }

}


vector<int> rand_numbers(int max_char){
    
    std::srand(time(NULL));
    if(max_char == 0) max_char = rand() % 20;
    
    vector<int> indexes;
    int max_index = sizeof(alfabeto) - 1;

    for (size_t i = 0; i < max_char; i++){   
        int number = rand() % max_index;
        indexes.push_back(number);
    }
    
    return indexes;
}


std::string aleatory_text(int max_char = 0){
    
    vector<int> indexes = rand_numbers(max_char);
    std::string text;
    
    for (size_t i = 0; i < indexes.size(); i++){
        text += alfabeto[indexes[i]];
    }

    return text;
}


int main() {
    
    // generate a random key
    std::string key  = aleatory_text(key_len);
    // use the key to encrypt a text
    std::string enc_cipher  = vigenere_cipher_encrypt("Um texto para ver como fica, pois textos pequenos dao problema e nao use acentos", key);
    // try to find out the randomly generated key through brute force
    std::string key_cracked = cracking(enc_cipher);
    
    cout << "Cracked Key: " << key_cracked << "\n";
    // tests the key to decrypt the text
    // if the same text means the key is correct
    cout << vigenere_cipher_decrypt(enc_cipher, key_cracked);

    return 0;
}
