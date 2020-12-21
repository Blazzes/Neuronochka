#pragma once
#include "ClassNeiron.h"
#include "InputNeiron.h"
#include "OutputNeiron.h"
#include "ShiftNeiron.h"
class NeironNetwork
{
public:
    NeironNetwork(std::vector<uint16_t> countNe);
    void NetUpdate(std::vector<double> input, std::vector<double> output, std::vector<double>* NetOut, bool learn);
private:
    void NextUpdate(std::vector<double> input, std::vector<double>* NetOut);
    void ErrorUpdate(std::vector<double> output);
    void WeightUpdate();
    //std::vector<std::vector<Neiron*>> net;
    Neiron*** net3;
    std::vector<uint16_t> size_slize;
};

