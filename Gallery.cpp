#include "Gallery.h"

Gallery::Gallery(SDL_Renderer* renderer_)
{
    renderer = renderer_;
    mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Gallery::~Gallery()
{
    free();
}

bool Gallery::loadTexture(std::string path )
{
	//Get rid of preexisting texture
	free();
    SDL_Texture* newTexture = NULL;
	//Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else {
		//Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        //Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		//Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    mTexture = newTexture;
    return newTexture;
}

bool Gallery::loadFromRenderedText( TTF_Font* gFont, std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}

void Gallery::render( int x_, int y_ )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x_, y_, mWidth, mHeight };
	SDL_RenderCopy( renderer, mTexture, NULL, &renderQuad );
}

void Gallery::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}