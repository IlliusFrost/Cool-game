#include "stdafx.h"

#include "UI.h"

void UIManager::SetPlayerScoreImage(int aPlayerScore,int aPlayerID)
{
	if (aPlayerScore <= myPlayerScoreSprites.size())
	{
	myPlayerScoreOutput[aPlayerID] = myPlayerScoreSprites[aPlayerScore];
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
		if (i == 0)
		{
			myPlayerScoreOutput[0]->SetPosition({ 0.01f,0.1f });
		}
		else if (i == 1)
		{
			myPlayerScoreOutput[1]->SetPosition({ 0.8f,0.1f });
		}
		else if (i == 2)
		{
			myPlayerScoreOutput[2]->SetPosition({ 0.8f,0.8f });
		}
		else
		{
			myPlayerScoreOutput[3]->SetPosition({ 0.01f,0.8f });
		}
		std::cout << myPlayerScoreOutput[i]->GetPosition().x << " " << myPlayerScoreOutput[i]->GetPosition().y << " "<< i<<  std::endl;
		myPlayerScoreOutput[i]->Render();
	}
	
}

void UIManager::Update()
{

}

UIManager::UIManager()
{

	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin(), new Tga2D::CSprite("sprites/ScoreImage1.png"));
	myPlayerScoreSprites[0]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[0]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[0]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin()+ 1, new Tga2D::CSprite("sprites/ScoreImage2.png"));
	myPlayerScoreSprites[1]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[1]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[1]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 2, new Tga2D::CSprite("sprites/ScoreImage3.png"));
	myPlayerScoreSprites[2]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[2]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[2]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 3, new Tga2D::CSprite("sprites/ScoreImage4.png"));
	myPlayerScoreSprites[3]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[3]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[3]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 4, new Tga2D::CSprite("sprites/ScoreImage5.png"));
	myPlayerScoreSprites[4]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[4]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[4]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 5, new Tga2D::CSprite("sprites/ScoreImage6.png"));
	myPlayerScoreSprites[5]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[5]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[5]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 6, new Tga2D::CSprite("sprites/ScoreImage7.png"));
	myPlayerScoreSprites[6]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[6]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[6]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 7, new Tga2D::CSprite("sprites/ScoreImage8.png"));
	myPlayerScoreSprites[7]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[7]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[7]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 8, new Tga2D::CSprite("sprites/ScoreImage9.png"));
	myPlayerScoreSprites[8]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[8]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[8]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 9, new Tga2D::CSprite("sprites/ScoreImage10.png"));
	myPlayerScoreSprites[9]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[9]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[9]->SetSizeRelativeToImage({ 2.f, 2.f });
	myPlayerScoreSprites.insert(myPlayerScoreSprites.begin() + 10, new Tga2D::CSprite("sprites/ScoreImage11.png"));
	myPlayerScoreSprites[10]->SetPivot({ 0.f,0.f });
	myPlayerScoreSprites[10]->SetPosition({ 0.0f,0.0f });
	myPlayerScoreSprites[10]->SetSizeRelativeToImage({ 2.f, 2.f });

	myPlayerScoreOutput.insert(myPlayerScoreOutput.begin(), myPlayerScoreSprites[0]);
	myPlayerScoreOutput.insert(myPlayerScoreOutput.begin(), myPlayerScoreSprites[0]);
	myPlayerScoreOutput.insert(myPlayerScoreOutput.begin(), myPlayerScoreSprites[0]);
	myPlayerScoreOutput.insert(myPlayerScoreOutput.begin(), myPlayerScoreSprites[0]);



}