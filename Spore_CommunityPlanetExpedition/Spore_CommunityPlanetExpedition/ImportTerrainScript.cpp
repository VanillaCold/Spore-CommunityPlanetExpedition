#include "stdafx.h"
#include "ImportTerrainScript.h"

ImportTerrainScript::ImportTerrainScript()
{
}


ImportTerrainScript::~ImportTerrainScript()
{
}


void ImportTerrainScript::ParseLine(const ArgScript::Line& line)
{
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* ImportTerrainScript::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "ImportTerrainScript: Elaborate description of what this cheat does.";
	}
}
