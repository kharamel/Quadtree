//File: Dot.cpp
//Name: Sushil Kharal
//Description: Implementation of functions in Dot.h file

#include "Dot.h"

Dot::Dot(Surface* surfacep, int x, int y, int r,
    int red, int green, int blue, int speed, bool collided)
    : surface_(*surfacep), x_(x), y_(y), r_(r),
      red_(red), green_(green), blue_(blue),
      speed_(speed), collided_(collided)
{
    xdir_ = (sin(rand() % 10) < 0 ? -speed_ : speed_);
    ydir_ = (sin(rand() % 10) < 0 ? -speed_ : speed_);
}


int Dot::x() const
{
    return x_;
}


int Dot::y() const
{
    return y_;
}

int Dot::r() const
{
    return r_;
}

bool Dot::collided() const
{
    return collided_;
}

bool & Dot::collided()
{
    return collided_;
}

// If dot/circle reaches edge of screen change direction of movement accordingly.
void Dot::check_direction()
{
    if (x_ >= W || x_ <= 0)
    {
        xdir_ = -xdir_;
    }

    if (y_ >= H || y_ <= 0)
    {
        ydir_ = -ydir_;
    }        
    x_ += xdir_;
    y_ += ydir_;
}

void Dot::change_color()
{
    red_ = 0;
    green_ = 0;
    blue_ = 255;
}

// draw the dots on the surface
void Dot::draw()
{
    surface_.put_circle(x_, y_, r_, red_, green_, blue_);
}


