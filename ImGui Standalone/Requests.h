#pragma once
#include <string>
#include <vector>

namespace Requests
{
	void sendRequest();
	void clearData();
}

struct RequestData
{
	//Setup
	bool hasData = false;
	std::string word;

	//Response
	std::string rWord;
	std::vector<std::string> rPartOfSpeech;
	std::vector<std::string> rDefinitions;
	std::vector<std::string> rSynonyms;
	std::vector<std::string> rAntonyms;
	std::vector<std::string> rExample;
};

extern RequestData requestData;