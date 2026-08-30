#include "Field.hpp"

Field::Field(const Mesh& mesh_)
    : mesh(mesh_)
{
    static constexpr uint32_t ghostCellOffset = 2;
    static constexpr double defualtValue = 0.0;

    grid.resize(mesh.nx + ghostCellOffset);

    for (auto& row : grid)
        row.resize(mesh.ny + ghostCellOffset, defualtValue);
}

void Field::Initialize(std::function<double(double, double)> initializeFunction)
{
    for (std::size_t row_id = 0; row_id < grid.size(); ++row_id)
    {
        for (std::size_t column_id = 0; column_id < grid.at(0).size(); ++ column_id)
        {
            grid[row_id][column_id] = initializeFunction(row_id * mesh.dx, column_id * mesh.dy);
        }
    }
}
