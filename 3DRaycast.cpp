/*
TODO:                                                                                    |𝔻𝕠𝕟𝕖𝕟𝕖𝕤𝕤|
	-Add and impliment/use ray.length                                                    |Maybe Do|
	-classes.cpp line 182: add position to ball shadow casting(??)                       |StilToDo|
	-Find the normal of a triangle when it is created                                    |StilToDo|
	-Finish triangle.cast                                                                |StilToDo|
	-Make triangle.cast work for shadows                                                 |StilToDo|
	-Find the required vectors for the camera when it is created                         |StilToDo|
	-Finish camera.rotate and camera.getRay to make them actually work with rotation     |StilToDo|
	-Add shadows for plane.cast                                                          |StilToDo|
	-Add reflections to all objects                                                      |StilToDo|
	-Properly clean up World objects on exit                                             |StilToDo|
	-Redefine operators and such to work with points (and rays?)  (Object overloading)   |StilToDo|
	-Fix shadows!                                                                        |StilToDo|
	-Make shadows more realistic (add indirect lighting, integrate into normal cast)     |StilToDo|
	-                                                                                    |_-_-_-_-|
	-                                                                                    |_-_-_-_-|
	-Avoid drawing spheres that are behind the camera                                    |PartDone|
	-Make use of Point object universal                                                  |  Done  |
	-Restructure so that world object contains all objects to be cast                    |  Done  |
	-Figure out mouseX and mouseY polarity                                               |  Done  |
	-Make the plane cast actually get what axis it is on from the variable               |  Done  |
*/


#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdint>
#include <string>
#include "rays.h"
#include "camera.h"
#include "objects.h"

void set(int, int, uint8_t, uint8_t, uint8_t);
//float square(float num);
//float dist3D(float x1, float y1, float z1, float x2, float y2, float z2);

int displayWidth = 1000;
int displayHeight = 700;
Uint32* pixels = new Uint32[displayWidth*displayHeight];
int frameCount = 0;
int mouseX = 0;
int mouseY = -displayHeight/2;
bool print;

World world;
Camera camera(Point(0, 0, 0), displayWidth, 0, -90);
CRay cRay(Ray(Point(0, 0, 0), Point(0, 0, displayWidth)));
Object* testTri = new Tri(Point(0, 0, displayWidth*2), Point(displayWidth, 0, displayWidth*2), Point(displayWidth/2, displayWidth/2, displayWidth*5/2), 100, 100, 100, 255);


void setup(){
	world.objList.emplace_back(new Ball(Point(0, 0, -displayWidth), displayHeight/2, 255, 255, 255, 255, 0));//testBall
	world.objList.emplace_back(new Ball(world.light, displayHeight/10, 255, 0, 0, 255, 0));//lightBall
	world.objList.emplace_back(new Plane(1, -displayWidth/5, displayWidth/3, 0, 150, 150, 255, 150, 0, 150, 255, 0));//testPlane
}

/*CRay test2D(CRay ray){
	if(square(ray.p2.x)+square(ray.p2.y)<square(displayHeight/2)){
		if(ray.p2.y<sin(ray.p2.x*15.7079632679/displayWidth-frameCount*displayWidth/50)*displayHeight/4){
			ray.r = 50;
			ray.g = 200;
			ray.b = 20;
		}
		else{
			ray.r = 200;
			ray.g = 20;
			ray.b = 50;
		}
		ray.escape = false;
	}
	return ray;
}*/


void renderPixel(int x, int y){
	//print = x==0 && y==0 && frameCount==15;
	int detail = 1;
	int detailSq = detail*detail;
	uint32_t rTotal = 0;
	uint32_t gTotal = 0;
	uint32_t bTotal = 0;
	for(int subX = 0; subX<detail; subX ++){
		for(int subY = 0; subY<detail; subY ++){
			camera.getRay(cRay, x+subX*1.0/detail, y+subY*1.0/detail);
			world.cast(cRay);
			rTotal += cRay.r;
			gTotal += cRay.g;
			bTotal += cRay.b;
		}
	}
	set(x+displayWidth/2, displayHeight-(y+displayHeight/2)/*optomizing here could cause an off-by-one error with some display sizes*/, (int)(rTotal/detailSq), (int)(gTotal/detailSq), (int)(bTotal/detailSq));
}

void draw(){
	//camera.pos.z = (displayWidth*frameCount/5);
	camera.pos.z = (mouseX+displayWidth/2)*4;
	static_cast<Plane*>(world.objList[2])->dist = mouseY*4;
	for(int y = displayHeight; y>0; y --){
		for(int x = 0; x<displayWidth; x ++){
			renderPixel(x-displayWidth/2, y-displayHeight/2);
			//set(x, y, 255, 0, 255);
		}
	}
}



int main(/*int argc, char* args[]*/){
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_DisplayMode DM;
	SDL_Texture* buffer = nullptr;
	bool quit = false;
    SDL_Event event;
	SDL_GetCurrentDisplayMode(0, &DM);
	printf("width: %i, ", DM.w);
	printf("height: %i\n", DM.h);
	//displayWidth = DM.w;
	//displayHeight = DM.h;
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		printf("SDL could not initialize.  SDL_Error: %s\n", SDL_GetError());
	}
	else{
		window = SDL_CreateWindow("3D Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayWidth, displayHeight, 0);//used to end with "SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI" instead of "0"
		if(window==NULL){
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

		}
		else{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
			buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, displayWidth, displayHeight);
			setup();
			while(!quit){
				draw();
				//memset(pixels, 255, displayWidth*displayHeight*sizeof(Uint32));
				SDL_UpdateTexture(buffer, NULL, pixels, displayWidth*sizeof(Uint32));
				SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, buffer, NULL, NULL);
				SDL_RenderPresent(renderer);

				frameCount ++;

				/*if(frameCount<=20){
					const char* name = ("frame_"+std::to_string(frameCount)+".bmp").c_str();
					SDL_SaveBMP(SDL_CreateRGBSurfaceFrom(pixels, displayWidth, displayHeight, 32, displayWidth*4, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000), name);
					printf("Saved file %s\n", name);
				}
				else{quit = true;}*/

				//if(frameCount==30){quit = true;}
				while(SDL_PollEvent(&event)!=0){
					switch(event.type){
						case SDL_QUIT:
							quit = true;
							break;
						case SDL_MOUSEMOTION:
							mouseX = event.motion.x-displayWidth/2;
							mouseY = -event.motion.y+displayHeight/2;
							//printf("mouseX=%f, mouseY=%f\n", mouseX*1.0/displayWidth, mouseY*1.0/displayHeight);
					}
				}
			}
		}
	}
	delete testTri;
	//delete testBall;
	//delete lightBall;
	//delete testPlane;
	delete[] pixels;
	SDL_DestroyTexture(buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("Done\n");
	return 0;
}

void set(int x, int y, uint8_t r, uint8_t g, uint8_t b){
	if(x>=0 && x<displayWidth && y>=0 && y<displayHeight){pixels[y*displayWidth+x] = (r<<16)+(g<<8)+b;}
	else{printf("Tried to draw pixel out of bounds at (%i, %i)\n", x, y);}
}
/*float square(float num){
	return num*num;
}
float dist3D(float x1, float y1, float z1, float x2, float y2, float z2){
	return sqrt(square(x2-x1)+square(y2-y1)+square(z2-z1));
}*/


