#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

// define some constants for max analogue axes, so we can use it later
#define AXIS_MAX 32767
#define AXIS_MIN -32767
// or is it +-32768?

// our program-wide SDL joystick struct
SDL_Joystick *joy;

// fullscreen flag
int fullscreen;


