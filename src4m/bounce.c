/**
 * bounce.c
 *
 * David J. Malan
 * malan@harvard.edu
 *
 * Bounces a circle back and forth in a window.
 */

// standard libraries
#include <stdio.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

int main(void)
{
    // instantiate window
    GWindow window = newGWindow(320, 240);

    // instantiate circle
    GOval circle = newGOval(0, 110, 20, 20);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle);
    
    // initial velocity
    double velocityX = 1.0;
    double velocityY = 1.0;
    
    // bounce forever
    while (true)
    {
        // move circle along x-axis
        move(circle, velocityX, velocityY);

        // bounce off right edge of window
        if (getY(circle) + getWidth(circle)/2 >= getHeight(window))
        {
           velocityY = -velocityY;

        }
        else if(getY(circle) + getWidth(circle)<=0)
        {
            velocityY = -velocityY;
            velocityX = -velocityX;
        }

        // bounce off left edge of window
        else if (getX(circle) <= 0)
        {
            velocityX = -velocityX;
        }

        // linger before moving again
        pause(10);
    }
}
