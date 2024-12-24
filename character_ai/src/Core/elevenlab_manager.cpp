#include "elevenlab_manager.h"

#include <fstream>
#include <iostream>
#include <vector>

#include <curl.h>


size_t WriteAudioCallback(void* contents, size_t size, size_t nmemb, void* response)
{
    size_t totalSize = size * nmemb;
    std::vector<char>* res = static_cast<std::vector<char>*>(response);
    res->insert(res->end(), (char*)contents, (char*)contents + totalSize);
    return totalSize;
}

bool GetAudioFromText(std::string& text)
{
    CURL* curl = curl_easy_init();

    if (curl) {
        std::string baseUrl = "https://api.elevenlabs.io/v1/text-to-speech/";
        std::string voiceId = "DRIQ49Y9B1OmoQ4Nseqg";

        std::vector<char> response;

        std::string payload = R"({"text":")" +  text + R"("})";

        // Set URL
        curl_easy_setopt(curl, CURLOPT_URL, (baseUrl + voiceId).c_str());

        // Set headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Xi-Api-Key: " + GetEnvironmentalVariable("ELEVENAI_KEY")).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set POST and POST fields
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, payload.size());

        // Write to response string
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteAudioCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Get results
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        std::ofstream audioFile("audiofile.mp3", std::ios::binary);
        if (audioFile)
        {
            audioFile.write(response.data(), response.size());
            audioFile.close();
            return true;
        }
        else {
            std::cout << "lol" << std::endl;
            return false;
        }
    }
}
