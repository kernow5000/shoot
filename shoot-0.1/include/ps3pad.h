// PLAYSTATION 3 SIXAXIS DEFINES

// the actual usb device string found on a sixaxis, used for comparison lock
#define sixaxisOfficialName "Sony PLAYSTATION(R)3 Controller"

// these are in a human logical order looking at the pad, not numerical
#define PS3_PAD_SELECT_BUTTON   0
#define PS3_PAD_START_BUTTON    3
#define PS3_PAD_PS_BUTTON       16
#define PS3_PAD_DPAD_UP	        4
#define PS3_PAD_DPAD_DOWN       6
#define PS3_PAD_DPAD_LEFT       7
#define PS3_PAD_DPAD_RIGHT      5
#define PS3_PAD_SQUARE_BUTTON   15
#define PS3_PAD_TRIANGLE_BUTTON 12
#define PS3_PAD_CROSS_BUTTON	14
#define PS3_PAD_CIRCLE_BUTTON   13
#define PS3_PAD_L1_BUTTON	10
#define PS3_PAD_R1_BUTTON	11
#define PS3_PAD_L2_BUTTON	8
#define PS3_PAD_R2_BUTTON	9
#define PS3_PAD_L3_BUTTON	1
#define PS3_PAD_R3_BUTTON	2
// 17 buttons eh? - how come it reports 19?

// its a pity we couldn't incorporate mappings for dualshock 2 also
// like we used to have in ps2pad.h, but its better this way
