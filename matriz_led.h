#ifndef matriz_led_h
#define matriz_led_h

#include<stdio.h>
#include"pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "matriz_led.pio.h"


//número de LEDs
#define NUM_PIXELS 25

//pino de saída
static int GPIO_MATRIZ_LED;

static PIO pio;
static uint sm;


static const int mapeamento[25] = {24,23,22,21,20,
                      15,16,17,18,19,
                      14,13,12,11,10,
                       5,6,7,8,9,
                       4,3,2,1,0};

static uint32_t cores[25];


uint32_t getCorRGB(double r, double g, double b);

void pintaFrameCompletoComIntervalo(uint32_t intervalo);
void pintaFrameCompleto();

void ligaLEDsNaCor(int *leds, int quant, uint32_t cor);


void ligaLEDsNaCorComIntervalo(int *leds, int quant, uint32_t cor,uint32_t intervalo);

void ligaLEDsNasCores(int *leds, int quant, uint32_t *cores_esc);

void ligaLEDsNasCoresComIntervalo(int *leds, int quant, uint32_t *cores_esc,uint32_t intervalo);

void ligaTodosLEDsNaCor(uint32_t cor);

void ligaTodosLEDsNasCores(uint32_t *cores_esc);

void desligaTodosLEDs();

void resetLeds();

void inicializacaoMatrizLed(int gpio_matriz);


#endif