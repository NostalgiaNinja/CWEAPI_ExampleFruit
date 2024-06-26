#include "pch.h"
#include "cwe_api.h"
#include "ModelInfo.h"

extern "C"
{
	//registering data functions. - Needs to exist.
	void (*RegisterDataFunc)(void* ptr);

	//NJS Type texture name and texture list. As is for old documentation.
	NJS_TEXNAME ExampleTex[10];
	NJS_TEXLIST example_texlist = { arrayptrandlength(ExampleTex) };

	//Define models
	ModelInfo* MDLExampleFruit;

	//Define a fruit ID - This is used for making the fruit visible in the Black Market
	int exampleFruitID;

	//Define Black Market Attributes
	BlackMarketItemAttributes BMExampleFruit = { 250, 100, 0, -1, -1, 0 };

	//Define Fruit Stats
	ChaoItemStats customFruitStats = { 10, 10, 0, 0, 0, 0, 0, 0, 0, 0 }; //mood, belly, swim, fly, run, power, stamina, luck, intel, unknown;

	//Custom Fruit Function - Changes ChaoData Stats on the last bite of the fruit.
	void __cdecl customFruitFunction(ChaoData* data, ObjectMaster* fruit)
	{
		data->data.Happiness += 0.1;
	}

	//main CWE Load function -- Important stuff like adding your CWE mod goes here
	void CWELoad(CWE_REGAPI* cwe_api)
	{
		//register texture lists
		cwe_api->RegisterChaoTexlistLoad("ExampleTex", &example_texlist);
		
		// 2.1.0 - Assign the Fruit ID to the fruit assignment function
		exampleFruitID = cwe_api->RegisterChaoFruit(MDLExampleFruit->getmodel(), &example_texlist, &customFruitStats, &BMExampleFruit, customFruitFunction, "Example Fruit Name", "Example Fruit Description");
	
		// 2.1.0 - use General or Rare Assignment - chance must add up to 100%
		cwe_api->RegisterBlackMarketGeneralFruit(exampleFruitID, 50);
		//cwe_api->RegisterBlackMarketRareFruit(exampleFruitID, 50);
	}

	//initialization function - MUST exist in order to have CWE and SA2 see your mod
	__declspec(dllexport) void Init(const char* path)
	{
		HMODULE h = GetModuleHandle(L"CWE");

		std::string pathStr = std::string(path) + "\\";

		//Tell what models need to be associated to their variables here.
		MDLExampleFruit = new ModelInfo(pathStr + "ExampleFruit.sa2mdl");

		RegisterDataFunc = (void (*)(void* ptr))GetProcAddress(h, "RegisterDataFunc");
		RegisterDataFunc(CWELoad);
	}
	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}