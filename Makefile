# MPLAB IDE generated this makefile for use with GNU make.
# Project: zadanie2.mcp
# Date: Tue Apr 26 18:29:13 2022

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

zadanie2.hex : zadanie2.cof
	$(HX) "zadanie2.cof"

zadanie2.cof : zadanie2main.o
	$(CC) -mcpu=24FJ128GA010 "zadanie2main.o" -o"zadanie2.cof" -Wl,--script="C:\Program Files (x86)\Microchip\MPLAB C30\support\PIC24F\gld\p24FJ128GA010.gld",--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD2=1,--defsym=__ICD2RAM=1,-Map="zadanie2.map",--report-mem

zadanie2main.o : c:/program\ files\ (x86)/microchip/mplab\ c30/support/PIC24F/h/p24fj128ga010.h zadanie2main.c
	$(CC) -mcpu=24FJ128GA010 -x c -c "zadanie2main.c" -o"zadanie2main.o" -D__DEBUG -D__MPLAB_DEBUGGER_ICD2=1 -g -Wall

clean : 
	$(RM) "zadanie2main.o" "zadanie2.cof" "zadanie2.hex"

