// ============================================================
// NetGuard - CP2 AICSS
// Verificação do IP de um domínio com ESP32
// Domínio monitorado: harvard.edu  |  IP de referência: 192.0.66.20
// ============================================================
#include <Arduino.h>
// ---------- Pinos ----------
#define BOTAO 12     // botão ligado entre o pino 4 e o GND
#define AZUL 23     // LED azul (sucesso)
#define VERMELHO 19 // LED vermelho (alerta)

// ---------- Dados da verificação ----------
const String DOMINIO = "harvard.edu";
const String REFERENCIA = "192.0.66.20"; // IP obtido no checkpoint de Cyber

// ------------------------------------------------------------
// Apaga os dois LEDs (estado inicial e início de cada verificação)
// ------------------------------------------------------------
void apagarLeds()
{

    digitalWrite(AZUL, LOW);
    digitalWrite(VERMELHO, LOW);
}

// ------------------------------------------------------------
// Retorna true se o botão foi realmente pressionado.
// O delay de 50 ms ignora a "trepidação" (bounce) do botão.
// Com INPUT_PULLUP, o botão pressionado lê LOW.
// ------------------------------------------------------------
bool botaoPressionado()
{

    if (digitalRead(BOTAO) == LOW)
    {
        delay(50);
        return digitalRead(BOTAO) == LOW; // confirma que continua pressionado
    }
    return false;
}

// ------------------------------------------------------------
// Espera o botão ser solto, para que um único clique
// não gere duas verificações seguidas.
// ------------------------------------------------------------
void esperarSoltarBotao()
{

    while (digitalRead(BOTAO) == LOW)
        ;
    {
        // aguarda soltar
    }
    delay(50); // ignora a trepidação ao soltar
}

// ------------------------------------------------------------
// Pede o IP no Serial Monitor e devolve o texto digitado.
// ------------------------------------------------------------
String lerIP()
{

    // Descarta qualquer texto digitado antes do botão ser pressionado
    while (Serial.available())
    {

        Serial.read();
    }

    Serial.println("\nDigite o IP e pressione Enter:");

    while (!Serial.available())
    {

        // aguarda o usuário digitar
    }

    String ip = Serial.readStringUntil('\n');
    ip.trim(); // remove espaços e o '\r' que alguns terminais enviam
    return ip;
}

// ------------------------------------------------------------
// Compara o IP informado com a referência, acende o LED
// correspondente e mostra o resultado no Serial Monitor.
// ------------------------------------------------------------
void verificarIP(String ip)
{

    Serial.println("----------------------------------");
    Serial.print("Dominio monitorado: ");
    Serial.println(DOMINIO);
    Serial.print("IP informado:       ");
    Serial.println(ip);

    if (ip == REFERENCIA)
    {

        digitalWrite(AZUL, HIGH); // sucesso
        digitalWrite(VERMELHO, LOW);
        Serial.println("Resultado:          IP CORRESPONDENTE (LED azul)");
    }
    else
    {

        digitalWrite(AZUL, LOW);
        digitalWrite(VERMELHO, HIGH); // alerta
        Serial.println("Resultado:          ALERTA - IP DIFERENTE (LED vermelho)");
    }

    Serial.println("----------------------------------");
    Serial.println("Pressione o botao para nova verificacao.");
}

// ============================================================
void setup()
{

    Serial.begin(115200);

    pinMode(BOTAO, INPUT_PULLUP); // entrada com resistor interno
    pinMode(AZUL, OUTPUT);
    pinMode(VERMELHO, OUTPUT);

    apagarLeds(); // os dois LEDs começam apagados

    Serial.println("=== NetGuard - Verificacao de IP ===");
    Serial.print("Dominio monitorado: ");
    Serial.println(DOMINIO);
    Serial.print("IP de referencia:   ");
    Serial.println(REFERENCIA);
    Serial.println("Pressione o botao para iniciar.");
}

// ============================================================
void loop()
{

    if (botaoPressionado())
    {
        apagarLeds(); // nova verificação começa com os LEDs apagados
        esperarSoltarBotao();

        String ip = lerIP();
        verificarIP(ip);
    }
}
