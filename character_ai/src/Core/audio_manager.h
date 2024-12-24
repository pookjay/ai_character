#pragma once
#include <string>

class AudioManager {
	
public:
	AudioManager();

	void PlaySoundFromFile(std::string file);

	void PlaySoundFromFileAndWait(std::string file);

private:

};