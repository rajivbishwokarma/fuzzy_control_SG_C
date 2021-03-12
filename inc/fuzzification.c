#include <string.h>
#include <stdlib.h>
#include "fuzzification.h"

/* Function definition section */
void Fuzzification(float freq_crisp, float *ptr_freq_fuzzy, int *ptr_input_fuzzy_set_id, float *ptr_negGigantic, float *ptr_negHuge, float *ptr_negBig, float *ptr_negMedium, float *ptr_negSmall, 
					float *ptr_zero, float *ptr_posSmall, float *ptr_posMedium, float *ptr_posBig, float *ptr_posHuge, float *ptr_posGigantic) 
{
	if (freq_crisp < 0) {
		*ptr_negGigantic = 1.0;
		
		/* Identifying the selected fuzzy set */
		*ptr_input_fuzzy_set_id = 1;


		/* The input to rule base is calculated with MAX rule, direct assignment works as only one value exists */
		*ptr_freq_fuzzy = *ptr_negGigantic;

		*ptr_negHuge = 0;
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
	else if ((freq_crisp >= 0) && (freq_crisp < 2)) {
		*ptr_negHuge =(float) ((0.5) * freq_crisp);
		*ptr_negGigantic = (float)((0.5) * (2 - freq_crisp));
		
		/* Here, however, the fuzzy membership function that has maximum value is assigned to the fuzzy frequency pointer. */
		if (*ptr_negHuge >= *ptr_negGigantic) {
			*ptr_freq_fuzzy = *ptr_negHuge;
			*ptr_input_fuzzy_set_id = 2;
		}
		else {
			*ptr_freq_fuzzy = *ptr_negGigantic;
			*ptr_input_fuzzy_set_id = 1;
		}


		/* Set everything else to zero */
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
	else if ((freq_crisp >= 2) && (freq_crisp < 4)) {
		*ptr_negHuge = (float)((0.5) * (4 - freq_crisp));
		*ptr_negBig = (float)((0.5) * (freq_crisp - 2));

		/* Choosing the maximum value */
		if (*ptr_negHuge >= *ptr_negBig) {
			*ptr_freq_fuzzy = *ptr_negHuge;
			*ptr_input_fuzzy_set_id = 2;
		}
		else {
			*ptr_freq_fuzzy = *ptr_negBig;
			*ptr_input_fuzzy_set_id = 3;
		}

		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negMedium = 0;
		*ptr_negSmall = 0;
		*ptr_zero = 0;
		*ptr_posSmall = 0;
		*ptr_posMedium = 0;
		*ptr_posBig = 0;
		*ptr_posHuge = 0;
		*ptr_posGigantic = 0;
	} 
	else if ((freq_crisp >= 4) && (freq_crisp < 6)) {
		*ptr_negBig = (float)((0.5) * (6- freq_crisp));
		*ptr_negMedium = (float)((0.5) * (freq_crisp - 4));

		/* Selecting the maximum value */
		if (*ptr_negBig >= *ptr_negMedium) {
			*ptr_freq_fuzzy = *ptr_negBig;
			*ptr_input_fuzzy_set_id = 3;
		}
		else {
			*ptr_freq_fuzzy = *ptr_negMedium;
			*ptr_input_fuzzy_set_id = 4;
		}

		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negSmall = 0;
		*ptr_zero = 0;
		*ptr_posSmall = 0;
		*ptr_posMedium = 0;
		*ptr_posBig = 0;
		*ptr_posHuge = 0;
		*ptr_posGigantic = 0;
	} 
	else if ((freq_crisp >= 6) && (freq_crisp < 8)) {
		*ptr_negMedium = (float)((0.5) * (6 - freq_crisp));
		*ptr_negSmall = (float)((0.5) * (freq_crisp - 6));

		/* Selecting the maximum value */
		if (*ptr_negMedium >= *ptr_negSmall) {
			*ptr_freq_fuzzy = *ptr_negMedium;
			*ptr_input_fuzzy_set_id = 4;
		}
		else {
			*ptr_freq_fuzzy = *ptr_negSmall;
			*ptr_input_fuzzy_set_id = 5;
		}


		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negBig = 0;
		*ptr_zero = 0;
		*ptr_posSmall = 0;
		*ptr_posMedium = 0;
		*ptr_posBig = 0;
		*ptr_posHuge = 0;
		*ptr_posGigantic = 0;
	} 
	else if ((freq_crisp >= 8) && (freq_crisp < 10)) {
		*ptr_zero = (float)((0.5) * (freq_crisp - 8));
		*ptr_negSmall = (float)((0.5) * (10 - freq_crisp));


		/* Selecting the maximum value */
		if (*ptr_zero >= *ptr_negSmall) {
			*ptr_freq_fuzzy = *ptr_zero;
			*ptr_input_fuzzy_set_id = 6;
		}
		else {
			*ptr_freq_fuzzy = *ptr_negSmall;
			*ptr_input_fuzzy_set_id = 5;
		}


		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negBig = 0;
		*ptr_negMedium = 0;
		*ptr_posSmall = 0;
		*ptr_posMedium = 0;
		*ptr_posBig = 0;
		*ptr_posHuge = 0;
		*ptr_posGigantic = 0;
	} 
	else if ((freq_crisp >= 10) && (freq_crisp < 12)) {
		*ptr_zero = (float)((0.5) * (12 - freq_crisp));
		*ptr_posSmall = (float)((0.5) * (freq_crisp - 10));


		/* Selecting the maximum value */
		if (*ptr_zero >= *ptr_posSmall) {
			*ptr_freq_fuzzy = *ptr_zero;
			*ptr_input_fuzzy_set_id = 6;
		}
		else {
			*ptr_freq_fuzzy = *ptr_posSmall;
			*ptr_input_fuzzy_set_id = 7;
		}


		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negBig = 0;
		*ptr_negMedium = 0;
		*ptr_negSmall = 0;
		*ptr_posMedium = 0;
		*ptr_posBig = 0;
		*ptr_posHuge = 0;
		*ptr_posGigantic = 0;
	} 
	else if ((freq_crisp >= 12) && (freq_crisp < 14)) {
		*ptr_posMedium = (float)((0.5) * (freq_crisp - 12));
		*ptr_posSmall = (float)((0.5) * (14 - freq_crisp));


		/* Selecting the maximum value */
		if (*ptr_posSmall >= *ptr_posMedium) {
			*ptr_freq_fuzzy = *ptr_posSmall;
			*ptr_input_fuzzy_set_id = 7;
		}
		else {
			*ptr_freq_fuzzy = *ptr_posMedium;
			*ptr_input_fuzzy_set_id = 8;
		}


		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negBig = 0;
		*ptr_negMedium = 0;
		*ptr_negSmall = 0;
		*ptr_zero = 0;
		*ptr_posBig = 0;
		*ptr_posHuge = 0;
		*ptr_posGigantic = 0;
	} 
	else if ((freq_crisp >= 14) && (freq_crisp < 16)) {
		*ptr_posMedium = (float)((0.5) * (16 - freq_crisp));
		*ptr_posBig = (float)((0.5) * (freq_crisp - 14));


		/* Selecting the maximum value */
		if (*ptr_posMedium >= *ptr_posBig) {
			*ptr_freq_fuzzy = *ptr_posMedium;
			*ptr_input_fuzzy_set_id = 8;
		}
		else {
			*ptr_freq_fuzzy = *ptr_posBig;
			*ptr_input_fuzzy_set_id = 9;
		}

		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negBig = 0;
		*ptr_negMedium = 0;
		*ptr_negSmall = 0;
		*ptr_zero = 0;
		*ptr_posSmall = 0;
		*ptr_posHuge = 0;
		*ptr_posGigantic = 0;
	} 
	else if ((freq_crisp >= 16) && (freq_crisp < 18)) {
		*ptr_posHuge = (float)((0.5) * (freq_crisp - 16));
		*ptr_posBig = (float)((0.5) * (18 - freq_crisp));


		/* Selecting the maximum value */
		if (*ptr_posHuge >= *ptr_posBig) {
			*ptr_freq_fuzzy = *ptr_posHuge;
			*ptr_input_fuzzy_set_id = 10;
		}
		else {
			*ptr_freq_fuzzy = *ptr_posBig;
			*ptr_input_fuzzy_set_id = 9;
		}

		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negBig = 0;
		*ptr_negMedium = 0;
		*ptr_negSmall = 0;
		*ptr_zero = 0;
		*ptr_posSmall = 0;
		*ptr_posMedium = 0;
		*ptr_posGigantic = 0;
	} 
	else if ((freq_crisp >= 18) && (freq_crisp < 20)) {
		*ptr_posHuge = (float)((0.5) * (20 - freq_crisp));
		*ptr_posGigantic = (float)((0.5) * (freq_crisp - 18));


		/* Selecting the maximum value */
		if (*ptr_posHuge >= *ptr_posGigantic) {
			*ptr_freq_fuzzy = *ptr_posHuge;
			*ptr_input_fuzzy_set_id = 10;
		}
		else {
			*ptr_freq_fuzzy = *ptr_posGigantic;
			*ptr_input_fuzzy_set_id = 11;
		}

		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negBig = 0;
		*ptr_negMedium = 0;
		*ptr_negSmall = 0;
		*ptr_zero = 0;
		*ptr_posSmall = 0;
		*ptr_posMedium = 0;
		*ptr_posBig = 0;
	}
	else if (freq_crisp >= 20) {
		*ptr_posGigantic = 1.0;

		/* The input to rule base is calculated with MAX rule, direct assignment works as only one value exists */
		*ptr_freq_fuzzy = *ptr_posGigantic;
		*ptr_input_fuzzy_set_id = 11;

		/* Set everything else to zero */
		*ptr_negGigantic = 0;
		*ptr_negHuge = 0;
		*ptr_negBig = 0;
		*ptr_negMedium = 0;
		*ptr_negSmall = 0;
		*ptr_zero = 0;
		*ptr_posSmall = 0;
		*ptr_posMedium = 0;
		*ptr_posBig = 0;
		*ptr_posHuge = 0;
	}
}


/* This function outputs the fuzzy set when passed the identification number of the set */
char* FuzzySetIdentification(int input_fuzzy_set_id) {
	char *ptr_set;

	ptr_set = (char *) malloc (sizeof (char) * 15);
	switch (input_fuzzy_set_id)
	{
	case 1: 
		strcpy(ptr_set, "negGigantic");
		break;
	case 2:
		strcpy(ptr_set, "negHuge");
		break;
	case 3:
		strcpy(ptr_set, "negBig");
		break;
	case 4:
		strcpy(ptr_set, "negMedium");
		break;
	case 5:
		strcpy(ptr_set, "negSmall");
		break;
	case 6: 
		strcpy(ptr_set, "zero");
		break;
	case 7:
		strcpy(ptr_set, "posSmall");
		break;
	case 8:
		strcpy(ptr_set, "posMedium");
		break;
	case 9:
		strcpy(ptr_set, "posBig");
		break;
	case 10:
		strcpy(ptr_set, "posHuge");
		break;
	case 11:
		strcpy(ptr_set, "posGigantic");
		break;
	default:
		strcpy(ptr_set, "No Fuzzy Set!");
		break;
	}
	return ptr_set;
}