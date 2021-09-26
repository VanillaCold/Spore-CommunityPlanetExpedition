#include "stdafx.h"
#include "PlanetScriptOverrider.h"

PlanetScriptOverrider::PlanetScriptOverrider()
{
}


PlanetScriptOverrider::~PlanetScriptOverrider()
{
}

void PlanetScriptOverrider::OverrideHomeworldScripts()
{
	//0x4084A100
	vector<uint32_t> IDs;
	vector<uint32_t> PlanetIDs;
	bool IsCollabInstalled = PropManager.GetAllListIDs(id("CollabPlanets"), PlanetIDs);
	if (PropManager.GetAllListIDs(0x4084A100, IDs) && IsCollabInstalled != 0)
	{
		for (int i = 0; i < IDs.size(); i++)
		{
			PropertyListPtr propList;
			bool IsDoneAlready = 0;
			bool isAlreadyGenerated = 0;
			PropManager.GetPropertyList(IDs[i], 0x4084A100, propList);
			App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), IsDoneAlready);

			size_t countUseless; ResourceKey* keyUseless;

			isAlreadyGenerated = App::Property::GetArrayKey(propList.get(), 0x043B29E1, countUseless, keyUseless); //terrainModelFootprints
			string16 result;
			App::Property::GetString16(propList.get(), 0x00B2CCCA, result);

			if (IsDoneAlready == 0 && isAlreadyGenerated == false)
			{
				SporeDebugPrint("Overrided planet script: %u", IDs[i]);
				RandomNumberGenerator rng(IDs[i]);
				rng.seed = IDs[i] * IDs[i];
				int index = rng.RandomInt(PlanetIDs.size());

				PropertyListPtr OverrideProplist;
				PropManager.GetPropertyList(PlanetIDs[index], id("CollabPlanets"), OverrideProplist);

				App::Property* prop;
				OverrideProplist->GetProperty(0x02A907B5, prop); //0x02A907B5 is modelEffect
				propList->SetProperty(0x02A907B5, prop);

				OverrideProplist->GetProperty(0x04E13CB7, prop); //0x04E13CB7 is terrainThemeFlora
				propList->SetProperty(0x04E13CB7, prop);

				OverrideProplist->GetProperty(0x03A90C57, prop); //0x03A90C57 is terrainScriptModels
				propList->SetProperty(0x03A90C57, prop);

				OverrideProplist->GetProperty(0x03A90C5F, prop); //0x03A90C5F is terrainScriptModelTransforms
				propList->SetProperty(0x03A90C5F, prop);

				OverrideProplist->GetProperty(0x02A907B6, prop); //0x02A907B6 is modelEffectTransforms
				propList->SetProperty(0x02A907B6, prop);

				OverrideProplist->GetProperty(0x02A907B7, prop); //0x02A907B7 is modelEffectSeed
				propList->SetProperty(0x02A907B7, prop);

				OverrideProplist->GetProperty(0x03DD8E5A, prop); //0x03DD8E5A is terrainScriptEffectIntensities
				propList->SetProperty(0x03DD8E5A, prop);

				OverrideProplist->GetProperty(0x03DD8E59, prop); //0x03DD8E59 is terrainScriptEffectSeeds
				propList->SetProperty(0x03DD8E59, prop);

				OverrideProplist->GetProperty(0x03A23F97, prop); //0x03A23F97 is terrainScriptEffectTimes
				propList->SetProperty(0x03A23F97, prop);

				OverrideProplist->GetProperty(0x7A6AA70B, prop); //0x7A6AA70B is terrainScriptEffectWaterLevels
				propList->SetProperty(0x7A6AA70B, prop);

				OverrideProplist->GetProperty(0x03A23F99, prop); //0x03A23F99 is terrainScriptPlanetInfo
				propList->SetProperty(0x03A23F99, prop);

				OverrideProplist->GetProperty(0x073137BB, prop); //0x073137BB is terrainThemeFloraGlobalDensity
				propList->SetProperty(0x073137BB, prop);

				OverrideProplist->GetProperty(0x03A23F98, prop); //0x03A23F98 is terrainScriptWTALevels
				propList->SetProperty(0x03A23F98, prop);

				OverrideProplist->GetProperty(0x07B18058, prop); //0x07B18058 is terrainOverrideMode
				propList->SetProperty(0x07B18058, prop);


				propList->SetProperty(id("PlanetOverrider-IsAlreadyDone"), prop);

				PropManager.SetPropertyList(propList.get(), IDs[i], 0x4084A100);

			}
		}
	}
}

void PlanetScriptOverrider::OverrideRegularScripts()
{
	//0x4084A100
	vector<uint32_t> IDs_1;
	vector<uint32_t> IDs_2;
	vector<uint32_t> IDs_3;
	vector<uint32_t> IDs_4;
	vector<ResourceKey> TerrainScriptIDs;
	PropManager.GetAllListIDs(0x4084B100, IDs_1);//0x4084B100 is planetScriptsT1~
	PropManager.GetAllListIDs(0x4084B200, IDs_2);//0x4084B200 is planetScriptsT2~
	PropManager.GetAllListIDs(0x4084B300, IDs_3);//0x4084B300 is planetScriptsT3~
	PropManager.GetAllListIDs(0xE38475D9, IDs_4);//0xE38475D9 is PlanetScripts~
	for (int i = 0; i < max(IDs_1.size(),max(max(IDs_2.size(),IDs_3.size()), IDs_4.size())); i++)
	{
		if (IDs_1.size() > i)
		{
			PropertyListPtr propList;
			PropManager.GetPropertyList(IDs_1[i], 0x4084B100, propList);
			bool isDoneAlready = 0;
			App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), isDoneAlready);

			if (!isDoneAlready) TerrainScriptIDs.push_back(ResourceKey(IDs_1[i], TypeIDs::prop, 0x4084B100));
		}
		if (IDs_2.size() > i)
		{
			PropertyListPtr propList;
			PropManager.GetPropertyList(IDs_2[i], 0x4084B200, propList);
			bool isDoneAlready = 0;
			App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), isDoneAlready);

			if (!isDoneAlready) TerrainScriptIDs.push_back(ResourceKey(IDs_2[i], TypeIDs::prop, 0x4084B200));
		}
		if (IDs_3.size() > i)
		{
			PropertyListPtr propList;
			PropManager.GetPropertyList(IDs_3[i], 0x4084B300, propList);
			bool isDoneAlready = 0;
			App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), isDoneAlready);

			if (!isDoneAlready) TerrainScriptIDs.push_back(ResourceKey(IDs_3[i], TypeIDs::prop, 0x4084B300));
		}
		if (IDs_4.size() > i)
		{
			PropertyListPtr propList;
			PropManager.GetPropertyList(IDs_4[i], 0xE38475D9, propList);
			bool isValid = 0;
			bool isDoneAlready = 0;
			ResourceKey tScriptSource;
			isValid = App::Property::GetKey(propList.get(), 0x03D03F84, tScriptSource);
			App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), isDoneAlready);
			if (isValid && !isDoneAlready) TerrainScriptIDs.push_back(ResourceKey(IDs_4[i], TypeIDs::prop, 0xE38475D9));
		}
	}


	vector<uint32_t> PlanetIDs;
	bool IsCollabInstalled = PropManager.GetAllListIDs(id("CollabStandardPlanets"), PlanetIDs);
	if (TerrainScriptIDs.size() > 0 && IsCollabInstalled != 0) 
	{
		for (int i = 0; i < TerrainScriptIDs.size(); i++)
		{
			PropertyListPtr propList;
			bool IsDoneAlready = 0;
			bool isAlreadyGenerated = 0;
			PropManager.GetPropertyList(TerrainScriptIDs[i].instanceID, TerrainScriptIDs[i].groupID, propList);
			App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), IsDoneAlready);

			size_t countUseless; ResourceKey* keyUseless;

			isAlreadyGenerated = App::Property::GetArrayKey(propList.get(), 0x043B29E1, countUseless, keyUseless); //terrainModelFootprints
			string16 result;
			App::Property::GetString16(propList.get(), 0x00B2CCCA, result);

			if (IsDoneAlready == 0 && isAlreadyGenerated == false)
			{
				SporeDebugPrint("Overrided planet script: %u", TerrainScriptIDs[i].instanceID);
				RandomNumberGenerator rng(0);
				rng.seed = TerrainScriptIDs[i].instanceID * TerrainScriptIDs[i].groupID;
				int index = rng.RandomInt(PlanetIDs.size());

				PropertyListPtr OverrideProplist;
				PropManager.GetPropertyList(PlanetIDs[index], id("CollabStandardPlanets"), OverrideProplist);

				App::Property* prop;
				OverrideProplist->GetProperty(0x02A907B5, prop); //0x02A907B5 is modelEffect
				propList->SetProperty(0x02A907B5, prop);

				OverrideProplist->GetProperty(0x04E13CB7, prop); //0x04E13CB7 is terrainThemeFlora
				propList->SetProperty(0x04E13CB7, prop);

				OverrideProplist->GetProperty(0x03A90C57, prop); //0x03A90C57 is terrainScriptModels
				propList->SetProperty(0x03A90C57, prop);

				OverrideProplist->GetProperty(0x03A90C5F, prop); //0x03A90C5F is terrainScriptModelTransforms
				propList->SetProperty(0x03A90C5F, prop);

				OverrideProplist->GetProperty(0x02A907B6, prop); //0x02A907B6 is modelEffectTransforms
				propList->SetProperty(0x02A907B6, prop);

				OverrideProplist->GetProperty(0x02A907B7, prop); //0x02A907B7 is modelEffectSeed
				propList->SetProperty(0x02A907B7, prop);

				OverrideProplist->GetProperty(0x03DD8E5A, prop); //0x03DD8E5A is terrainScriptEffectIntensities
				propList->SetProperty(0x03DD8E5A, prop);

				OverrideProplist->GetProperty(0x03DD8E59, prop); //0x03DD8E59 is terrainScriptEffectSeeds
				propList->SetProperty(0x03DD8E59, prop);

				OverrideProplist->GetProperty(0x03A23F97, prop); //0x03A23F97 is terrainScriptEffectTimes
				propList->SetProperty(0x03A23F97, prop);

				OverrideProplist->GetProperty(0x7A6AA70B, prop); //0x7A6AA70B is terrainScriptEffectWaterLevels
				propList->SetProperty(0x7A6AA70B, prop);

				OverrideProplist->GetProperty(0x03A23F99, prop); //0x03A23F99 is terrainScriptPlanetInfo
				propList->SetProperty(0x03A23F99, prop);

				OverrideProplist->GetProperty(0x073137BB, prop); //0x073137BB is terrainThemeFloraGlobalDensity
				propList->SetProperty(0x073137BB, prop);

				OverrideProplist->GetProperty(0x03A23F98, prop); //0x03A23F98 is terrainScriptWTALevels
				propList->SetProperty(0x03A23F98, prop);

				OverrideProplist->GetProperty(0x07B18058, prop); //0x07B18058 is terrainOverrideMode
				propList->SetProperty(0x07B18058, prop);


				propList->SetProperty(id("PlanetOverrider-IsAlreadyDone"), prop);

				PropManager.SetPropertyList(propList.get(), TerrainScriptIDs[i].instanceID, TerrainScriptIDs[i].groupID);

			}
		}
	}
}

void PlanetScriptOverrider::Update()
{
	OverrideRegularScripts();
	OverrideHomeworldScripts();
}

// For internal use, do not modify.
int PlanetScriptOverrider::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int PlanetScriptOverrider::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* PlanetScriptOverrider::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(PlanetScriptOverrider);
	return nullptr;
}
