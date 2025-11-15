#pragma once

#include <array>

static constexpr long BOUNDARY_NEIGHBOR_CELL = -1;
static constexpr double dz = 0.1; //just for now 10 cm

class Face
{
private:
    double CalculateArea(const double length);

public:
    long cellID = 0;
    long neighborCellID = BOUNDARY_NEIGHBOR_CELL;
    std::array<long, 2> nodeIds{};
    double area = 0;
    std::array<double, 2> normal{};

    Face(const long cellID_) : cellID(cellID_) {};
};
