#include "input_key_macro.h"

// keycode_name returns string name of its input key value
// using X macro, the match of name-val is from "keycodes.def"
// if no key matchs with value, it returns string "UNKNOWN_KEY"

const char* keycode_name(int code)
{
    switch (code) {

#define X(name, val) case (val): return #name;
#include "keycodes.def"
#undef X

    default:
        return "UNKNOWN_KEY";
    }
}