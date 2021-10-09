#ifndef ENROLL_H
#define ENROLL_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>

uint8_t getFingerprintEnroll(Adafruit_Fingerprint finger, uint8_t id);
#endif
