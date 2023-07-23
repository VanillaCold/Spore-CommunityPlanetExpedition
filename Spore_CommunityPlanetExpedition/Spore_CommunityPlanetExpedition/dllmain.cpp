// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "ExportTerrainScript.h"
#include <Spore\Terrain\cTerrainSphere.h>
#include "ExportLVLFile.h"
#include "PlanetType.h"
#include "SpatialPlanetCollisions.h"
#include <Spore\App\ScenarioMode.h>

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
	//App::AddUpdateFunction(new PlanetScriptOverrider());

	CheatManager.AddCheat("ExportTerrainScript", new ExportTerrainScript());
	CheatManager.AddCheat("ExportLVLFile", new ExportLVLFile());
	CheatManager.AddCheat("PlanetTerrainType", new PlanetType());
	CheatManager.AddCheat("SpatialPlanetCollisions", new SpatialPlanetCollisions());
}

member_detour(TerrainSphereGenerate_detour, Terrain::cTerrainSphere, void(int*, int*, bool, bool, float)) {
	void detoured(int* unused0, int* unused1, bool unk = false,
		bool generateSingleStep = false, float generateTimeLimit = 10.0f) {
		//PlanetScriptOverrider::OverrideRegularScripts(this->mpPropList);



		original_function(this, unused0, unused1, unk, generateSingleStep, generateTimeLimit);
		
		if (Simulator::IsCreatureGame() || (Simulator::IsScenarioMode() && ScenarioMode.mMode == App::cScenarioMode::Mode::PlayMode))
		{
			string16 planetName;
	
			if (!App::Property::GetString16(this->mpPropList.get(), id("planet_name"), planetName))
			{
				planetName = u"Vanilla Planet";
			}

			string name; 
			name.assign_convert(planetName);

			name = "Planet type is: " + name;


			if (this->mNumModels != 0)
			{
				SpatialPlanetCollisions::Get()->PlanetModelsToSpatialObjects(this);
				//do stuff
			}
		}



		//PlanetScriptOverrider::OverrideRegularScripts(this->mpPropList);
	}
};

static_detour(DetourTest, void* (int))
{
	void* detoured(int arg1)
	{
		if (arg1)
		{
			original_function(arg1);
		}
		else
		{
			return (void*)nullptr;
		}
	}
};

void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	TerrainSphereGenerate_detour::attach(GetAddress(Terrain::Sphere::cTerrainSphere, Generate));
	//DetourTest::attach(Address(0x00bd9b30));
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

