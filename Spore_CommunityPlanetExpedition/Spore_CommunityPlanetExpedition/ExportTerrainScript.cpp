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
	mode = 0;
	if (line.HasFlag("altName")) mode = 1;

	//if (!Simulator::IsSpaceGame()) 
	{
		Sporepedia::ShopperRequest request;
		request.pMultiListener = this;
		request.shopperID = 0x67060110;
		request.maxSelections = 50;
		request.Show(request);
		return;
	}

	/*/if (Simulator::IsSpaceGame())
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
	creationFolder = creationFolder + u"Export/";

	string str;
	str.assign_convert(creationFolder);

	std::filesystem::create_directory(str.c_str());

	pRecord->GetStream()->SetPosition(0);
	auto size = pRecord->GetStream()->GetSize();
	char* buffer = new char[size];
	pRecord->GetStream()->Read(buffer, size);
	pRecord->Close();

	string16 name = Simulator::Activ
	name += u" - " + metadata->GetAuthor();

	string16 path;
	path.sprintf(u"%ls%ls.prop", creationFolder.c_str(), Simulator::GetActivePlanetRecord()->mName.c_str());
	intrusive_ptr<IO::FileStream> outputStream = new IO::FileStream(path.c_str());
	outputStream->Open(IO::kAccessFlagReadWrite, IO::kCDCreateAlways);
	outputStream->Write(buffer, size);
	outputStream->Close();
	delete[] buffer;*/
}

void ExportTerrainScript::OnShopperAccept(const vector<ResourceKey>& selection)
{
	if (selection.size() != 0)
	{
		for (int i = 0; i < selection.size(); i++)
		{
			cAssetMetadataPtr metadata;
			Pollinator::GetMetadata(selection[i].instanceID, selection[i].groupID, metadata);
			string16 name = metadata->GetName();
			if (mode == 1) name += u" - " + metadata->GetAuthor();
			else name += u"_" + metadata->GetAuthor();

			Resource::IPFRecord* pRecord;
			auto resource = ResourceKey(selection[i].instanceID, TypeIDs::adventure, selection[i].groupID);
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
}

/*void ExportTerrainScript::OnShopperAccept(const ResourceKey& selection)
{
	if (selection.groupID != 0)
	{
		cAssetMetadataPtr metadata;
		Pollinator::GetMetadata(selection.instanceID, selection.groupID, metadata);
		string16 name = metadata->GetName();
		name += u" - "+metadata->GetAuthor();


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
}*/

const char* ExportTerrainScript::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "Export's a planet's terrain script";
	}
	else {
		return "ExportTerrainScript: Exports a planet's terrain script to My Spore Creations/Adventures/Export.";
	}
}
