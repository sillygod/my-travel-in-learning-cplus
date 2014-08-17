//Sprite.cpp


#include "Sprite.h"

Sprite::Sprite(HINSTANCE hAppInst, int imageID, int maskID, const Circle& bc, const Vec2& p0, const Vec2& v0)
{
    mhAppInst = hAppInst;

	// Load the bitmap resources.
	mhImage = LoadBitmap(hAppInst, MAKEINTRESOURCE(imageID));
	mhMask  = LoadBitmap(hAppInst, MAKEINTRESOURCE(maskID));

	// Get the BITMAP structure for each of the bitmaps.
	GetObject(mhImage, sizeof(BITMAP), &mImageBM);
	GetObject(mhMask,  sizeof(BITMAP), &mMaskBM);


	mBoundingCircle = bc;
	mPosition       = p0;
	mVelocity       = v0;

}

Sprite::~Sprite()
{
	// Free the resources we created in the constructor.
	DeleteObject(mhImage);
	DeleteObject(mhMask);
}


int Sprite::height()
{
    return mImageBM.bmHeight;
}

int Sprite::width()
{
    return mImageBM.bmWidth;
}

void Sprite::draw(HDC hBackBufferDC, HDC hSpriteDC)
{

    int w = width();
	int h = height();

	int x = (int)mPosition.x - (w / 2);
	int y = (int)mPosition.y - (h / 2);

	// Note: For this masking technique to work, it is assumed
	// the backbuffer bitmap has been cleared to some
	// non-zero value.

	// Select the mask bitmap.
	HGDIOBJ oldObj = SelectObject(hSpriteDC, mhMask);

	// Draw the mask to the backbuffer with SRCAND.  This
	// only draws the black pixels in the mask to the backbuffer,
	// thereby marking the pixels we want to draw the sprite
	// image onto.
	BitBlt(hBackBufferDC, x, y, w, h, hSpriteDC, 0, 0, SRCAND);

	// Now select the image bitmap.
	SelectObject(hSpriteDC, mhImage);

	// Draw the image to the backbuffer with SRCPAINT.  This
	// will only draw the image onto the pixels that where previously
	// marked black by the mask.
	BitBlt(hBackBufferDC, x, y, w, h, hSpriteDC, 0, 0, SRCPAINT);

	// Restore the original bitmap object.
	SelectObject(hSpriteDC, oldObj);


}

void Sprite::update(float dt)
{
    // Update the sprites position.
	mPosition += mVelocity * dt;

	// Update bounding circle, too.  That is, the bounding
	// circle moves with the sprite.
	mBoundingCircle.c = mPosition;

}
