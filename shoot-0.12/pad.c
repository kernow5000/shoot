#include <stdio.h>
#include <SDL.h>
// our own headers follow
#include <global.h>
#include <sixaxis.h>



int checkControllerPresent() {
  // returns 1 on failure to init  pad, 0 for success
  
  // open joystick 0 
  if((joy = SDL_JoystickOpen(0)) == NULL) {
    return 1;
  } else 
     {
       // we did open a controller so do something with it
       fprintf(stdout, "Opened Controller: %s, %i axes, %i buttons\n", SDL_JoystickName(0),SDL_JoystickNumAxes(joy), SDL_JoystickNumButtons(joy));
       
       if(strcmp(sixaxisOfficialName, SDL_JoystickName(0)) != 0) {
         fprintf(stdout,"You have not connected a %s!\n", sixaxisOfficialName); 
         return 1;
       }
     
       return 0; 
     }
   
  // if we get this far, we didn't get a pad
  return 1; 
}


// an optional controller test that just dumps output to the screen
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
	    // its something to do with the 10% padding on the line below, or being over SSH 
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

	   // a keyboard key was pressed, check if it was escape or q and quit
	   /*case SDL_KEYDOWN:
	     switch (event.key.keysym.sym) {
      
	      case SDLK_ESCAPE:
	      case SDLK_q:
		quitLoop = 1;
	      break;
	     }
	   
	   break;
  	   */
	   // this don't seem to do very much
	   
	   
	   case SDL_QUIT:
             // SDL_QUIT seems to be CTRL-C, not escape, end the loop here.
	     // i'd like it to be escape, but we could just quit on a button pressed
	     quitLoop = 1;
           break;
        } // end switch

	// reinitialise event.jbutton.button out of range to prevent button mashing/spamming
	//event.jbutton.button = 255;

    } // end while loop
  // end of test loop, pretty similar to a game loop really

  return 0;
}


