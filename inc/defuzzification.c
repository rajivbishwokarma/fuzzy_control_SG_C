#include <string.h>
#include <stdlib.h>
#include "defuzzification.h"

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