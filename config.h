#ifndef CONFIG_H
#define CONFIG_H

//! Buffer sizes.
#define BUFFER_SIZE                     (128)

//! Use csum
#define USE_CSUM                        (0)

//! Spew debug of parser.
#define SPEW_DEBUG_PARSER               (0)

//! Firmware's major version number.
#define DEV_VER                         (1)
//! Firmware's revision number.
#define DEV_REV                         (0)
//! Firmware's patch level.
#define DEV_PAT                         (0)

//! LED PIN for tx feedback (led is on while TX is being used)
#define TX_LED                          (25)

//! PWM PIN for Motor R
#define PIN_motorL                      (0)
//! PWM PIN for Motor L
#define PIN_motorR                      (1)

#endif