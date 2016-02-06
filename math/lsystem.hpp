#ifndef LSYSTEM_HPP
#define LSYSTEM_HPP

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class LSystem{
private:
    char* variables;
    char* constants;
    char* axiom;
    map<char, std ::string> rules;
public:
    void loadfile(string f);
};

#endif
