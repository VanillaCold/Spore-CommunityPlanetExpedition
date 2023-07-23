#include "stdafx.h"
#include "PlanetType.h"
#include <Spore\Terrain\cTerrainSphere.h>
#include <stdexcept>

PlanetType::PlanetType()
{
}


PlanetType::~PlanetType()
{
}


void PlanetType::ParseLine(const ArgScript::Line& line)
{
	size_t numArgs;
	auto args = line.GetArgumentsRange(&numArgs, 0, 1);
	if (numArgs == 0)
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
	}
	else
	{
		uint32_t hash = mpFormatParser->ParseUInt(args[0]);
		try {
			PropertyListPtr propList;
			if (PropManager.GetPropertyList(hash, 0x4184A100, propList))
			{
				ResourceKey* terrainStamps;
				size_t numTerrainStamps;
				if (App::Property::GetArrayKey(propList.get(), 0x02A907B5, numTerrainStamps, terrainStamps))
				{
					string text = "Planet has " + to_string(numTerrainStamps) + " effects.";
					App::ConsolePrintF(text.c_str());
				}
				else
				{
					throw(std::invalid_argument("Planet has invalid effect list!"));
				}
			}
			else
			{
				throw(std::invalid_argument("Planet does not exist!"));
			}
		}
		catch (std::exception except)
		{
			App::ConsolePrintF(except.what());
		}
	}
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
