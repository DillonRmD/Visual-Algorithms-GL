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

struct vaGame
{
    vaRect rects[30];
    size_t num_rects = sizeof(rects) / sizeof(rects[0]);
    float data[30];
};

vaGame game;

void AssingValuesRandomly(vaGame* game)
{
    srand (time(NULL));
    for(int i = 0; i < game->num_rects; i++)
    {
        game->data[i] = 0.05 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.0 - 0.05)));
    }
}

//TODO(Dillon): This is gross and hacky!
void AssignValuesToData_DEBUG(vaGame* game)
{
    game->data[0] = 0.43;
    game->data[1] = 0.61;
    game->data[2] = 0.62;
    game->data[3] = 0.16;
    game->data[4] = 0.24;
    game->data[5] = 0.69;
    game->data[6] = 0.15;
    game->data[7] = 0.24;
    game->data[8] = 0.63;
    game->data[9] = 0.39;
    game->data[10] = 0.14;
    game->data[11] = 0.61;
    game->data[12] = 0.39;
    game->data[13] = 0.22;
    game->data[14] = 0.35;
    game->data[15] = 0.18;
    game->data[16] = 0.07;
    game->data[17] = 0.14;
    game->data[18] = 0.10;
    game->data[19] = 0.64;
    game->data[20] = 0.81;
    game->data[21] = 0.95;
    game->data[22] = 0.47;
    game->data[23] = 0.44;
    game->data[24] = 0.81;
    game->data[25] = 0.26;
    game->data[26] = 0.81;
    game->data[27] = 0.65;
    game->data[28] = 0.07;
    game->data[29] = 0.14;
}

void DrawRects(vaRect* rects, int num_rects)
{
    for(int i = 0; i < num_rects; i++)
    {
        vaRect currRect = rects[i];

        glBegin(GL_QUADS);
        {
            glColor4f(currRect.color.r, currRect.color.g, currRect.color.b, currRect.color.a);
            glVertex2f(currRect.position.x, currRect.position.y);
            glVertex2f(currRect.position.x + currRect.size.width, currRect.position.y);
            glVertex2f(currRect.position.x + currRect.size.width, currRect.position.y + currRect.size.height);
            glVertex2f(currRect.position.x, currRect.position.y + currRect.size.height);
        }
        glEnd();
    }  
}; 

unsigned int dtb_init(dtb_platform* platform)
{
    //AssignValuesToData_DEBUG(&game);
    AssingValuesRandomly(&game);

    float xPosition = -1.f;
    // Set initial values
    for(int i = 0; i < game.num_rects; i++)
    {
        game.rects[i].color = dtbVec4(1.f, 0.f, 0.f, 1.f);

        game.rects[i].position.y = -1;
        game.rects[i].size.height = game.data[i];
        game.rects[i].position.x = xPosition;
        game.rects[i].size.width = 0.05f;
        xPosition += game.rects[i].size.width + 0.005f;
    }

    return 0;
}

void dtb_loop(dtb_platform* platform, float delta_time)
{
    DrawRects(game.rects, game.num_rects);
    static bool sort = false;
    if(dtb_key_is_pressed(platform, DTB_KEY_SPACE))
    {
        sort = true;
    }

    // Then run the sorting algorithm
    if(sort == true)
    {
        for (int i = 0; i < game.num_rects; i++)
        {
            for (int j = i + 1; j < game.num_rects; j++)
            {
                if (game.data[i] > game.data[j])
                {
                    float temp = game.data[i];
                    game.data[i] = game.data[j];
                    game.data[j] = temp;
                }

            }
        }
    }
}
