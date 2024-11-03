#include "sound.hpp"

sound::sound(const char *path)
{
    sound_texture = LoadSound(path);
    SetSoundVolume(sound_texture, 1.5);
}

void sound::playSound()
{
    PlaySound(sound_texture);
}

sound::~sound()
{
    UnloadSound(sound_texture);
}
