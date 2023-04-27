#include "stdafx.h"
#include "SpatialPlanetCollisions.h"
#include <Spore\App\cCreatureModeStrategy.h>
#include <Spore\Simulator\cInteractiveOrnament.h>
#include <Spore\Simulator\cCreatureGameData.h>

SpatialPlanetCollisions::SpatialPlanetCollisions()
{
	sInstance = this;
	//App::AddUpdateFunction(this);
}


SpatialPlanetCollisions::~SpatialPlanetCollisions()
{
}


void SpatialPlanetCollisions::Update()
{

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
		cVehiclePtr test = simulator_new<Simulator::cVehicle>();
		test->Load(VehicleLocomotion::kVehicleLand, VehiclePurpose::kVehicleColony, GameNounManager.GetAvatar()->GetModelKey());
		test->Teleport(GameNounManager.GetAvatar()->GetPosition(),GameNounManager.GetAvatar()->GetOrientation());
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
	objects = vector<cSpatialObjectPtr>{};
	for each (ModelPtr model in sphere->mModels)
	{
		

		Transform mTrans = model->mTransform;
		ResourceKey mKey = model->mpPropList->GetResourceKey();
		bool isSpatial;

		if (App::Property::GetBool(model->mpPropList.get(), id("isSpatialStamp"), isSpatial) && isSpatial == true)
		{

			auto test = simulator_new<Simulator::cInteractiveOrnament>();
			//void* gonzagoPhysics = STATIC_CALL_(Address(0xB3D410), void*);
			//auto physTest = CALL(Address(0xB48870), void*, Args(void*, Simulator::cGameData*, bool), Args(gonzagoPhysics, test, false));
			
			//test->Load(VehicleLocomotion::kVehicleLand, VehiclePurpose::kVehicleColony, mKey);
		
			//auto test = GameNounManager.CreateInstance(Simulator::GameNounIDs::kRock);
			Simulator::cSpatialObject* obj = object_cast<Simulator::cSpatialObject>(test);

			test->Teleport(mTrans.GetOffset(),mTrans.GetRotation().ToQuaternion());

			//cSpatialObjectPtr obj = simulator_new<Simulator::cSpatialObject>();
			obj->SetModelKey(mKey);
			obj->SetPosition(mTrans.GetOffset());
			obj->SetOrientation(mTrans.GetRotation().ToQuaternion());
			obj->SetScale(mTrans.GetScale());
			obj->mbFixed = true;
			obj->mbPickable = false;
			obj->mbKeepPinnedToPlanet = true;
			obj->mbIsTangible = true;
			obj->mbIsGhost = false;
		

			model->mCollisionMode = Graphics::CollisionMode::BoundingBox;
			model->mDefaultBBox = BoundingBox(Vector3(0, 0, 0), Vector3(0, 0, 0));
			model->mDefaultBoundingRadius = 0;
			model->mTransform.SetScale(0.00001);
			model->mFlags -= Graphics::ModelFlags::kModelFlagVisible;
		

			objects.push_back(obj);
		}
	}

}

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