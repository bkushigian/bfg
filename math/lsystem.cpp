#include "lsystem.hpp"

void LSystem::loadfile(string f){
    std::string line;
    ifstream F;
    F.open(f);
    if (! F.is_open()){
        std::cout << "Error loading file " << f << std::endl;
        return;
    }
    while( getline(f, line)){
        switch (line[0]){
            case 'V':           // Variables

            case 'C':           // Constant

            case 'A':           // Axiom

            case 'R':           // Rules
        }
    }
}
