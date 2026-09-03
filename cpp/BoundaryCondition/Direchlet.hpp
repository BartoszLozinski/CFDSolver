#include "BoundaryConditionBase.hpp"

namespace BoundaryCondition
{
    class Direchlet : public BoundaryConditionBase
    {
    protected:
        std::function<double(double)> function;
        
    public:
        Direchlet(Cells& boundaryCells_, std::function<double(double)> function_);
        void Apply(const double spaceStep) final override;
    };
};