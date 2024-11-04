#pragma once

enum Ray_KeyboardKey
{
    RAY_KEY_NULL            = 0,        // Key: NULL, used for no key pressed
    RAY_KEY_APOSTROPHE      = 39,       // Key: '
    RAY_KEY_COMMA           = 44,       // Key: ,
    RAY_KEY_MINUS           = 45,       // Key: -
    RAY_KEY_PERIOD          = 46,       // Key: .
    RAY_KEY_SLASH           = 47,       // Key: /
    RAY_KEY_ZERO            = 48,       // Key: 0
    RAY_KEY_ONE             = 49,       // Key: 1
    RAY_KEY_TWO             = 50,       // Key: 2
    RAY_KEY_THREE           = 51,       // Key: 3
    RAY_KEY_FOUR            = 52,       // Key: 4
    RAY_KEY_FIVE            = 53,       // Key: 5
    RAY_KEY_SIX             = 54,       // Key: 6
    RAY_KEY_SEVEN           = 55,       // Key: 7
    RAY_KEY_EIGHT           = 56,       // Key: 8
    RAY_KEY_NINE            = 57,       // Key: 9
    RAY_KEY_SEMICOLON       = 59,       // Key: ;
    RAY_KEY_EQUAL           = 61,       // Key: =
    RAY_KEY_A               = 65,       // Key: A | a
    RAY_KEY_B               = 66,       // Key: B | b
    RAY_KEY_C               = 67,       // Key: C | c
    RAY_KEY_D               = 68,       // Key: D | d
    RAY_KEY_E               = 69,       // Key: E | e
    RAY_KEY_F               = 70,       // Key: F | f
    RAY_KEY_G               = 71,       // Key: G | g
    RAY_KEY_H               = 72,       // Key: H | h
    RAY_KEY_I               = 73,       // Key: I | i
    RAY_KEY_J               = 74,       // Key: J | j
    RAY_KEY_K               = 75,       // Key: K | k
    RAY_KEY_L               = 76,       // Key: L | l
    RAY_KEY_M               = 77,       // Key: M | m
    RAY_KEY_N               = 78,       // Key: N | n
    RAY_KEY_O               = 79,       // Key: O | o
    RAY_KEY_P               = 80,       // Key: P | p
    RAY_KEY_Q               = 81,       // Key: Q | q
    RAY_KEY_R               = 82,       // Key: R | r
    RAY_KEY_S               = 83,       // Key: S | s
    RAY_KEY_T               = 84,       // Key: T | t
    RAY_KEY_U               = 85,       // Key: U | u
    RAY_KEY_V               = 86,       // Key: V | v
    RAY_KEY_W               = 87,       // Key: W | w
    RAY_KEY_X               = 88,       // Key: X | x
    RAY_KEY_Y               = 89,       // Key: Y | y
    RAY_KEY_Z               = 90,       // Key: Z | z
    RAY_KEY_LEFT_BRACKET    = 91,       // Key: [
    RAY_KEY_BACKSLASH       = 92,       // Key: '\'
    RAY_KEY_RIGHT_BRACKET   = 93,       // Key: ]
    RAY_KEY_GRAVE           = 96,       // Key: `
    // Function keys
    RAY_KEY_SPACE           = 32,       // Key: Space
    RAY_KEY_ESCAPE          = 256,      // Key: Esc
    RAY_KEY_ENTER           = 257,      // Key: Enter
    RAY_KEY_TAB             = 258,      // Key: Tab
    RAY_KEY_BACKSPACE       = 259,      // Key: Backspace
    RAY_KEY_INSERT          = 260,      // Key: Ins
    RAY_KEY_DELETE          = 261,      // Key: Del
    RAY_KEY_RIGHT           = 262,      // Key: Cursor right
    RAY_KEY_LEFT            = 263,      // Key: Cursor left
    RAY_KEY_DOWN            = 264,      // Key: Cursor down
    RAY_KEY_UP              = 265,      // Key: Cursor up
    RAY_KEY_PAGE_UP         = 266,      // Key: Page up
    RAY_KEY_PAGE_DOWN       = 267,      // Key: Page down
    RAY_KEY_HOME            = 268,      // Key: Home
    RAY_KEY_END             = 269,      // Key: End
    RAY_KEY_CAPS_LOCK       = 280,      // Key: Caps lock
    RAY_KEY_SCROLL_LOCK     = 281,      // Key: Scroll down
    RAY_KEY_NUM_LOCK        = 282,      // Key: Num lock
    RAY_KEY_PRINT_SCREEN    = 283,      // Key: Print screen
    RAY_KEY_PAUSE           = 284,      // Key: Pause
    RAY_KEY_F1              = 290,      // Key: F1
    RAY_KEY_F2              = 291,      // Key: F2
    RAY_KEY_F3              = 292,      // Key: F3
    RAY_KEY_F4              = 293,      // Key: F4
    RAY_KEY_F5              = 294,      // Key: F5
    RAY_KEY_F6              = 295,      // Key: F6
    RAY_KEY_F7              = 296,      // Key: F7
    RAY_KEY_F8              = 297,      // Key: F8
    RAY_KEY_F9              = 298,      // Key: F9
    RAY_KEY_F10             = 299,      // Key: F10
    RAY_KEY_F11             = 300,      // Key: F11
    RAY_KEY_F12             = 301,      // Key: F12
    RAY_KEY_LEFT_SHIFT      = 340,      // Key: Shift left
    RAY_KEY_LEFT_CONTROL    = 341,      // Key: Control left
    RAY_KEY_LEFT_ALT        = 342,      // Key: Alt left
    RAY_KEY_LEFT_SUPER      = 343,      // Key: Super left
    RAY_KEY_RIGHT_SHIFT     = 344,      // Key: Shift right
    RAY_KEY_RIGHT_CONTROL   = 345,      // Key: Control right
    RAY_KEY_RIGHT_ALT       = 346,      // Key: Alt right
    RAY_KEY_RIGHT_SUPER     = 347,      // Key: Super right
    RAY_KEY_KB_MENU         = 348,      // Key: KB menu
    // Keypad keys
    RAY_KEY_KP_0            = 320,      // Key: Keypad 0
    RAY_KEY_KP_1            = 321,      // Key: Keypad 1
    RAY_KEY_KP_2            = 322,      // Key: Keypad 2
    RAY_KEY_KP_3            = 323,      // Key: Keypad 3
    RAY_KEY_KP_4            = 324,      // Key: Keypad 4
    RAY_KEY_KP_5            = 325,      // Key: Keypad 5
    RAY_KEY_KP_6            = 326,      // Key: Keypad 6
    RAY_KEY_KP_7            = 327,      // Key: Keypad 7
    RAY_KEY_KP_8            = 328,      // Key: Keypad 8
    RAY_KEY_KP_9            = 329,      // Key: Keypad 9
    RAY_KEY_KP_DECIMAL      = 330,      // Key: Keypad .
    RAY_KEY_KP_DIVIDE       = 331,      // Key: Keypad /
    RAY_KEY_KP_MULTIPLY     = 332,      // Key: Keypad *
    RAY_KEY_KP_SUBTRACT     = 333,      // Key: Keypad -
    RAY_KEY_KP_ADD          = 334,      // Key: Keypad +
    RAY_KEY_KP_ENTER        = 335,      // Key: Keypad Enter
    RAY_KEY_KP_EQUAL        = 336,      // Key: Keypad =
    // Android key buttons
    RAY_KEY_BACK            = 4,        // Key: Android back button
    RAY_KEY_MENU            = 82,       // Key: Android menu button
    RAY_KEY_VOLUME_UP       = 24,       // Key: Android volume up button
    RAY_KEY_VOLUME_DOWN     = 25        // Key: Android volume down button
};

typedef struct Ray_Vector2 {
    float x;
    float y;
} Ray_Vector2;

typedef struct Ray_Vector3 {
    float x;
    float y;
    float z;
} Ray_Vector3;

typedef struct Ray_Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Ray_Color;

typedef struct Ray_Camera3D {
    Ray_Vector3 position;
    Ray_Vector3 target;
    Ray_Vector3 up;
    float fovy;
    int projection;
} Ray_Camera3D;

const Ray_Color RAY_LIGHTGRAY  = { 200, 200, 200, 255 };
const Ray_Color RAY_GRAY       = { 130, 130, 130, 255 };
const Ray_Color RAY_DARKGRAY   = {  80,  80,  80, 255 };
const Ray_Color RAY_YELLOW     = { 253, 249,   0, 255 };
const Ray_Color RAY_GOLD       = { 255, 203,   0, 255 };
const Ray_Color RAY_ORANGE     = { 255, 161,   0, 255 };
const Ray_Color RAY_PINK       = { 255, 109, 194, 255 };
const Ray_Color RAY_RED        = { 230,  41,  55, 255 };
const Ray_Color RAY_MAROON     = { 190,  33,  55, 255 };
const Ray_Color RAY_GREEN      = {   0, 228,  48, 255 };
const Ray_Color RAY_LIME       = {   0, 158,  47, 255 };
const Ray_Color RAY_DARKGREEN  = {   0, 117,  44, 255 };
const Ray_Color RAY_SKYBLUE    = { 102, 191, 255, 255 };
const Ray_Color RAY_BLUE       = {   0, 121, 241, 255 };
const Ray_Color RAY_DARKBLUE   = {   0,  82, 172, 255 };
const Ray_Color RAY_PURPLE     = { 200, 122, 255, 255 };
const Ray_Color RAY_VIOLET     = { 135,  60, 190, 255 };
const Ray_Color RAY_DARKPURPLE = { 112,  31, 126, 255 };
const Ray_Color RAY_BEIGE      = { 211, 176, 131, 255 };
const Ray_Color RAY_BROWN      = { 127, 106,  79, 255 };
const Ray_Color RAY_DARKBROWN  = {  76,  63,  47, 255 };
const Ray_Color RAY_WHITE      = { 255, 255, 255, 255 };
const Ray_Color RAY_BLACK      = {   0,   0,   0, 255 };
const Ray_Color RAY_BLANK      = {   0,   0,   0,   0 };
const Ray_Color RAY_MAGENTA    = { 255,   0, 255, 255 };
const Ray_Color RAY_RAYWHITE   = { 245, 245, 245, 255 };

void Ray_InitWindow(int width, int height, const char* title);
void Ray_CloseWindow();
bool Ray_WindowShouldClose();
void Ray_HideCursor();
void Ray_rlDisableBackfaceCulling();
void Ray_PollInputEvents();

void Ray_DrawFPS(int posX, int posY);
void Ray_DrawText(const char* text, int posX, int posY, int fontSize, Ray_Color color);

Ray_Vector2 Ray_GetMouseDelta();
void Ray_SetMousePosition(int x, int y);

void Ray_DrawTriangle3D(Ray_Vector3 v1, Ray_Vector3 v2, Ray_Vector3 v3, Ray_Color color);
void Ray_DrawLine3D(Ray_Vector3 v1, Ray_Vector3 v2, Ray_Color color);
void Ray_DrawPlane(Ray_Vector3 position, Ray_Vector2 size, Ray_Color color);
void Ray_DrawSphere(Ray_Vector3 position, float radius, Ray_Color color);
void Ray_DrawSphereWires(Ray_Vector3 position, float radius, Ray_Color color);
void Ray_DrawCubeV(Ray_Vector3 position, Ray_Vector3 size, Ray_Color color);
void Ray_DrawCylinder(Ray_Vector3 position, float radius, float height, Ray_Color color);

void Ray_ClearBackground(Ray_Color color);
void Ray_BeginDrawing();
void Ray_EndDrawing();
void Ray_BeginMode3D(Ray_Camera3D camera);
void Ray_EndMode3D();

bool Ray_IsKeyPressed(int key);
bool Ray_IsKeyDown(int key);
