#pragma once

#include <Spore\BasicIncludes.h>
#include <Spore/Simulator/cInteractiveOrnament.h>

class SpatialPlanetCollisions
	: public ArgScript::ICommand
	, public App::IUpdatable
	, public DefaultRefCounted
{
public:
	SpatialPlanetCollisions();
	~SpatialPlanetCollisions();

	vector<cSpatialObjectPtr> objects;
	void Update() override;

	// Called when the cheat is invoked
	void ParseLine(const ArgScript::Line& line) override;
	
	// Returns a string containing the description. If mode != DescriptionMode::Basic, return a more elaborated description
	const char* GetDescription(ArgScript::DescriptionMode mode) const override;

	void PlanetModelsToSpatialObjects(Terrain::cTerrainSphere* sphere);

	static SpatialPlanetCollisions* Get();

	int AddRef() override;
	int Release() override;
	int flags = 0;
	private:
		static SpatialPlanetCollisions* sInstance;
};

