#pragma once

#include <Spore\BasicIncludes.h>

#define PlanetScriptOverriderPtr intrusive_ptr<PlanetScriptOverrider>

class PlanetScriptOverrider
	: public Object
	, public DefaultRefCounted
	, public App::IUpdatable
{
public:
	static const uint32_t TYPE = id("PlanetScriptOverrider");
	
	PlanetScriptOverrider();
	~PlanetScriptOverrider();

	void OverrideHomeworldScripts();
	static void OverrideRegularScripts(PropertyListPtr planetPropList);

	void Update() override;
	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;
};
