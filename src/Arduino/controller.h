#pragma once


// Definition of the controller setup
// Enum code, button name, analog
#define CONTROLLER                \
X(START, "start", false)          \
X(A, "a", false)                  \
X(B, "b", false)                  \
X(C_LEFT, "c_left", false)        \
X(C_UP, "c_up", false)            \
X(C_RIGHT, "c_right", false)      \
X(C_DOWN, "c_down", false)        \
X(D_LEFT, "d_left", false)        \
X(D_UP, "d_up", false)            \
X(D_RIGHT, "d_right", false)      \
X(D_DOWN, "d_down", false)        \
X(L, "l", false)                  \
X(R, "r", false)                  \
X(Z, "z", false)                  \
X(JOY_LEFT, "joy_left", true)     \
X(JOY_UP, "joy_up", true)         \
X(JOY_RIGHT, "j_right", true)     \
X(JOY_DOWN, "j_ddown", true)      \

// Enum value
#define X(code, name, analog) code,
enum Controller : byte
{
  CONTROLLER
};
#undef X

// Button name
#define X(code, name, analog) name,
const char * button_name[] =
{
  CONTROLLER
};
#undef X

// Analog input
#define X(code, name, analog) analog,
bool button_analog[]
{
  CONTROLLER
};
#undef X
