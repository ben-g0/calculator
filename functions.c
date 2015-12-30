#include <knightos/display.h>
#include <knightos/system.h>
#include <knightos/keys.h>
#include <corelib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

char *strcat(char *restrict dst, const char *restrict src) {
	const size_t destination_length= strlen(dst);
	const size_t src_length = strlen(src);
	memcpy(dst+destination_length, src, src_length+1);
	return dst;
}

double strToDouble(char* string){
	double result= 0.0;
	int dotpos = 9999;
	int pos = 0;
	char currentChar = string[pos];
	while(isdigit(currentChar) || currentChar == '.'){
		if(isdigit(currentChar)){
			result *= 10.0;
			result += (double)(currentChar-'0');
		}else{
			dotpos = pos;
		}
		pos++;
		currentChar = string[pos];
	}
	dotpos = pos-dotpos-1;
	while(dotpos>0){
		result /= 10.0;
		dotpos--;
	}
	return result;
}

char *doubleToStr(double d, char *result){
	//converts a double to a string.
	//result is stored in the result parameter, or returned as a newly generated string
	//when result == NULL
	double i;
	int length = 0;
	char currentChar;
	//char *result = malloc(21);
	char *copy;
	char *single = malloc(2);
	bool negative = false;
	strcpy(single,"0");

	copy = malloc(21);

	if(result == NULL){
		result = malloc(21);
	}
	strcpy(result,"");

	if(d<0){
		negative = true;
		d = -d;
	}
	i = d;

	//integer part
	do{
		//get character
		//currentChar = ((int)fmod(i,10.0))+'0';
		currentChar = (((int)i)%10)+'0';
		//add to start of the string
		strcpy(copy,result);
		//strncopy(single,&currentChar,1);
		single[0] = currentChar;//
		strcpy(result,single);
		strcat(result,copy);
		i /= 10.0;
		length++;
	}while(i > 1.0 && length<20);

	//add a minus if the number is negative
	if(negative){
		//strcpy(result,"-");
		single[0] = '-';
		strcpy(copy,result);
		strcpy(result,single);
		strcat(result,copy);
		length++;
	}

	//get rid of the integer part
	d -= (double)((long)d);
	//d = fmod(d,1.0);
	if(d == 0.0){
		//no decimal part, so we're done
		//free(copy);
		return result;
	}
	//add a . before adding the decimal part
	strcat(result,".");
	length++;

	//decimal part
	while((d != 0.0) && (length<20)){
		//get character
		d *= 10.0;
		//add to end of string
		currentChar = ((int)d)+'0';
		d -= (double)((int)d);
		//d = fmod(d,1.0);
		//strncopy(single,&currentChar,1);
		single[0] = currentChar;//
		strcat(result,single);
	}
	//free(copy);
	return result;
}
