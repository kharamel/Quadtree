//File: Dot.h
//Author: Sushil Kharal

#ifndef DOT_H
#define DOT_H
#include "Surface.h"
#include "Constants.h"

class Dot
{
  public:
    Dot(Surface* surfacep=NULL,
    int x=W/2, int y=H/2, int r=1,
    int red=255, int green=0, int blue=0,
        int speed=3, bool collided=false);

    int x() const;
    int y() const;
    int r() const;
    bool collided() const;
    bool & collided();
    void check_direction();
    void change_color();
    void draw();
    
private:
    Surface surface_;
    int x_;
    int y_;
    int r_;
    int red_;
    int green_;
    int blue_;
    int speed_;
    int xdir_;
    int ydir_;
    bool collided_;
};
#endif
