
/* Droid mobil kontrol için mikroişlemci yazılımı
 * Bu yazılımı mikroişlemcinize yükleyip, Play Store'da mevcut olan Droid
 * uygulaması ile aracınızı kontrol edebilirsiniz.
*/

#include <Droid.h>

#define KOMUT_GAZ             94  //{^<gaz>,<donus>}
#define KOMUT_FREN            102 //{f}

void komutAlindi( uint8_t code );

SimpleSerial  seriBaglanti( &Serial , komutAlindi ); 
Droid  droid;

void setup(){
  Serial.begin(9600); //Seri port baslatiliyor
}

void loop(){
  seriBaglanti.check(); //Gelen komut varmi diye kontrol ediliyor
}

void komutAlindi(uint8_t code){
  switch(code){
    case KOMUT_GAZ  : {
      
      int gaz = seriBaglanti.readIntArg();//Ilk parametreyi okunuyor <gaz>
      int donus = seriBaglanti.readIntArg();//Ikinci parametre okunuyor <donus>
      droid.ilerle( gaz , donus );
      break;
    }
    case KOMUT_FREN : {
      droid.fren();
      break;
    }
  }
}
