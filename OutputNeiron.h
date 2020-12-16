#pragma once
#include "Neiron.h"
class OutputNeiron :
    public Neiron
{
public:
    OutputNeiron(std::vector<Neiron*>* inputs);
    void CompError(double comp) override;
    void CompResult(double comp);
private:
};

