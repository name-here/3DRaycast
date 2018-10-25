/*
TODO:                                                                                    |𝔻𝕠𝕟𝕖𝕟𝕖𝕤𝕤|
	-Add and impliment/use ray.length                                                    |Maybe Do|
	-Separate alpha from color object (not needed for some uses)                         |Maybe Do|
	-classes.cpp line 182: add position to ball shadow casting(??)                       |StilToDo|
	-Find the normal of a triangle when it is created                                    |StilToDo|
	-Finish triangle.cast                                                                |StilToDo|
	-Make triangle.cast work for shadows                                                 |StilToDo|
	-Find the required vectors for the camera when it is created                         |StilToDo|
	-Properly clean up World objects on exit                                             |StilToDo|
	-Make shadows more realistic (add indirect lighting, integrate into normal cast)     |StilToDo|
	-Fix issue of no shadows on line of x=0                                              |StilToDo|
	-Optimize getting rays for camera (maybe don't use sine/cosine)                      |StilToDo|
	-Make new file for world and make camera part of world class                         |StilToDo|
	-                                                                                    |_-_-_-_-|
	-                                                                                    |_-_-_-_-|
	-Add shadows for plane.cast                                                          |PartDone|
	-Add reflections to all objects                                                      |PartDone|
	-Redefine operators and such to work with points (and rays?)  (Object overloading)   |PartDone|
	-Avoid drawing spheres that are behind the camera                                    |PartDone|
	-Finish camera.rotate and camera.getRay to make them actually work with rotation     |  Done  |
	-Fix color issues caused by non-linear association of RGB values and brightness      |  Done  |
	-Make use of Color objects universal                                                 |  Done  |
	-Fix shadows!                                                                        |  Done  |
	-Make use of Point object universal                                                  |  Done  |
	-Restructure so that world object contains all objects to be cast                    |  Done  |
	-Figure out mouseX and mouseY polarity                                               |  Done  |
	-Make the plane cast actually get what axis it is on from the variable               |  Done  |
*/


#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdint>
#include <cmath>
//#include <string>
#include "rays.h"
#include "camera.h"
#include "objects.h"

void set(int, int, Color);

int windowWidth = 512;//600
int windowHeight = 512;//420
Uint32* pixels = new Uint32[ windowWidth * windowHeight ];
int frameCount = 0;
int mouseX = 0;
int mouseY = -windowHeight/2;
bool print;
int detail = 1;
int detailSq = detail*detail;

World world;
Camera camera( Point( 0, 0, -windowWidth*3 ), windowWidth, 0, 0 );
CRay cRay( Ray( Point( 0, 0, 0 ), Point( 0, 0, windowWidth ) ) );
Object* testTri = new Tri( Point( 0, 0, windowWidth*2 ), Point( windowWidth, 0, windowWidth*2 ), Point( windowWidth/2, windowWidth/2, windowWidth*5/2 ), Color( 25600, 25600, 25600, 65535 ) );


void setup() {
	world.lightList.emplace_back( new Light( Point( 0, windowHeight, windowWidth ), Color( 65535, 65535, 65535, 65535 ) ) );//light1
	world.objList.emplace_back( new Ball( world.lightList[0]->pos, windowHeight/10, world.lightList[0]->color, 0));//lightBall
	world.objList.emplace_back( new Plane( 1, -windowWidth*11/20, windowWidth/3, Color( 0, 38400, 38400, 65535 ), Color( 0, 10000, 20000, 65535 ), 0 ) );//testPlane
	world.objList.emplace_back( new Ball( Point( 0, 0, windowWidth*2 ), windowHeight/2, Color( 65535, 65535, 65535, 65535 ), 0 ) );//testBall
}


void renderPixel( int x, int y ) {
	//print = x==0 && y==0 && frameCount==15;
	uint32_t rTotal = 0;
	uint32_t gTotal = 0;
	uint32_t bTotal = 0;
	for( int subX = 0; subX<detail; subX ++ ) {
		for( int subY = 0; subY<detail; subY ++ ) {
			camera.getRay( cRay, x+subX*1.0/detail, y+subY*1.0/detail );
			world.cast( cRay );
			rTotal += cRay.color.r;
			gTotal += cRay.color.g;
			bTotal += cRay.color.b;
		}
	}
	set(x+windowWidth/2, windowHeight-1-(y+windowHeight/2)/*optomizing here could cause an off-by-one error with some display sizes*/, Color((int)(rTotal/detailSq), (int)(gTotal/detailSq), (int)(bTotal/detailSq)));
}

void draw() {
	camera.move( Point( 0, 0, ((mouseY*1.5)/(windowHeight-1.5))*windowWidth ) );
	camera.rotate( -M_PI*3/2*mouseX/windowWidth, 0);

	//camera.pos.z = -(mouseX+windowWidth/2)*4;
	//static_cast<Plane*>(world.objList[1])->dist = mouseY*4;
	//camera.pos.z = (windowWidth*frameCount/5);
	//static_cast<Plane*>(world.objList[2])->dist = (-21+frameCount)*windowHeight/20;

	world.lightList[0]->pos.x = sin(frameCount*M_PI/20)*windowWidth;
	world.lightList[0]->pos.y = cos(frameCount*M_PI/20)*windowHeight;
	static_cast<Ball*>(world.objList[0])->pos.x = world.lightList[0]->pos.x;
	static_cast<Ball*>(world.objList[0])->pos.y = world.lightList[0]->pos.y;
	for(int y = windowHeight-1; y>=0; y --){
		for(int x = 0; x<windowWidth; x ++){
			renderPixel(x-windowWidth/2, y-windowHeight/2);
			//set(x, y, Color(65535*x/windowWidth/2, 0, 0));
		}
	}
}



int main(/*int argc, char* args[]*/) {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_DisplayMode DM;
	SDL_Texture* buffer = nullptr;
	bool quit = false;
    SDL_Event event;
	SDL_GetCurrentDisplayMode( 0, &DM );
	//printf("width: %i, ", DM.w);
	//printf("height: %i\n", DM.h);
	//windowWidth = DM.w;
	//windowHeight = DM.h;
	if(SDL_Init( SDL_INIT_VIDEO ) < 0){
		printf( "SDL could not initialize.  SDL_Error: %s\n", SDL_GetError() );
	}
	else{
		window = SDL_CreateWindow( "3D Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0 );//used to end with "SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI" instead of "0"
		if( window == NULL ){
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );

		}
		else{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );
			buffer = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, windowWidth, windowHeight );
			setup();
			while(!quit){
				draw();
				SDL_UpdateTexture( buffer, NULL, pixels, windowWidth*sizeof(Uint32) );
				SDL_RenderClear( renderer );
				SDL_RenderCopy( renderer, buffer, NULL, NULL );
				SDL_RenderPresent( renderer );

				frameCount ++;

				/*if(frameCount<=20){
					const char* name = ("frame_"+std::to_string(frameCount)+".bmp").c_str();
					SDL_SaveBMP(SDL_CreateRGBSurfaceFrom(pixels, windowWidth, windowHeight, 32, windowWidth*4, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000), name);
					printf("Saved file %s\n", name);
				}
				else{quit = true;}*/

				while( SDL_PollEvent( &event ) != 0 ){
					switch( event.type ) {
						case SDL_QUIT:
							quit = true;
							break;
						case SDL_MOUSEMOTION:
							mouseX = event.motion.x-(windowWidth/2);
							mouseY = -event.motion.y+(windowHeight/2);
							//printf("mouseX=%f, mouseY=%f\n", mouseX*1.0/windowWidth, mouseY*1.0/windowHeight);
					}
				}
			}
		}
	}
	delete testTri;
	delete[] pixels;
	SDL_DestroyTexture( buffer );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}

void set( int x, int y, Color color ){
	if( x >= 0  &&  x < windowWidth  &&  y >= 0  &&  y < windowHeight ){
		pixels[ (y*windowWidth)+x ] = ( ( (int)sqrt( color.r ) ) << 16 ) + ( ( (int)sqrt( color.g ) ) << 8 ) + ( (int)sqrt( color.b ) );
	}
	else{ printf( "Tried to draw pixel out of bounds at (%i, %i)\n", x, y ); }
}


