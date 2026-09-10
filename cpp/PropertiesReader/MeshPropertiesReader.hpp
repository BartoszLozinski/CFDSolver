#pragma once

#include <string>
#include "../Properties/MeshProperties.hpp"
#include "PropertiesReaderBase.hpp"

class MeshPropertiesReader : public PropertiesReaderBase<MeshPropertiesReader>
{
friend PropertiesReaderBase<MeshPropertiesReader>;

protected:
    PropertiesMap CreatePropertiesMap_Impl(MeshProperties& propertiesStruct) const;

public:
    MeshPropertiesReader() = default;
    MeshProperties ReadFromSetupFile(const std::string& filename = "Setup/MeshProperties") const;
};
