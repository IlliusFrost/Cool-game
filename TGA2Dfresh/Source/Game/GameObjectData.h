#pragma once
#include "stdafx.h"

struct ObjectData
{
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> myVelocity;
	Sprite mySprite;
	float myRadius;
	float myGravitationalPull;
	int myMass;
	bool isGrounded;
};