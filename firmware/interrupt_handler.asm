#include <xc.inc>

    
GLOBAL _int_handler, _getch, _identify_NCAP_cmd, _adc_int_handler   ;declare global functions
    
PSECT intcode

    
_int_handler:    ;é chamada quando ocorre uma interrupção
    BANKSEL PIR1
    BTFSC PIR1,0   ;verifica se a flag de interrupção do ADC está ativa. Se estiver ativa vai para adc_int_handler, se não estiver dá skip
    goto _adc_int_handler
    
    BANKSEL PIR3
    BTFSC PIR3,5   ;verifica se a flag do EUSART1 RX está ativa. Se estiver vai para a função _identify_NCAP_cmd que está no main C e se não estiver dá skip
    call _identify_NCAP_cmd
    
    RETFIE ;retorna da interrupção
    

    

_adc_int_handler:
    BANKSEL ADRESH ;ADRESH guarda os 8 bits mais significativos do resultado da conversão
    BANKSEL PIR1
    BCF PIR1,0   ;clear the ADC interrupt flag
    RETFIE  ;retorna da interrupção
