#include <iostream>

#include "Core/speech_recognition_manager.h"
#include "Core/openai_manager.h"
#include "Core/elevenlab_manager.h"
#include "Core/audio_manager.h"

int main()
{
	AudioManager audio;
	OpenAiManager openai;

	while (true)
	{
		//std::cout << "Send a message" << std::endl;
		std::string req;

		if (GetTextFromSpeech(req))
		{
			std::cout << "User: " << req << std::endl;

			std::cout << std::endl;

			std::string response = openai.GetCompletion(req);

			GetAudioFromText(response);

			std::cout << "Assistant: " << response << std::endl << std::endl;

			audio.PlaySoundFromFileAndWait("audiofile.mp3");
		}
	}

}

