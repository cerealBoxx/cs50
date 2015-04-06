//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600

#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

#define ROW_HEIGHT 10

// lives
#define LIVES 3

// paddle width
#define PADDLE_WIDTH 60

//brick width
#define BRICK_WIDTH 35

#define MARGIN 2.5

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
void updateScoreboardEnd(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void movePaddle(GEvent event, GRect paddle, GWindow window);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    //add objects to window
    
    add(window, ball);
    add(window, paddle);
    add(window, label);
    double velocityX = drand48()*3; 
    double velocityY = 1.0;
    waitForClick();
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {           
        // move circle along x-axis
        move(ball, velocityX , velocityY);
        
        if (getY(ball) >= getHeight(window))
        {
            lives--;
            if(lives==0 || points==bricks)
            {
                updateScoreboardEnd(window,label, points);
                break;
            }
            else 
            {
                pause(1000);
                setLocation(ball, WIDTH/2, HEIGHT/2);
                waitForClick();
            }
            
        }

        else if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocityX = -velocityX;
            
        }
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
        }
        
        else if (getY(ball) <= 0)
        {
            velocityY = -velocityY;
        }
        
        // linger before moving again
        pause(10);
        
        GObject object = detectCollision(window, ball);
        
        if(object != NULL)
        {
            if(object == paddle)
            {   
                if(getX(ball) > getX(paddle) && getY(ball)== getY(paddle))
                {
                    velocityY = -velocityY;
                }
                else
                {
                    velocityY = -velocityY;
                } 
            }
        
            else if(strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                              
                velocityY = -velocityY;
                points++;
                updateScoreboard(window,label,points);
            
            }
        }
        
        GEvent move = getNextEvent(MOUSE_EVENT);
        movePaddle(move, paddle, window);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    double x = 0;
    double y = 0;
    char *colors[] = {"RED","MAGENTA","ORANGE","YELLOW", "CYAN"};
    double margin_down = 3*ROW_HEIGHT;
    
    for(int r = 0; r < ROWS; r++)
    {      
        for(int c = 0; c < COLS; c++)
        {
           x = c*(BRICK_WIDTH+5) + MARGIN;
           y = r*(ROW_HEIGHT +5) + margin_down;
           GRect brick = newGRect(x, y, BRICK_WIDTH, ROW_HEIGHT);
           setFilled(brick, true);
           setColor(brick, colors[r]);
           add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2, HEIGHT/2, RADIUS, RADIUS);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double x = (getWidth(window) - PADDLE_WIDTH) / 2;
    double y = (getHeight(window) - 4*ROW_HEIGHT);
    GRect paddle = newGRect(x, y, PADDLE_WIDTH, ROW_HEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-18");
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    return label;
}
/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

void updateScoreboardEnd(GWindow window, GLabel label, int points)
{
    char s[25];
    sprintf(s, "Final score: %i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

void movePaddle(GEvent event, GRect paddle, GWindow window)
{
    if(event != NULL)
    {
        if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - PADDLE_WIDTH/2;
                double y = (getHeight(window) - 4*ROW_HEIGHT);
                
                if (x + PADDLE_WIDTH >= WIDTH-MARGIN)
                {
                   setLocation(paddle, WIDTH - PADDLE_WIDTH - MARGIN, y);
                }       

                else if (getX(event) - PADDLE_WIDTH/2 - MARGIN <= 0)
                {
                    setLocation(paddle, 0+MARGIN, y);
                }
                else
                {
                    setLocation(paddle, x, y);
                }
            }
    }
}


/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
