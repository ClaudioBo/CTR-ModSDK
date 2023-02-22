#ifndef TEX_H
#define TEX_H

#define NUM_PAINT_JOB 19
#define NUM_CHARACTERS 15

typedef union {
    struct {
        const char * front;
        const char * back;
        const char * floor;
        const char * brown;
        const char * motorside;
        const char * motortop;
        const char * bridge;
        const char * exhaust;
    };
    const char * p[8];
} Texture;

const int numTex = sizeof(Texture) / sizeof(char *);

typedef struct
{
    Texture colors[NUM_PAINT_JOB];
    Texture spriteTex;
    Texture spriteRacePos;
    Texture spriteMenuPos;
    Texture colorsMenuPos[NUM_CHARACTERS];
    Texture colorsRacePos[NUM_CHARACTERS];
} TexData;


#endif