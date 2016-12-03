#include <stdio.h>
#include <SDL.h>
#include <ps3pad.h> 
// ps3 sixaxis (we lock to this and use on ps3, doesn't work on my laptop though :(
// this code works fine with a sixaxis on gentoo, on the actual PS3 hardware.


// NOTES
//
// reinitilasing event.jbutton.button to 255 is preventing from holding actions 
// such as holding the dpad left, or holding a button down
// how can we get around this? no idea



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
     fprintf(stdout, "Opened Controller: %s, %i axes, %i buttons\n", SDL_JoystickName(0),SDL_JoystickNumAxes(joy), SDL_JoystickNumButtons(joy));
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
        switch(event.type) {
	    // a button has been pressed
	    case SDL_JOYBUTTONDOWN:
	    	// debug the button pressed
		//fprintf(stdout, "button %i\n", event.jbutton.button);
		switch(event.jbutton.button) {
		  
		  case PS3_PAD_SELECT_BUTTON:
		    printf("%s", "Select\n");
		  break;

		  case PS3_PAD_START_BUTTON:
		    printf("%s", "Start\n");
		  break;  

		  case PS3_PAD_PS_BUTTON:
		    printf("%s", "PS button\n");
		  break;  
		  
		  case PS3_PAD_DPAD_UP:
		    printf("%s", "Dpad Up\n");
		  break;

		  case PS3_PAD_DPAD_DOWN:
		    printf("%s", "Dpad Down\n");
		  break;  

		  case PS3_PAD_DPAD_LEFT:
		    printf("%s", "Dpad Left\n");
		  break;

		  case PS3_PAD_DPAD_RIGHT:
		    printf("%s", "Dpad Right\n");
		  break;

		  case PS3_PAD_SQUARE_BUTTON:
		    printf("%s", "Square\n");
		  break;

		  case PS3_PAD_TRIANGLE_BUTTON:
		    printf("%s", "Triangle\n");
		  break;

		  case PS3_PAD_CROSS_BUTTON:
		    printf("%s", "Cross\n");
		  break;

		  case PS3_PAD_CIRCLE_BUTTON:
		    printf("%s", "Circle\n");
		  break;
		 
   		  case PS3_PAD_L1_BUTTON:
		    printf("%s", "L1\n");
		  break;  

		  case PS3_PAD_R1_BUTTON:
		    printf("%s", "R1\n");
		  break;
		
		  case PS3_PAD_L2_BUTTON:
		    printf("%s", "L2\n");
		  break;

		  case PS3_PAD_R2_BUTTON:
		    printf("%s", "R2\n");
		  break;

		  case PS3_PAD_L3_BUTTON:
		    printf("%s", "L3\n");
		  break;

		  case PS3_PAD_R3_BUTTON:
		    printf("%s", "R3\n");
		  break;

		}
            break;


	    case SDL_JOYAXISMOTION:  
	    // motion on one of the axes.., seems a little 'sticky' on analog axes?
	    // its something to do with the 10% padding on the line below.. 
    	    if ( (event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) ) {
		// first analog stick x axis
               	if(event.jaxis.axis == 0) {
                  if(event.jaxis.value < 0)
		    // left
	            fprintf(stdout, "L3 left: %i\n", event.jaxis.value);
		  if(event.jaxis.value > 0)
		    // right 
		    fprintf(stdout, "L3 right: %i\n", event.jaxis.value);
		}
		// first analog stick y axis
                if(event.jaxis.axis == 1) {
		  if(event.jaxis.value < 0)
		    // up 
		    fprintf(stdout, "L3 up: %i\n", event.jaxis.value);
		  if(event.jaxis.value > 0)
		    // down
		    fprintf(stdout, "L3 down: %i\n", event.jaxis.value);
                }
		// second analog stick x axis
		if(event.jaxis.axis == 5) {
	          if(event.jaxis.value < 0)
		    // left 
		    fprintf(stdout, "R3 left: %i\n", event.jaxis.value);
		  if(event.jaxis.value > 0)
		    // right
		    fprintf(stdout, "R3 right: %i\n", event.jaxis.value);
	        }
		// second analog stick y axis
	        if(event.jaxis.axis == 2) {
		  if(event.jaxis.value < 0)
		    // up
		    fprintf(stdout, "R3 up: %i\n", event.jaxis.value);
		  if(event.jaxis.value > 0)
	            // down
		    fprintf(stdout, "R3 down: %i\n", event.jaxis.value);
                }
              }
           break;
            
	   case SDL_QUIT:
             // SDL_QUIT seems to be CTRL-C, not escape, end the loop here.
	     // i'd like it to be escape, but we could just quit on startbutton pressed
	     quitLoop = 1;
           break;
        } // end switch

	// reinitialise event.jbutton.button out of range to prevent button mashing/spamming
	//event.jbutton.button = 255;

    } // end while loop
  // end of test loop, pretty similar to a game loop really

  return 0;
}


int doMainLoop() {
// practically the same as the doControllerTest() loop, but uses the input
// doControllerTest() is not to be used if this is.
  SDL_Event event;
  int quitLoop = 0;
  
  printf("%s", "Main loop starting - press PS button to quit\n");
  // check controller is still connected
  if(SDL_NumJoysticks() < 1) {
    printf("Controller is not connected\n");
    return 1;
  }

  // if we are here, controller is still connected, begin the main loop
  // turn on automatic event polling
  SDL_JoystickEventState(SDL_ENABLE);
 
  // this loop doesn't even have a control-c exit from the terminal, only PS button on pad exits
  while(quitLoop == 0) {

    // get a new event
    SDL_PollEvent(&event);
    // work out what to do with it
    switch(event.type) {
      
      // a button was pressed
      case SDL_JOYBUTTONDOWN:
        // we only care about buttons being pressed
	// and one buttin in particular, so check for it and quit loop if so
	if(event.jbutton.button == PS3_PAD_PS_BUTTON) {
	  printf("%s", "Quitting\n");
	  quitLoop = 1;
	}

	// and just because I'm bored at present
	if(event.jbutton.button == PS3_PAD_START_BUTTON) {
	  printf("Parp!\n");
	}

	if(event.jbutton.button == PS3_PAD_SELECT_BUTTON) {
	  printf("Reject\n");
	}
	// end boredom

      break;

    } // end switch

    // initialise event.jbutton.button to something way out of range
    // to prevent button spamming (more times than one press on digital)
    //event.jbutton.button = 255;

  } // end while

  return 0;
}


int init() {	
  
  // we need to initialise SDL first
  // we need more robust video initialisation
  // as it segfaults if we aren't in X, or $DISPLAY isn't set
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
  
  // perform our controller test for now
  if (doControllerTest() != 0) {
      printf("%s", "doControllerTest() failed\n");
    return 1;
  }
 
  // as doControllerTest() is just a test, try a main loop, quittable with the PS button 
  //if (doMainLoop() != 0) {
    //printf("%s", "doMainLoop() failed, Exiting\n");
    //return 1;
  //}
  
  // quit and cleanup
  cleanup();
  return 0;
  // fin
}


