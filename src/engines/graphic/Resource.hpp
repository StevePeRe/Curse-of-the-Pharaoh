#pragma once

#include <string>

struct Resource
{
    //virtual ~Resource() = default;
    std::string getName() { return name; }
    void setName(std::string nameFile) { name = nameFile; }
    virtual void loadResource(std::string resource) = 0;

    protected:
        std::string name; 
};