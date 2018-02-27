#include <Droid.h>

Droid  droid( 7 , 8 , 9 , 6 , 4 , 5 );

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("İleri Tam Gaz");
  droid.ilerle(255 , 0);
  delay(2000);
  Serial.println("Durduruldu.");
  delay(1000);
  Serial.println("Geri Tam Gaz");
  droid.ilerle(-255 , 0);
  delay(2000);
  Serial.println("Sağa Dönüş");
  droid.ilerle(255 , 127);
  delay(2000);
  Serial.println("Sola Dönüş");
  droid.ilerle(255 , -127);
  delay(2000);
  Serial.println("Durduruldu.");
  droid.ilerle(0 , 0);
  delay(2000);
}
