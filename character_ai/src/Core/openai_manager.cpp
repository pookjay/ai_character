#include "openai_manager.h"

#include <iostream>

#include <curl.h>

#include "Utility/json.hpp"


OpenAiManager::OpenAiManager()
{   
    message_request["messages"][0]["role"] = "system";
    message_request["messages"][0]["content"] = R"(You are a helpful assistant. Keep your answers short.)";

    //message_request["temperature"] = 0;
}

std::string OpenAiManager::GetCompletion(const std::string& prompt, const std::string& model)
{
    std::string apiKey = GetEnvironmentalVariable("OPENAI_KEY");
    std::string baseUrl = "https://api.openai.com/v1/chat/completions";
    std::string response;

    CURL* curl = curl_easy_init();

    if (curl) {
        message_request["model"] = model;

        nlohmann::json newPrompt;
        newPrompt["role"] = "user";
        newPrompt["content"] = prompt;
        message_request["messages"].push_back(newPrompt);

        std::string requestDataStr = message_request.dump().c_str();

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        curl_easy_setopt(curl, CURLOPT_URL, baseUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestDataStr.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, requestDataStr.length());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "Curl request failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);

        // return response;
        nlohmann::json jresponse = nlohmann::json::parse(response);
        std::string responseContent = jresponse["choices"][0]["message"]["content"].get<std::string>();

        nlohmann::json newMessage;
        newMessage["role"] = "assistant";
        newMessage["content"] = responseContent;
        message_request["messages"].push_back(newMessage);

        return responseContent;
    }
    return "";
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}
