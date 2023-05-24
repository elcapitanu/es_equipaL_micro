#include "main.h"
#include <RP2040_PWM.h>

// Instância das classes de controle PWM dos motores
RP2040_PWM* PWM_motorL;
RP2040_PWM* PWM_motorR;

// Variáveis para controle da transição progressiva
unsigned long startTime = 0;
unsigned long t = 0;
float valorDesejadoL = 0;
float valorDesejadoR = 0;

boolean auxL = false;
boolean auxR = false;

float timeL = 0;
float timeR = 0;
 
void setup() {
  Serial.begin(115200);
  pinMode(TX_LED, OUTPUT);
  PWM_motorL = new RP2040_PWM(PIN_motorL, 50, 0);
  PWM_motorR = new RP2040_PWM(PIN_motorR, 50, 0);
  PWM_motorL->setPWM(PIN_motorL, 50, 7.5);
  PWM_motorR->setPWM(PIN_motorR, 50, 7.5);
  ASVmotors.pwmL = 0;
  ASVmotors.pwmR = 0;
  t = millis();
  delay(5000);
}

void loop() {
  
  parser(Serial.read());

  /*if(auxL = false) {
    timeL = abs(ASVmotors.pwmL * 500 / 100);
    auxL = true;
  }
  if(auxR = false) {
    timeR = abs(ASVmotors.pwmR * 500 / 100);
    auxR = true;
  }*/

  static unsigned long startTimeL = 0;
  static unsigned long startTimeR = 0;
  unsigned long currentTime = millis();
  
  // Verificar se os valores dos motores precisam ser ajustados
  if (ASVmotors.pwmL != valorDesejadoL) {
    if (startTimeL == 0) {
      startTimeL = currentTime;
    }

    unsigned long elapsedTime = currentTime - startTimeL;

    if (elapsedTime <= 500) {
      float percentComplete = static_cast<float>(elapsedTime) / 500.0;
      float incrementoL = percentComplete * percentComplete * (ASVmotors.pwmL - valorDesejadoL);
      valorDesejadoL += incrementoL;
    } else {
      valorDesejadoL = ASVmotors.pwmL;
      startTimeL = 0;
    }

    // Mapear o valor para o intervalo desejado
    float mappedValueL = map(valorDesejadoL, -100.0, 100.0, 5.5, 9.5);
    // Ativar o motor L com o valor mapeado
    PWM_motorL->setPWM(PIN_motorL, 50, mappedValueL);
    Serial.print("Motor Esquerdo \n");
    Serial.print(startTimeL, 3);
    Serial.print(", ");
    Serial.print(valorDesejadoL, 3);
    Serial.print("\n");
  }

  if (ASVmotors.pwmR != valorDesejadoR) {
    if (startTimeR == 0) {
      startTimeR = currentTime;
    }

    unsigned long elapsedTime = currentTime - startTimeR;

    if (elapsedTime <= 500) {
      float percentComplete = static_cast<float>(elapsedTime) / 500.0;
      float incrementoR = percentComplete * percentComplete * (ASVmotors.pwmR - valorDesejadoR);
      valorDesejadoR += incrementoR;
    } else {
      valorDesejadoR = ASVmotors.pwmR;
      startTimeR = 0;
    }

    // Mapear o valor para o intervalo desejado
    float mappedValueR = map(valorDesejadoR, -100.0, 100.0, 5.5, 9.5);
    // Ativar o motor R com o valor mapeado
    PWM_motorR->setPWM(PIN_motorR, 50, mappedValueR);    
    Serial.print("Motor Direito \n");
    Serial.print(startTimeR, 3);
    Serial.print(", ");
    Serial.print(valorDesejadoR, 3);
    Serial.print("\n");
  }

  // Outro código de processamento aqui
}
