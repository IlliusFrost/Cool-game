#pragma once
#include "stdafx.h"

struct ObjectData
{
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> myVelocity;
	CommonUtilities::Vector2<float> myGravitationalVelocity;
	Vector2f latestCollideObjectPosition;
	Sprite mySprite;
	float myVelocityIncrement;
	float myVelocityCap;
	float myRadius;
	float myRotation;
	int myMass;
	unsigned int myControllerData;
	bool isGrounded;
	bool isJumping;
};