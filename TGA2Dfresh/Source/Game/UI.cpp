#include "stdafx.h"

#include "UI.h"

void UIManager::SetPlayerScoreImage(int aPlayerScore)
{
	if (aPlayerScore <= myPlayerScoreSprites.size())
	{
		myPlayerScoreOutput[0] = myPlayerScoreSprites[aPlayerScore];
	}
	else
	{
		std::cout << "Score too large! Score is " <<aPlayerScore << " and the amount of score sprites is " << myPlayerScoreSprites.size() << "!" << std::endl;
	}

}

void UIManager::Draw()
{
	for (int i = 0; i < myPlayerScoreOutput.size(); ++i)
	{
		myPlayerScoreOutput[i]->Render();
	}
	
}

void UIManager::Update()
{

}

UIManager::UIManager()
{

	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin(), new Tga2D::CSprite("sprites/PlayerTwo.png"));
	myPlayerScoreSprites[0]->SetPivot({ 0.5f,0.5f });
	myPlayerScoreSprites[0]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin()+ 1, new Tga2D::CSprite("sprites/PlayerThree.png"));
	myPlayerScoreSprites[1]->SetPivot({ 0.5f,0.5f });
	myPlayerScoreSprites[1]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 2, new Tga2D::CSprite("sprites/PlayerFour.png"));
	myPlayerScoreSprites[2]->SetPivot({ 0.5f,0.5f });
	myPlayerScoreSprites[2]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 3, new Tga2D::CSprite("sprites/SpaceJunk.png"));
	myPlayerScoreSprites[3]->SetPivot({ 0.5f,0.5f });
	myPlayerScoreSprites[3]->SetPosition({ 0.0f,0.0f });

	myPlayerScoreOutput.insert(myPlayerScoreOutput.begin(), myPlayerScoreSprites[0]);
}