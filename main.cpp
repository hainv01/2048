#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>

#include "Board.h"
#include "Gallery.h"

using namespace std;

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 600;

const char WINDOW_TITLE[] = "2048";

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer;

Gallery* background = NULL;

Gallery* score_img = NULL, *bestscore_img = NULL;

Gallery* GameOver_img = NULL, *Win_img = NULL;

Gallery* Sc_text = NULL, *Best_text = NULL;

Gallery* Num = NULL;

SDL_Rect score_img_size;

bool loadBackground();

void GetBestScore(int &BestScore);

void UpdataBestScore(int &Score, int &BestScore);

void PrintScore(std::string const sc);

void ShowBoard(Board GameBoard, std::string const sc, std::string const best);

int main() {
    srand(time(0));
    initSDL(gWindow, gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    background = new Gallery(gRenderer);
    score_img = new Gallery(gRenderer), bestscore_img = new Gallery(gRenderer);
    GameOver_img = new Gallery(gRenderer), Win_img = new Gallery(gRenderer);
    Num = new Gallery(gRenderer);
	Sc_text = new Gallery(gRenderer), Best_text = new Gallery(gRenderer);
    score_img_size.h = 55; score_img_size.w = 124;
    int BestScore;
    int Score = 0;
    if ( !loadBackground()  ) {
		printf( "Failed to load BackGround!\n" );
	}
    else {
		// if ( !loadBGM() ) {
		// 	printf( "Failed to load BGM!\n" );
		// }
		//Main loop flag
        Board GameBoard;
		GetBestScore(BestScore);
        bool quit = false;
        int move = NoMove;
        ShowBoard(GameBoard, to_string(Score), to_string(BestScore));
        
		//Event handler
		SDL_Event e;
		//Load BGM
		//Mix_PlayMusic( BGM, -1 );
		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
                else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
                    switch(e.key.keysym.sym) {
					case SDLK_w:
						move = Up;
						break;
					case SDLK_a:
						move = Left;
						break;
					case SDLK_s:
						move = Down;
						break;
					case SDLK_d:
						move = Right;
						break;
                    }
                }
			}
			if(move != NoMove && !GameBoard.CheckGameOver() && !GameBoard.CheckWin()) {
                Score = GameBoard.GetScore();
                UpdataBestScore( Score, BestScore);
                if (GameBoard.Move(move)) {
                    ShowBoard(GameBoard, to_string(Score), to_string(BestScore));
                }
                move = NoMove;
		    }
		}
		ofstream file("BestScore.txt", ios::out);
        if (file.is_open()) {
            UpdataBestScore(Score, BestScore);
            file << BestScore;
            file.close();
        }
	}
    delete background;
    delete score_img, bestscore_img;
    delete GameOver_img, Win_img;
    delete Num;
	delete Sc_text, Best_text;
	// Mix_FreeMusic( BGM );
	// BGM = NULL;
	quitSDL(gWindow, gRenderer);
	return 0;
}

bool loadBackground()
{
	//Loading success flag
	bool success = true;
	//Load banner background
	if( !background->loadTexture( "Img/2048.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    if( !score_img->loadTexture( "Img/score.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    if( !bestscore_img->loadTexture( "Img/best.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    if( !GameOver_img->loadTexture( "Img/gameover.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
    if( !Win_img->loadTexture( "Img/win.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	return success;
}

void GetBestScore(int &BestScore) {
    ifstream file("BestScore.txt");
    if (file.is_open()) {
        file >> BestScore;
        file.close();
    }
}

void UpdataBestScore(int &Score, int &BestScore) {
    if (Score > BestScore) {
        BestScore = Score;
    }
}

void ShowBoard(Board GameBoard, std::string const sc, std::string const best) {
    //Clear screen
    SDL_SetRenderDrawColor( gRenderer, 250, 248, 239, 98 );
    SDL_RenderClear( gRenderer );
    TTF_Font* font = TTF_OpenFont("ClearSans-Bold.ttf", 20);
    SDL_Color color = { 250, 248, 239, 98 };
    Sc_text->loadFromRenderedText(font, sc.c_str(), color);
	Best_text->loadFromRenderedText(font, best.c_str(), color);
	int l1 = sc.length();
	int l2 = best.length();
    int a = 14, number_size = 107;
    background->render(0, SCREEN_HEIGHT/6);
    score_img->render(SCREEN_WIDTH/6, SCREEN_HEIGHT / 15);
    bestscore_img->render(SCREEN_WIDTH / 6 * 5 - score_img_size.w, SCREEN_HEIGHT / 15);
	Sc_text->render(SCREEN_WIDTH/6 + 55 - ( (l1-1) * 6), SCREEN_HEIGHT / 15 + 20);
	Best_text->render(SCREEN_WIDTH / 6 * 5 - score_img_size.w + 55 - ( (l2-1) * 6), SCREEN_HEIGHT / 15 + 20);
	for(int i = 0; i < Board_Size ; i++){
		for(int j = 0; j < Board_Size; j++){
			int tmp = GameBoard.GetNumAt_xy(i,j);
            string s = to_string(tmp);
            string img_path = "Img/";
			img_path = img_path + s + ".png";
            if (tmp == 0) {
                continue;
            }
            else {
                if (!Num->loadTexture(img_path)) {
                    printf( "Failed to load texture image!\n" );
                }
                else {
                    Num->render( a * (j + 1) + number_size * j, SCREEN_HEIGHT/6 + a * (i + 1) + number_size * i);
                }
            }
		}
	}
    if (GameBoard.CheckGameOver()) {
        GameOver_img->render(0, SCREEN_WIDTH / 2);
    }
    else if (GameBoard.CheckWin()){
        Win_img->render(0, SCREEN_WIDTH / 2);
    }
	//Update screen
    SDL_RenderPresent( gRenderer );
}