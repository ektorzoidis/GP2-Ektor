#include "SDLAudio.h"

SDLAudio::SDLAudio()
{
    // Set up
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    // Output error if failed to initalise
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
        exit(-1);
    }
}

SDLAudio::~SDLAudio()
{
    SDL_Quit();
}

void SDLAudio::addSoundEffect(const char* path)
{
    // Load SFX
    Mix_Chunk* tmpChunk = Mix_LoadWAV(path);

    // Output success message
    if (tmpChunk != nullptr)
    {
        mSoundEffectBank.push_back(tmpChunk);
        std::cout << (mSoundEffectBank.size() - 1) << " Sound is Ready, path: " << path << '\n';
    }
    // Output error if failed to initalise
    else
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
    }
}

void SDLAudio::addAudioTrack(const char* path)
{
    // Load audio track
    backgroundMusic = Mix_LoadMUS(path);

    // Output error if failed to initalise
    if (backgroundMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void SDLAudio::playSoundEffect(const int which) const
{
    // Output error if out of range
    if (which > mSoundEffectBank.size() - 1)
    {
        std::cout << "Sound out of range.\n";
        return;
    }

    // Play SFX
    Mix_PlayChannel(-1, mSoundEffectBank[which], 0);

    // Output success message
    std::cout << "Played Sound: " << which << '\n';
}

void SDLAudio::playAudioTrack()
{
    // If song isn't already playing
    if (Mix_PlayingMusic() == 0)
    {
        //Play audio track and loop it
        Mix_PlayMusic(backgroundMusic, -1);
    }
}
