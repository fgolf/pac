#if !defined(__CINT__) || defined(__MAKECINT__)
#include "rt/keyboard.h"
#include <iostream>
#endif

// includes needed by interpreter
#ifdef __CINT__
#include <stdexcept>
#endif


int main()
{
    rt::test_character_from_keyboard();
}
