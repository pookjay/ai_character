#include "audio_manager.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_mixer.h>

AudioManager::AudioManager()
{
	int init = SDL_Init(SDL_INIT_AUDIO);
	Mix_VolumeMusic(128 / 2);
}

void AudioManager::PlaySoundFromFile(std::string file)
{
	SDL_AudioDeviceID audioDeviceId = 0;
	int channelCount = 0;

	int i = 0;

	Mix_Music* soundPlayer = nullptr;
	Mix_Chunk* sound = nullptr;

	SDL_AudioSpec audioSpec;
	SDL_zero(audioSpec);
	audioSpec.format = SDL_AUDIO_F32;
	audioSpec.channels = 2;
	audioSpec.freq = 44100;

	audioDeviceId = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec);

	Mix_OpenAudio(audioDeviceId, nullptr);

	soundPlayer = Mix_LoadMUS("audiofile.mp3");

	Mix_PlayMusic(soundPlayer, 0);

	//Mix_FreeMusic(soundPlayer);
	//Mix_CloseAudio();
}

void AudioManager::PlaySoundFromFileAndWait(std::string file)
{
	SDL_AudioDeviceID audioDeviceId = 0;
	int channelCount = 0;

	Mix_Music* soundPlayer = nullptr;
	Mix_Chunk* sound = nullptr;

	SDL_AudioSpec audioSpec;
	SDL_zero(audioSpec);
	audioSpec.format = SDL_AUDIO_F32;
	audioSpec.channels = 2;
	audioSpec.freq = 44100;

	audioDeviceId = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audioSpec);

	Mix_OpenAudio(audioDeviceId, nullptr);

	soundPlayer = Mix_LoadMUS("audiofile.mp3");

	Mix_PlayMusic(soundPlayer, 0);

	while (Mix_PlayingMusic())
	{
		SDL_Delay(100);
	}

	Mix_FreeMusic(soundPlayer);

	Mix_CloseAudio();
}
