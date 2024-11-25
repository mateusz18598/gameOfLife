#pragma once

struct RGBA {
    unsigned char r, g, b, a;
};

struct Frame {
    int width, height;
    RGBA *pixels = 0;
};