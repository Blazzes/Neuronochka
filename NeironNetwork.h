#pragma once
#include "ClassNeiron.h"
#include "InputNeiron.h"
#include "OutputNeiron.h"
class NeironNetwork
{
public:
    NeironNetwork(std::vector<uint16_t> countNe);
    void NetUpdate(std::vector<double> input, std::vector<double> output, std::vector<double>* NetOut);
private:
    void NextUpdate(std::vector<double> input);
    void ErrorUpdate(std::vector<double> output, std::vector<double>* NetOut);
    void WeightUpdate();
    std::vector<std::vector<Neiron*>*> net;
};

