#include "../../Inc/Webserver.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: ./parser <filename>" << std::endl;
        return 1;
    }
    (void)argv;
    return 0;
}