#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"

#include"matriz_led.h"



#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define BUTTON_1 6
#define BUTTON_2 5
#define MATRIZ_LED 7

#define INTENSIDADE_LUZ 0.05

static volatile uint32_t last_time = 0;
static volatile uint32_t debounce_time = 200000;

int numero_matriz = 0;

    int numero0[13] = {1,2,3,8,13,18,23,22,21,16,11,6,1};
    int numero1[5] = {3,8,13,18,23};
    int numero2[11] = {1,2,3,8,13,12,11,16,21,22,23};
    int numero3[11] = {1,2,3,8,13,12,11,18,23,22,21};
    int numero4[9] = {1,6,11,12,13,8,3,18,23};
    int numero5[11] = {3,2,1,6,11,12,13,18,23,22,21};
    int numero6[12] = {3,2,1,6,11,16,21,22,23,18,13,12};
    int numero7[7] = {1,2,3,8,13,18,23};
    int numero8[13] = {1,2,3,8,13,18,23,22,21,16,11,6,12};
    int numero9[12] = {12,11,6,1,2,3,8,13,18,23,22,21};


void configuracao(){
  gpio_init(LED_RED);
  gpio_set_dir(LED_RED,GPIO_OUT);
  gpio_init(LED_GREEN);
  gpio_set_dir(LED_GREEN,GPIO_OUT);
  gpio_init(LED_BLUE);
  gpio_set_dir(LED_BLUE,GPIO_OUT);

  gpio_init(BUTTON_1);
  gpio_set_dir(BUTTON_1,GPIO_IN);
  gpio_pull_up(BUTTON_1);

  gpio_init(BUTTON_2);
  gpio_set_dir(BUTTON_2,GPIO_IN);
  gpio_pull_up(BUTTON_2);

  inicializacaoMatrizLed(MATRIZ_LED);

  
}


void exibiNumero(){
    resetLeds();
    switch (numero_matriz){
        case 0:
            ligaLEDsNaCor(numero0,13,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 1:
            ligaLEDsNaCor(numero1,5,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 2:
            ligaLEDsNaCor(numero2,11,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 3:
            ligaLEDsNaCor(numero3,11,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 4:
            ligaLEDsNaCor(numero4,9,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 5:
            ligaLEDsNaCor(numero5,11,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 6:
            ligaLEDsNaCor(numero6,12,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 7:
            ligaLEDsNaCor(numero7,7,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 8:
            ligaLEDsNaCor(numero8,13,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
        case 9:
            ligaLEDsNaCor(numero9,12,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));
            break;
    }
}

void gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if ((current_time - last_time) > debounce_time) {
        last_time = current_time; 
        if (gpio==BUTTON_1){
            numero_matriz++;
            if(numero_matriz>9){
                numero_matriz=9;
            }
            exibiNumero();
        }else if(gpio==BUTTON_2){
            numero_matriz--;
            if(numero_matriz<0){
                numero_matriz=0;
            }
            exibiNumero();
        }
    }
    
}

int main() {
  stdio_init_all();
  configuracao();

  gpio_set_irq_enabled_with_callback(BUTTON_1, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
  gpio_set_irq_enabled_with_callback(BUTTON_2, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

  resetLeds();
  ligaLEDsNaCor(numero0,13,getCorRGB(INTENSIDADE_LUZ,0.0,0.0));

  while (true) {

    for(int i=0;i<5;i++){
        gpio_put(LED_RED,1);
        sleep_ms(100);
        gpio_put(LED_RED,0);
        sleep_ms(100);
    }
  }
}
