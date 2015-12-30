#include <knightos/display.h>
#include <knightos/system.h>
#include <knightos/keys.h>
#include <corelib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

SCREEN *screen;
unsigned char lost_focus;
unsigned char nextChar;

void main() {
	char *floatstring = malloc(50);
	char *charstring = "0";
	double float1 = 0.0;
	double float2;
	int operation;
	double result;
	char *resultString = malloc(100);
	int status=0;
	strcpy(floatstring, "");
	load_library("/lib/core");
	get_lcd_lock();
	get_keypad_lock();
	screen = screen_allocate();
	flush_keys();
	screen_clear(screen);
	draw_window(screen,"Calculator",0);
	//doubleToStr(-1337.125,resultString);
	//draw_string(screen, 2, 14, resultString);
	screen_draw(screen);
	launch_castle();
	while (1){
		unsigned char key;
		screen_draw(screen);
		//screen_clear(screen);//
		key = app_wait_key(&lost_focus);
		set_charset(2);//force number input
		nextChar = get_character_input(&lost_focus);
		flush_keys();
		if(nextChar == ','){
			nextChar = '.';
		}
		if(isdigit(nextChar) || (nextChar == '.')){
			strncpy(charstring,&nextChar,1);
			strcat(floatstring,charstring);
			if(status<2){
				draw_string(screen, 2, status*6+8, floatstring);
			}
		}else if(key==56){
			strcpy(floatstring, "");
			strcpy(resultString, "");
			screen_clear(screen);
			draw_window(screen,"Calculator",0);
			status = 0;
		}else if(key==9 && status==1){
			char *fasstr;
			//float1 = strToDouble(floatstring);
			//doubleToStr(float1,resultString);
			//draw_string(screen, 2, 14, resultString);
			float2 = strToDouble(floatstring);
			switch(operation){
				case 0:
					result = float1+float2;
					break;
				case 1:
					result = float1-float2;
					break;
				case 2:
					result = float1*float2;
					break;
				case 3:
					result = float1/float2;
					break;
			}
			strcpy(resultString," = ");
			fasstr = doubleToStr(result,NULL);
			strcat(resultString,fasstr);
			//free(fasstr);
			draw_string(screen, 2, 20, resultString);
			status = 2;
		}else if(nextChar=='+' && status==0){
			operation = 0;
			status = 1;
			draw_string(screen,90,8,"+");
			float1 = strToDouble(floatstring);
			strcpy(floatstring, "");
		}else if(nextChar=='-' && status==0){
			operation = 1;
			status = 1;
			draw_string(screen,90,8,"-");
			float1 = strToDouble(floatstring);
			strcpy(floatstring, "");
		}else if(nextChar=='*' && status==0){
			operation = 2;
			status = 1;
			draw_string(screen,90,8,"*");
			float1 = strToDouble(floatstring);
			strcpy(floatstring, "");
		}else if(nextChar=='/' && status==0){
			operation = 3;
			status = 1;
			draw_string(screen,90,8,"/");
			float1 = strToDouble(floatstring);
			strcpy(floatstring, "");
		}
		//draw_byte(screen,2,14,key);
		//sprintf(resultString,"= %lf",221.0);
	}
}
