/*
 * File:   main.c
 * Author: Daniela Longras
 *
 * Created on 23 de Novembro de 2023, 10:10
 */


#include <xc.h>
#include <stdio.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include "TEDS_definition.h"

#define _XTAL_FREQ 32000000   //the clock frequency defined in config() must be provided here for the delay function

//declaration of global variables and functions
void config(void);
void __interrupt() int_handler(void); 
void define_METATEDS(void);
void define_TCTEDS(void);
void identify_NCAP_cmd(void);
void send_METATEDS(void);
void send_TCTEDS(uint8_t);
void send_VALUES_SENSOR(uint8_t);
void receive_VALUES(void);
void putch(char);
int getch(void);

char get_char;


uint8_t metateds[]={0,0,1,2,0,2,1,0};
uint8_t tcteds1[]= {0,1,1,2,0,2,3,0};
uint8_t tcteds2[]={0,2,1,2,0,2,3,0};
uint8_t tcteds3[]={0,3,1,2,0,2,3,0};
uint8_t tcteds4[]={0,4,1,2,0,2,3,0};
uint8_t sensor1[]={0,1,3,1,0,1,0};
uint8_t sensor2[]={0,2,3,1,0,1,0};
uint8_t sensor3[]={0,3,3,1,0,1,0};
uint8_t atuador[]={0,4,3,2,0,2,0,255};


//create the structs for the Meta TEDS and for the TransducerChannels TEDS for 2 channels
struct METATEDS_TEMPLATE METATED;
struct TRANSDUCERCHANNEL_TEDS_TEMPLATE TCTEDS1;
struct TRANSDUCERCHANNEL_TEDS_TEMPLATE TCTEDS2;
struct TRANSDUCERCHANNEL_TEDS_TEMPLATE TCTEDS3;
struct TRANSDUCERCHANNEL_TEDS_TEMPLATE TCTEDS4;

void main(void) {


    config();

    define_METATEDS();
    define_TCTEDS();
    
    //If the main ends, the microcontroller resets. So, a while(1) is desirable to keep it looping
    while(1){
        
        ;
        
        }
    
}

//definição das METATEDS
void define_METATEDS(void) {
    uint8_t array1[] = {3, 4, 0, 1, 0, 1};
    memcpy(METATED.TEDSID, array1, 6);
    uint8_t array2[] = {4, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    memcpy(METATED.UUID, array2, 12);
    uint8_t array3[] = {13, 2, 0, 4};
    memcpy(METATED.MAXCHAN, array3, 4);

    return;
}

//definição das TEDS
void define_TCTEDS(void) {
    //TCTEDS1 - TEDS DO TRANSDUCER CHANNEL 1 - SENSOR (eixo x)
    uint8_t array11[] = {3, 4, 0, 3, 0, 1};
    memcpy(TCTEDS1.TEDSID, array11, 6);
    uint8_t array12[] = {11, 1, 0};
    memcpy(TCTEDS1.CHANNEL_TYPE, array12, 3);
    uint8_t array13[] = {12, 10, 128, 128, 128, 130, 128, 124, 128, 128, 128, 128};
    memcpy(TCTEDS1.UNITS, array13, 12);
    uint8_t array14[] = {13, 1, 0};
    memcpy(TCTEDS1.LOW_RANGE_LIMIT, array14, 3);
    uint8_t array15[] = {14, 1, 255};
    memcpy(TCTEDS1.HIGH_RANGE_LIMIT, array15, 3);
    uint8_t array16[] = {40, 1, 0};
    memcpy(TCTEDS1.DATA_MODEL, array16, 3);
    uint8_t array17[] = {41, 1, 1};
    memcpy(TCTEDS1.DATA_MODEL_LENGTH, array17, 3);
    uint8_t array18[] = {42, 1, 8};
    memcpy(TCTEDS1.MODEL_SIG_BITS, array18, 3);

    //TCTEDS2 - TEDS DO TRANSDUCER CHANNEL 2 - SENSOR (eixo y)
    uint8_t array21[] = {3, 4, 0, 3, 0, 1};
    memcpy(TCTEDS2.TEDSID, array21, 6);
    uint8_t array22[] = {11, 1, 0};
    memcpy(TCTEDS2.CHANNEL_TYPE, array22, 3);
    uint8_t array23[] = {12, 10, 128, 128, 128, 130, 128, 124, 128, 128, 128, 128};
    memcpy(TCTEDS2.UNITS, array23, 12);
    uint8_t array24[] = {13, 1, 0};
    memcpy(TCTEDS2.LOW_RANGE_LIMIT, array24, 3);
    uint8_t array25[] = {14, 1, 255};
    memcpy(TCTEDS2.HIGH_RANGE_LIMIT, array25, 3);
    uint8_t array26[] = {40, 1, 0};
    memcpy(TCTEDS2.DATA_MODEL, array26, 3);
    uint8_t array27[] = {41, 1, 1};
    memcpy(TCTEDS2.DATA_MODEL_LENGTH, array27, 3);
    uint8_t array28[] = {42, 1, 8};
    memcpy(TCTEDS2.MODEL_SIG_BITS, array28, 3);
    
    //TCTEDS3 - TEDS DO TRANSDUCER CHANNEL 3 - SENSOR (eixo z)
    uint8_t array31[] = {3, 4, 0, 3, 0, 1};
    memcpy(TCTEDS3.TEDSID, array31, 6);
    uint8_t array32[] = {11, 1, 0};
    memcpy(TCTEDS3.CHANNEL_TYPE, array32, 3);
    uint8_t array33[] = {12, 10, 128, 128, 128, 130, 128, 124, 128, 128, 128, 128};
    memcpy(TCTEDS3.UNITS, array33, 12);
    uint8_t array34[] = {13, 1, 0};
    memcpy(TCTEDS3.LOW_RANGE_LIMIT, array34, 3);
    uint8_t array35[] = {14, 1, 255};
    memcpy(TCTEDS3.HIGH_RANGE_LIMIT, array35, 3);
    uint8_t array36[] = {40, 1, 0};
    memcpy(TCTEDS3.DATA_MODEL, array36, 3);
    uint8_t array37[] = {41, 1, 1};
    memcpy(TCTEDS3.DATA_MODEL_LENGTH, array37, 3);
    uint8_t array38[] = {42, 1, 8};
    memcpy(TCTEDS3.MODEL_SIG_BITS, array38, 3);
    
    //TCTEDS4 - TEDS DO TRANSDUCER CHANNEL 4 - TRANSDUTOR (LED)
    uint8_t array41[] = {3, 4, 0, 3, 0, 1};
    memcpy(TCTEDS4.TEDSID, array41, 6);
    uint8_t array42[] = {11, 1, 1};
    memcpy(TCTEDS4.CHANNEL_TYPE, array42, 3);
    uint8_t array43[] = {12, 10, 128, 128, 128, 132, 130, 122, 126, 128, 128, 128};
    memcpy(TCTEDS4.UNITS, array43, 12);
    uint8_t array44[] = {13, 1, 0};
    memcpy(TCTEDS4.LOW_RANGE_LIMIT, array44, 3);
    uint8_t array45[] = {14, 1, 255};
    memcpy(TCTEDS4.HIGH_RANGE_LIMIT, array45, 3);
    uint8_t array46[] = {40, 1, 0};
    memcpy(TCTEDS4.DATA_MODEL, array46, 3);
    uint8_t array47[] = {41, 1, 1};
    memcpy(TCTEDS4.DATA_MODEL_LENGTH, array47, 3);
    uint8_t array48[] = {42, 1, 8};
    memcpy(TCTEDS4.MODEL_SIG_BITS, array48, 3);

    return;
}


void identify_NCAP_cmd(void) {
    //verifica o comando enviado pelo NCAP e decide o que fazer
    
    int indice=0;
    uint8_t cmd1[]={0,0,0,0,0,0}; //array inicializado a 0 que irá armazenar os valores do comado do NCAP
    while (indice <6 )  {  
    //enquanto o indice do valor recebido do NCAP for menor do que 6 faz-se o que está a seguir (comandos do NCAP são arrays de 6 valores)
    if (PIR3bits.RC1IF==1){  
        //verifica se a flag de interrupção de receção (RC1IF) está ativa para o USART, ou seja, 
        //espera até que os dados válidos estejam prontos para serem processados antes de tentar lê-los da porta série
        getch(); 
        cmd1[indice] = get_char; //substituem-se os valores do array cmd1 com os valores recebidos do NCAP
        indice+=1;
        
    }
    }
    indice = 0; //reinicialização do indice antes de iniciar um novo loop
    
    int indice_d = 0; //contador para controlar a escrita dos dados recebidos do NCAP para o array dados[]
    uint8_t dados[256] = {0}; //array inicializado a 0 que pode ter até 255 valores
    while (indice_d < cmd1[5]){ 
        if (PIR3bits.RC1IF==1){
            
            getch();
            dados[indice_d] = get_char;
            indice_d+=1;
     
        }
    }
    indice_d = 0; //reinicialização do indice_d antes de iniciar um novo loop
    
    //compara os valores do cmd1 (array recebido do NCAP) com os valores do array que identifica as metateds ou teds (definidos no inicio) 
    //para fazer o reconhecimento do comando decidindo o que fazer dependendo da condição que se verificar
    if (cmd1[0]==metateds[0] && cmd1[1]==metateds[1] && cmd1[2]==metateds[2] && cmd1[3]==metateds[3] && cmd1[4]==metateds[4] && cmd1[5]==metateds[5] && dados[0]==metateds[6] && dados[1]==metateds[7])
    { send_METATEDS();
    
    }
    else if (cmd1[0]==tcteds1[0] && cmd1[1]==tcteds1[1] && cmd1[2]==tcteds1[2] && cmd1[3]==tcteds1[3] && cmd1[4]== tcteds1[4] && cmd1[5]==tcteds1[5] && dados[0]==tcteds1[6] && dados[1]==tcteds1[7])
    { send_TCTEDS(1);
    
    }
    else if (cmd1[0]==tcteds2[0] && cmd1[1]==tcteds2[1] && cmd1[2]==tcteds2[2] && cmd1[3]==tcteds2[3] && cmd1[4]==tcteds2[4] && cmd1[5]==tcteds2[5] && dados[0]==tcteds2[6] && dados[1]==tcteds2[7])
    { send_TCTEDS(2);
    
    }
    else if (cmd1[0]==tcteds3[0] && cmd1[1]==tcteds3[1] && cmd1[2]==tcteds3[2] && cmd1[3]==tcteds3[3] && cmd1[4]==tcteds3[4] && cmd1[5]==tcteds3[5] && dados[0]==tcteds3[6] && dados[1]==tcteds3[7])
    { send_TCTEDS(3);
    
    }
    else if (cmd1[0]==tcteds4[0] && cmd1[1]==tcteds4[1] && cmd1[2]==tcteds4[2] && cmd1[3]==tcteds4[3] && cmd1[4]==tcteds4[4] && cmd1[5]==tcteds4[5] && dados[0]==tcteds4[6] && dados[1]==tcteds4[7])
    { send_TCTEDS(4);
    
    }

    else if (cmd1[0]==sensor1[0] && cmd1[1]==sensor1[1] && cmd1[2]==sensor1[2] && cmd1[3]==sensor1[3] && cmd1[4]==sensor1[4] && cmd1[5]==sensor1[5] && dados[0]==sensor1[6])
    {
      send_VALUES_SENSOR(1);
    }
    
    else if (cmd1[0]==sensor2[0] && cmd1[1]==sensor2[1] && cmd1[2]==sensor2[2] && cmd1[3]==sensor2[3] && cmd1[4]==sensor2[4] && cmd1[5]==sensor2[5] && dados[0]==sensor2[6])
    {
      send_VALUES_SENSOR(2);
    }
    
    else if (cmd1[0]==sensor3[0] && cmd1[1]==sensor3[1] && cmd1[2]==sensor3[2] && cmd1[3]==sensor3[3] && cmd1[4]==sensor3[4] && cmd1[5]==sensor3[5] && dados[0]==sensor3[6])
    {
      send_VALUES_SENSOR(3);
    }
    
    else if (cmd1[0]==atuador[0] && cmd1[1]==atuador[1] && cmd1[2]==atuador[2] && cmd1[3]==atuador[3] && cmd1[4]==atuador[4] && cmd1[5]==atuador[5])
    {
        receive_VALUES();
   
    if (dados[1]==1){
        LATAbits.LATA6 = 1;}
    
    }
}


void send_METATEDS(void) {
    putch(1); 
    putch(0);
    putch(22);
    for (int i = 0; i < 6; i++) {
        putch(METATED.TEDSID[i]);
    }
    for (int j = 0; j < 12; j++) {
        putch(METATED.UUID[j]);
    }
    for (int k = 0; k < 4; k++) {
        putch(METATED.MAXCHAN[k]);
    }
    return;
}


void send_TCTEDS(uint8_t channel) {
    if (channel == 1) {
        putch(1);
        putch(0);
        putch(36);

        for (int i = 0; i < 6; i++) {
            putch(TCTEDS1.TEDSID[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.CHANNEL_TYPE[i]);
        }
        for (int i = 0; i < 12; i++) {
            putch(TCTEDS1.UNITS[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.LOW_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.HIGH_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.DATA_MODEL[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.DATA_MODEL_LENGTH[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS1.MODEL_SIG_BITS[i]);
        }
    } 
    
    if (channel == 2) {
        putch(1);
        putch(0);
        putch(36);

        for (int i = 0; i < 6; i++) {
            putch(TCTEDS2.TEDSID[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.CHANNEL_TYPE[i]);
        }
        for (int i = 0; i < 12; i++) {
            putch(TCTEDS2.UNITS[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.LOW_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.HIGH_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.DATA_MODEL[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.DATA_MODEL_LENGTH[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS2.MODEL_SIG_BITS[i]);
        }
    } 
    
    if (channel == 3) {
        putch(1);
        putch(0);
        putch(36);

        for (int i = 0; i < 6; i++) {
            putch(TCTEDS3.TEDSID[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.CHANNEL_TYPE[i]);
        }
        for (int i = 0; i < 12; i++) {
            putch(TCTEDS3.UNITS[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.LOW_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.HIGH_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.DATA_MODEL[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.DATA_MODEL_LENGTH[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS3.MODEL_SIG_BITS[i]);
        }
    } 
    
    if (channel == 4) {
        putch(1);
        putch(0);
        putch(36);

        for (int i = 0; i < 6; i++) {
            putch(TCTEDS4.TEDSID[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS4.CHANNEL_TYPE[i]);
        }
        for (int i = 0; i < 12; i++) {
            putch(TCTEDS4.UNITS[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS4.LOW_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS4.HIGH_RANGE_LIMIT[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS4.DATA_MODEL[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS4.DATA_MODEL_LENGTH[i]);
        }
        for (int i = 0; i < 3; i++) {
            putch(TCTEDS4.MODEL_SIG_BITS[i]);
        }
    } 
    
    return;
}

// Defina os canais ADC desejados
#define CHANNEL_X 0b00000001  // Canal X no pino RA1
#define CHANNEL_Y 0b00000010  // Canal Y no pino RA2
#define CHANNEL_Z 0b00000011  // Canal Z no pino RA3

void send_VALUES_SENSOR(uint8_t channel) {
    if (channel==1){
        putch(1);
        putch(0);
        putch(1);
        
        ADPCH = CHANNEL_X;
        
        ADCON0bits.ADGO=1; 
        
        while (PIR1bits.ADIF==0) {
            ; // Aguarda a conclusão da conversão
        }

        putch(ADRESH);
        ADRESH = 0; // Limpar o registrador ADRESH
        ADRESL = 0; // Limpar o registrador ADRESL

        
    }
       
    // Enviar valores do Canal Y
    if (channel==2){
        putch(1);
        putch(0);
        putch(1);

        ADPCH = CHANNEL_Y;
        
        ADCON0bits.ADGO=1; 
        
        while (PIR1bits.ADIF==0) {
            ; // Aguarda a conclusão da conversão
        }

        putch(ADRESH);
        ADRESH = 0; // Limpar o registrador ADRESH
        ADRESL = 0; // Limpar o registrador ADRESL

        
    }
    
    // Enviar valores do Canal Z
    if (channel==3){
        putch(1);
        putch(0);
        putch(1);

        ADPCH = CHANNEL_Z;
        
        ADCON0bits.ADGO=1; 
        
        while (PIR1bits.ADIF==0) {
            ; // Aguarda a conclusão da conversão
        }

        putch(ADRESH);
        ADRESH = 0; // Limpar o registrador ADRESH
        ADRESL = 0; // Limpar o registrador ADRESL
        
    }
    return;
    // Agora você tem os valores convertidos de todos os três canais em adc_values[1], adc_values[2], adc_values[3]
}


void receive_VALUES(void){
    putch(1);
    putch(0);
    putch(0);
}

void putch(char byte) //função que envia um byte pela porta série
{
    //verifica se a flag de interrupção TX1IF está definido como 0, ou seja, se não foi ativada
    while (PIR3bits.TX1IF == 0) {
        ;
   }
    TX1REG = byte; //transmite o byte para o TX1REG (porta série)

    //espera que o valor seja enviado, ou seja, que a flag de interrupção TX1IF esteja desativada
    while (PIR3bits.TX1IF == 0) {
        ;
    }
}  

    
int getch(void)   //this function gets the received char from XXXXXX
{   
    get_char = RC1REG ;  //quando a UART recebe um byte ele vai para o RC1REG
    
    return 0;
}


