#include <stdint.h>     /* Para las definiciones de uint8_t por ej.*/
#include <stdio.h>      /* Archivo de Encabezados StdIO */
typedef enum{Inicializacion, FusibleCheck, ReguladorCheck, IntegradoCheck, TrafoCheck, Normal, EGeneral, EFusible, ETrafo, EIntegrado, EAlimGen, EAlimReg} estadoMEF_t;
uint8_t ALIM_REG, ALIM_GEN, BUZZER, TRAFO, PRE_TRAFO1, PRE_TRAFO2, FUS, CI = 0;
uint8_t estadoActual, R1, R2, G1, G2, B1, B2 = 0;


void main(void) {
    appInit();
    InicializarMEF();
    while (1) {
        ActualizarMEF();
    }
}

void colorLED(numero, color){
    switch(numero) {
        case 1:
            if (color == "apagado"){
                R1 = 0;
                G1 = 0;
                B1 = 0;
            }
            if (color == "rojo"){
                R1 = 1;
                G1 = 0;
                B1 = 0;
            }
            if (color == "verde"){
                R1 = 0;
                G1 = 1;
                B1 = 0;
            }
            if (color == "azul"){
                R1 = 0;
                G1 = 0;
                B1 = 1;
            }
            if (color == "amarillo"){
                R1 = 1;
                G1 = 1;
                B1 = 0;
            }
        
        case 2:
            if (color == "apagado"){
                R1 = 0;
                G1 = 0;
                B1 = 0;
            }
            if (color == "rojo"){
                R2 = 1;
                G2 = 0;
                B2 = 0;
            }
            if (color == "verde"){
                R2 = 0;
                G2 = 1;
                B2 = 0;
            }
            if (color == "azul"){
                R2 = 0;
                G2 = 0;
                B2 = 1;
            }
            if (color == "amarillo"){
                R2 = 1;
                G2 = 1;
                B2 = 0;
            }
    }
}

void InicializarMEF(void) {
    estadoActual = Inicializacion;
    colorLED(1, "apagado");
    colorLED(2, "apagado");
}

void ActualizarMEF(void) {
    switch (estadoActual) {
        case Inicializacion:
            colorLED(1, "amarillo");
            colorLED(2, "apagado");

            estadoActual = FusibleCheck;
            break;

        case FusibleCheck:
            if (ALIM_GEN == 0 && FUS == 0){
                estadoActual = EAlimGen;
            }
            if (ALIM_GEN == 1 && FUS == 0){
                estadoActual = EFusible;
            }
            if (ALIM_GEN == 1 && FUS == 1){
                estadoActual = ReguladorCheck;
            }

        case ReguladorCheck:
            if (ALIM_REG == 0){
                estadoActual = EAlimReg;
            }
            if (ALIM_REG == 1){
                estadoActual = IntegradoCheck;
            }

        case IntegradoCheck:
            if (CI == 0){
                estadoActual = EIntegrado;
            }
            else{
                estadoActual = TrafoCheck;
            }

        case TrafoCheck:

            if (PRE_TRAFO1 == 0 && PRE_TRAFO2 == 0 ){
                estadoActual = EGeneral;
            }
            else
                if( (PRE_TRAFO1 == 1 && PRE_TRAFO2 == 0)||(PRE_TRAFO1 == 0 && PRE_TRAFO2 == 1) )
                    if (TRAFO == 0) estadoActual = ETrafo;
                    else estadoActual = Normal;       

        case Normal:
            colorLED(1, "verde");
            colorLED(2, "apagado");
            estadoActual = FusibleCheck;

        case EFusible:
            colorLED(1, "rojo");
            colorLED(2, "rojo");

        case EGeneral:
            colorLED(1, "rojo");
            colorLED(2, "apagado");

        case ETrafo:
            colorLED(1, "rojo");
            colorLED(2, "amarillo");

        case EIntegrado:
            colorLED(1, "rojo");
            colorLED(2, "azul");

        case EAlimGen:
            colorLED(1, "azul");
            colorLED(2, "rojo");

        case EAlimReg:
            colorLED(1, "azul");
            colorLED(2, "amarillo");

        default:
            InicializarMEF();
    }
}