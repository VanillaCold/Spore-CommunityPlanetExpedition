#include "stdafx.h"
#include "SpatialPlanetCollisions.h"
#include <Spore\App\cCreatureModeStrategy.h>
#include <Spore\Simulator\cInteractiveOrnament.h>
#include <Spore\Simulator\cCreatureGameData.h>

SpatialPlanetCollisions::SpatialPlanetCollisions()
{
	sInstance = this;
	gameTimer = 0;
	App::AddUpdateFunction(this);
}


SpatialPlanetCollisions::~SpatialPlanetCollisions()
{
}


void SpatialPlanetCollisions::Update()
{
	if (gameTimer > 0  && !Simulator::IsLoadingGameMode() && (Simulator::IsCreatureGame() || Simulator::IsScenarioMode()) && GameNounManager.GetAvatar())
	{
		gameTimer-= 1/GameTimeManager.GetSpeed();
		if (gameTimer < 2)
		{
			for (int i = 0; i < objects.size(); i++)
			{
				cSpatialObjectPtr spatial = objects[i];
				Vector3 pos = spatial->GetPosition();
				spatial->Teleport(pos, objRots[i]);
			}
		}
	}
}

void SpatialPlanetCollisions::ParseLine(const ArgScript::Line& line)
{
	if (!line.HasFlag("test"))
	{
		auto sphere = (Terrain::cTerrainSphere*)ScenarioMode.mpTerraformMode->mpTerrain;
		PlanetModelsToSpatialObjects(sphere);
		flags = mpFormatParser->ParseInt(line.GetArguments(1)[0]);
	}
	else
	{
		for (int i = 0;i<objects.size();i++)
		{
			cSpatialObjectPtr spatial = objects[i];
			Vector3 pos = spatial->GetPosition();
			
			spatial->mbFixed = true;
			spatial->mbPickable = false;
			spatial->mbKeepPinnedToPlanet = false;
			spatial->mbIsTangible = true;
			spatial->mbIsGhost = false;
			spatial->mbTransformDirty = false;
			
			spatial->Teleport(pos, objRots[i]);
			
			gameTimer = 5;
		}
	}
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* SpatialPlanetCollisions::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "SpatialPlanetCollisions: Elaborate description of what this cheat does.";
	}
}

void SpatialPlanetCollisions::PlanetModelsToSpatialObjects(Terrain::cTerrainSphere* sphere)
{
	/*if (objects.size() != 0)
	{
		for each (cSpatialObjectPtr obj in objects)
		{
			delete obj.get();
		}
		objects = vector<cSpatialObjectPtr>{};
	}*/

	if (!Simulator::IsScenarioMode() && !Simulator::IsCreatureGame())
	{
		return;
	}

	objects = vector<cSpatialObjectPtr>{};
	
	auto propList = sphere->mpPropList;
	bool isPreGenerated;
	if (App::Property::GetBool(propList.get(), id("CPE-IsTerrainGenerated"), isPreGenerated) && !Simulator::IsScenarioMode())
	{
		App::ConsolePrintF("Pre-generated property is found!");
	}
	else
	{
		isPreGenerated = false;
		gameTimer = 150;
	}

	for(int i = 0;i<sphere->mModels.size();i++)
	{
		
		ModelPtr model = sphere->mModels[i];
		Transform mTrans = sphere->mModelTransforms[i];
		ResourceKey mKey = model->mpPropList->GetResourceKey();
		bool isSpatial;

		if (App::Property::GetBool(model->mpPropList.get(), id("isSpatialStamp"), isSpatial) && isSpatial == true)
		{

			if (isPreGenerated == false)
			{
				auto test = GameNounManager.CreateInstance(Simulator::kRock);
				Simulator::cSpatialObject* obj = object_cast<Simulator::cSpatialObject>(test);
				size_t count;
				Vector3 rot = mTrans.GetRotation().ToEuler();

				if ((Math::Quaternion::FromEuler(rot)) == Math::Quaternion(0, 0, 0, 0))
				{
					SporeDebugPrint("WE GOT ANOTHER ONE");
					SporeDebugPrint("Object number %i", i)
				}
				obj->SetModelKey(mKey);
				obj->Teleport(mTrans.GetOffset(), Math::Quaternion::FromEuler(rot));
				objRots.push_back(Math::Quaternion::FromEuler(rot));
				obj->SetScale(mTrans.GetScale());
				obj->mbFixed = true;
				obj->mbPickable = false;
				obj->mbKeepPinnedToPlanet = false;
				obj->mbIsTangible = true;
				obj->mbIsGhost = false;
				obj->mbTransformDirty = false;
				obj->Teleport(mTrans.GetOffset(), Math::Quaternion::FromEuler(rot));
				objects.push_back(obj);
			}


			model->mCollisionMode = Graphics::CollisionMode::BoundingBox;
			model->mDefaultBBox = BoundingBox(Vector3(0, 0, 0), Vector3(0, 0, 0));
			model->mDefaultBoundingRadius = 0;
			model->mTransform.SetScale(0.00001);
			model->mFlags &= ~Graphics::ModelFlags::kModelFlagVisible;
		}
	}
	App::Property* prop = new App::Property();
	prop->SetValueBool(true);
	propList->SetProperty(id("CPE-IsTerrainGenerated"), prop);
}

/*bool SpatialPlanetCollisions::HandleMessage(uint32_t messageID, void* message) {
	if (messageID == id("SpatialPlanetMessage"))
	{
		MessageManager.MessageSend(id("SpatialPlanetMessage2"),new void*());
		return true;
	}
	if (messageID == id("SpatialPlanetMessage2"))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			cSpatialObjectPtr spatial = objects[i];
			Vector3 pos = spatial->GetPosition();
			spatial->Teleport(pos, objRots[i]);
		}
		return true;
	}
	return false;
}*/

SpatialPlanetCollisions* SpatialPlanetCollisions::Get()
{
	return sInstance;
}

int SpatialPlanetCollisions::AddRef()
{
	return DefaultRefCounted::AddRef();
}

int SpatialPlanetCollisions::Release()
{
	return DefaultRefCounted::Release();
}

SpatialPlanetCollisions* SpatialPlanetCollisions::sInstance = nullptr;