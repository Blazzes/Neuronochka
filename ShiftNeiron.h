#pragma once
#include "Neiron.h"
class ShiftNeiron :
    public Neiron
{
public:
    ShiftNeiron(std::vector<Neiron*>* inputs);
    virtual void Calc_Result() override {}
    virtual void CompError(double pre_error) override {};
private:
    //double m_result = 1;
};

