#pragma once
#include "ClassNeiron.h"
#include "InputNeiron.h"
#include "OutputNeiron.h"
class NeironNetwork
{
public:
    NeironNetwork(std::vector<uint16_t> countNe);
    void NetUpdate(std::vector<double> input, std::vector<double> output);
private:
    void NextUpdate(std::vector<double> input);
    void ErrorUpdate(std::vector<double> output);
    void WeightUpdate();
    std::vector<std::vector<Neiron*>*> net;
};

