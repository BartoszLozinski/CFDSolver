#include <iostream>

#include "Mesh/Node.hpp"
#include "Mesh/Face.hpp"
#include "Mesh/Cell.hpp"

int main()
{
    std::cout << "Hello there!\n";

    Node node{0.1, 0.1};
    Face face{0};
    Cell cell{0};

    return 0;
}
