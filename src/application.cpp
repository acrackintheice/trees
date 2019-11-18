#include <iostream>
#include "../include/tree.h"

int main (int argc, char *argv[]) {
    typedef Red_Black<std::string> StringTree;
    StringTree tree = StringTree();
    tree.insert(12, new std::string("Element 12"));
    tree.insert(15, new std::string("Element 15"));

    std::cout << "Tress are great" << std::endl;
    std::cout << "This is my Tree: \n" << tree.to_string() << std::endl; 
    std::cout << "This is my Tree: \n" << *(tree.search(15)->data()) << std::endl; 
    return 0;

}

