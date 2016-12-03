#include <stdio.h>
#include <SDL.h>
//#include <ps2pad.h> // ps2 pad defines
#include <ps3pad.h> // ps3 sixaxis (we'll be locking to this and using it explicitly on ps3, doesn't work on my laptop though :(

// this code works fine(nearly) with a sixaxis, on gentoo, on the actual PS3 hardware.
// how wierd is that, the buttons are wrong because of our ps2 pad defines, but those can be changed


// global joystick variable, boo
SDL_Joystick *joy;


int checkControllerPresent() {
  // returns 1 on failure to init  pad, 0 for success
   
  // open joystick 0
  if((joy = SDL_JoystickOpen(0)) == NULL) {
    return 1;
  } 
  else 
   {
     // we did open a controller so do something with it
     // show a little information about the joystick, and perform sixaxis check
     fprintf(stdout, "\nOpened Controller: %s, %i axes, %i buttons\n", SDL_JoystickName(0),SDL_JoystickNumAxes(joy), SDL_JoystickNumButtons(joy));
     if(strcmp(sixaxisOfficialName, SDL_JoystickName(0)) != 0) {
       fprintf(stdout,"You have not connected a %s!\n", sixaxisOfficialName);
       return 1;
     }

     // return that we got a pad
     return 0;
   }

  // if we get this far, we didn't get a pad
  return 1;
}


int doControllerTest() {
  
  SDL_Event event;
  int quitLoop = 0;
  
  printf("%s", "Controller test starting\n");
  // check controller is still connected
  if(SDL_NumJoysticks() < 1) {
	printf("Controller is not connected\n");
        return 1;
  }	

  // turn on automatic event polling
  SDL_JoystickEventState(SDL_ENABLE);
  
  printf("%s", "\n");
  // start test loop here
    while(quitLoop == 0) {

        // get a new event
	SDL_PollEvent(&event);

	// work out what to do with it
        switch(event.type)
        { 
/* disable button checking for now, as its mapped to the ps2 dualshock 2, not ps3 sixaxis 
            case SDL_JOYBUTTONDOWN:
	    // somewhere, a button has been pressed
              if(event.jbutton.button == PAD_TRIANGLE_BUTTON) {
		//printf("%s", "Triangle\n");
                // because event.jbutton.button was 0 beforehand anyway, it thinks triangle is pressed when run
	      }
	      if(event.jbutton.button == PAD_CIRCLE_BUTTON) {
                printf("%s", "Circle\n");
              }
              if(event.jbutton.button == PAD_CROSS_BUTTON) {
                printf("%s", "Cross\n");
              }
              if(event.jbutton.button == PAD_SQUARE_BUTTON) {
                printf("%s", "Square\n"); 
              }
	      if(event.jbutton.button == PAD_L2_BUTTON) {
	        printf("%s", "L2\n"); 
              }
              if(event.jbutton.button == PAD_R2_BUTTON) {
                printf("%s", "R2\n");
              }
              if(event.jbutton.button == PAD_L1_BUTTON) {
                printf("%s", "L1\n");
              }
	      if(event.jbutton.button == PAD_R1_BUTTON) {
		printf("%s", "R1\n");
	      }
              if(event.jbutton.button == PAD_SELECT_BUTTON) {
                printf("%s", "Select\n");
              }
	      if(event.jbutton.button == PAD_START_BUTTON) {
                printf("%s", "Start\n"); 
	      }
	      if(event.jbutton.button == PAD_L3_BUTTON) {
		printf("%s", "L3\n");
              }
	      if(event.jbutton.button == PAD_R3_BUTTON) {
		printf("%s", "R3\n");
              }
	      if(event.jbutton.button == 12) {
		printf("%s", "? button\n");
		// what the hell is this and why do we have so many spare buttons??
	      }
            break;
*/
	    case SDL_JOYAXISMOTION:  
	    // motion on one of the axes.., seems a little 'sticky' on analog axes?
	    // its something to do with the 10% padding on the line below.. 
    	    if ( (event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) ) {
		// first analog stick x axis
               	if(event.jaxis.axis == 0) {
                  if(event.jaxis.value < 0)
		    // left
	            fprintf(stdout, "L3 direction left: %i\n", event.jaxis.value);
		  if(event.jaxis.value > 0)
		    // right 
		    fprintf(stdout, "L3 direction right: %i\n", event.jaxis.value);
		}
		// first analog stick y axis
                if(event.jaxis.axis == 1) {
		  if(event.jaxis.value < 0)
		    // up 
		    fprintf(stdout, "L3 direction up: %i\n", event.jaxis.value);
		  if(event.jaxis.value > 0)
		    // down
		    fprintf(stdout, "L3 direction down: %i\n", event.jaxis.value);
                }
		// second analog stick x axis
		if(event.jaxis.axis == 5) {
	          if(event.jaxis.value < 0)
		    // left 
		    fprintf(stdout, "R3 direction left: %i\n", event.jaxis.value);
		  if(event.jaxis.value > 0)
		    // right
		    fprintf(stdout, "R3 direction right: %i\n", event.jaxis.value);
	        }
		// second analog stick y axis
	        if(event.jaxis.axis == 2) {
		  if(event.jaxis.value < 0)
		    // up
		    fprintf(stdout, "R3 direction up: %i\n", event.jaxis.value);
		  if(event.jaxis.value > 0)
	            // down
		    fprintf(stdout, "R3 direction down: %i\n", event.jaxis.value);
                }
              }
           break;
            
	   case SDL_QUIT:
             // SDL_QUIT seems to be CTRL-C, not escape, end the loop here.
	     quitLoop = 1;
           break;
        }
    }
  // end of test loop

  return 0;
}


int init() {	
  
  // we need to initialise SDL first
  // we need more robust video initialisation
  // as it segfaults if we aren't in X, or $DISPLAY isn't set
  printf("%s", "\nInitialising SDL");
  if (SDL_Init(SDL_INIT_JOYSTICK|SDL_INIT_VIDEO) < 0 ) {
        printf("%s", "\nSDL init failed: ");
        printf("%s", SDL_GetError());
        return 1;
  }

  if (checkControllerPresent() != 0) {
    printf("%s", "No Compatible controller detected\n");
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
    printf("%s", "Init failed, Exiting\n");
    cleanup();
    return 1;
  } 
	
  // if we are here, init() went well and we can continue!
  printf("%s", "Init OK, Continuing\n");
  // using the dualshock2 over a usb convertor as the sixaxis over usb simply doesn't work 
  if (doControllerTest() != 0) {
    printf("%s", "doControllerTest() failed\n");
  }
  
  // quit and cleanup
  cleanup();
  return 0;
  // fin
}


