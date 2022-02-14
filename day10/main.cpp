#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream in("input.txt");
    std::string input((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::cout << input;

    return 0;
}
