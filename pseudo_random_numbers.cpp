#include <iostream>
#include <winsock.h>
#include <stdint.h>
#include <string>
#include <sstream>

uint64_t microseconds()
{
    LARGE_INTEGER fq, t;
    QueryPerformanceFrequency(&fq);
    QueryPerformanceCounter(&t);
    return (1000000 * t.QuadPart) / fq.QuadPart;
}

int unsigned_num_rand(){
    uint64_t t = microseconds();
    std::stringstream ss;
    ss << t;
    std::string s = ss.str();
    int a = (s[s.length()-1] - '0');
    int x = (s[s.length()-2] - '0');
    int b = (s[s.length()-3] - '0');
    return (a*x+b) % 1000000;
}

int main()
{
    for (size_t i = 0; i < 20; i++)
    {
        std::cout << unsigned_num_rand() << "\n";
    }
    
    std::cin.ignore();
    return 0;
}
