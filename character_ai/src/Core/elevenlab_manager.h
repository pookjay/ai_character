#pragma once

#include <string>

size_t WriteAudioCallback(void* contents, size_t size, size_t nmemb, void* response);

bool GetAudioFromText(std::string& text);

extern std::string GetEnvironmentalVariable(const char* name);
