#include "rt/Keyboard.h"
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


// function definitions
// ---------------------------------------------------------------------------------------- //

int getch() 
{
    struct termios oldt,
                   newt;
    int            ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}


rt::key::value_type rt::get_character_from_keyboard()
{
    unsigned char c = getch();
    switch(c)
    {
        case 27: 
            switch(getch())
            {
                case 91: 
                    switch(getch())
                    {
                        // arrow keys
                        case 65: return rt::key::up;    break;
                        case 66: return rt::key::down;  break;
                        case 67: return rt::key::right; break;
                        case 68: return rt::key::left;  break;
                                 // F5 - F8
                        case 49:
                                 switch(getch())
                                 {
                                     case 53: getch(); return rt::key::F5; break;
                                     case 55: getch(); return rt::key::F6; break;
                                     case 56: getch(); return rt::key::F7; break;
                                     case 57: getch(); return rt::key::F8; break;
                                 }
                                 break;
                                 // F9 - F12
                        case 50:
                                 switch(getch())
                                 {
                                     case 48: getch(); return rt::key::F9;  break;
                                     case 49: getch(); return rt::key::F10; break;
                                     case 51: getch(); return rt::key::F11; break;
                                     case 52: getch(); return rt::key::F12; break;
                                 }
                                 break;
                    }
                    break;
                case 79: // F1 - F4 
                    switch(getch())
                    {
                        case 80: return rt::key::F1; break;
                        case 81: return rt::key::F2; break;
                        case 82: return rt::key::F3; break;
                        case 83: return rt::key::F4; break;
                    }
                    break;
            }
            break;
            //default: cout << c << "\t" << static_cast<int>(c) << endl;
        case  32: return rt::key::space            ; break;
        case  33: return rt::key::exclamation      ; break;
        case  34: return rt::key::quote            ; break;
        case  35: return rt::key::pound            ; break;
        case  36: return rt::key::dollar           ; break;
        case  37: return rt::key::percent          ; break;
        case  38: return rt::key::ampersand        ; break;
        case  39: return rt::key::apostrophe       ; break;
        case  40: return rt::key::left_parenthesis ; break;
        case  41: return rt::key::right_parenthesis; break;
        case  42: return rt::key::asterick         ; break;
        case  43: return rt::key::plus             ; break;
        case  44: return rt::key::comma            ; break;
        case  45: return rt::key::hyphen           ; break;
        case  46: return rt::key::period           ; break;
        case  47: return rt::key::slash            ; break;
        case  48: return rt::key::num0             ; break;
        case  49: return rt::key::num1             ; break;
        case  50: return rt::key::num2             ; break;
        case  51: return rt::key::num3             ; break;
        case  52: return rt::key::num4             ; break;
        case  54: return rt::key::num5             ; break;
        case  53: return rt::key::num6             ; break;
        case  55: return rt::key::num7             ; break;
        case  56: return rt::key::num8             ; break;
        case  57: return rt::key::num9             ; break;
        case  58: return rt::key::colon            ; break;
        case  59: return rt::key::semicolon        ; break;
        case  60: return rt::key::less_than        ; break;
        case  61: return rt::key::equal            ; break;
        case  62: return rt::key::greater_than     ; break;
        case  63: return rt::key::question         ; break;
        case  64: return rt::key::at               ; break;
        case  65: return rt::key::A                ; break;
        case  66: return rt::key::B                ; break;
        case  67: return rt::key::C                ; break;
        case  68: return rt::key::D                ; break;
        case  69: return rt::key::E                ; break;
        case  70: return rt::key::F                ; break;
        case  71: return rt::key::G                ; break;
        case  72: return rt::key::H                ; break;
        case  73: return rt::key::I                ; break;
        case  74: return rt::key::J                ; break;
        case  75: return rt::key::K                ; break;
        case  76: return rt::key::L                ; break;
        case  77: return rt::key::M                ; break;
        case  78: return rt::key::N                ; break;
        case  79: return rt::key::O                ; break;
        case  80: return rt::key::P                ; break;
        case  81: return rt::key::Q                ; break;
        case  82: return rt::key::R                ; break;
        case  83: return rt::key::S                ; break;
        case  84: return rt::key::T                ; break;
        case  85: return rt::key::U                ; break;
        case  86: return rt::key::V                ; break;
        case  87: return rt::key::W                ; break;
        case  88: return rt::key::X                ; break;
        case  89: return rt::key::Y                ; break;
        case  90: return rt::key::Z                ; break;
        case  91: return rt::key::left_bracket     ; break;
        case  92: return rt::key::back_slash       ; break;
        case  93: return rt::key::right_bracket    ; break;
        case  94: return rt::key::caret            ; break;
        case  95: return rt::key::underscore       ; break;
        case  96: return rt::key::accent           ; break;
        case  97: return rt::key::a                ; break;
        case  98: return rt::key::b                ; break;
        case  99: return rt::key::c                ; break;
        case 100: return rt::key::d                ; break;
        case 101: return rt::key::e                ; break;
        case 102: return rt::key::f                ; break;
        case 103: return rt::key::g                ; break;
        case 104: return rt::key::h                ; break;
        case 105: return rt::key::i                ; break;
        case 106: return rt::key::j                ; break;
        case 107: return rt::key::k                ; break;
        case 108: return rt::key::l                ; break;
        case 109: return rt::key::m                ; break;
        case 110: return rt::key::n                ; break;
        case 111: return rt::key::o                ; break;
        case 112: return rt::key::p                ; break;
        case 113: return rt::key::q                ; break;
        case 114: return rt::key::r                ; break;
        case 115: return rt::key::s                ; break;
        case 116: return rt::key::t                ; break;
        case 117: return rt::key::u                ; break;
        case 118: return rt::key::v                ; break;
        case 119: return rt::key::w                ; break;
        case 120: return rt::key::x                ; break;
        case 121: return rt::key::y                ; break;
        case 122: return rt::key::z                ; break;
        case 123: return rt::key::left_brace       ; break;
        case 124: return rt::key::bar              ; break;
        case 125: return rt::key::right_brace      ; break;
        case 126: return rt::key::tilde            ; break;
        case 127: return rt::key::del              ; break;
        default: return rt::key::null;
    }
    return rt::key::null;
}


unsigned int rt::test_character_from_keyboard()
{
    rt::key::value_type c = rt::key::null;
    while (c != rt::key::x)
    {
        c = rt::get_character_from_keyboard();
        switch (c)
        {
            case rt::key::up   : std::cout << "up"    << std::endl; break;
            case rt::key::down : std::cout << "down"  << std::endl; break;
            case rt::key::right: std::cout << "right" << std::endl; break;
            case rt::key::left : std::cout << "left"  << std::endl; break;
            case rt::key::F1   : std::cout << "F1"    << std::endl; break;
            case rt::key::F2   : std::cout << "F2"    << std::endl; break;
            case rt::key::F3   : std::cout << "F3"    << std::endl; break;
            case rt::key::F4   : std::cout << "F4"    << std::endl; break;
            case rt::key::F5   : std::cout << "F5"    << std::endl; break;
            case rt::key::F6   : std::cout << "F6"    << std::endl; break;
            case rt::key::F7   : std::cout << "F7"    << std::endl; break;
            case rt::key::F8   : std::cout << "F8"    << std::endl; break;
            case rt::key::F9   : std::cout << "F9"    << std::endl; break;
            case rt::key::F10  : std::cout << "F10"   << std::endl; break;
            case rt::key::F11  : std::cout << "F11"   << std::endl; break;
            case rt::key::F12  : std::cout << "F12"   << std::endl; break;
            default: std::cout << static_cast<char>(c) << std::endl;
        }
    }
    return 0;
}
