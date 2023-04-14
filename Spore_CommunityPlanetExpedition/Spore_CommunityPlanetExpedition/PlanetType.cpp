#include "stdafx.h"
#include "PlanetType.h"
#include <Spore\Terrain\cTerrainSphere.h>

PlanetType::PlanetType()
{
}


PlanetType::~PlanetType()
{
}


void PlanetType::ParseLine(const ArgScript::Line& line)
{
	ResourceKey key = Simulator::GetActivePlanetRecord()->mGeneratedTerrainKey;

	PropertyListPtr propList; PropManager.GetPropertyList(key.instanceID, key.groupID, propList);

	string16 planetName;

	if (!App::Property::GetString16(propList.get(), id("planet_name"), planetName))
	{
		planetName = u"Vanilla Planet";
	}

	string name;
	name.assign_convert(planetName);

	name = "Planet type is: " + name;

	App::ConsolePrintF(name.c_str());

	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* PlanetType::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "PlanetType: Elaborate description of what this cheat does.";
	}
}
