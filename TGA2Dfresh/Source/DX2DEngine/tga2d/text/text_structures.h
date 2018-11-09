#pragma once

namespace Tga2D
{
	namespace Tga2DText
	{
		struct SCharData
		{
			Tga2D::Vector2<float> myTopLeftUV;
			Tga2D::Vector2<float> myBottomRightUV;

			short myWidth;
			short myHeight;
			short myAdvanceX; //Distance to next character.
			short myAdvanceY;
			short myBearingX;
			short myBearingY;
			char myChar;
		};

		struct STextToRender
		{
			Vector2f mySize;
			Vector2f myUV;
			Vector2f uvScale;
			Vector2f myPosition;
			CColor myColor;
		};

		struct SCountData
		{
			int xNCount = 0;
			int xPCount = 0;
			int yNCount = 0;
			int yPCount = 0;
		};

		struct SOutlineOffset
		{
			int xDelta = 0;
			int yDelta = 0;

		};
	}
}