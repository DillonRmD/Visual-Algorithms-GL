#include <stdio.h>

#include "dtb_platform.h"

#define DTB_MATH_USE_TYPES
#include "dtb_math.h"

#include <stdlib.h>
#include <ctime>

struct vaRect
{
    v2 position;
    v2 size; //NOTE(Dillon): This may be redudant since all rectangles are the same size
    v4 color;
};

void DrawRects(vaRect* rects, int num_rects)
{
    for(int i = 0; i < num_rects; i++)
    {
        vaRect currRect = rects[i];

        glBegin(GL_QUADS);
        {
            glColor4f(currRect.color.r, currRect.color.g, currRect.color.b, currRect.color.a);
            glVertex2f(currRect.position.x, currRect.position.y);
            glVertex2f(currRect.position.x + currRect.size.x, currRect.position.y);
            glVertex2f(currRect.position.x + currRect.size.x, currRect.position.y + currRect.size.y);
            glVertex2f(currRect.position.x, currRect.position.y + currRect.size.y);
        }
        glEnd();
    }  
};

struct vaGame
{
    vaRect rects[30];
    size_t num_rects = sizeof(rects) / sizeof(rects[0]);
    float data[30];
};

vaGame game;

//TODO(Dillon): This is gross and hacky!
void AssignValuesToData_DEBUG(vaGame* game)
{
    game->data[0] = -0.43;
    game->data[0] = 0.61;
    game->data[0] = 0.62;
    game->data[0] = -0.16;
    game->data[0] = -0.24;
    game->data[0] = 0.69;
    game->data[0] = -0.01;
    game->data[0] = 0.63;
    game->data[0] = 0.39;
    game->data[0] = -0.14;
    game->data[0] = 0.61;
    game->data[0] = 0.39;
    game->data[0] = 0.22;
    game->data[0] = -0.35;
    game->data[0] = 0.18;
    game->data[0] = 0.07;
    game->data[0] = -0.14;
    game->data[0] = -0.10;
    game->data[0] = 0.64;
    game->data[0] = 0.81;
    game->data[0] = 0.95;
    game->data[0] = -0.47;
    game->data[0] = 0.44;
    game->data[0] = 0.81;
    game->data[0] = 0.26;
    game->data[0] = 0.81;
    game->data[0] = 0.65;
    game->data[0] = 0.07;
    game->data[0] = 0.14;
    game->data[0] = -0.22;
}

unsigned int dtb_init(dtb_platform* platform)
{
    AssignValuesToData_DEBUG(&game);

    float xPosition = -1.f;
    // Set initial values
    for(int i = 0; i < game.num_rects; i++)
    {
        game.rects[i].color = dtbVec4(1.f, 1.f, 1.f, 1.f);

        game.rects[i].position.y = -1;
        game.rects[i].size.height = 0.25f;
        game.rects[i].position.x = xPosition;
        game.rects[i].size.width = 0.05f;
        xPosition += game.rects[i].size.width;
    }

    return 0;
}

void dtb_loop(dtb_platform* platform, float delta_time)
{
    DrawRects(game.rects, game.num_rects);    
}
