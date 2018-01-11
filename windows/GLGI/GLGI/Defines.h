#pragma once
#ifndef GLGI_DEFINES_H 
#define GLGI_DEFINES_H GLGI_DEFINES_H

#define uint unsigned int

#define GLGI_CURSOR_NORMAL GLFW_CURSOR_NORMAL  

#define GLGI_CURSOR_HIDDEN GLFW_CURSOR_HIDDEN  

#define GLGI_CURSOR_DISABLED GLFW_CURSOR_DISABLED 

#define GLGI_RELEASE  0
#define GLGI_PRESS   1
#define GLGI_REPEAT   2


/* The unknown key */
#define GLGI_KEY_UNKNOWN            -1

/* Printable keys */
#define GLGI_KEY_SPACE              32
#define GLGI_KEY_APOSTROPHE         39  /* ' */
#define GLGI_KEY_COMMA              44  /* , */
#define GLGI_KEY_MINUS              45  /* - */
#define GLGI_KEY_PERIOD             46  /* . */
#define GLGI_KEY_SLASH              47  /* / */
#define GLGI_KEY_0                  48
#define GLGI_KEY_1                  49
#define GLGI_KEY_2                  50
#define GLGI_KEY_3                  51
#define GLGI_KEY_4                  52
#define GLGI_KEY_5                  53
#define GLGI_KEY_6                  54
#define GLGI_KEY_7                  55
#define GLGI_KEY_8                  56
#define GLGI_KEY_9                  57
#define GLGI_KEY_SEMICOLON          59  /* ; */
#define GLGI_KEY_EQUAL              61  /* = */
#define GLGI_KEY_A                  65
#define GLGI_KEY_B                  66
#define GLGI_KEY_C                  67
#define GLGI_KEY_D                  68
#define GLGI_KEY_E                  69
#define GLGI_KEY_F                  70
#define GLGI_KEY_G                  71
#define GLGI_KEY_H                  72
#define GLGI_KEY_I                  73
#define GLGI_KEY_J                  74
#define GLGI_KEY_K                  75
#define GLGI_KEY_L                  76
#define GLGI_KEY_M                  77
#define GLGI_KEY_N                  78
#define GLGI_KEY_O                  79
#define GLGI_KEY_P                  80
#define GLGI_KEY_Q                  81
#define GLGI_KEY_R                  82
#define GLGI_KEY_S                  83
#define GLGI_KEY_T                  84
#define GLGI_KEY_U                  85
#define GLGI_KEY_V                  86
#define GLGI_KEY_W                  87
#define GLGI_KEY_X                  88
#define GLGI_KEY_Y                  89
#define GLGI_KEY_Z                  90
#define GLGI_KEY_LEFT_BRACKET       91  /* [ */
#define GLGI_KEY_BACKSLASH          92  /* \ */
#define GLGI_KEY_RIGHT_BRACKET      93  /* ] */
#define GLGI_KEY_GRAVE_ACCENT       96  /* ` */
#define GLGI_KEY_WORLD_1            161 /* non-US #1 */
#define GLGI_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define GLGI_KEY_ESCAPE             256
#define GLGI_KEY_ENTER              257
#define GLGI_KEY_TAB                258
#define GLGI_KEY_BACKSPACE          259
#define GLGI_KEY_INSERT             260
#define GLGI_KEY_DELETE             261
#define GLGI_KEY_RIGHT              262
#define GLGI_KEY_LEFT               263
#define GLGI_KEY_DOWN               264
#define GLGI_KEY_UP                 265
#define GLGI_KEY_PAGE_UP            266
#define GLGI_KEY_PAGE_DOWN          267
#define GLGI_KEY_HOME               268
#define GLGI_KEY_END                269
#define GLGI_KEY_CAPS_LOCK          280
#define GLGI_KEY_SCROLL_LOCK        281
#define GLGI_KEY_NUM_LOCK           282
#define GLGI_KEY_PRINT_SCREEN       283
#define GLGI_KEY_PAUSE              284
#define GLGI_KEY_F1                 290
#define GLGI_KEY_F2                 291
#define GLGI_KEY_F3                 292
#define GLGI_KEY_F4                 293
#define GLGI_KEY_F5                 294
#define GLGI_KEY_F6                 295
#define GLGI_KEY_F7                 296
#define GLGI_KEY_F8                 297
#define GLGI_KEY_F9                 298
#define GLGI_KEY_F10                299
#define GLGI_KEY_F11                300
#define GLGI_KEY_F12                301
#define GLGI_KEY_F13                302
#define GLGI_KEY_F14                303
#define GLGI_KEY_F15                304
#define GLGI_KEY_F16                305
#define GLGI_KEY_F17                306
#define GLGI_KEY_F18                307
#define GLGI_KEY_F19                308
#define GLGI_KEY_F20                309
#define GLGI_KEY_F21                310
#define GLGI_KEY_F22                311
#define GLGI_KEY_F23                312
#define GLGI_KEY_F24                313
#define GLGI_KEY_F25                314
#define GLGI_KEY_KP_0               320
#define GLGI_KEY_KP_1               321
#define GLGI_KEY_KP_2               322
#define GLGI_KEY_KP_3               323
#define GLGI_KEY_KP_4               324
#define GLGI_KEY_KP_5               325
#define GLGI_KEY_KP_6               326
#define GLGI_KEY_KP_7               327
#define GLGI_KEY_KP_8               328
#define GLGI_KEY_KP_9               329
#define GLGI_KEY_KP_DECIMAL         330
#define GLGI_KEY_KP_DIVIDE          331
#define GLGI_KEY_KP_MULTIPLY        332
#define GLGI_KEY_KP_SUBTRACT        333
#define GLGI_KEY_KP_ADD             334
#define GLGI_KEY_KP_ENTER           335
#define GLGI_KEY_KP_EQUAL           336
#define GLGI_KEY_LEFT_SHIFT         340
#define GLGI_KEY_LEFT_CONTROL       341
#define GLGI_KEY_LEFT_ALT           342
#define GLGI_KEY_LEFT_SUPER         343
#define GLGI_KEY_RIGHT_SHIFT        344
#define GLGI_KEY_RIGHT_CONTROL      345
#define GLGI_KEY_RIGHT_ALT          346
#define GLGI_KEY_RIGHT_SUPER        347
#define GLGI_KEY_MENU               348

#define GLGI_KEY_LAST               GLGI_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
*
*  See [key input](@ref input_key) for how these are used.
*
*  @ingroup input
*  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
*/
#define GLGI_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
*/
#define GLGI_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
*/
#define GLGI_MOD_ALT             0x0004
/*! @brief If this bit is set one or more Super keys were held down.
*/
#define GLGI_MOD_SUPER           0x0008

/*! @} */

/*! @defgroup buttons Mouse buttons
*
*  See [mouse button input](@ref input_mouse_button) for how these are used.
*
*  @ingroup input
*  @{ */
#define GLGI_MOUSE_BUTTON_1         0
#define GLGI_MOUSE_BUTTON_2         1
#define GLGI_MOUSE_BUTTON_3         2
#define GLGI_MOUSE_BUTTON_4         3
#define GLGI_MOUSE_BUTTON_5         4
#define GLGI_MOUSE_BUTTON_6         5
#define GLGI_MOUSE_BUTTON_7         6
#define GLGI_MOUSE_BUTTON_8         7
#define GLGI_MOUSE_BUTTON_LAST      GLGI_MOUSE_BUTTON_8
#define GLGI_MOUSE_BUTTON_LEFT      GLGI_MOUSE_BUTTON_1
#define GLGI_MOUSE_BUTTON_RIGHT     GLGI_MOUSE_BUTTON_2
#define GLGI_MOUSE_BUTTON_MIDDLE    GLGI_MOUSE_BUTTON_3
/*! @} */

/*! @defgroup joysticks Joysticks
*
*  See [joystick input](@ref joystick) for how these are used.
*
*  @ingroup input
*  @{ */
#define GLGI_JOYSTICK_1             0
#define GLGI_JOYSTICK_2             1
#define GLGI_JOYSTICK_3             2
#define GLGI_JOYSTICK_4             3
#define GLGI_JOYSTICK_5             4
#define GLGI_JOYSTICK_6             5
#define GLGI_JOYSTICK_7             6
#define GLGI_JOYSTICK_8             7
#define GLGI_JOYSTICK_9             8
#define GLGI_JOYSTICK_10            9
#define GLGI_JOYSTICK_11            10
#define GLGI_JOYSTICK_12            11
#define GLGI_JOYSTICK_13            12
#define GLGI_JOYSTICK_14            13
#define GLGI_JOYSTICK_15            14
#define GLGI_JOYSTICK_16            15
#define GLGI_JOYSTICK_LAST          GLGI_JOYSTICK_16
/*! @} */

#endif // !GLGI_DEFINES_H
