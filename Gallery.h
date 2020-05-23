#ifndef GALLERY_H
#define GALLERY_H

#include <vector>
#include <string>
#include <memory>

#include "SDL_utils.h"

class Gallery
{
    SDL_Renderer* renderer;
    SDL_Texture* mTexture;
    int mWidth;
	int mHeight;
    
public:
    
    Gallery(SDL_Renderer* renderer_);
    ~Gallery();
    bool loadFromRenderedText( TTF_Font* gFont, std::string textureText, SDL_Color textColor );
    bool loadTexture(std::string path);
    void render( int x, int y );
    void free();
    //static SDL_Renderer* last_renderer;
};

#endif // GALLERY_H
