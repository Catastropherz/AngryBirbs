#pragma once
#include "box2d/box2d.h"

const inline float g_sizeScale = 100.0f; //100 pixels per meter
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