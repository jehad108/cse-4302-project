#include<raylib.h>

class sound{
    private:
    Sound sound_texture;
    public:
    sound(const char* path);
    void playSound();
    ~sound();
};