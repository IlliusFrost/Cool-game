#pragma once
#include "tga2d/render/render_object.h"

namespace Tga2D
{
	class CTexture;
	class CCustomShape : public CRenderObjectCustom
	{
	public:
		CCustomShape();
		~CCustomShape();

		// Do this first, must be %3 (3, 6, 9, 12 etc..)
		int AddPoint(Tga2D::Vector2f aPoint, CColor aColor, Tga2D::Vector2f aUV = Tga2D::Vector2f(0, 0));
		void Reset();
		void RemovePoint(int aIndex);

		// Do this second
		void BuildShape();
		void Render();
		void SetTexture(const char* aPath);

		const CTexture* GetTexture() const { return myTexture; }
	private:
		CTexture* myTexture;
		bool myIsDirty;
		int myIndex;
		bool myHasTexture;
		
		
	};
}