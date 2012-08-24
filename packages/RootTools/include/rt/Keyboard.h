#ifndef RT_KEYBOARD_H
#define RT_KEYBOARD_H


// namespace rt --> root tools
namespace rt
{

// enum 
// -------------------------------------------------------------------------------------------------//

struct key
{
    enum value_type
    {
        // 0 - 31 are unprintable
        null                 =   0, // NULL
        start_of_heading     =   1, // start of heading
        start_of_text        =   2, // start of text
        end_of_text          =   3, // end of text
        end_of_transmission  =   4, // end of transmission
        enquiry              =   5, // enquiry
        acknowledge          =   6, // acknowledge
        bell                 =   7, // bell
        backspace            =   8, // backspace
        horizontal_tab       =   9, // horizontal tab      
        new_line             =  10, // new line            
        vertical_tab         =  11, // vertical tab        
        new_page             =  12, // new page            
        carriage_return      =  13, // carriage return     
        shift_out            =  14, // shift out           
        shift_in             =  15, // shift in            
        data_link_escape     =  16, // data link escape    
        device_control_1     =  17, // device control 1    
        device_control_2     =  18, // device control 2    
        device_control_3     =  19, // device control 3    
        device_control_4     =  20, // device_control 4    
        negative_acknowledge =  21, // negative acknowledge
        synchronous_idle     =  22, // synchronous idle    
        end_of_trans_block   =  23, // end of trans block  
        cancel               =  24, // cancel              
        end_of_medium        =  25, // end of medium       
        substitute           =  26, // substitute          
        escape               =  27, // escape              
        file_separator       =  28, // file separator      
        group_separator      =  29, // group separator     
        record_separator     =  30, // record separator    
        unit_separator       =  31, // unit separator      

        // printable
        space               =  32, // a space
        exclamation         =  33, // !
        quote               =  34, // "
        pound               =  35, // #
        dollar              =  36, // $
        percent             =  37, // %
        ampersand           =  38, // &
        apostrophe          =  39, // '
        left_parenthesis    =  40, // (
        right_parenthesis   =  41, // )
        asterick            =  42, // *
        plus                =  43, // +
        comma               =  44, // ,
        hyphen              =  45, // -
        period              =  46, // .
        slash               =  47, // /
        num0                =  48, // 0
        num1                =  49, // 1
        num2                =  50, // 2
        num3                =  51, // 3
        num4                =  52, // 4
        num5                =  54, // 5
        num6                =  53, // 6
        num7                =  55, // 7
        num8                =  56, // 8
        num9                =  57, // 9
        colon               =  58, // :
        semicolon           =  59, // ;
        less_than           =  60, // <
        equal               =  61, // =
        greater_than        =  62, // >
        question            =  63, // ?
        at                  =  64, // @
        A                   =  65, // A 
        B                   =  66, // B 
        C                   =  67, // C 
        D                   =  68, // D 
        E                   =  69, // E 
        F                   =  70, // F 
        G                   =  71, // G 
        H                   =  72, // H 
        I                   =  73, // I 
        J                   =  74, // J 
        K                   =  75, // K 
        L                   =  76, // L 
        M                   =  77, // M 
        N                   =  78, // N 
        O                   =  79, // O 
        P                   =  80, // P 
        Q                   =  81, // Q 
        R                   =  82, // R 
        S                   =  83, // S 
        T                   =  84, // T 
        U                   =  85, // U 
        V                   =  86, // V 
        W                   =  87, // W 
        X                   =  88, // X 
        Y                   =  89, // Y 
        Z                   =  90, // Z 
        left_bracket        =  91, // [ 
        back_slash          =  92, // backshash
        right_bracket       =  93, // ] 
        caret               =  94, // ^ 
        underscore          =  95, // _ 
        accent              =  96, // ` 
        a                   =  97, // a 
        b                   =  98, // b 
        c                   =  99, // c 
        d                   = 100, // d 
        e                   = 101, // e 
        f                   = 102, // f 
        g                   = 103, // g 
        h                   = 104, // h 
        i                   = 105, // i 
        j                   = 106, // j 
        k                   = 107, // k 
        l                   = 108, // l 
        m                   = 109, // m 
        n                   = 110, // n 
        o                   = 111, // o 
        p                   = 112, // p 
        q                   = 113, // q 
        r                   = 114, // r 
        s                   = 115, // s 
        t                   = 116, // t 
        u                   = 117, // u 
        v                   = 118, // v 
        w                   = 119, // w 
        x                   = 120, // x 
        y                   = 121, // y 
        z                   = 122, // z 
        left_brace          = 123, // { 
        bar                 = 124, // | 
        right_brace         = 125, // } 
        tilde               = 126, // ~ 
        del                 = 127, // DEL
        left                = 128, // Left arrow
        right               = 129, // Right arrow
        up                  = 130, // Up arrow
        down                = 131, // Down arrow
        F1                  = 132, // F1 
        F2                  = 133, // F2
        F3                  = 134, // F3
        F4                  = 135, // F4
        F5                  = 136, // F5
        F6                  = 137, // F6
        F7                  = 138, // F7
        F8                  = 139, // F8
        F9                  = 140, // F8
        F10                 = 141, // F10
        F11                 = 142, // F11
        F12                 = 143, // F12

        // not supported
        //F13               = 148, // F13
        //F14               = 148, // F14
        //F15               = 148, // F15

        pause               = 144, // Pause
        static_size
    };
};


// functions 
// -------------------------------------------------------------------------------------------------//

// returns the key of the character pressed
rt::key::value_type get_character_from_keyboard();


// test the get_character_from_keyboard() funciton
unsigned int test_character_from_keyboard();


// -------------------------------------------------------------------------------------------------//

} // namespace rt

#endif //RT_KEYBOARD_H
