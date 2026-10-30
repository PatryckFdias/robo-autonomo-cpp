# 🤖 Robô Autônomo com Evasão de Obstáculos (C++)

Arquitetura e desenvolvimento de um sistema embarcado para navegação autônoma. O projeto utiliza lógica de controle diferencial e processamento de sinais ultrassônicos para evasão de obstáculos em tempo real, desenvolvido em C++ sob a plataforma Arduino.

## ⚙️ Topologia de Hardware e Esquemático

<img width="424" height="227" alt="image" src="https://github.com/user-attachments/assets/945668ea-fe9f-4893-b7af-0220ccb6c10c" />

**Stack de Hardware:**
* Microcontrolador: Arduino Uno
* Controle de Tração: Driver Motor Ponte H (L298N)
* Sensoriamento: Sensor Ultrassônico HC-SR04 e Sensores Infravermelhos (TCRT5000)

## 📐 Projeto Mecânico

<img width="242" height="214" alt="image" src="https://github.com/user-attachments/assets/9d387bed-17cd-4865-a6ea-6e7182fa4933" />
<img width="244" height="216" alt="image" src="https://github.com/user-attachments/assets/b1a375fd-9652-433b-b1bf-f8ae0c784ba4" />
<img width="244" height="216" alt="image" src="https://github.com/user-attachments/assets/00d82f19-585c-45c6-851e-9615733e318e" />

## 🧠 Lógica de Decisão e Dívida Técnica

O algoritmo atual processa os dados dos sensores infravermelhos para a rotina de `Line Following`. Caso o sensor ultrassônico identifique uma barreira a menos de 15cm, o fluxo é desviado para a função `desviar_obstaculo()`, que inverte os vetores de tração da ponte H.

**Roadmap de Refatoração (Next Steps):**
A arquitetura atual utiliza funções bloqueantes (`delay()`) para as manobras de evasão. A próxima iteração do firmware substituirá essas chamadas por controle de tempo assíncrono via `millis()`, garantindo que o microcontrolador não perca ciclos de leitura dos sensores durante as curvas.

## Como abrir e carregar o firmware

1. Instale a Arduino IDE e abra [`main.ino`](main.ino).
2. Selecione a placa Arduino Uno e a porta correspondente.
3. Confira a alimentação, a ligação dos motores no L298N e o mapeamento de pinos definido no código antes de carregar.
4. Grave o firmware e verifique o comportamento na pista e diante de obstáculos.

## Pinagem definida no código

| Função | Pino Arduino |
| --- | --- |
| Enable A / Enable B | 5 / 6 |
| Motor esquerdo (frente / ré) | 9 / 8 |
| Motor direito (frente / ré) | 7 / 4 |
| Sensores de linha (esq. / dir.) | 2 / 3 |
| Ultrassônico (TRIG / ECHO) | 13 / 12 |

As velocidades e o estado lógico dos sensores estão definidos como constantes no início do arquivo. Confira se correspondem ao seu circuito antes de utilizar.

**Limitação conhecida:** as manobras usam `delay()`, que bloqueia temporariamente novas leituras. A migração para `millis()` permanece como melhoria futura, não implementada nesta revisão.
