#include <xc.inc>
#include <pic18F47Q10.inc>

    
GLOBAL _config  ;define the function to link it with the C definition

    
PSECT text0,local,class=CODE,reloc=2
    
CONFIG FEXTOSC=0b100 ;deactivate external oscillator (to allow write to RA7)
CONFIG CSWEN=0b1 ;allow editing NDIV and NOSC for CLK config
CONFIG WDTE=OFF ;required to avoid WDT restarting micro all the time

    
_config:
    
    ;===============
    ;CONFIGURE PORTA
    ;===============
    BANKSEL LATA
    CLRF LATA,1 ; Set all LatchA bits to zero
    
    MOVLW 0b00001110 
    BANKSEL TRISA
    MOVWF TRISA,1 ;defines the pin direction. 0=out, 1=in. RA1, RA2, RA3 are input pins, all other are output pins.
    
    MOVLW 0b00001110
    BANKSEL ANSELA
    MOVWF ANSELA,1 ;analog select. RA1, RA2, RA3 are analog pins, the others are digital pins.
    
    
    ;===============
    ;CONFIGURE PORTC
    ;===============
    BANKSEL LATC
    CLRF LATC,1 ; Set all LatchD bits to zero
    
    BANKSEL TRISC
    CLRF TRISC,1 ;All pins are output
    BSF  TRISC,7 ;except RC7, that will be used as RX - microchip specifies RX as input pin
    
    BANKSEL ANSELC
    CLRF ANSELC,1 ;All digital pins
    
    BANKSEL RC4PPS
    MOVLW 0x09  ;estabelecer a EUSART1 (TX/CK) no pino RC4
    MOVWF RC4PPS, 1  ;place the EUSART1 (TX/CK) in RC4   
    
    BANKSEL RX1PPS
    MOVLW 0b00010111 ;estabelecer o pino RC7 como RX  datasheet (pagina 302)
    MOVWF RX1PPS, 1  ;place the EUSART1 (RX) in RC7      
    
    
    
    
    ;===============
    ;CONFIGURE CLOCK
    ;===============
    BANKSEL OSCCON1
    MOVLW 0b01100000  ;NOSC=0110 (internal high speed osc)
    MOVWF OSCCON1,1   ;NDIV=0000 (divider=1, clk divided by 1)
    
    BANKSEL OSCFRQ
    MOVLW 0b0000110 ; HFFRQ 0110 -> clk= 32 MHz
    MOVWF OSCFRQ,1
    
    BANKSEL OSCEN
    MOVLW 0b01000000 ;internal clock @freq=OSCFRQ ativo
    MOVWF OSCEN,1
   
    
    
    ;===============
    ;CONFIGURE USART
    ;===============
    ;BR=9600 @ CLK=32 MHz    
    
    ;Q: WHAT VALUE SHOULD WE PUT IN SP1BRGL AND SP1BRG1H TO GET A BAUD RATE OF 9600 BPS FOR A CLOCK SPEED OF 32 MHZ? HINT: CHECK SECTION 28.2
    BANKSEL SP1BRGL
    movlw 0b00110011
    movwf SP1BRGL  
    movlw 0x00
    movwf SP1BRGH ,1 
    
    BANKSEL TX1STA
    movlw 0b10100000   ;8 data bits, TX enabled, ASYNC
    movwf TX1STA
    
    ;Q: HERE YOU MUST ENABLE THE USART AND THE RECEIVER WITH REGISTER RC1STA
    BANKSEL RC1STA
    movlw 0b10010000	; USART enabled, 8 data bits / enable receiver 
    movwf RC1STA  
    
    
    
    
    ;=============
    ;CONFIGURE ADC
    ;=============
    BANKSEL ADPCH
    MOVLW 0b00000001   ;set RA1 as ADC input (eixo x)
    MOVWF ADPCH,1
    
    BANKSEL ADREF
    MOVLW 0b00000000  ;Vref set to vdd = 5V and vss = GND 
    MOVWF ADREF,1
    
    BANKSEL ADCLK  
    MOVLW 0b00001111  ; Q: SET THE ADC CLOCK FREQUENCY TO 1 MHZ, KNOWING THAT FOSC = 32 MHZ
    MOVWF ADCLK,1
    
    BANKSEL ADCON0
    MOVLW 0b10000000  ;Q: SET THE ADC TO: results left-justified, clock=Fosc/div, non-continuous operation
    MOVWF ADCON0,1
    
    
    
    
    ;=================
    ;ENABLE INTERRUPTS
    ;=================
    BANKSEL PIR1
    BCF PIR1,0  ;clear ADC interrupt flag
    
    BANKSEL PIR3 
    BCF PIR3,5 ;clear RX1 interrupt flag
    
    BANKSEL PIE1
    BSF PIE1, 0 ; Q: enable adc int
    
    BANKSEL PIE3
    BSF PIE3, 5; Q: enable RX1 int
    
    BANKSEL ADCON0  
    BSF ADCON0,7   ;ENABLE ADC

    
    
    ; Q: HERE YOU MUST ENABLE PERIPHERAL INTERRUPTIONS AND GLOBAL INTERRUPTIONS
    BSF INTCON,7  ;enable peripheral interruptions
    BSF INTCON,6  ;enable global interruptions - do this after configurations are SET	  
    
    
    
    RETURN








