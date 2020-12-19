#include "ClassNeiron.h"

ClassNeiron::ClassNeiron(std::vector<Neiron*>* inputs): Neiron(inputs) {}

ClassNeiron::ClassNeiron(Neiron** inputs, size_t size) : Neiron(inputs, size) {}
