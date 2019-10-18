#include "LedScreen.hpp"

LedScreen::LedScreen(Module *mod) {
    module = mod;
    BG = nvgRGBA(0, 0, 0, 0xff);
    OFF = nvgRGBA(0x0f, 0x0c, 0x00, 0x00); // 0xff);
    ON = nvgRGBA(0xff, 0xcc, 0x00, 0xff); // 0xff);5
    clearAll();
}

void LedScreen::clearAll() {
    for (int x = 0; x < MAXX; x++)
        for (int y = 0; y < MAXY; y++)
            dots[x][y] = 0;
}

void LedScreen::set(int x, int y, int alpha) {
    if (x >= MAXX || y >= MAXY) return;
    dots[x][y] = alpha;
}

void LedScreen::clr(int x, int y) {
    if (x >= MAXX || y >= MAXY) return;
    dots[x][y] = 0;
}
    
void LedScreen::draw(const DrawArgs &args) {
    if (!W) {
        W = (float)box.size.x / (float)MAXX;
        H = (float)box.size.y / (float)MAXY;
    }

    nvgFillColor(args.vg, BG);
    {
        nvgBeginPath(args.vg);
        nvgMoveTo(args.vg, 0, 0);
        nvgLineTo(args.vg, box.size.x, 0);
        nvgLineTo(args.vg, box.size.x, box.size.y);
        nvgLineTo(args.vg, 0, box.size.y);
        nvgClosePath(args.vg);
    }
    nvgFill(args.vg);

    for (int x = 0; x < MAXX; x++)
        for (int y = 0; y < MAXY; y++)
            drawSquare(args, x, y, dots[x][y]);
}    

void LedScreen::drawSquare(const DrawArgs &args, int _x, int _y, int alpha) {
    float x = _x * W + 0.5f;
    float y = _y * H + 0.5f;
    
    NVGcolor _on = nvgRGBA(0xff, 0xcc, 0x00, 0xff - _x * _y);
    nvgFillColor(args.vg, alpha ? _on : OFF); // ON
    {
        nvgBeginPath(args.vg);
        nvgMoveTo(args.vg, x, y);
        nvgLineTo(args.vg, x+W-0.5f, y);
        nvgLineTo(args.vg, x+W-0.5f, y+H-0.5f);
        nvgLineTo(args.vg, x, y+H-0.5f);
        nvgClosePath(args.vg);
    }
    nvgFill(args.vg);
}
