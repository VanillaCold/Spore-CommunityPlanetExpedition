#include "stdafx.h"
#include "ExportTerrainScript.h"
#include <Spore/App/ScenarioMode.h>
#include <sys/stat.h>
#include <string>
#include <filesystem>



ExportTerrainScript::ExportTerrainScript()
{
}


ExportTerrainScript::~ExportTerrainScript()
{
}


void ExportTerrainScript::ParseLine(const ArgScript::Line& line)
{
	ResourceKey resource;
	bool mode = 0;
	if (!Simulator::IsSpaceGame()) 
	{
		Sporepedia::ShopperRequest request(this);
		request.shopperID = 0x67060110;
		request.Show(request);
		return;
	}

	if (Simulator::IsSpaceGame())
	{
		if (Simulator::SpacePlayerData::Get()->mCurrentContext == Simulator::SpaceContext::kSpaceContextSolarSystem ||
			Simulator::SpacePlayerData::Get()->mCurrentContext == Simulator::SpaceContext::kSpaceContextPlanet)
		{
			resource = Simulator::GetActivePlanetRecord()->mKey;
		}
		else return;
	}
	Resource::IPFRecord* pRecord;
	auto dbpf = ResourceManager.GetDBPF(resource);
	if (!dbpf || !dbpf->GetFile(resource, &pRecord)) {
		App::ConsolePrintF("An error has occured - either the package doesn't exist or the terrain script doesn't exist.");
		return;
	}

	string16 creationFolder;
	if (!App::Thumbnail_cImportExport::Get()->GetFolderPath(TypeIDs::adventure, creationFolder)) return;


	pRecord->GetStream()->SetPosition(0);
	auto size = pRecord->GetStream()->GetSize();
	char* buffer = new char[size];
	pRecord->GetStream()->Read(buffer, size);
	pRecord->Close();

	string16 path;
	path.sprintf(u"%ls%ls.prop", creationFolder.c_str(), Simulator::GetActivePlanetRecord()->mName.c_str());
	intrusive_ptr<IO::FileStream> outputStream = new IO::FileStream(path.c_str());
	outputStream->Open(IO::kAccessFlagReadWrite, IO::kCDCreateAlways);
	outputStream->Write(buffer, size);
	outputStream->Close();
	delete[] buffer;
}

void ExportTerrainScript::OnShopperAccept(const ResourceKey& selection)
{
	if (selection.groupID != 0)
	{
			cAssetMetadataPtr metadata;
			Pollinator::GetMetadata(selection.instanceID, selection.groupID, metadata);
			string16 name = metadata->GetName();
			name += metadata->GetAuthor();


			Resource::IPFRecord* pRecord;
			auto resource = ResourceKey(selection.instanceID, TypeIDs::adventure, selection.groupID);
			auto dbpf = ResourceManager.GetDBPF(resource);
			if (!dbpf || !dbpf->GetFile(resource, &pRecord)) {
				App::ConsolePrintF("An error has occured - either the package doesn't exist or the terrain script doesn't exist.");
				return;
			}
			string16 creationFolder;
			if (!App::Thumbnail_cImportExport::Get()->GetFolderPath(TypeIDs::adventure, creationFolder)) return;
			creationFolder = creationFolder + u"Export/";
			
			string str;
			str.assign_convert(creationFolder);
			
			std::filesystem::create_directory(str.c_str());

			pRecord->GetStream()->SetPosition(0);
			auto size = pRecord->GetStream()->GetSize();
			char* buffer = new char[size];
			pRecord->GetStream()->Read(buffer, size);
			pRecord->Close();

			string16 path;
			path.sprintf(u"%ls%ls.0x366A930D", creationFolder.c_str(), name.c_str());
			intrusive_ptr<IO::FileStream> outputStream = new IO::FileStream(path.c_str());
			outputStream->Open(IO::kAccessFlagReadWrite, IO::kCDCreateAlways);
			outputStream->Write(buffer, size);
			outputStream->Close();
			delete[] buffer;
			
			str.assign_convert(path);
			App::ConsolePrintF("Exported to %s", str);
	}
}

const char* ExportTerrainScript::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat does something.";
	}
	else {
		return "ExportTerrainScript: Elaborate description of what this cheat does.";
	}
}
