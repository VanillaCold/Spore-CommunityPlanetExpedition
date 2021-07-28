#include "stdafx.h"
#include "PlanetScriptOverrider.h"

PlanetScriptOverrider::PlanetScriptOverrider()
{
}


PlanetScriptOverrider::~PlanetScriptOverrider()
{
}

void PlanetScriptOverrider::Update()
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
			PropManager.GetPropertyList(IDs[i],0x4084A100,propList);
			App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), IsDoneAlready);
			string16 result;
			App::Property::GetString16(propList.get(), 0x00B2CCCA, result);
			
			if (IsDoneAlready == 0 && result == u"Gameplay Theme")
			{
				SporeDebugPrint(to_string(PlanetIDs.size()).c_str());
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
