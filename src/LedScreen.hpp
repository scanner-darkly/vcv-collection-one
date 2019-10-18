#include "rack.hpp"
#include "plugin.hpp"
 
struct LedScreen : Widget {
    
    public: 
        static const int MAXX = 16;
        static const int MAXY = 16;

        int dots[MAXX][MAXY];

        LedScreen(Module *mod);
        void clearAll(void);
        void set(int x, int y, int alpha);
        void clr(int x, int y);
        
    private:
        Module *module;
        NVGcolor OFF, ON, BG;
        float W = 0, H;
        
        void draw(const DrawArgs &args) override;
        void drawSquare(const DrawArgs &args, int _x, int _y, int alpha);
};
