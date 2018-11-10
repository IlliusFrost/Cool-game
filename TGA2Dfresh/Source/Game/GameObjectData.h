#pragma once
#include "stdafx.h"

struct ObjectData
{
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> myVelocity;
	CommonUtilities::Vector2<float> myGravityVelocity;
	Sprite mySprite;
	float myVelocityIncrement;
	float myVelocityCap;
	float myRadius;
	int myMass;
	bool isGrounded;
};