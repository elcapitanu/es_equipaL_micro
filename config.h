#ifndef CONFIG_H
#define CONFIG_H

//! Buffer sizes.
#define BUFFER_SIZE (128)

//! Use CSUM
#define USE_CSUM (1)
//! Use IMU
#define USE_IMU (1)

//! Spew debug of parser.
#define SPEW_DEBUG_PARSER (0)

//! Firmware's major version number.
#define DEV_VER (1)
//! Firmware's revision number.
#define DEV_REV (0)
//! Firmware's patch level.
#define DEV_PAT (0)

//! LED PIN for Debug
#define DEBUG_LED (25)

//! PWM PIN for Motor R
#define PIN_motorL (22)
//! PWM PIN for Motor L
#define PIN_motorR (21)
//! PWM DEBUG
#define PWM_DEBUG (0)

//! IMU PIN for SDA
#define IMU_SDA (4)
//! IMU PIN for SCL
#define IMU_SCL (5)
//! IMU DEBUG
#define IMU_DEBUG (0)

#endif