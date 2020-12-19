#pragma once
#include "Neiron.h"
class ClassNeiron :
    public Neiron
{
public:
    ClassNeiron(std::vector<Neiron*>* inputs);
    ClassNeiron(Neiron** inputs, size_t size);
private:
};

