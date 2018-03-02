#include <QTRSensors.h>

#define Kp 0.15          
#define Kd 0.25     
#define sagMaksHiz 255  // Sag motor maksimum hiz
#define solMaksHiz 255  // Sol motor maksimum hiz
#define sagTemelHiz 180 // Sensor tam cizginin uzerindeyken izlemesi gereken hiz
#define solTemelHiz 180 //  Sensor tam cizginin uzerindeyken izlemesi gereken hiz
#define SENSOR_SAYISI 3
#define SENSOR_BASINA_ORNEKLEME 4
#define INFRARED_PIN 2

#define sagMotor1 6
#define sagMotor2 4
#define sagMotorPwm 5
#define solMotor1 7
#define leftMotor2 8
#define solMotorPwm 9
#define motorGuc 8

QTRSensorsAnalog qtrrc((unsigned char[]){0, 1, 2},
                       SENSOR_SAYISI, SENSOR_BASINA_ORNEKLEME, INFRARED_PIN);

unsigned int sensorValues[SENSOR_SAYISI];

void setup()
{
    Serial.begin(9600);
    pinMode(sagMotor1, OUTPUT);
    pinMode(sagMotor2, OUTPUT);
    pinMode(sagMotorPwm, OUTPUT);
    pinMode(solMotor1, OUTPUT);
    pinMode(leftMotor2, OUTPUT);
    pinMode(solMotorPwm, OUTPUT);
    pinMode(motorGuc, OUTPUT);

    Serial.println("Kalibre Ediliyor...");

    int i;
    for (int i = 0; i < 200; i++)
        qtrrc.calibrate();
    delay(20);
}

int sonHata = 0;

void loop()
{
    unsigned int sensors[6];
    int pozisyon = qtrrc.readLine(sensors); // cizginin pozisyonunu QTR8A sensorunden oku
    int hata = pozisyon - 1000;
//
//    Serial.print("Pozisyon => ");
//    Serial.print(pozisyon);
//    Serial.print(" Hata => ");
//    Serial.println(hata);

    int motorHiz = Kp * hata + Kd * (hata - sonHata); 
    sonHata = hata;

    int sagMotorHiz = sagTemelHiz + motorHiz;
    int solMotorHiz = solTemelHiz - motorHiz;

    if (sagMotorHiz > sagMaksHiz)
        sagMotorHiz = sagMaksHiz; // motorun maksimum hizi gecmesini engeller
    if (solMotorHiz > solMaksHiz)
        solMotorHiz = solMaksHiz; // motorun maksimum hizi gecmesini engeller
    if (sagMotorHiz < 0)
        sagMotorHiz = 0; // motorun hizini pozitifte tutar
    if (solMotorHiz < 0)
        solMotorHiz = 0; // motorun hizini pozitifte tutar

    {
        digitalWrite(motorGuc, HIGH); // ileri dogru uygnu degerde ilerle
        digitalWrite(sagMotor1, HIGH);
        digitalWrite(sagMotor2, LOW);
        analogWrite(sagMotorPwm, sagMotorHiz);
        digitalWrite(motorGuc, HIGH);
        digitalWrite(solMotor1, HIGH);
        digitalWrite(leftMotor2, LOW);
        analogWrite(solMotorPwm, solMotorHiz);
    }
}

void wait()
{
    digitalWrite(motorGuc, LOW);
}
