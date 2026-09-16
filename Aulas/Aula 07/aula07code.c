#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Diretivas de Pre-processador para economia de SRAM 
#define TENSAO_FONTE 5.0f
#define TENSAO_LED   2.0f

// Definicao dos estados logicos do sistema 
typedef enum {
    NIVEL_LOW = 0,
    ZONA_INCERTEZA,
    NIVEL_HIGH
} EstadoLogico;

int main() {
    // ---------------------------------------------------------------
    // IDENTIFICACAO DO ALUNO (Parametro Individual)
    // ---------------------------------------------------------------
    // TODO: Substitua o numero 0 abaixo pelo ultimo digito da sua matricula
    int ultimoDigito = 0; 
    
    // Regra de contingencia: se a matricula terminar em 0, adota-se D = 5
    if (ultimoDigito == 0) {
        ultimoDigito = 5; 
    }

    // ---------------------------------------------------------------
    // ETAPA 1: Calculos Eletricos - Lei de Ohm 
    // ---------------------------------------------------------------
    float correnteLED_mA = 10.0f + (float)ultimoDigito; //
    float correnteLED_A  = correnteLED_mA / 1000.0f;     // Conversao para Ampères
    
    // TODO: Declare a variavel 'rLED' e complete o calculo da Lei de Ohm: (Vcc - Vl) / I
    // float rLED = ... ;
    
    printf("========================================\n");
    printf("SENAI - Pratica de Embarcados e Eletronica\n");
    printf("Digito Matricula: %d\n", ultimoDigito);
    printf("Corrente LED: %.1f mA | R_LED Calculado: %.1f Ohms\n", correnteLED_mA, rLED);
    printf("========================================\n\n");

    // Vetor com as 4 tensoes de teste de bancada 
    float tensoesTeste[4] = {0.4f, 1.4f, 2.8f, 4.9f}; //

    // ---------------------------------------------------------------
    // ETAPA 2: Processamento e Classificacao 
    // ---------------------------------------------------------------
    for (int i = 0; i < 4; i++) {
        float vin = tensoesTeste[i];
        
        // TODO: Declare a variavel 'valorADC' e faca a conversao para 10 bits (0 a 1023 LSB)
        // uint16_t valorADC = ... ;

        // Classificacao por limites fisicos de tensao 
        EstadoLogico estado;
        if (vin <= 0.8f) {
            estado = NIVEL_LOW;       // 0,0V a 0,8V: Nivel Logico Baixo
        } else if (vin >= 2.0f) {
            estado = NIVEL_HIGH;      // 2,0V a 5,0V: Nivel Logico Alto
        } else {
            estado = ZONA_INCERTEZA;  // 0,8V a 2,0V: Estado Proibido / Ruido
        }

        printf("Amostra %d: Vin = %.2f V | ADC = %u LSB\n", i + 1, vin, valorADC);

        // Maquina de decisao via switch...case
        switch (estado) {
            case NIVEL_LOW:
                printf(" -> Estado: LOW  | Carga: DESLIGADA\n\n");
                break;

            case NIVEL_HIGH:
                printf(" -> Estado: HIGH | Carga: LIGADA (LED Ativado)\n\n");
                break;

            case ZONA_INCERTEZA:
                printf(" -> ALERTA: Zona de Incerteza (0.8V a 2.0V)! Carga BLOQUEADA por seguranca.\n\n"); //
                break;
        }
    }

    return 0;
}
