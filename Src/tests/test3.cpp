#include "tempRequest.hpp"

int main(int argc, char **argv)
{
    std::string filename;
    std::cout << "insert filename"<<std::endl;
    std::cin >> filename;
    Request bobby(filename);
    return(0);
}