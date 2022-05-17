#include <p24fj128ga010.h>
#include <math.h>
//Konfiguracja dla Explorer 16 z progr. icd2
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & FWDTEN_OFF)
_CONFIG2(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMOD_HS & FNOSC_PRI)

#define SCALE 308L

int main(void) {
  int przesunwPrawo(int x, int k) {
    return x >> k;
  }

  int decToBin(int x) {

    int number = x;
    int n, i;
    static int tab[32];

    n = 31;

    while (n >= 0) {
      tab[n] = x & 1;
      n--;
      x >>= 1;
    }

    return tab;
  }

  int zwrocKtyBit(int x, int k) {
    int * wynik;
    wynik = decToBin(x);

    return *(wynik + 32 - k);
  }

  unsigned long i;
  unsigned char count = 0;
  unsigned char count2 = 0;
  unsigned char display = 0;
  unsigned char sign = 1;
  unsigned char start = 1;
  unsigned char losowa = 115;
  unsigned char pierwszy = zwrocKtyBit(losowa, 6) ^ zwrocKtyBit(losowa, 5) ^ zwrocKtyBit(losowa, 2) ^ zwrocKtyBit(losowa, 1);
  unsigned char pojemnik = 7;
  unsigned char pomoc = 0;
  unsigned char pojemnik2 = 0;   
  unsigned char pojemnik3 = 1; 

  //inicjalizacja
  PORTA = 0x0000;
  TRISA = 0xFF00;
  TRISD = 0xFFFF;

  //niekoÅ?czÄ?ca siÄ? pÄ?tla 
  again:
    Nop();
  if (display == 6 && start == 1) {
    count = 7;
    start = -1;
  }
  if (display == 4 && start == 1) {
    count = 0;
    count2 = 0;
    start = -1;
  }
if (display == 7 && start == 1) {
pojemnik = 7;
pomoc = 0;
pojemnik2 = 0;
pojemnik3 = 1;  
start=-1;
    
  }

  if (display == 5 && start == 1) {
    count2 = 144;
    count = 9;
    start = -1;
  }

  if (display == 2 || display == 3) {
    PORTA = (unsigned int) count ^ (count >> 1);
  } else if (display == 4 || display == 5) {
    PORTA = (unsigned int) count + count2;
  } else {
    PORTA = (unsigned int) count;
  }

  for (i = 300L * SCALE; i > 0; i--) Nop();
  if (PORTDbits.RD13 == 0) {
    start = 1;
    if (display == 8)
      display = 0;
    else
      display = display + 1;
  } else if (PORTDbits.RD6 == 0) {
    start = 1;

    if (display == 0)
      display = 8;
    else
      display = display - 1;
  }

  switch (display) {
  case 0:
    count = count + 1;
    if (count > 256)
      count = 0;
    break;
  case 1:
    count = count - 1;
    if (count < 0)
      count = 256;
    break;
  case 2:
    count = count + 1;
    if (count > 256)
      count = 0;
    break;
  case 3:
    count = count - 1;
    if (count < 0)
      count = 256;
    break;
  case 4:
    count = count + 1;
    if (count > 9) {
      count2 += 16;
      count = 0;
    }
    if (count2 > 144) {
      count = 0;
      count2 = 0;
    }
    break;
  case 5:
    count = count - 1;
    if (count <= 0) {
      count2 -= 16;
      count = 9;
    }
    if (count2 < 16) {
      start = 1;
    }
    break;
  case 6:
    if (count == 7) {
      sign = 1;
      start = -1;
    }
    if (count == 224)
      sign = -1;
    if (sign == 1)
      count = count << 1;
    else
      count = count >> 1;
	break;
  case 7:
if(pojemnik2>=255)
{
pojemnik = 7;
pomoc = 0;
pojemnik2 = 0;
pojemnik3 = 1;  
}
else
{
if(pomoc<pojemnik)
{
pojemnik3=pojemnik3<<1;

pomoc=pomoc+1;
}
else
{
pojemnik2=pojemnik2+pow(2,pojemnik);
pojemnik=pojemnik-1;
pomoc=0;
pojemnik3=1;
}
}

count=pojemnik2+pojemnik3;



    break;
  case 8:

    losowa = przesunwPrawo(losowa, 1) | (pierwszy << 5);
    count = losowa;
    pierwszy = zwrocKtyBit(losowa, 6) ^ zwrocKtyBit(losowa, 5) ^ zwrocKtyBit(losowa, 2) ^ zwrocKtyBit(losowa, 1);
    break;

  default:
    count = 0;
  }

  goto again;

}