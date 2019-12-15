#include <iostream>
#include "../include/tree.h"

int main(int argc, char *argv[])
{
    typedef Red_Black<std::string> StringTree;
    StringTree tree = StringTree();
    tree.insert(1, new std::string("Element 1"));
    tree.insert(3, new std::string("Element 3"));
    tree.insert(5, new std::string("Element 5"));
    tree.insert(8, new std::string("Element 8"));
    tree.insert(10, new std::string("Element 10"));
    tree.insert(12, new std::string("Element 12"));
    tree.insert(13, new std::string("Element 13"));
    tree.insert(16, new std::string("Element 16"));
    tree.insert(18, new std::string("Element 18"));
    tree.insert(19, new std::string("Element 19"));
    tree.insert(24, new std::string("Element 24"));
    tree.insert(26, new std::string("Element 26"));

    std::cout << "Tress are great" << std::endl;
    std::cout << "This is my Tree: \n" << tree.to_string() << std::endl;
    std::cout << "Search for 5: \n" << ((tree.search(5)->color() == Tree_Nodes::Red_Black_Node<std::string>::Color::RED) ? std::string("RED") : std::string("Black")) << std::endl;

    return 0;
}
