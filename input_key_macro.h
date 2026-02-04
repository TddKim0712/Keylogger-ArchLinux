#ifndef INPUT_KEY_MACRO_H
#define INPUT_KEY_MACRO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/*
original key - values are from <linux/input-event-codes.h>
customized to use like macro
values are generated from keycodes.def  (X-macro lists)

*/

typedef enum keycode_t {

#define X(name, val) name = (val) ,
#include keycodes.def
#undef X

} keycode_t;


// X-macro :: preprocessor firstly checks and modifies # ~texts~ 
// keycode_t declaration above will be like:
// enum keycode_t {
// 	 KEY_F11 = 87,
//    KEY_F12 = 88, ......
// 	} keycode_t;



/*
keycode_name :
	returns a string name for its matched own key value 
*/

const char* keycode_name(int code);





