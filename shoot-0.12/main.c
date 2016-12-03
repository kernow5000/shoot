// reinitilasing event.jbutton.button to 255 is preventing from holding actions 
// such as holding the dpad left, or holding a button down, but isn't this correct behaviour?

#include <stdio.h>
#include <SDL.h>
// our own headers follow
#include <global.h>
#include <sixaxis.h> 

// function prototypes, just external funcs for now
extern int checkControllerPresent();
extern int doControllerTest();


// main loop for getting input, moving things, etc
int doMainLoop() {

  SDL_Event event;
  SDL_Surface* screen;  // main window
  SDL_Surface* temp;    // buffer
  SDL_Surface* bg;      // background
  SDL_Surface* sprite;  // our sprite
  int quitLoop = 0;
    
  printf("%s", "Main loop starting - press PS button to quit\n");
  // check controller is still connected
  if(SDL_NumJoysticks() < 1) {
    printf("Controller is not connected\n");
    return 1;
  }

  // if we are here, controller is still connected, carry on going
  // turn on automatic event polling
  SDL_JoystickEventState(SDL_ENABLE);

  // set window title
  SDL_WM_SetCaption("SDL input/graphics Test", "SDL input/graphics Test");
  // create window, check fullscreen flag, var needs initialising
  if(fullscreen == 0) {
    fprintf(stdout,"Creating %ix%i window on desktop\n", SCREEN_WIDTH, SCREEN_HEIGHT);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  } 
  else {
    fprintf(stdout,"Attempting fullscreen %ix%i\n", SCREEN_WIDTH, SCREEN_HEIGHT);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_FULLSCREEN); 
    // this is actually 1024x768 i think, as the image is centered, not 800x600
  }
 
  // load a background image, should really choose the right size image dependent on screen size, but meh
  temp = SDL_LoadBMP("bg.bmp");
  bg = SDL_DisplayFormat(temp);
  // free temp surface 
  SDL_FreeSurface(temp);
  // any error checking on this? if texture files go missing etc?

  // begin the 'game loop'
  while(quitLoop == 0) {

    // get a new event
    SDL_PollEvent(&event);
    // work out what to do with it
    switch(event.type) {
      
      // a button was pressed, this is where a lot of work will be
      case SDL_JOYBUTTONDOWN:
        // we only care about buttons being pressed, so check for it and quit loop if so
	if(event.jbutton.button == PS3_PAD_PS_BUTTON) {
	  printf("%s", "Quitting\n");
	  quitLoop = 1;
	}
	// just another little event catch for a test
	if(event.jbutton.button == PS3_PAD_START_BUTTON) {
 	  printf("%s", "Start\n");
	}
      break;

      // handle keyboard events, either quit or fullscreen really
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
	  // quit on ESC or q pressed
          case SDLK_ESCAPE:
          case SDLK_q:
 	    printf("%s", "Quitting\n");
            quitLoop = 1;
          break;
	   
	  // toggle fullscreen mode with f key
	  case SDLK_f:
	    printf("%s", "Toggling fullscreen mode\n");
	    // destroy old screen
	    SDL_FreeSurface(screen);
            if(fullscreen == 0) {
              fullscreen = 1;
	      //fprintf(stdout, "Attempting to go fullscreen %ix%i\n", SCREEN_WIDTH, SCREEN_HEIGHT);
              SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_FULLSCREEN);
	    } else
	    if(fullscreen == 1) {
	      fullscreen = 0;
	      //fprintf(stdout, "Reverting back to %ix%i window\n", SCREEN_WIDTH, SCREEN_HEIGHT);
	      SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
	    }
	  break;
        }
      break; 

    } // end switch

    // initialise event.jbutton.button to something way out of range to prevent button spamming
    //event.jbutton.button = 255;

    // update graphics
    // draw background?
    SDL_BlitSurface(bg, NULL, screen, NULL);
    // update the screen
    SDL_UpdateRect(screen, 0, 0, 0, 0);

  } // end while

  // game loop finished, clean up our graphics now
  // free the background surface
  SDL_FreeSurface(bg);

  return 0;
}






void cleanup() {
// just to be used on exit
  if(SDL_JoystickOpened(0))
    SDL_JoystickClose(joy);
    SDL_Quit;
  printf("%s", "\n");
}



int init() {	
  
  // we need to initialise SDL first
  // we need more robust video initialisation as it segfaults if we aren't in X, or $DISPLAY isn't set
  printf("%s", "\nInitialising SDL\n");
  if (SDL_Init(SDL_INIT_JOYSTICK|SDL_INIT_VIDEO) < 0 ) {
        printf("%s", "\nSDL init failed: ");
        printf("%s", SDL_GetError());
        return 1;
  }

  if (checkControllerPresent() != 0) {
    printf("%s", "No Compatible controller detected\n");
    return 1;
  }

  // is there anything else we need to initialise?
  return 0;
}



int main() {

  // init everything 
  if (init() !=0) {
    printf("%s", "Init failed, Exiting\n");
    cleanup();
    return 1;
  } 
	
  // if we are here, init() went well and we can continue!
  printf("%s", "Init OK, Continuing\n");
  
  // perform our controller test for now
  //if (doControllerTest() != 0) {
      //printf("%s", "doControllerTest() failed\n");
    //return 1;
  //}
 
  // as doControllerTest() is just a test, try a main loop, quittable with the PS button 
  if (doMainLoop() != 0) {
    printf("%s", "doMainLoop() failed, Exiting\n");
    return 1;
  }
  
  // quit and cleanup
  cleanup();
  return 0;
  // fin
}


