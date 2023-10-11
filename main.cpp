#include "./Parser/Parser.hpp"

int main(int argc, char **argv)
{
    Parser parser;

    parser.parse(argv[1]);
    parser.print_values();
    return 0;
}