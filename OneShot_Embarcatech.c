#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos
#define LED_VERDE 12 
#define LED_VERMELHO 11
#define LED_AZUL 10
#define BOTAO 5

// Variável para que evita múltiplas execuções enquanto o temporizador está ativo
volatile bool temporizador_ativo = false;

// Callback para desligar o último LED (verde)
int64_t turn_off_last_led(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, 0); // Desliga LED verde
    temporizador_ativo = false; // Permite que o botão seja pressionado novamente
    return 0;
}

// Callback para desligar o segundo LED (vermelho)
int64_t turn_off_second_led(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, 0); // Desliga LED vermelho
    add_alarm_in_ms(3000, turn_off_last_led, NULL, false);
    return 0;
}

// Callback para desligar o primeiro LED (azul)
int64_t turn_off_first_led(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, 0); // Desliga LED azul
    add_alarm_in_ms(3000, turn_off_second_led, NULL, false);
    return 0;
}

// Callback para tratar o pressionamento do botão
void botao_callback(uint gpio, uint32_t eventos) {
    if (!temporizador_ativo) { // Verifica se o temporizador já está rodando
        temporizador_ativo = true; // Bloqueia novas chamadas até o ciclo terminar
        //Liga todos os LEDs
        gpio_put(LED_VERDE, 1);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AZUL, 1);
        // Inicia o temporizador para desligar o primeiro LED (azul) após 3s
        add_alarm_in_ms(3000, turn_off_first_led, NULL, false);
    }
}

int main() {
    stdio_init_all();
    
    // Configuração dos LEDs como saída
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    
    // Configuração do botão como entrada com pull-up interno
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);
    
    /* Interrupção para detectar pressionamento do botão
    configura o botão para chamar botao_callback() automaticamente quando for pressionado */
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &botao_callback);
    
    while (1) {
        tight_loop_contents(); // Função para otimizar loops infinitos
    }
}
