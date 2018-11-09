#include "stdafx.h"

#include "animation/spineanimation.h"
#include <tga2d/animation/SpineAnimation_internal.h>

#define SPINE_SHORT_NAMES
#include <spine/spine.h>
#include <spine/extension.h>

using namespace Tga2D;
CSpineAnimation::CSpineAnimation()
{
	myPosition.Set(0, 0);
	myScale.Set(1, 1);
	myRotation = 0.0f;
	myFlipX = false;
	myFlipY = false;
	myColor.Set(1, 1, 1, 1);
}

Tga2D::CSpineAnimation::~CSpineAnimation()
{

}


void callback(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event)
{
	const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;

	CSpineAnimation* classInstance = static_cast<CSpineAnimation*>(state->userData);
	if (!classInstance)
	{
		return;
	}

	if (type == ANIMATION_EVENT)
	{
		std::string sEvent = event->stringValue ? event->stringValue : "";
		classInstance->OnEventCallback(entry->trackIndex, animationName, event->data->name, event->intValue, event->floatValue, sEvent);
	}
	else
	{
		classInstance->OnCallback(entry->trackIndex, animationName);
	}

}

void Tga2D::CSpineAnimation::Init(const char* aAtlasPath, const char* aBonePath)
{
	myInternalAnimation = new CSpineAnimation_Internal(aAtlasPath, aBonePath);
	myInternalAnimation->timeScale = 1;

	Skeleton* skeleton = myInternalAnimation->skeleton;
	skeleton->flipX = false;
	skeleton->flipY = false;
	Skeleton_setToSetupPose(skeleton);

	skeleton->x = 0;
	skeleton->y = 0;

	Skeleton_updateWorldTransform(skeleton);

	myInternalAnimation->myAnimationState->userData = this;
	myInternalAnimation->myAnimationState->listener = callback;
	
}

void Tga2D::CSpineAnimation::Update(float aTimeDelta)
{
	myInternalAnimation->skeleton->root->scaleX = myScale.x;
	myInternalAnimation->skeleton->root->scaleY = myScale.y;
	myInternalAnimation->skeleton->root->rotation= myRotation;
	myInternalAnimation->skeleton->x = myPosition.x * CEngine::GetInstance()->GetWindowSize().x;
	myInternalAnimation->skeleton->y = myPosition.y * CEngine::GetInstance()->GetWindowSize().y;
	myInternalAnimation->skeleton->flipX = myFlipX == true ? 1 : 0;
	myInternalAnimation->skeleton->flipY = myFlipY == true ? 1 : 0;
	myInternalAnimation->myColor = myColor;
	myInternalAnimation->update(aTimeDelta);
}

void Tga2D::CSpineAnimation::Render()
{
	myInternalAnimation->draw();
}

void Tga2D::CSpineAnimation::RenderDebug()
{
	myInternalAnimation->DrawDebug();
}

void Tga2D::CSpineAnimation::RegisterAnimationCallback(anim_callback_function aAnimCallback, int aRegisterID)
{
	myAnimCallbacks[aRegisterID] = (aAnimCallback);
}

void Tga2D::CSpineAnimation::RegisterAnimationEventCallback(anim_callback_function_event aAnimEvent, int aRegisterID)
{
	myAnimationCallbackEvents[aRegisterID] = (aAnimEvent);
}

void Tga2D::CSpineAnimation::RemoveCallback(int aRegisterID)
{
	myAnimCallbacks.erase(aRegisterID);
}

void Tga2D::CSpineAnimation::RemoveEventCallback(int aRegisterID)
{
	myAnimationCallbackEvents.erase(aRegisterID);
}

void Tga2D::CSpineAnimation::SetMixTimings(std::string aFrom, std::string aTo, float aDelay)
{
	myInternalAnimation->DoMixAnimation(aFrom, aTo, aDelay);

}

void Tga2D::CSpineAnimation::AddAnimationToQueue(int aTrackIndex, std::string aName, bool aLoop, float aDelay)
{
	myInternalAnimation->AddAnimationToQueue(aTrackIndex, aName, aLoop, aDelay);

}

void Tga2D::CSpineAnimation::SetCurrentAnimation(int aTrackIndex, std::string aName, bool aLoop)
{
	myInternalAnimation->SetCurrentAnimation(aTrackIndex, aName, aLoop);
}

const char* Tga2D::CSpineAnimation::GetCurrentAnimation(int aTrackIndex)
{
	return myInternalAnimation->GetCurrentAnimation(aTrackIndex);
}

void Tga2D::CSpineAnimation::ClearQueue()
{
	myInternalAnimation->ClearQueue();
}

void Tga2D::CSpineAnimation::OnCallback(int aTrackIndex, std::string aName)
{
	for (auto onCall : myAnimCallbacks)
	{
		onCall.second(aTrackIndex, aName);
	}
}

void Tga2D::CSpineAnimation::OnEventCallback(int aTrackIndex, std::string aName, std::string aEventName, int aIntVal, float aFloatVal, std::string aStringVal)
{
	for (auto onCall : myAnimationCallbackEvents)
	{
		onCall.second(aTrackIndex, aName, aEventName, aIntVal, aFloatVal, aStringVal);
	}
}

