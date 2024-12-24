#pragma once

#include <string>

#include "Utility/json.hpp"

class OpenAiManager {
public:

	OpenAiManager();

	std::string GetCompletion(const std::string& prompt, const std::string& model = "gpt-3.5-turbo");

private:

	nlohmann::json message_request;

};

extern std::string GetEnvironmentalVariable(const char* name);

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response);