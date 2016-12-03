#include <stdio.h>
#include <SDL.h>
// our own headers follow
#include <stuff.h>
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
