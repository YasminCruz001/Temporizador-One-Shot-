# Simulação de Semáforo com Temporizador Periódico
Yasmin Damasceno Cruz - TIC370101610
Unidade 4 - Capítulo 5

Este projeto implementa a simulação de LEDs utilizando um temporizador de 3 segundos e a interação com um botão (pushbutton). Quando o botão é pressionado, os LEDs são acesos, e a cada 3 segundos, um LED é desligado, até que apenas um LED permaneça aceso. O temporizador é gerenciado por funções de callback e utiliza a função `add_alarm_in_ms()` do Pico SDK.

O código é desenvolvido em C e executado no microcontrolador Raspberry Pi Pico W. A simulação pode ser realizada utilizando a ferramenta educacional Wokwi integrada ao VS Code.


## Componentes Utilizados

- 1x Microcontrolador Raspberry Pi Pico W
- 3x LEDs (azul, vermelho e verde)
- 3x Resistores de 330 Ω
- 1x Botão (Pushbutton)

## Configuração Inicial

1. Clone o repositório para sua máquina local:
   ```bash
   git clone <https://github.com/YasminCruz001/Temporizador-One-Shot-.git>
   ```
2. Abra o projeto no VS Code.
3. Abra o arquivo `diagram.json` no Wokwi para visualizar a simulação dos componentes.

## Execução

- Ao pressionar o botão, todos os LEDs são acesos.
- A cada 3 segundos, um LED é desligado: primeiro o azul, depois o vermelho e, por último, o verde
- O processo é controlado por temporizadores, onde cada estado de LED é gerenciado por funções callback.
- O botão só pode ser pressionado novamente quando todos os LEDs estiverem desligados.