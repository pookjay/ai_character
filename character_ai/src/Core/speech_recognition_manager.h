#pragma once

#include <iostream> 
#include <stdlib.h>
#include <speechapi_cxx.h>

bool GetTextFromSpeech(std::string& text);

std::string GetEnvironmentalVariable(const char* name);