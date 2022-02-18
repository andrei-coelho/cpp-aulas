#include <iostream>
#include <string>

#include "vigenere_cipher.cpp";

int main()
{
    std::string key = "-]z3:*j.,=15/b{5+Q]";

    std::string crypt_str1 = vigenere_cipher_encrypt("uma frase simples a", key);
    std::string crypt_str2 = vigenere_cipher_encrypt("frase uma simples a", key);
    std::string crypt_str3 = vigenere_cipher_encrypt("simples uma frase a", key);
    std::string crypt_str4 = vigenere_cipher_encrypt("a simples uma frase", key);
    std::string crypt_str5 = vigenere_cipher_encrypt("uma a simples frase", key);
    std::string crypt_str6 = vigenere_cipher_encrypt("frase a simples uma", key);
    std::string crypt_str7 = vigenere_cipher_encrypt("a frase uma simples", key);

    std::cout << crypt_str1 << "\n";
    std::cout << crypt_str2 << "\n";
    std::cout << crypt_str3 << "\n";
    std::cout << crypt_str4 << "\n";
    std::cout << crypt_str5 << "\n";
    std::cout << crypt_str6 << "\n";
    std::cout << crypt_str7 << "\n";

    return 0;
}
