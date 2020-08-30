#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

/* Function decleration section */

void Fuzzification(float freq_crisp, float *ptr_freq_fuzzy, int *ptr_input_fuzzy_set_id, float *ptr_ng, float *ptr_nh, float *ptr_nb, float *ptr_nm, float *ptr_ns,
					float *ptr_z, float *ptr_ps, float *ptr_pm, float *ptr_pb, float *ptr_ph, float *ptr_pg);

char* RuleBase(int input_fuzzy_set_id, int *output_fuzzy_set_id);

float Defuzzification(int output_fuzzy_set_id, float freq_fuzzy);

char* FuzzySetIdentification(int input_fuzzy_set_id);

void WelcomeScreen();

/* 
Variables that represent membership function are of the following form:
Input fuzzy set membership function: memi_<fuzzy_set>
Ouptut fuzzy set memebership funciton: memo_<fuzzy_set>

Integer Code		Representation		Fuzzy Sets

 [1]		negGigantic:			Negative Gigantic
 [2]		negHuge:				Negative Huge
 [3]		negBig:					Negative Big
 [4]		negMedium:				Negative Medium
 [5]		negSmall:				Legative Small
 [6]		zero:					Zero
 [7]		posSmall:				Positive Small
 [8]		posMedium:				Positive Medium
 [9]		posBig:					Positive Big
 [10]		posHuge:				Positive Huge
 [11]		posGigantic:			Positive Gigantic
 */


/* Execution starts here */

int main() {
	float freq_crisp, freq_fuzzy;
	float duty_cycle;

	int input_fuzzy_set_id;			/* The selected input memebership function identification number */
	char *input_fuzzy_set;			/* Identified fuzzy set name */

	int output_fuzzy_set_id;
	char *output_fuzzy_set;

	/* Input fuzzy set membership functions */
	float memi_negGigantic, memi_negHuge, memi_negBig, memi_negMedium, memi_negSmall;
	float memi_zero;
	float memi_posSmall, memi_posMedium, memi_posBig, memi_posHuge, memi_posGigantic;

	/* Display the welcome screen message */
	WelcomeScreen();

	printf("\nEnter the frequency of the generator (Hz): ");
	scanf_s("%f", &freq_crisp);

	while (freq_crisp >= 0) {
		printf("\n\nFrequency = %.2f Hz\n", freq_crisp);

		freq_crisp = freq_crisp - 40;
		printf("Normalized Frequency = %.2f Hz", freq_crisp);

		Fuzzification(freq_crisp, &freq_fuzzy, &input_fuzzy_set_id, &memi_negGigantic, &memi_negHuge, &memi_negBig, &memi_negMedium, &memi_negSmall,
			&memi_zero, &memi_posSmall, &memi_posMedium, &memi_posBig, &memi_posHuge, &memi_posGigantic);

		printf_s("\n\n\nNegative Gigantic\t=\t%.2f", memi_negGigantic);
		printf_s("\nNegative Huge\t\t=\t%.2f", memi_negHuge);
		printf_s("\nNegative Big\t\t=\t%.2f", memi_negBig);
		printf_s("\nNegative Medium\t\t=\t%.2f", memi_negMedium);
		printf_s("\nNegative Small\t\t=\t%.2f", memi_negSmall);

		printf_s("\nZero\t\t\t=\t%.2f", memi_zero);

		printf_s("\nPositive Small\t\t=\t%.2f", memi_posSmall);
		printf_s("\nPositive Medium\t\t=\t%.2f", memi_posMedium);
		printf_s("\nPositive Big\t\t=\t%.2f", memi_posBig);
		printf_s("\nPositive Huge\t\t=\t%.2f", memi_posHuge);
		printf_s("\nPositive Gigantic\t=\t%.2f", memi_posGigantic);

		/* Get the name of selected fuzzy set */
		input_fuzzy_set = FuzzySetIdentification(input_fuzzy_set_id);
		printf_s("\n\n\nInput Fuzzy Set = %s", input_fuzzy_set);
		free(input_fuzzy_set);

		/* Print the value of the degree of membership */
		printf_s("\nDegree of membership = %.2f", freq_fuzzy);

		/* Get the output fuzzy set */
		output_fuzzy_set = RuleBase(input_fuzzy_set_id, &output_fuzzy_set_id);
		printf_s("\n\nOutput Fuzzy Set = %s", output_fuzzy_set);
		free(output_fuzzy_set);

		duty_cycle = Defuzzification(output_fuzzy_set_id, freq_fuzzy);
		printf_s("\n\n\nOutput Duty Cycle = %.2f%%", duty_cycle);

		printf("\n\n\nEnter the frequency of the generator (Hz): ");
		scanf_s("%f", &freq_crisp);
		
		if (freq_crisp < 0) {
			printf_s("Press any key to exit...");
			_getch();
			return 0;
		}
		system("cls");
	}

	return 0;
}

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


float Defuzzification(int output_fuzzy_set_id, float freq_fuzzy)
{
	/* Output fuzzy set membership functions */
	float memo_negGigantic, memo_negHuge, memo_negBig, memo_negMedium, memo_negSmall;
	float memo_zero;
	float memo_posSmall, memo_posMedium, memo_posBig, memo_posHuge, memo_posGigantic;

	float degree_mem;
	degree_mem = freq_fuzzy;

	float duty_cycle;

	switch (output_fuzzy_set_id)
	{
	case 1: /* Negative Gigantic */
		memo_negGigantic = -(degree_mem / 10) + 10;
		memo_negHuge = degree_mem / 10;

		duty_cycle = (memo_negGigantic >= memo_negHuge) ? memo_negHuge : memo_negGigantic;

		break;
	case 2:	/* Negative Huge */
		memo_negHuge = -(degree_mem / 10) + 20;
		memo_negBig = (degree_mem / 10) + 10;
		
		duty_cycle = (memo_negBig >= memo_negHuge) ? memo_negHuge : memo_negBig;

		break;
	case 3: /* Negative Big */
		memo_negBig = -(degree_mem / 10) + 30;
		memo_negMedium = (degree_mem / 10) + 20;
		
		duty_cycle = (memo_negBig >= memo_negMedium) ? memo_negMedium : memo_negBig;
		
		break;
	case 4: /* Negative Medium */
		memo_negMedium = -(degree_mem / 10) + 40;
		memo_negSmall = (degree_mem / 10) + 30;

		duty_cycle = (memo_negSmall >= memo_negMedium) ? memo_negMedium : memo_negSmall;

		break;
	case 5: /* Negative Small */
		memo_negSmall = -(degree_mem / 10) + 50;
		memo_zero = (degree_mem / 10) + 40;

		duty_cycle = (memo_negSmall >= memo_zero) ? memo_zero : memo_negSmall;

		break;
	case 6:	/* Zero */
		memo_zero = 50;

		duty_cycle = memo_zero;

		break;
	case 7:	/* Positive Small*/
		memo_zero = -(degree_mem / 10) + 60;
		memo_posSmall = (degree_mem / 10) + 50;

		duty_cycle = (memo_zero >= memo_posSmall) ? memo_posSmall : memo_zero;

		break;
	case 8: /* Positive Medium */
		memo_posSmall = -(degree_mem / 10) + 70;
		memo_posMedium = (degree_mem / 10) + 60;

		duty_cycle = (memo_posMedium >= memo_posSmall) ? memo_posSmall : memo_posMedium;

		break;
	case 9: /* Positive Big */
		memo_posMedium = -(degree_mem / 10) + 80;
		memo_posBig = (degree_mem / 10) + 70;

		duty_cycle = (memo_posMedium >= memo_posBig) ? memo_posBig : memo_posMedium;

		break;
	case 10: /* Positive Huge */
		memo_posBig = -(degree_mem / 10) + 90;
		memo_posHuge = (degree_mem / 10) + 80;

		duty_cycle = (memo_posHuge >= memo_posBig) ? memo_posBig : memo_posHuge;

		break;
	case 11: /* Positive Gigantic*/
		memo_posHuge = -(degree_mem / 10) + 100;
		memo_posGigantic = (degree_mem / 10) + 90;

		duty_cycle = (memo_posHuge >= memo_posGigantic) ? memo_posGigantic : memo_posHuge;
		
		break;
	default:
		duty_cycle = 0;
		break;
	}
	return duty_cycle;
}


/* This sets everything passed as a parameter to zero. */
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

void WelcomeScreen() {
	SetConsoleTitle("Fuzzy Logic Frequency Controller for Synchronous Generator");
	printf_s("=================================================================================================================");
	printf_s("\n\t\t\t\tFuzzy Logic Frequeny Controller for Synchronous Generator");
	printf_s("\n1. The controller is designed for frequency control in the range of [40, 60] Hz.");
	printf_s("\n2. For exiting the console, please enter any negative number [-1].");
	printf_s("\n=================================================================================================================");
}
