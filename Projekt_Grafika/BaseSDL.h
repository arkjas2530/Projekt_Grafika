#ifndef BaseSDL_h
#define BaseSDL_h

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;

class BaseSDL
{
	
	bool Init();
	void Close();
	bool loadImage();

public:
	BaseSDL();
	~BaseSDL();
	
};

#endif
