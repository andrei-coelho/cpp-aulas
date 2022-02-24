#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <fstream>

const std::string consts = "0x428a2f98 0x71374491 0xb5c0fbcf 0xe9b5dba5 0x3956c25b 0x59f111f1 0x923f82a4 0xab1c5ed5 0xd807aa98 0x12835b01 0x243185be 0x550c7dc3 0x72be5d74 0x80deb1fe 0x9bdc06a7 0xc19bf174 0xe49b69c1 0xefbe4786 0x0fc19dc6 0x240ca1cc 0x2de92c6f 0x4a7484aa 0x5cb0a9dc 0x76f988da 0x983e5152 0xa831c66d 0xb00327c8 0xbf597fc7 0xc6e00bf3 0xd5a79147 0x06ca6351 0x14292967 0x27b70a85 0x2e1b2138 0x4d2c6dfc 0x53380d13 0x650a7354 0x766a0abb 0x81c2c92e 0x92722c85 0xa2bfe8a1 0xa81a664b 0xc24b8b70 0xc76c51a3 0xd192e819 0xd6990624 0xf40e3585 0x106aa070 0x19a4c116 0x1e376c08 0x2748774c 0x34b0bcb5 0x391c0cb3 0x4ed8aa4a 0x5b9cca4f 0x682e6ff3 0x748f82ee 0x78a5636f 0x84c87814 0x8cc70208 0x90befffa 0xa4506ceb 0xbef9a3f7 0xc67178f2";
const std::string initv  = "0x6a09e667 0xbb67ae85 0x3c6ef372 0xa54ff53a 0x510e527f 0x9b05688c 0x1f83d9ab 0x5be0cd19";

std::vector<std::string> ssplit(std::string str, std::string del){
    
    size_t pos = 0;
    std::vector<std::string> strs;
    
    while ((pos = str.find(del)) != std::string::npos) {
        std::string token = str.substr(0, pos);
        strs.push_back(token);
        str.erase(0, pos + del.length());
    }

    strs.push_back(str);
    return strs;

}


int main()
{
    std::vector<std::string> vec_consts = ssplit(consts, " ");
    std::vector<std::string> vec_initv  = ssplit(initv, " ");

    std::string content = "#include <vector>\n#include <string>\n#include <bitset>\n\n";
    content += "std::vector<std::bitset<32> > constants_bytes_values = { \n";
    
    for (size_t i = 0; i < vec_consts.size(); i++) {
        
        std::string line = (i+1) % 4 != 0 ? " " : "\n";
        content += "std::bitset<32>(" + vec_consts[i] + "),"+line;

    }

    content = content.substr(0, content.length()-2)+" };\n\n";
    content += "std::vector<std::bitset<32> > H = { \n";

    for (size_t y = 0; y < vec_initv.size(); y++) {
        
        std::string line = (y+1) % 2 != 0 ? " " : "\n";
        content += "std::bitset<32>(" + vec_initv[y] + "),"+line;

    }
    
    content = content.substr(0, content.length()-2)+" };\n\n";

    std::ofstream myfile;
    myfile.open ("constants.cpp");
    myfile << content;
    myfile.close();

    return 0;
}
