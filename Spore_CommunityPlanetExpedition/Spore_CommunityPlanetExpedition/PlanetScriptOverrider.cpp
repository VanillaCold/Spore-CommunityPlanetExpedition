#include "stdafx.h"
#include <asyncinfo.h>
#include "PlanetScriptOverrider.h"
#include <Spore\Terrain\Sphere\cTerrainSphere.h>

PlanetScriptOverrider::PlanetScriptOverrider()
{
}


PlanetScriptOverrider::~PlanetScriptOverrider()
{
}

void PlanetScriptOverrider::OverrideRegularScripts(PropertyListPtr planetPropList)
{
	if (Simulator::IsScenarioMode())
	{
		return;
	}

	vector<uint32_t> PlanetIDs;
	uint32_t groupIDToUse;
	ResourceKey sourcePropList;

	bool IsCollabInstalled = 0;
	bool isDoneAlready = 0;
	bool isAlreadyGenerated = 0;

	App::Property::GetBool(planetPropList.get(), id("PlanetOverrider-IsAlreadyDone"), isDoneAlready);
	size_t countUseless; ResourceKey* keyUseless;
	isAlreadyGenerated = App::Property::GetArrayKey(planetPropList.get(), 0x043B29E1, countUseless, keyUseless); //terrainModelFootprints
	App::Property::GetKey(planetPropList.get(), id("PlanetOverrider-SourceProplist"), sourcePropList);



	ResourceKey planetScriptKey = planetPropList->GetResourceKey();
	switch (planetScriptKey.groupID)
	{
		case 0x4084A100:
		{
			IsCollabInstalled = PropManager.GetAllListIDs(id("CollabPlanets"), PlanetIDs);
			groupIDToUse = id("CollabPlanets");

			RandomNumberGenerator rng(planetScriptKey.instanceID);
			rng.seed = planetScriptKey.instanceID * planetScriptKey.groupID / planetScriptKey.typeID;
			int index = rng.RandomInt(PlanetIDs.size());

			SporeDebugPrint("RNG seed is %u", rng.seed);

			PropertyListPtr propList = planetPropList;
			PropertyListPtr OverrideProplist;
			PropManager.GetPropertyList(PlanetIDs[index], groupIDToUse, OverrideProplist);

			if (sourcePropList != ResourceKey(0, 0, 0))
			{
				PropManager.GetPropertyList(sourcePropList.instanceID, sourcePropList.groupID, OverrideProplist);
			}

			if (isDoneAlready && !isAlreadyGenerated)
			{
				App::Property* prop;
				App::Property* prop2;
				OverrideProplist->GetProperty(0x03A90C57, prop);
				propList->GetProperty(0x03A90C57, prop2);
				if (prop->GetValue() != prop2->GetValue())
				{
					isAlreadyGenerated = 0;
					isDoneAlready = 0;
				}
			}

			break;
		}
		case 0x4084AF00:
		{
			return;
		}
		default:
		{
			
			RandomNumberGenerator rng(planetScriptKey.instanceID);
			rng.seed = planetScriptKey.instanceID * planetScriptKey.instanceID;
			if (rng.RandomFloat() > 0.0625)
			{
				groupIDToUse = id("CollabStandardPlanets");
				IsCollabInstalled = PropManager.GetAllListIDs(id("CollabStandardPlanets"), PlanetIDs);
			}
			else
			{
				IsCollabInstalled = PropManager.GetAllListIDs(id("CollabPlanets"), PlanetIDs);
				groupIDToUse = id("CollabPlanets");
			}

			break;
		}
	}

	if (isAlreadyGenerated || isDoneAlready)
	{
		SporeDebugPrint("Already overrided this terrain script, sorry!");
		return;
	}

	if (IsCollabInstalled != 0)
	{
		SporeDebugPrint("Overrided planet script: %u", planetScriptKey.instanceID);
		RandomNumberGenerator rng(planetScriptKey.instanceID);
		rng.seed = planetScriptKey.instanceID * planetScriptKey.instanceID;
		int index = rng.RandomInt(PlanetIDs.size());

		PropertyListPtr& propList = planetPropList;
		PropertyListPtr OverrideProplist;
		PropManager.GetPropertyList(PlanetIDs[index], groupIDToUse, OverrideProplist);

		if (sourcePropList != ResourceKey(0, 0, 0))
		{
			PropManager.GetPropertyList(sourcePropList.instanceID, sourcePropList.groupID, OverrideProplist);
		}

		App::Property* prop;
		OverrideProplist->GetProperty(0x02A907B5, prop); //0x02A907B5 is modelEffect
		propList->SetProperty(0x02A907B5, prop);

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
		
		if (planetScriptKey.groupID == 0x4084A100)
		{
			OverrideProplist->GetProperty(0x03A23F99, prop); //0x03A23F99 is terrainScriptPlanetInfo
			propList->SetProperty(0x03A23F99, prop);

			OverrideProplist->GetProperty(0x04E13CB7, prop); //0x04E13CB7 is terrainThemeFlora
			propList->SetProperty(0x04E13CB7, prop);

			OverrideProplist->GetProperty(0x073137BB, prop); //0x073137BB is terrainThemeFloraGlobalDensity
			propList->SetProperty(0x073137BB, prop);
		}

		OverrideProplist->GetProperty(0x03A23F98, prop); //0x03A23F98 is terrainScriptWTALevels
		propList->SetProperty(0x03A23F98, prop);

		OverrideProplist->GetProperty(0x07B18058, prop); //0x07B18058 is terrainOverrideMode
		propList->SetProperty(0x07B18058, prop);


		propList->SetProperty(id("PlanetOverrider-IsAlreadyDone"), prop);

		prop->SetValueKey(OverrideProplist->GetResourceKey());
		propList->SetProperty(id("PlanetOverrider-SourceProplist"), prop);

		//PropManager.SetPropertyList(propList.get(), planetScriptKey.instanceID, planetScriptKey.groupID);

		if (!App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), isDoneAlready))
		{
			SporeDebugPrint("ERROR! It somehow has not saved properly!");
		}
	}
	//0x4084A100
}

void PlanetScriptOverrider::Update()
{
	//OverrideRegularScripts();
	if (GameModeManager.GetActiveModeID() == kGGEMode)
	{
		OverrideHomeworldScripts();
	}

	//return;

	if (Simulator::IsCreatureGame() || Simulator::IsScenarioMode() && Simulator::cPlanetModel::Get() != nullptr)
	{
		intrusive_ptr<Graphics::Model>* model;
		auto size = PlanetModel.mpTerrain->GetModels(model);

		if (size <= 0) return;

		for (int i = 0; size_t(i) < size; i++)
		{
			bool result;
			bool result2 = App::Property::GetBool(model[i]->mpPropList.get(), id("CPEOverrideCollision"), result);
			if (true || (result && result2))
			{

				//SporeDebugPrint("Model %u, collision mode %s", model[i]->GetPropList()->GetResourceKey().instanceID,  to_string(uint8_t(model[i]->mCollisionMode)).c_str());
				//SporeDebugPrint("Model %u, flags %i", model[i]->GetPropList()->GetResourceKey().instanceID, model[i]->mFlags);
				//SporeDebugPrint("Model %u, group flags %i", model[i]->GetPropList()->GetResourceKey().instanceID, model[i]->mGroupFlags);
				//SporeDebugPrint("Model %u, unknown float %f", model[i]->GetPropList()->GetResourceKey().instanceID, model[i]->field_88);
				//SporeDebugPrint("Model %u, unknown float 2 %f", model[i]->GetPropList()->GetResourceKey().instanceID, model[i]->field_8C);

				//model[i]->field_88 = 1 - model[i]->field_88;

				//model[i]->mFlags = model[i]->mFlags;//49185;
				//model[i]->mFlags = 77108;

				
				//model[i]->mFlags = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256 + 512 + 1024 + 2048 + 4096 + 8192 + 8192 * 2 + 8192 * 4 + 8192 * 8;
				
				//model[i]->mFlags = Graphics::kModelFlagOverrideBoundingBox + Graphics::kModelFlagHighRes + Graphics::kModelFlagOverrideBoundingRadius + 128 + Graphics::kModelFlagVisible;

				//model[i]->mFlags = 770081;
				
				//model[i]->mCollisionMode = Graphics::CollisionMode::Lod0KDTree;
				//auto owner = model[i]->GetOwner();
				//model[i]->mDefaultBBox.lower = -model[i]->mTransform.GetOffset();
				//model[i]->mDefaultBBox.upper = model[i]->mTransform.GetOffset();

				//SporeDebugPrint("test");

				//auto modelOwner = object_cast<Simulator::>(owner);
				
				/*if (owner)
				{
					App::ConsolePrintF("yeehaw!");
				}*/

				//auto test = (Simulator::cGameData*)model[i].get();
				//if (object_cast<Simulator::cSpatialObject>(test->GetGameDataOwner()))
				//{
				//	App::ConsolePrintF("yeehaw");
				//}
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

//Depricated planet-overrider
void PlanetScriptOverrider::OverrideHomeworldScripts()
{
	//0x4084A100
	vector<uint32_t> IDs;
	vector<uint32_t> PlanetIDs;

	/*			RandomNumberGenerator rng(planetScriptKey.instanceID);
			rng.seed = planetScriptKey.instanceID * planetScriptKey.groupID / planetScriptKey.typeID;
			int index = rng.RandomInt(PlanetIDs.size());

			SporeDebugPrint(to_string(rng.seed).c_str());*/

	bool IsCollabInstalled = PropManager.GetAllListIDs(id("CollabPlanets"), PlanetIDs);
	if (PropManager.GetAllListIDs(0x4084A100, IDs) && IsCollabInstalled != 0)
	{
		for (int i = 0; i < IDs.size(); i++)
		{
			PropertyListPtr propList;
			ResourceKey sourcePropList;
			bool IsDoneAlready = 0;
			bool isAlreadyGenerated = 0;
			PropManager.GetPropertyList(IDs[i], 0x4084A100, propList);
			App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), IsDoneAlready);
			App::Property::GetKey(propList.get(), id("PlanetOverrider-SourceProplist"), sourcePropList);

			size_t countUseless; ResourceKey* keyUseless;

			isAlreadyGenerated = App::Property::GetArrayKey(propList.get(), 0x043B29E1, countUseless, keyUseless); //terrainModelFootprints
			string16 result;
			App::Property::GetString16(propList.get(), 0x00B2CCCA, result);

			if (IsDoneAlready && !isAlreadyGenerated)
			{
				PropertyListPtr OverrideProplist;
				RandomNumberGenerator rng(IDs[i]);
				rng.seed = IDs[i] * IDs[i];
				int index = rng.RandomInt(PlanetIDs.size());
				PropManager.GetPropertyList(PlanetIDs[index], id("CollabPlanets"), OverrideProplist);

				if (sourcePropList != ResourceKey(0,0,0))
				{
					PropManager.GetPropertyList(sourcePropList.instanceID, sourcePropList.groupID, OverrideProplist);
				}

				App::Property* prop;
				App::Property* prop2;
				OverrideProplist->GetProperty(0x03A90C57, prop);
				propList->GetProperty(0x03A90C57, prop2);
				if (prop->GetValue() != prop2->GetValue())
				{
					isAlreadyGenerated = 0;
					IsDoneAlready = 0;
				}
			}


			if (IsDoneAlready == 0 && isAlreadyGenerated == 0)
			{
				SporeDebugPrint("Overrided planet script: %u", IDs[i]);
				RandomNumberGenerator rng(IDs[i]);

				SporeDebugPrint("RNG seed is %u", rng.seed);
				//rng.seed = IDs[i] * IDs[i];
				int index = rng.RandomInt(PlanetIDs.size());

				PropertyListPtr OverrideProplist;
				PropManager.GetPropertyList(PlanetIDs[index], id("CollabPlanets"), OverrideProplist);

				if (sourcePropList != ResourceKey(0, 0, 0))
				{
					PropManager.GetPropertyList(sourcePropList.instanceID, sourcePropList.groupID, OverrideProplist);
				}

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

				prop->SetValueBool(true);
				propList->SetProperty(id("PlanetOverrider-IsAlreadyDone"), prop);

				prop->SetValueKey(OverrideProplist->GetResourceKey());
				propList->SetProperty(id("PlanetOverrider-SourceProplist"), prop);

				//PropManager.SetPropertyList(propList.get(), IDs[i], 0x4084A100);
				SporeDebugPrint("Property list has been set.");
				
				//check if saved properly
				if (!App::Property::GetBool(propList.get(), id("PlanetOverrider-IsAlreadyDone"), IsDoneAlready))
				{
					SporeDebugPrint("ERROR! It somehow has not saved properly!");
				}

			}
		}
	}
}