#pragma once
#include "Neiron.h"
class InputNeiron :
    public Neiron
{
public:
    InputNeiron(std::vector<Neiron*>* inputs);
    void SetResult(double input);
    virtual void Calc_Result() override = 0;
private:
};

