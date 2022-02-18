/*

EXERCÍCIO

Abaixo estão 7 textos cifrados, cada um dos quais foi gerado criptografando algum 
texto simples ASCII de 31 caracteres com o one-time pad usando a mesma chave. 
Descriptografe-os e recupere todos os 7 textos simples, cada um dos quais é uma 
frase em inglês gramaticalmente correta. 

Contanto que você possa descriptografar todos eles, não importa como você faça isso.

    Textos Cifrados:

    58301B135C580B5D491D425C4212175058713C
    4B2F1B405F0A1F434D1D425C4212175058713C
    5E341743564F190E5950501549101A464E713C
    4C7D095A575A064B5F1D44584E421D474A2238
    58301B135B0A1947414D5D505C421D474A2238
    4B2F1B405F0A0B0E5F545C45430708155E3C3C
    4C7D1C415B590F0E595050155C0B164547342E


TODO:

    Na criação das possiveis chaves, analisar
    se há o texto de filtro contido no valor.

    A melhor forma de fazer isso é fazer essa 
    análise em bits.

*/

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "vigenere_cipher.cpp"


char const chars[] = {
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
};

std::vector < std::string > filter_words;
int size_filter_words;

std::vector < std::bitset<8> > bin_chars;
std::vector < std::vector < std::string > > parts_keys_approved;
std::vector < std::string > possibles_keys;

std::vector < std::string > encrypt_texts;
std::vector < std::string > results;



std::string gen_res(std::string strhex){
    
    int len = strhex.length();
    std::string str;

    for(int i=0; i< len; i+=2){
        std::string byte = strhex.substr(i,2);
        str += (char) (int) strtoull(byte.c_str(), 0, 16);
    }

    return str;
}


bool analise_num(int num){
    bool statusNum = true;
    if(num < 97 || num > 122){
        if(num != 32){
            statusNum = false;
        }
    }
    return statusNum;
}


std::bitset<8> char_to_bin(char c){
    return std::bitset<8>(int(c));
}


std::bitset<8> hex_to_bin(int hex){
    return std::bitset<8>(hex);
}


std::bitset<8> hexstr_to_bin(std::string hex){
    std::stringstream ss;
    unsigned int x;
    ss << "0x" << std::hex << hex;
    ss >> x;
    return std::bitset<8>(x);
}


std::string one_byte_to_hex(std::bitset<8> byte){
    std::stringstream res;
    res << std::hex << byte.to_ulong();
    return res.str();
}


std::vector<std::bitset<8> > get_keys(std::string charhex){

    std::vector<std::bitset<8> > resFinal;
    int total_chars = bin_chars.size();

    for (size_t i = 0; i < total_chars; i++)
    {
        std::bitset<8> key = hexstr_to_bin(charhex) ^ bin_chars[i];
        resFinal.push_back(key);
    }
    
    return resFinal;
    
}


void test_keys(std::string str_pattern , std::vector<std::string> list){

    std::string encpattern = encrypt_texts[0];
    
    for (size_t i = 0; i < list.size(); i++) 
    {

        std::string st = str_pattern + list[i];
        bool statusRes = true;

        for (size_t x = 0; x < st.length(); x+=2)
        {
            
            std::bitset<8> byte = hexstr_to_bin(encpattern.substr(x, 2)) ^ hexstr_to_bin(st.substr(x,2));
            int num = byte.to_ulong();
            
            if(!analise_num(num)){
                statusRes = false;
                break;
            }

        }

        if(size_filter_words > 0){
            for (size_t i = 0; i < size_filter_words; i++)
            {
                if (filter_words[i].find(encpattern) == std::string::npos) {
                    statusRes = false;
                    break;
                }
            }
            
        }
        
        if(statusRes) {
            
            std::string key = hex2ascii(st);
            std::string res = vigenere_cipher_decrypt(encpattern, key);
            
            std::cout << "Resultado encontrado: " << res << "\n";
            std::cout << "Chave Usada: " << key << "\n";
            
            results.push_back(res);
        
        }
        
    }

}


void add_keys(int pos_char = 0, std::string strAtual = ""){
    
    int max_pos = parts_keys_approved.size() -1;
    
    if(pos_char == max_pos) {
        test_keys(strAtual, parts_keys_approved[pos_char]);
        return;
    }

    int max = parts_keys_approved[pos_char].size();
    
    for (size_t i = 0; i < max; i++){
        int next = pos_char + 1;
        add_keys(next, strAtual + parts_keys_approved[pos_char][i]);
    }

}


void decrypt_texts(){

    std::cout << "Buscando resultados validos..." << "\n";
    std::cout << "Isso pode demorar..." << "\n";

    std::string encpattern = encrypt_texts[0];

    int charPosHex = 0;
    int charPos = 0;
    int charMax = encpattern.length();
    int size    = encrypt_texts.size();

    while (charPosHex < charMax){

        std::string charhex = encpattern.substr(charPosHex, 2);
        std::vector<std::bitset<8> > keys = get_keys(charhex);
        int totalKeys = keys.size();

        for (size_t x = 0; x < totalKeys; x++){
            
            bool statusKey = true;
            std::bitset<8> k = keys[x];

            for (size_t y = 0; y < size; y++) {

                std::string nextCharHex = encrypt_texts[y].substr(charPosHex, 2);
                int num = std::bitset<8>(hexstr_to_bin(nextCharHex) ^ k).to_ulong();
                if(!analise_num(num)){
                    statusKey = false;
                    break;
                }

            }

            if(statusKey) {
                if(parts_keys_approved.size() <= charPos){
                    std::vector<std::string> list;
                    parts_keys_approved.push_back(list);
                }
                parts_keys_approved[charPos].push_back(one_byte_to_hex(k));
            }

        }

        charPosHex += 2;
        charPos++;

    }
    
    add_keys();

}


int main() {
    
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << "Iniciado em: " << dt << "\n";

    // transforma todos os chars[] em hexadecimal e salva no vetor hex_chars
    int chars_len = sizeof(chars);
    for (size_t i = 0; i < chars_len; i++) bin_chars.push_back(char_to_bin(chars[i]));
    bin_chars.push_back(hex_to_bin(0x20)); // add space char
    
    // inserindo textos para análise ...
    encrypt_texts.push_back("58301B135C580B5D491D425C4212175058713C");
    encrypt_texts.push_back("4B2F1B405F0A1F434D1D425C4212175058713C");
    encrypt_texts.push_back("5E341743564F190E5950501549101A464E713C");
    encrypt_texts.push_back("4C7D095A575A064B5F1D44584E421D474A2238");
    encrypt_texts.push_back("58301B135B0A1947414D5D505C421D474A2238");
    encrypt_texts.push_back("4B2F1B405F0A0B0E5F545C45430708155E3C3C");
    encrypt_texts.push_back("4C7D1C415B590F0E595050155C0B164547342E");

    // filter_words.push_back("uma");

    size_filter_words = filter_words.size();

    // decriptando os textos...
    decrypt_texts();

    time_t now2 = time(0);
    char* dt2 = ctime(&now2);

    std::cout << "Total Decriptado: " << results.size() << "\n";
    std::cout << "Programa finalizado em: " << dt2 << "\n\n";
    
    return 0;
}
