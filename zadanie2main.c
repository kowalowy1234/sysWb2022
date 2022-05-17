#include <p24fj128ga010.h>

_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRI)

#define SCALE 308L

/* numer którym dostajemy siê do czujnika temperatury */

#define TSENS 4
#define AINPUTS 0xffcf
void ADCinit(int amask)

{
	AD1PCFG = amask;
	AD1CON1 = 0x00e0;
	AD1CSSL = 0;
	AD1CON2 = 0;
	AD1CON3 = 0x1f02;
	AD1CON1bits.ADON = 1;
}

int readADC(int ch)

{
	AD1CHS = ch;
	AD1CON1bits.SAMP = 1;
	while (!AD1CON1bits.DONE);
	return ADC1BUF0;
}


int main(void)
{
	TRISA = 0xFF00;
	TRISD = 0xFFFF;

	unsigned long i;
	int j;
	unsigned char display = 0;
	int temp;
	unsigned int szybkosc = 10L;

	PORTA = 0x0000;
	ADCinit(AINPUTS); /*inicjalizacja konwertera AD*/

	display = 1;

	while (1) {

		Nop();

		if(temp <= 250){
			display = 0;
		}

		PORTA = display;

		for (i = 500L * SCALE; i > 0; i--) Nop();
		temp = readADC(TSENS);
		
		if (temp > 250) {
			for(j = 6; j>=0; j--) {
				for (i = 500L * SCALE; i > 0; i--) Nop();
				temp = readADC(TSENS);
				if(temp <= 250){
					display = 0;
					break;
				}
				if(display == 1){
					display = 0;
				}
				else if(display == 0){
					display = 1;
				}
				if(j == 0){
					display = 255;
				}
				PORTA = display;
			}
		} 

	}

}