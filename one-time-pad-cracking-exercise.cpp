/*

EXERCÍCIO

Abaixo estão 7 textos cifrados, cada um dos quais foi gerado criptografando algum 
texto simples ASCII de 31 caracteres com o one-time pad usando a mesma chave. 
Descriptografe-os e recupere todos os 7 textos simples, cada um dos quais é uma 
frase em inglês gramaticalmente correta. 

Contanto que você possa descriptografar todos eles, não importa como você faça isso.

    Textos Cifrados:

    BB3A65F6F0034FA957F6A767699CE7FABA855AFB4F2B520AEAD612944A801E
    BA7F24F2A35357A05CB8A16762C5A6AAAC924AE6447F0608A3D11388569A1E
    A67261BBB30651BA5CF6BA297ED0E7B4E9894AA95E300247F0C0028F409A1E
    A57261F5F0004BA74CF4AA2979D9A6B7AC854DA95E305203EC8515954C9D0F
    BB3A70F3B91D48E84DF0AB702ECFEEB5BC8C5DA94C301E0BECD241954C831E
    A6726DE8F01A50E849EDBC6C7C9CF2B2A88E19FD423E0647ECCB04DD4C9D1E
    BC7570BBBF1D46E85AF9AA6C7A9CEFA9E9825CFD5E3A0047F7CD009305A71E

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
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

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
    if(num < 65 || num > 123){
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


    for (size_t y = 0; y < encrypt_texts.size(); y++)
    {
        for (size_t i = 0; i < list.size(); i++) 
        {
            
            std::string st = str_pattern + list[i];
            bool statusRes = true;

            for (size_t x = 0; x < st.length(); x+=2)
            {
                std::bitset<8> byte = hexstr_to_bin(encrypt_texts[y].substr(x, 2)) ^ hexstr_to_bin(st.substr(x,2));
                int num = byte.to_ulong();
                if(!analise_num(num)){
                    statusRes = false;
                    break;
                }
            }
            
            if(statusRes) {
                std::string res = vigenere_cipher_decrypt(encrypt_texts[y], st);
                std::cout << "Resultado encontrado: " << res << "\n";
                results.push_back(res);
            }
            

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
    encrypt_texts.push_back("BA7F24F2A35357A05CB8A16762C5A6AAAC924AE6447F0608A3D11388569A1E");
    encrypt_texts.push_back("A67261BBB30651BA5CF6BA297ED0E7B4E9894AA95E300247F0C0028F409A1E");
    encrypt_texts.push_back("A57261F5F0004BA74CF4AA2979D9A6B7AC854DA95E305203EC8515954C9D0F");
    encrypt_texts.push_back("BB3A70F3B91D48E84DF0AB702ECFEEB5BC8C5DA94C301E0BECD241954C831E");
    encrypt_texts.push_back("A6726DE8F01A50E849EDBC6C7C9CF2B2A88E19FD423E0647ECCB04DD4C9D1E");
    encrypt_texts.push_back("BC7570BBBF1D46E85AF9AA6C7A9CEFA9E9825CFD5E3A0047F7CD009305A71E");
    encrypt_texts.push_back("BB3A65F6F0034FA957F6A767699CE7FABA855AFB4F2B520AEAD612944A801E");

    // decriptando os textos...
    decrypt_texts();

    std::cout << "Total encontrado: " << results.size() << "\n";
    std::cout << "Programa finalizado" << "\n";

    time_t now2 = time(0);
    char* dt2 = ctime(&now2);
    cout << "Finalizado em: " << dt2 << "\n";

    return 0;
}
