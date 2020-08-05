// #include "HX711.h"

#define CAL_FACTOR -7050.0

#define LOADCELL_DT 2
#define LOADCELL_SDK 3
#define PI1 30
#define PI2 32

#define E_STOP 22
#define SERVO_ON 23
#define RESET 24
#define SPEED1 25
#define SPEED2 26
#define RS1 27
#define RS2 28
#define TORQUE1 DAC0
#define TORQUE2 DAC1

// HX711 scale(LOADCELLDT, LOADCELLSDK);

int val = 0;

void setup()
{
    Serial.begin(9600);
    //   scale.set_scale(CALFACTOR);
    //   scale.tare();

    pinMode(E_STOP, OUTPUT);
    pinMode(SERVO_ON, OUTPUT);
    pinMode(RESET, OUTPUT);
    pinMode(SPEED1, OUTPUT);
    pinMode(SPEED2, OUTPUT);
    pinMode(RS1, OUTPUT);
    pinMode(RS2, OUTPUT);
    pinMode(PI1, INPUT);
    pinMode(PI2, INPUT);

    digitalWrite(E_STOP, HIGH);
    digitalWrite(SERVO_ON, HIGH);
    digitalWrite(RESET, HIGH);
    digitalWrite(SPEED1, HIGH);
    digitalWrite(SPEED2, HIGH);
    digitalWrite(RS1, HIGH);
    digitalWrite(RS2, HIGH);

    Serial.println("init complete");
}

void loop()
{
    if (Serial.available())
    {
      Serial.println("Serial input!");
        String packet = Serial.readStringUntil('\n');
        String designation = packet.substring(0, 2);
        Serial.println(designation);
        int value = packet.substring(2, 6).toInt();
        Serial.println(value);

        if (designation[0] == 'E' & designation[1] == 'S')
        {
            if (value == 0)
            {
                digitalWrite(E_STOP, HIGH);
                Serial.println("E STOP OFF");
            }
            else
            {
                digitalWrite(E_STOP, LOW);
                Serial.println("E STOP ON");
            }
        }

        if (designation[0] == 'S' & designation[1] == 'O')
        {
            if (value == 0)
            {
                digitalWrite(SERVO_ON, HIGH);
            }
            else
            {
                digitalWrite(SERVO_ON, LOW);
            }
        }

        
        if (designation[0] == 'R' & designation[1] == 'S')
        {
            if (value == 0)
            {
                digitalWrite(RESET, HIGH);
            }
            else
            {
                digitalWrite(RESET, LOW);
            }
        }

        if (designation[0] == 'V' & designation[1] == '1')
        {
            if (value == 0)
            {
                digitalWrite(SPEED1, HIGH);
            }
            else
            {
                digitalWrite(SPEED1, LOW);
            }
        }

        if (designation[0] == 'V' & designation[1] == '2')
        {
            if (value == 0)
            {
                digitalWrite(SPEED2, HIGH);
            }
            else
            {
                digitalWrite(SPEED2, LOW);
            }
        }

        if (designation[0] == 'D' & designation[1] == '1')
        {
            if (value == 0)
            {
                digitalWrite(RS1, HIGH);
            }
            else
            {
                digitalWrite(RS1, LOW);
            }
        }

        if (designation[0] == 'D' & designation[1] == '2')
        {
            if (value == 0)
            {
                digitalWrite(RS2, HIGH);
            }
            else
            {
                digitalWrite(RS2, LOW);
            }
        }

        if (designation[0] == 'T' & designation[1] == 'Q')
        {
            if (value > 0)
            {
                analogWriteResolution(12);
                analogWrite(TORQUE2, 4095);
                analogWriteResolution(12);
                analogWrite(TORQUE1, 4095 - value);
            }
            else
            {
                analogWriteResolution(12);
                analogWrite(TORQUE2, 4095 + value);
                analogWriteResolution(12);
                analogWrite(TORQUE1, 4095);
            }
        }
    }
}
