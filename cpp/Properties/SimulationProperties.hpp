#pragma once

#include <cstdint>

struct SimulationProperties
{
    double dt{};
    bool shouldExportResults{ false };
    uint32_t exportFrequency{};
    uint32_t timesteps{};
};