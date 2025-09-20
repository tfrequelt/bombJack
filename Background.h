#pragma once
namespace Tmpl8
{
    class Background
    {
    public:
        Background();
        ~Background();

        void Init();
        void Draw(Surface* screen);

        Surface* backgroundSurface;
        static const int ORIGINAL_SIZE = 224;
        static const int SCREEN_SIZE = 896;
    };
}