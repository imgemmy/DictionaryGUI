#include "Requests.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>


using json = nlohmann::json;
RequestData requestData;

void Requests::sendRequest()
{
    // Create string to send text
    std::string webUrl = "https://api.dictionaryapi.dev/api/v2/entries/en/" + requestData.word;
    cpr::Response r = cpr::Get(cpr::Url{ webUrl });
    json response = json::parse(r.text);
    requestData.hasData = true;

    if (r.status_code == 200)
    {
        
        for (auto& obj : response) {
            // Get the value of the "word" key
            requestData.rWord = obj["word"];

            int index = 0;
            // Loop over the meanings array
            for (auto& meaning : obj["meanings"])
            {
                //Part of Speech
                requestData.rPartOfSpeech.push_back(meaning["partOfSpeech"].get<std::string>());

                //Definitions
                if (meaning.contains("definitions")) {
                    auto& definitions = meaning["definitions"];
                    if (definitions.size() > index) {
                        requestData.rDefinitions.push_back(definitions[index].at("definition"));
                    }
                }

                // Get the first synonym from the synonyms array
                if (!meaning["synonyms"].empty()) {
                    requestData.rSynonyms.push_back(meaning["synonyms"][0].get<std::string>());
                }
                else {
                    requestData.rSynonyms.push_back("");
                }

                // Get the first antonym from the antonyms array
                if (!meaning["antonyms"].empty()) {
                    requestData.rAntonyms.push_back(meaning["antonyms"][0].get<std::string>());
                }
                else {
                    requestData.rAntonyms.push_back("");
                }

                index++;
            }
        }
    }

    if (r.status_code == 404)
    {
        requestData.rWord = "Sorry, we don't have this word!";
    }
}
    

void Requests::clearData()
{
    requestData.hasData = false;
    requestData.rWord = "";
    requestData.rPartOfSpeech.clear();
    requestData.rDefinitions.clear();
    requestData.rSynonyms.clear();
    requestData.rAntonyms.clear();
    requestData.rExample.clear();
}