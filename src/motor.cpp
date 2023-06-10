#include "motor.h"

struct motors ASVmotors = {0};

RP2040_PWM *PWM_motorL;
RP2040_PWM *PWM_motorR;

unsigned long startTime = 0;
float pause_in_inversion = 300;
float start_pauseL = 0;
float start_pauseR = 0;
boolean stopL = false;
boolean stopR = false;

boolean auxL = false;
boolean auxR = false;

float timeL = 0;
float timeR = 0;

void init_motors()
{
  PWM_motorL = new RP2040_PWM(PIN_motorL, 50, 0);
  PWM_motorR = new RP2040_PWM(PIN_motorR, 50, 0);

  ASVmotors.pwmL = 7.5f;
  ASVmotors.pwmR = 7.5f;
}

void actuate_motors()
{
  if (state != SERVICE)
  {
    ASVmotors.pwmL = 7.5f;
    ASVmotors.pwmR = 7.5f;
  }

#if PWM_DEBUG
  Serial.print("PWM L: ");
  Serial.print(ASVmotors.pwmL);
  Serial.print("| PWM R: ");
  Serial.println(ASVmotors.pwmR);
#endif

  PWM_motorL->setPWM(PIN_motorL, 50, ASVmotors.pwmL);
  PWM_motorR->setPWM(PIN_motorR, 50, ASVmotors.pwmR);

  // static unsigned long startTimeL = 0;
  // static unsigned long startTimeR = 0;
  // unsigned long currentTime = millis();

  // // Verificar se os valores dos motores precisam ser ajustados
  // if (ASVmotors.pwmL != ASVmotors.desiredL)
  // {
  //   if (startTimeL == 0)
  //   {
  //     startTimeL = currentTime;
  //   }

  //   if (ASVmotors.desiredL > 49 && ASVmotors.desiredL < 51 && stopL == false)
  //   {
  //     stopL = true;
  //     start_pauseL = currentTime;
  //     ASVmotors.desiredL = 50;
  //   }

  //   unsigned long elapsedTime_pauseL = currentTime - start_pauseL;

  //   if (stopL == true && elapsedTime_pauseL > pause_in_inversion)
  //   {
  //     stopL = false;
  //     startTimeL = currentTime;
  //     if (ASVmotors.pwmL < ASVmotors.desiredL)
  //     {
  //       ASVmotors.desiredL = 48.9;
  //     }
  //     else
  //     {
  //       ASVmotors.desiredL = 51.1;
  //     }
  //   }

  //   unsigned long elapsedTime = currentTime - startTimeL;

  //   if (elapsedTime <= 500 && stopL == false)
  //   {
  //     float percentComplete = static_cast<float>(elapsedTime) / 500.0;
  //     float incrementoL = percentComplete * percentComplete * (ASVmotors.pwmL - ASVmotors.desiredL);
  //     ASVmotors.desiredL += incrementoL;
  //   }
  //   else if (stopL == false)
  //   {
  //     ASVmotors.desiredL = ASVmotors.pwmL;
  //     startTimeL = 0;
  //   }

  //   // Mapear o valor para o intervalo desejado
  //   float mappedValueL = map(ASVmotors.desiredL, -100.0, 100.0, 5.5, 9.5);
  //   // Ativar o motor L com o valor mapeado
  //   PWM_motorL->setPWM(PIN_motorL, 50, mappedValueL);
  //   Serial.print("Motor Esquerdo \n");
  //   Serial.print(startTimeL, 3);
  //   Serial.print(", ");
  //   Serial.print(ASVmotors.desiredL, 3);
  //   Serial.print("\n");
  // }

  // if (ASVmotors.pwmR != ASVmotors.desiredR)
  // {
  //   if (startTimeR == 0)
  //   {
  //     startTimeR = currentTime;
  //   }

  //   if (ASVmotors.desiredR > 49 && ASVmotors.desiredR < 51 && stopR == false)
  //   {
  //     stopR = true;
  //     start_pauseR = currentTime;
  //     ASVmotors.desiredR = 50;
  //   }

  //   unsigned long elapsedTime_pauseR = currentTime - start_pauseR;

  //   if (stopR == true && elapsedTime_pauseR > pause_in_inversion)
  //   {
  //     stopR = false;
  //     startTimeR = currentTime;
  //     if (ASVmotors.pwmR < ASVmotors.desiredR)
  //     {
  //       ASVmotors.desiredR = 48.9;
  //     }
  //     else
  //     {
  //       ASVmotors.desiredR = 51.1;
  //     }
  //   }

  //   unsigned long elapsedTime = currentTime - startTimeR;

  //   if (elapsedTime <= 500 && stopR == false)
  //   {
  //     float percentComplete = static_cast<float>(elapsedTime) / 500.0;
  //     float incrementoR = percentComplete * percentComplete * (ASVmotors.pwmR - ASVmotors.desiredR);
  //     ASVmotors.desiredR += incrementoR;
  //   }
  //   else if (stopR == false)
  //   {
  //     ASVmotors.desiredR = ASVmotors.pwmR;
  //     startTimeR = 0;
  //   }

  //   // Mapear o valor para o intervalo desejado
  //   float mappedValueR = map(ASVmotors.desiredR, -100.0, 100.0, 5.5, 9.5);
  //   // Ativar o motor R com o valor mapeado
  //   PWM_motorR->setPWM(PIN_motorR, 50, mappedValueR);
  //   Serial.print("Motor Direito \n");
  //   Serial.print(startTimeR, 3);
  //   Serial.print(", ");
  //   Serial.print(ASVmotors.desiredR, 3);
  //   Serial.print("\n");
  // }
}