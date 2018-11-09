#pragma once


#define USE_VIDEO // If this is defined, you can play a video by using CVideo

#define USE_NOISE // If this is defined, a texture with perlin noise will be avalible in all shaders to play with
#define USE_LIGHTS // If this is defined, the engine will calculate per pixel lightning using CLight

#define CAN_USE_DDS_NOT_POWER_OF_TWO true
#define CAN_USE_OTHER_FORMATS_THAN_DDS true 

#define FONT_BUFF_SIZE 1024
#define MAX_TEXT_SPRITES 1024

#define NUMBER_OF_LIGHTS_ALLOWED 8 
