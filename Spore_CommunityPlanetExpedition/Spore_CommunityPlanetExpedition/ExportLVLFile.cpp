#include "stdafx.h"
#include "ExportLVLFile.h"
#include <filesystem>

ExportLVLFile::ExportLVLFile()
{
}


ExportLVLFile::~ExportLVLFile()
{
}


void ExportLVLFile::ParseLine(const ArgScript::Line& line)
{
	auto terrainObjects = ScenarioMode.GetTerraformMode()->mTerrainScriptModels;
	auto terrainTransforms = ScenarioMode.GetTerraformMode()->mTerrainScriptModelTransforms;

	auto arg = line.GetArguments(1);
	string16 name;
	name.assign_convert(arg[0]);

	//vector<ResourceKey> markers;
	//vector<Transform> markerTransforms;

	string markerText = "";

	for(int i = 0;i<terrainObjects.size();i++)
	{
		ResourceKey object = terrainObjects[i];
		Transform transform = terrainTransforms[i];
		
		PropertyListPtr propList;
		PropManager.GetPropertyList(object.instanceID, object.groupID, propList);
		bool isMarker;
		if (App::Property::GetBool(propList.get(), id("isMarker"), isMarker) && isMarker)
		{
			string markerType;
			
			auto orientation = transform.GetRotation().ToQuaternion();
			Vector3 position = transform.GetOffset();
			uint32_t markerPropertyCount;

			App::Property::GetString8(propList.get(), id("markerType"), markerType);
			markerText += markerType;
			markerText += "\n	position ("+to_string(position.x)+", "+to_string(position.y)+", "+to_string(position.z) + ")";
			markerText += "\n	orientation (" + to_string(orientation.x) + ", " + to_string(orientation.y) + ", " + to_string(orientation.z)+ ", " + to_string(orientation.w) + ")";

			if (App::Property::GetUInt32(propList.get(), id("markerPropertyCount"), markerPropertyCount))
			{
				markerText += "\n\n	propertyCount "+to_string(markerPropertyCount);
			}

			markerText += "\nend\n\n";
			

			//markers.push_back(object);
			//markerTransforms.push_back(transform);
		}

	}
	SporeDebugPrint(markerText.c_str());

	string16 creationFolder;
	if (!App::Thumbnail_cImportExport::Get()->GetFolderPath(TypeIDs::adventure, creationFolder)) return;
	creationFolder = creationFolder + u"Export/LevelEditor_Saves~/";

	string str;
	str.assign_convert(creationFolder);

	std::filesystem::create_directory(str.c_str());

	auto size = markerText.length();
	char* buffer = new char[size];


	buffer = (char*)markerText.data();

	string16 path;
	path.sprintf(u"%ls%ls.lvl.lvl_t", creationFolder.c_str(), name.c_str());
	intrusive_ptr<IO::FileStream> outputStream = new IO::FileStream(path.c_str());
	outputStream->Open(IO::AccessFlags::Write, IO::CD::CreateAlways);
	outputStream->Write(buffer, size);
	outputStream->Close();
	delete[] buffer;

	str.assign_convert(path);
	App::ConsolePrintF("Exported to %s", str);
	// This method is called when your cheat is invoked.
	// Put your cheat code here.
}

const char* ExportLVLFile::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "ExportLVLFile: Elaborate description of what this cheat does.";
	}
}
