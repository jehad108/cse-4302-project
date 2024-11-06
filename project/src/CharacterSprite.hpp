#include <raylib.h>
using namespace std;
class playersprite
{
    public:
    Texture2D spriteSheet;
    Rectangle sourceRect;
    Rectangle destRect;
    Vector2 position;
    int frameCount;
    int currentFrame;
    float frameTime;
    float elapsedTime;
    Rectangle sourcerect{96, 0, 64, 64};
    playersprite(const char* imagePath, int totalFrames, float fps, Vector2 pos);
    void Update();
    void Draw(Rectangle destRect);
    void Reset();
    ~playersprite();
};