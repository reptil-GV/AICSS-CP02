# NetGuard – Verificação de Domínio e IP

Projeto do **CP2** das disciplinas **AI Computer Systems and Sensors (AICSS)** e **Cognitive CyberSecurity**, do curso Tecnólogo em IA (FIAP).

## Sobre o projeto

A empresa fictícia **NetGuard** precisa validar se o acesso a serviços na Internet está sendo direcionado aos endereços IP esperados, identificando possíveis desvios na resolução DNS.

O projeto tem duas partes:

- **Cognitive CyberSecurity:** escolha de um domínio real, identificação de um IP de referência por consulta DNS/whois, mini-mapa da comunicação e análise de cenários em que o IP retornado seja diferente do esperado.
- **AICSS:** um dispositivo com **ESP32** que recebe um IP pelo Serial Monitor e o compara com o IP de referência, sinalizando o resultado com LEDs.

## Integrantes

- Rafael Medici – RM 576249
- Renata Machado – RM 575149
- Matheo Gritti – RM 575773
- Murilo Wengrzynek – RM 575401

## Domínio e IP de referência

| Item | Valor |
|---|---|
| Domínio monitorado | harvard.edu |
| IP de referência (IPv4) | 192.0.66.20 |
| Método de consulta | nslookup (DNS local e 8.8.8.8) e whois |

## Componentes

- 1x ESP32
- 1x botão (push button)
- 1x LED azul
- 1x LED vermelho
- 2x resistores de 1 kΩ

## Ligações do circuito

| Componente | Pino do ESP32 |
|---|---|
| Botão | GPIO 13 (INPUT_PULLUP, outro lado no GND) |
| LED azul | GPIO 23 (via resistor de 1 kΩ) |
| LED vermelho | GPIO 19 (via resistor de 1 kΩ) |

## Como funciona

1. Ao ligar, os dois LEDs ficam **apagados**.
2. Ao pressionar o botão, o Serial Monitor solicita um endereço IP.
3. O IP digitado é comparado com o IP de referência.
4. **IP igual ao esperado:** o **LED azul** acende (validação com sucesso).
5. **IP diferente:** o **LED vermelho** acende (alerta).
6. A cada novo pressionamento do botão, uma nova verificação é iniciada.

O Serial Monitor exibe o domínio monitorado, o IP informado e o resultado de cada verificação.

## Experimentos realizados

| # | IP informado | Tipo | Resultado |
|---|---|---|---|
| 1 | 192.0.66.20 | IP de referência do checkpoint de Cyber | LED azul |
| 2 | 8.8.8.8 (exemplo) | IPv4 público diferente | LED vermelho (esperado) |
| 3 | 192.168.1.0 | IPv4 privado | LED vermelho |

> *Nota:* o teste 2 é um exemplo de IPv4 público diferente do IP de referência e não tem print registrado. Pela lógica do código, qualquer IP diferente de 192.0.66.20 acende o LED vermelho, como mostra o teste 3.

Os prints dos experimentos e a apresentação estão na pasta `docs/`.

## Estrutura do repositório

```
├── src/            → código do ESP32
├── docs/           → apresentação e prints dos experimentos
├── diagram.json    → circuito da simulação no Wokwi
├── wokwi.toml      → configuração do Wokwi
├── platformio.ini  → configuração do PlatformIO
└── README.md
```

## Tecnologias

- ESP32 programado com PlatformIO (framework Arduino)
- Simulação no Wokwi
- Consultas DNS/whois: nslookup, whois

## Como executar

1. Abra a pasta do projeto no VS Code com as extensões **PlatformIO** e **Wokwi**.
2. Compile o projeto com o PlatformIO.
3. Inicie a simulação pela extensão Wokwi (usa o `diagram.json`).
4. Abra o Serial Monitor, pressione o botão e digite o IP a ser verificado.