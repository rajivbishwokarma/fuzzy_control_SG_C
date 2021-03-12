#include <string.h>
#include <stdlib.h>
#include "rulebase.h"

/* Check the antecedent and assign the consequent */
char* RuleBase(int input_fuzzy_set_id, int *output_fuzzy_set_id)
{
	char *returnString;
	returnString = (char *)malloc(sizeof(char) * 15);

	if (input_fuzzy_set_id == 1) { 
		strcpy(returnString, "posGigantic");
		*output_fuzzy_set_id = 11;
	}
	else if (input_fuzzy_set_id == 2) {
		strcpy(returnString, "posHuge");
		*output_fuzzy_set_id = 10;
	} 
	else if (input_fuzzy_set_id == 3) {
		strcpy(returnString, "posBig");
		*output_fuzzy_set_id = 9;
	}
	else if (input_fuzzy_set_id == 4) {
		strcpy(returnString, "posMedium");
		*output_fuzzy_set_id = 8;
	}
	else if (input_fuzzy_set_id == 5) {
		strcpy(returnString, "posSmall");
		*output_fuzzy_set_id = 7;
	}
	else if (input_fuzzy_set_id == 6) {
		strcpy(returnString, "zero");
		*output_fuzzy_set_id = 6;
	}
	else if (input_fuzzy_set_id == 7) {
		strcpy(returnString, "negSmall");
		*output_fuzzy_set_id = 5;
	}
	else if (input_fuzzy_set_id == 8) {
		strcpy(returnString, "negMedium");
		*output_fuzzy_set_id = 4;
	}
	else if (input_fuzzy_set_id == 9) {
		strcpy(returnString, "negBig");
		*output_fuzzy_set_id = 3;
	}
	else if (input_fuzzy_set_id == 10) {
		strcpy(returnString, "negHuge");
		*output_fuzzy_set_id = 2;
	}
	else if (input_fuzzy_set_id == 11) {
		strcpy(returnString, "negGigantic");
		*output_fuzzy_set_id = 1;
	}
	else {
		strcpy(returnString, "no_fuzzy_set");
		*output_fuzzy_set_id = 0;
	}

	return returnString;
}


/* This sets everything passed as a parameter to zero. 
void SetZero(float *ptr_negBig, float *ptr_negMedium, float *ptr_negSmall,
	float *ptr_zero, float *ptr_posSmall, float *ptr_posMedium, float *ptr_posBig, float *ptr_posHuge, float *ptr_posGigantic)
{
	*ptr_negBig = 0;
	*ptr_negMedium = 0;
	*ptr_negSmall = 0;
	*ptr_zero = 0;
	*ptr_posSmall = 0;
	*ptr_posMedium = 0;
	*ptr_posBig = 0;
	*ptr_posHuge = 0;
	*ptr_posGigantic = 0;
}
*/