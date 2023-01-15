#pragma once
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <iostream>
#include <vector>

class SDLAudio
{
public:
	// -Methods
	/// <summary>
	/// SDLAudio constructor.
	/// </summary>
	SDLAudio();
	/// <summary>
	/// SDLAudio destructor.
	/// </summary>
	~SDLAudio();
	/// <summary>
	/// Add SFX.
	/// </summary>
	void addSoundEffect(const char* path);
	/// <summary>
	/// Add audio track.
	/// </summary>
	void addAudioTrack(const char* path);
	/// <summary>
	/// Play SFX.
	/// </summary>
	void playSoundEffect(const int which) const;
	/// <summary>
	/// Play audio track.
	/// </summary>
	void playAudioTrack();

private:
	// -Fields
	Mix_Music* backgroundMusic;
	std::vector<Mix_Chunk*> mSoundEffectBank;
};

