/*
This class will store a texture bound to DX11
*/
#pragma once

struct ID3D11ShaderResourceView;
struct ID3D11RenderTargetView;
namespace Tga2D
{
	class CTexture
	{
		friend class CDirectEngine;
	public:
		CTexture();
		~CTexture();

	public:
		std::string myPath;
		uint64_t myID;
		ID3D11ShaderResourceView* myResource;
		Vector2f mySize;
		Vector2<unsigned int> myImageSize;
		unsigned int myVideoMemeorySize;
		bool myIsFailedTexture;
		bool myIsReleased;

		// DDS format needs to be: A8R8G8B8
		CColor GetPixelColor(unsigned short aX, unsigned short aY, bool aRefreshData = false);
		bool IsWhiteTexture();
	private:
		BYTE* GrabPixelColors();
		BYTE* myPixelColors;
		bool myHasGrabbedColorData;
	protected:
		void InitAsRenderTarget(CDirectEngine* aDirectEngine, Tga2D::Vector2f aSize);
		ID3D11RenderTargetView* myRenderTarget;
	};

	
	class CRendertarget : public CTexture
	{
	public:
		CRendertarget();
		~CRendertarget();

	public:
		ID3D11RenderTargetView* myTarget;
	};
}
