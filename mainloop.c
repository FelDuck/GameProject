/////////////////////////////////////////header section///////////////////////////////
#include "stdio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

const u_int32_t MASKLOVE = 4278190080;
const u_int32_t MASKHATE = 16711680;
const u_int32_t MASKFEAR = 65280;
const u_int32_t MASKCOMP = 240;
const u_int32_t MASKRESP = 15;

struct window_box{
  SDL_Window* mainscreen;
  SDL_Surface* surface;
  SDL_Renderer* render;
};
struct dot{
  int x;
  int y;
};

//Function declaration will have to move to a dot h
struct window_box init_scr(int* initialised,int scr_width,int scr_height);
void SDL_end(struct window_box winBox);
void intUnload(u_int32_t toUnload);
///////////////////////////////////////////////////////////////////////////////
int main(){
  int* initialised = (int*)(malloc(sizeof(int)));
  *initialised = 0;
  SDL_Event e;
  bool quit = false;
  u_int32_t test =4294967295;
  //winBox CREATION
  struct window_box winBox = init_scr(initialised,640,480);
  if(*initialised == 0){
    printf("initialised failed");
    quit = true;
  }  
  free(initialised);

  //DOT CREATION
  struct dot dot;
  dot.x=0;
  dot.y=0;
  
  //main gameloop
  while(!quit){
    //event handler
    while(SDL_PollEvent(&e) != 0){
      switch(e.type){
      case SDL_QUIT:
	quit = true;
	break;
      case SDL_KEYDOWN:
	//Main KEYBOARD HANDLER
	switch(e.key.keysym.sym){
	case SDLK_UP:
	  dot.y-=2;
	  break;
	case SDLK_DOWN:
	  dot.y+=2;
	  break;
	case SDLK_LEFT:
	  dot.x-=2;
	  break;
	case SDLK_RIGHT:
	  dot.x+=2;
	  break;
	case SDLK_i:
	  printf("%x\n",test);
	  break;
	case SDLK_o:
	  intUnload(test);
	}
	break;
      }
    }
    //Clears the image on the screen
    //SDL_RenderClear(winBox.render);

    SDL_RenderDrawPoint(winBox.render,dot.x,dot.y);
    //Updates the image
    SDL_RenderPresent(winBox.render);
  }
  
  SDL_end(winBox);
  printf("\nend of programm");
}

void intUnload(u_int32_t toUnload){
  u_int8_t fear,love,hate,comp,resp;
  love = (toUnload & MASKLOVE)>>24;
  hate = (toUnload & MASKHATE)>>16;
  fear = (toUnload & MASKFEAR)>>8; 
  comp = (toUnload & MASKCOMP)>>4;
  resp = (toUnload & MASKRESP);
  printf("%x\n",love);
  printf("%x\n",fear);
  printf("%x\n",hate);
  printf("%x\n",comp);
  printf("%x\n",resp);
}

struct window_box init_scr(int* initialised,int scr_width,int scr_height){
  printf("inside  init\n");
  //Initialistion of winBox
  struct window_box winBox;
  winBox.mainscreen = NULL;
  winBox.surface = NULL;
  winBox.render = NULL;
  
  
  //initialisation of SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("sdl fucked up: %s",SDL_GetError());
    goto notinWorked;
  }
   //Create Window
  winBox.mainscreen = SDL_CreateWindow("lol",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, scr_width,scr_height,SDL_WINDOW_SHOWN);
  if(winBox.mainscreen == NULL){
    printf("window created fucked up: %s",SDL_GetError());
    goto windowFailed;
  }
  //Create Renderer
  winBox.render = SDL_CreateRenderer(winBox.mainscreen,-1,SDL_RENDERER_ACCELERATED);
  if(winBox.render == NULL){
    printf("RENDERER CREATION FAILED %s/n",SDL_GetError());
    goto renderFailed;
  }
  SDL_SetRenderDrawColor(winBox.render,0xFF,0xFF,0xFF,0xFF);
  winBox.surface = SDL_GetWindowSurface(winBox.mainscreen);
  *initialised = 1;
  return winBox;

  //FAILURE HANDLING
 renderFailed:
  SDL_DestroyWindow(winBox.mainscreen);
 windowFailed:
  SDL_Quit();
 notinWorked:
  return winBox;
}

void SDL_end(struct window_box winBox){
  SDL_DestroyRenderer(winBox.render);
  SDL_DestroyWindow(winBox.mainscreen);
  SDL_Quit();
}


