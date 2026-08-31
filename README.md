# 🤖 Robô Autônomo com Evasão de Obstáculos (C++)

Arquitetura e desenvolvimento de um sistema embarcado para navegação autônoma. O projeto utiliza lógica de controle diferencial e processamento de sinais ultrassônicos para evasão de obstáculos em tempo real, desenvolvido em C++ sob a plataforma Arduino.

## ⚙️ Topologia de Hardware e Esquemático

(<img width="424" height="227" alt="image" src="https://github.com/user-attachments/assets/945668ea-fe9f-4893-b7af-0220ccb6c10c" />
]()
magem_diagrama.png)

**Stack de Hardware:**
* Microcontrolador: Arduino Uno
* Controle de Tração: Driver Motor Ponte H (L298N)
* Sensoriamento: Sensor Ultrassônico HC-SR04 e Sensores Infravermelhos (TCRT5000)

## 📐 Projeto Mecânico

*(Suba a image_f28809.png aqui)*
![Dimensões CAD](./assets/nome_da_imagem_dimensoes.png)

## 🧠 Lógica de Decisão e Dívida Técnica

O algoritmo atual processa os dados dos sensores infravermelhos para a rotina de `Line Following`. Caso o sensor ultrassônico identifique uma barreira a menos de 15cm, o fluxo é desviado para a função `desviar_obstaculo()`, que inverte os vetores de tração da ponte H.

**Roadmap de Refatoração (Next Steps):**
A arquitetura atual utiliza funções bloqueantes (`delay()`) para as manobras de evasão. A próxima iteração do firmware substituirá essas chamadas por controle de tempo assíncrono via `millis()`, garantindo que o microcontrolador não perca ciclos de leitura dos sensores durante as curvas.
