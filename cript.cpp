#include <iostream>
#include <string>

char alfabeto[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

char getChar(int pos){
    while (pos > 25) pos = pos - 26;
    return alfabeto[pos];
}

int pos(char c) {
    for (size_t i = 0; i < 26; i++){
        if(c == alfabeto[i]){
            return i;
        }
    }
}

void decryptPorDeslocamento(std::string crypto, int key){
    for(int n = 0; n < crypto.length(); n++){
        std::cout << getChar(pos(crypto[n]) + (key % 26) - 26) << "\n";
    }
}

void encryptPorDeslocamento(std::string msg, int key){
    for(int n = 0; n < msg.length(); n++){
        std::cout << getChar(pos(msg[n]) + (key % 26) - 26) << "\n";
    }
}

void encryptVigenere(std::string msg, std::string key){
    int k = 0;
    int max = key.length();
    for(int n = 0; n < msg.length(); n++){
        if(k == max)  k = 0;
        std::cout << getChar(pos(msg[n]) + pos(key[k])) << "\n";
        k++;
    }
}

int main(int argc, char const *argv[]){
    std::string msg = "seeyouatnoon";
    int key = 25;
    encryptVigenere(msg, "spy");
    return 0;
}

