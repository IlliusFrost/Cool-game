#include "stdafx.h"
#include <tga2d/audio/audio.h>
#include <tga2d/audio/audio_out.h>
using namespace Tga2D;

#pragma comment(lib,"bass.lib")

AudioOut* CAudio::myAudioOut = nullptr;
CAudio::CAudio()
	:myLoadedAudio(0),
	myChannel(0)
{
	myPosition.Set(0, 0);
}
CAudio::~CAudio()
{

}

void CAudio::Init(const char * aPath, bool aIsLooping)
{
	if (!myAudioOut)
	{
		myAudioOut = new Tga2D::AudioOut();
	}
	myLoadedAudio = myAudioOut->Load(aPath, aIsLooping);

}

void CAudio::Play()
{
	if (myLoadedAudio == 0)
	{
		return;
	}
	myAudioOut->Play(myLoadedAudio, myChannel);
}

void Tga2D::CAudio::SetVolume(float aVolume)
{
	myAudioOut->SetVolume(myChannel, aVolume);
}

void Tga2D::CAudio::SetPosition(Tga2D::Vector2f aPosition)
{
	myPosition = aPosition;
	myAudioOut->SetPosition(myChannel, myPosition);
}

void CAudio::Stop(bool aImmediately)
{
	if (myLoadedAudio == 0)
	{
		return;
	}
	myAudioOut->Stop(myLoadedAudio, aImmediately);
}
