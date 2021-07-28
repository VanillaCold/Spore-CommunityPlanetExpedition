#pragma once

#include <Spore\BasicIncludes.h>
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
class ExportTerrainScript
	: public ArgScript::ICommand
	, public Sporepedia::IMultiShopperListener
	//, public Sporepedia::IShopperListener
{
public:
	ExportTerrainScript();
	~ExportTerrainScript();
	bool mode = 0;
	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	void OnShopperAccept(const vector<ResourceKey>& selection) override;
	//void OnShopperAccept(const ResourceKey& selection);

	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;
};

