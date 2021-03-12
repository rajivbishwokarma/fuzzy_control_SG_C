#include <stdio.h>
#include <stdlib.h>
#include "../inc/fuzzification.h"
#include "../inc/defuzzification.h"
#include "../inc/rulebase.h"


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
	
	printf("================================================================================================================="
			"\n\t\t\t\tFuzzy Logic Frequeny Controller for Synchronous Generator"
			"\n1. The controller is designed for frequency control in the range of [40, 60] Hz."
			"\n2. For exiting the console, please enter any negative number [-1]."
		 "\n=================================================================================================================");

	printf("\nEnter the frequency of the generator (Hz): ");
	scanf("%f", &freq_crisp);

	while (freq_crisp >= 0) {
		printf("\n\nFrequency = %.2f Hz\n", freq_crisp);

		freq_crisp = freq_crisp - 40;
		printf("Normalized Frequency = %.2f Hz", freq_crisp);

		Fuzzification(freq_crisp, &freq_fuzzy, &input_fuzzy_set_id, &memi_negGigantic, &memi_negHuge, &memi_negBig, &memi_negMedium, &memi_negSmall,
			&memi_zero, &memi_posSmall, &memi_posMedium, &memi_posBig, &memi_posHuge, &memi_posGigantic);

		printf("\n\n\nNegative Gigantic\t=\t%.2f", memi_negGigantic);
		printf("\nNegative Huge\t\t=\t%.2f", memi_negHuge);
		printf("\nNegative Big\t\t=\t%.2f", memi_negBig);
		printf("\nNegative Medium\t\t=\t%.2f", memi_negMedium);
		printf("\nNegative Small\t\t=\t%.2f", memi_negSmall);

		printf("\nZero\t\t\t=\t%.2f", memi_zero);

		printf("\nPositive Small\t\t=\t%.2f", memi_posSmall);
		printf("\nPositive Medium\t\t=\t%.2f", memi_posMedium);
		printf("\nPositive Big\t\t=\t%.2f", memi_posBig);
		printf("\nPositive Huge\t\t=\t%.2f", memi_posHuge);
		printf("\nPositive Gigantic\t=\t%.2f", memi_posGigantic);

		/* Get the name of selected fuzzy set */
		input_fuzzy_set = FuzzySetIdentification(input_fuzzy_set_id);
		printf("\n\n\nInput Fuzzy Set = %s", input_fuzzy_set);
		free(input_fuzzy_set);

		/* Print the value of the degree of membership */
		printf("\nDegree of membership = %.2f", freq_fuzzy);

		/* Get the output fuzzy set */
		output_fuzzy_set = RuleBase(input_fuzzy_set_id, &output_fuzzy_set_id);
		printf("\n\nOutput Fuzzy Set = %s", output_fuzzy_set);
		free(output_fuzzy_set);

		duty_cycle = Defuzzification(output_fuzzy_set_id, freq_fuzzy);
		printf("\n\n\nOutput Duty Cycle = %.2f%%", duty_cycle);

		printf("\n\n\nEnter the frequency of the generator (Hz): ");
		scanf("%f", &freq_crisp);
		
		if (freq_crisp < 0) {
			return 0;
		}
	}

	return 0;
}