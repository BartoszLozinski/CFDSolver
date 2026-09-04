#include "BoundaryConditionBase.hpp"

namespace BoundaryCondition
{
    class Direchlet : public BoundaryConditionBase
    {
    protected:
        std::function<double(double, double)> function; //space dx, space dy, 
        
    public:
        Direchlet(Grid& grid_, BoundaryIndicies boundaryIndicies_, std::function<double(double, double)> function_);
        void Apply(const double spaceStep) final override;
    };
};