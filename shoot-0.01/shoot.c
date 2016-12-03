#include <stdio.h>
#include "SDL.h"


// what are we going to do if they plug a non ps2 pad in??
#define PAD_TRIANGLE_BUTTON 0
#define PAD_CIRCLE_BUTTON   1
#define PAD_SQUARE_BUTTON   2
#define PAD_CROSS_BUTTON    3
#define PAD_L2_BUTTON	    4
#define PAD_R2_BUTTON	    5
#define PAD_L1_BUTTON	    6
#define PAD_R1_BUTTON	    7
#define PAD_SELECT_BUTTON   8
#define PAD_START_BUTTON    9
#define PAD_L3_BUTTON	    10
#define PAD_R3_BUTTON	    11

// global joystick variable, boo
SDL_Joystick *joy;


int checkControllerPresent() {
  // returns 1 on failure to init  pad, 0 for success
  
  // keep a copy of the official vendor string for future use
  //char sixaxisOfficialName[41];  
  //strcpy(sixaxisOfficialName, "Sony PLAYSTATION(R)3 Controller"); 
 
  // open joystick 0
  if((joy = SDL_JoystickOpen(0)) == NULL) {
    //fprintf(stderr,"Unable to open controller: %s\n",SDL_GetError());
    return 1;
  } 
  else 
   {
     // we did open a controller so do something with it
     // show a little information about the joystick, and perform sixaxis check
     fprintf(stdout, "\nOpened Controller: %s, %i axes, %i buttons\n", SDL_JoystickName(0),SDL_JoystickNumAxes(joy), SDL_JoystickNumButtons(joy));
     //if(strcmp(sixaxisOfficialName, SDL_JoystickName(0)) != 0) {
       //fprintf(stdout,"You have not connected a %s!\n", sixaxisOfficialName);
       //return 1;
     //}

     //SDL_JoystickClose(joy);
     // return that we got a pad
     return 0;
   }

  // if we get this far, we didn't get a pad
  return 1;
}


int doControllerTest() {
  
  SDL_Event event;
  int quitLoop = 0;
  
  // need to sort out the buttons and axes using sdl calls, somehow
  printf("%s", "Controller test starting\n");
  // learn how to parse events and tell whats being pressed from the pad.. 
  if(SDL_NumJoysticks() < 1) {
	printf("Controller is not connected\n");
        return 1;
  }	

  // turn on automatic event polling, bollocks to autoupdating myself
  SDL_JoystickEventState(SDL_ENABLE);
  
  printf("%s", "\n");
  // start test loop here
    while(SDL_PollEvent(&event) || quitLoop == 0) { 
        switch(event.type)
        {  
            case SDL_JOYBUTTONDOWN:
	    // somewhere, somehow, a button has been pressed
              if(event.jbutton.button == PAD_TRIANGLE_BUTTON) {
		//printf("%s", "Triangle button\n");
                // because event.jbutton.button was zero beforehand anyway, it thinks triangle is pressed when run
	      }

	      if(event.jbutton.button == PAD_CIRCLE_BUTTON) {
                printf("%s", "Circle button\n");
              }
              if(event.jbutton.button == PAD_CROSS_BUTTON) {
                printf("%s", "Cross button\n");
              }
              if(event.jbutton.button == PAD_SQUARE_BUTTON) {
                printf("%s", "Square button\n"); 
              }
	      if(event.jbutton.button == PAD_L2_BUTTON) {
	        printf("%s", "L2 button\n"); 
              }
              if(event.jbutton.button == PAD_R2_BUTTON) {
                printf("%s", "R2 button\n");
              }
              if(event.jbutton.button == PAD_L1_BUTTON) {
                printf("%s", "L1 button\n");
              }
	      if(event.jbutton.button == PAD_R1_BUTTON) {
		printf("%s", "R1 button\n");
	      }
              if(event.jbutton.button == PAD_SELECT_BUTTON) {
                printf("%s", "Select button\n");
              }
	      if(event.jbutton.button == PAD_START_BUTTON) {
                printf("%s", "Start button\n"); 
	      }
	      if(event.jbutton.button == PAD_L3_BUTTON) {
		printf("%s", "L3 button (only works with analog mode enabled\n");
              }
	      if(event.jbutton.button == PAD_R3_BUTTON) {
		printf("%s", "R3 button (only works with analog mode enabled\n");
              }
	      if(event.jbutton.button == 12) {
		printf("%s", "? button\n");
	      }
            break;

	    case SDL_JOYAXISMOTION:  
	    // motion on one of the axes.. 
    	      if ( (event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) ) {
               	if(event.jaxis.axis == 0) {
        	  printf("%s", "first analog stick X axis\n");
		}
                if(event.jaxis.axis == 1) {
                  printf("%s", "first analog stick Y axis\n");
                }
		if(event.jaxis.axis == 5) {
		  printf("%s", "second analog stick X axis\n");
		  // is it really 5? hmm, would be good if we printed values i guess
	        }
	        if(event.jaxis.axis == 2) {
                  printf("%s", "second analog stick Y axis\n");
                }
              }
           break;

            case SDL_QUIT:
             // end the loop here as we quit, SDL_QUIT seems to be CTRL-C, not escape
	     quitLoop = 1;
            break;
        }
    }
  // end of test loop

  return 0;
}


int init() {	
  
  // we need to initialise SDL first
  printf("%s", "\nInitialising SDL");
  if (SDL_Init(SDL_INIT_JOYSTICK|SDL_INIT_VIDEO) < 0 ) {
        printf("%s", "\nSDL init failed");
        printf("%s", SDL_GetError());
        return 1;
  }

  if (checkControllerPresent() != 0) {
    printf("%s", "\nNo Compatible controller detected");
    return 1;
  }

  // is there really much else we need to initialise?
  return 0;
}


void cleanup() {
// just to be used on exit
  if(SDL_JoystickOpened(0))
    SDL_JoystickClose(joy);
    SDL_Quit;
  printf("%s", "\n");
}



int main() {

  // init everything 
  if (init() !=0) {
    printf("%s", "\nInit failed, Exiting\n");
    cleanup();
    return 1;
  } 
	
  // if we are here, init() went well and we can continue!
  printf("%s", "Init OK, Continuing\n");
  // using the dualshock2 over a usb convertor as i don't feel like playing with the sixaxis over USB, sigh 
  if (doControllerTest() != 0) {
    printf("%s", "doControllerTest() failed\n");
  }
  
  // quit anyway for now
  cleanup();
  return 0;
  // fin
}


