#include "main.h"

unsigned long int t, n;
RP2040_PWM *PWM_motorL;
RP2040_PWM *PWM_motorR;

float a = 7.5;
float oldPWM_L = 7.5; // valor anterior do duty cycle do motor L
float oldPWM_R = 7.5; // valor anterior do duty cycle do motor R
float lastEnterL = 0;
float lastEnterR = 0;
float auxL = 0;
float auxR = 0;

void setup() {
  Serial.begin(115200);
  pinMode(TX_LED, OUTPUT);
  PWM_motorL = new RP2040_PWM(PIN_motorL, 50, 0);
  PWM_motorR = new RP2040_PWM(PIN_motorR, 50, 0);
  PWM_motorL->setPWM(PIN_motorL, 50, oldPWM_L);
  PWM_motorL->setPWM(PIN_motorR, 50, oldPWM_R);
  ASVmotors.pwmL = 9.5;
  ASVmotors.pwmR = 8.5;
  t = millis();
  delay(5000);
}

void loop() {
  n = millis();
  /*parser(Serial.read());
  if ((n - t) >= 200) {
    digitalWrite(TX_LED, HIGH);
    send_data();
    digitalWrite(TX_LED, LOW);
    t = millis();
  }
  if (millis() - start <= 5000) {
    ASVmotors.pwmL = 7.5f;
    ASVmotors.pwmR = 7.5f;
  }*/
  // atualiza o duty cycle dos motores gradualmente
  //5.5 -> full speed trás  7.5 -> parado  9.5 -> full speed frente

  if(ASVmotors.pwmL != oldPWM_L) {
    if((ASVmotors.pwmL > 7.5 &&  oldPWM_L >= 7.5) || (ASVmotors.pwmL < 7.5 &&  oldPWM_L <= 7.5) || ASVmotors.pwmL == 7.5 || oldPWM_L == 7.5) {
      const float deltaL = ASVmotors.pwmL - oldPWM_L;
      const float intervalL = ASVmotors.pwmL * 0.5 / 2.0;
      //const float intervalL = deltaL * 0.5 / 2.0;
      const float numStepsL = 50.0 * abs(deltaL) / 2.0;
      const float stepL = intervalL/numStepsL;
      // verificar se já passou tempo suficiente desde a última entrada no bloco
      //Serial.println(numStepsL);
      if(millis() - lastEnterL >= stepL * 1000) {
        // atualizar lastEnterL com o tempo atual
        lastEnterL = millis();
        // entrar no bloco de código desejado
        oldPWM_L += stepL;
        if(oldPWM_L > ASVmotors.pwmL) {
          oldPWM_L = ASVmotors.pwmL;
        }
        Serial.print("Left,");
        Serial.print(millis());
        Serial.print(",");
        Serial.print(oldPWM_L);
        Serial.print("\n");        
        PWM_motorL->setPWM(PIN_motorL, 50, oldPWM_L);
      }

    }
    else if((ASVmotors.pwmL > 7.5 &&  oldPWM_L < 7.5) || (ASVmotors.pwmL < 7.5 &&  oldPWM_L > 7.5)) {    
      auxL = ASVmotors.pwmL;
      ASVmotors.pwmL = 7.5;
      const float deltaL = ASVmotors.pwmL - oldPWM_L;
      const float intervalL = ASVmotors.pwmL * 0.5 / 2.0;
      const int numStepsL = int(50.0 * abs(deltaL) / 2.0);
      const float stepL = deltaL/numStepsL;
      // verificar se já passou tempo suficiente desde a última entrada no bloco
      if(millis() - lastEnterL >= intervalL * 1000) {
        // atualizar lastEnterL com o tempo atual
        lastEnterL = millis();
        // entrar no bloco de código desejado
        oldPWM_L += stepL;
        if(oldPWM_L > ASVmotors.pwmL) {
          oldPWM_L = ASVmotors.pwmL;
        }
        PWM_motorL->setPWM(PIN_motorL, 50, oldPWM_L);
      }
      ASVmotors.pwmL = auxL;
    }

  }
  if(ASVmotors.pwmR != oldPWM_R) {
    if((ASVmotors.pwmR >= 7.5 &&  oldPWM_R >= 7.5) || (ASVmotors.pwmR <= 7.5 &&  oldPWM_R <= 7.5) || ASVmotors.pwmR == 7.5 || oldPWM_L == 7.5) {
      const float deltaR = ASVmotors.pwmR - oldPWM_R;
      const float intervalR = ASVmotors.pwmR * 0.5 / 2.0;
      const int numStepsR = int(50.0 * abs(deltaR) / 2.0);
      const float stepR = deltaR/numStepsR;
      // verificar se já passou tempo suficiente desde a última entrada no bloco
      if(millis() - lastEnterR >= intervalR * 1000) {
        // atualizar lastEnterL com o tempo atual
        lastEnterR = millis();
        // entrar no bloco de código desejado
        oldPWM_R += stepR;
        if(oldPWM_R > ASVmotors.pwmR) {
          oldPWM_R = ASVmotors.pwmR;
        }
        PWM_motorR->setPWM(PIN_motorR, 50, oldPWM_R);
      }
      
    }
    else if((ASVmotors.pwmR > 7.5 &&  oldPWM_R < 7.5) || (ASVmotors.pwmR < 7.5 &&  oldPWM_R > 7.5)) {    
      auxR = ASVmotors.pwmR;
      ASVmotors.pwmR = 7.5;
      const float deltaR = ASVmotors.pwmR - oldPWM_R;
      const float intervalR = ASVmotors.pwmR * 0.5 / 2.0;
      const int numStepsR = int(50.0 * abs(deltaR) / 2.0);
      const float stepR = deltaR/numStepsR;
      // verificar se já passou tempo suficiente desde a última entrada no bloco
      if(millis() - lastEnterR >= intervalR * 1000) {
        // atualizar lastEnterL com o tempo atual
        lastEnterR = millis();
        // entrar no bloco de código desejado
        oldPWM_R += stepR;
        if(oldPWM_R > ASVmotors.pwmR) {
          oldPWM_R = ASVmotors.pwmR;
        }
        PWM_motorR->setPWM(PIN_motorR, 50, oldPWM_R);
      }
      ASVmotors.pwmR = auxR;
    }
  }
}