#pragma once

#include <cstdint>
#include "Common.hpp"

class Polynomial {
private:
    uint32_t order;
    std::vector<fpt> coefficients;

public:
    Polynomial(uint32_t order);
};