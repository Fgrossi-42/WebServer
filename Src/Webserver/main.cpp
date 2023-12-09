#include "../../Inc/Webserver.hpp"
#include "../../Inc/Location.hpp"

int main(int argc, char **argv)
{
    Location location(argv[1]);
    if (argc != 2)
    {
        std::cout << "Usage: ./parser <filename>" << std::endl;
        return 1;
    }
    location.printConfig();
    (void)argv;
    return 0;
}