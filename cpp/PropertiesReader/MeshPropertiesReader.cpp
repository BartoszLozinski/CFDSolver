#include "MeshPropertiesReader.hpp"

MeshPropertiesReader::PropertiesMap MeshPropertiesReader::CreatePropertiesMap_Impl(MeshProperties& propertiesStruct) const
    {
        return PropertiesMap{
            {"dx", DoubleRef(propertiesStruct.dx)},
            {"dy", DoubleRef(propertiesStruct.dy)},
            {"nx", UIntRef(propertiesStruct.nx)},
            {"ny", UIntRef(propertiesStruct.ny)}
        };
    };

MeshProperties MeshPropertiesReader::ReadFromSetupFile(const std::string& filename /* = "Setup/MaterialProperties" */) const
{
    return ParsePropertiesFile<MeshProperties>(filename);
}
