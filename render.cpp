#include "window.h"

void fill(int x1, int y1, int x2, int y2, RGBA col)
{
    static Frame frame;
    cout << "frame.width = " << frame.width << "frame.height = " << frame.height << endl;
    for (int x=0; x<frame.width; x++)
        for (int y=0; y<frame.height; y++)
        {
            cout << "x: " << x << "y: " << y << endl;
            frame.pixels[x+((y)*frame.width)] = col;    
        }   
}