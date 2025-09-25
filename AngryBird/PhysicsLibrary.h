#pragma once
#include "box2d/box2d.h"

const inline unsigned int CATEGORY_SPRITE =			0b00000001;
const inline unsigned int CATEGORY_PHYSICSOBJECT =	0b00000010;
const inline unsigned int CATEGORY_BIRD =			0b00000100;
const inline unsigned int CATEGORY_DEFAULT =		0b00001000;

const inline float g_sizeScale = 50.0f; //pixels per meter
const inline b2Vec2 g_gravity(0.0f, 9.81f);

const inline float g_timeStep = 1.0f / 60.0f;

inline float DegreesToRadians(float _degrees) 
{ 
	return _degrees * b2_pi / 180.0f; 
}

inline float RadiansToDegrees(float _radians)
{
	return _radians * 180.0f / b2_pi;
}