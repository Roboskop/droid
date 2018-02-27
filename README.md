cyber-droid
===========
  CyberDroid kütüphanesi Roboskop Şirketi tarafından geliştirilen kart ile kontrol edilen araçların sürüşünü kolaylaştırmak, bluetooth üzerinden telefon ile kolayca haberleşebilmesi için geliştirilmiştir.


Özellikler
================
Kütüphane 3 parçadan oluşur. Sürücü, motor ve iletişim protokol kütüphaneleri bu parçalardır. 

- Sürücü üzerinden kütüphaneyi kullanarak sola dönüş, sağa dönüş ve hız ayarları gibi işlemler gerçekleştirilebilir.
- Motor kütüphanesi motorların yönünü ve hızını ayarlayan kütüphanedir. Sürücü kütüphanesi kendi içinde aslında bu kütüphaneyi kullanır.
- İletişim kütüphaneleri ise Serial üzerinden gelen komutları yorumlama işlemlerini gerçekleştirir.
- Kütüphane başka herhangi bir kütüphaneye bağımlı değildir.

Sürücü
================
+ilerle( int hız , int direksiyon ) veya throttle( int th , int steering )
İlerle fonksiyonu CyberDroid aracını belirtilen hız ve direksiyon yönünde hareket ettirir. 

Örnek kullanım : 

        #include <CyberDroid.h>
        
        CyberDroid droid;

        void setup() {  }

        void loop() {
            droid.ilerle( 127 , 0 ); //Araç %50 hızla dümdüz ilerle
            delay(2000); //2 saniye bekle
            droid.ilerle( 0 , 0 ); //Aracı durdur
            delay(2000); //2 saniye bekle
            droid.ilerle( 255 , 127); //Araç tam gaz ilerle ve sağa dogru %50 güçle dönüş yap
            delay(2000); //2 saniye bekle
            droid.ilerle( 255 , -127 ); //Araç tam gaz ilerle ve sol doğru %50 güçle dönüş yap
            delay(2000); //2 saniye bekle
            droid.ilerle( 0 , 0 ); //Aracı durdur
            delay(2000); //2 saniye bekle
            droid.ilerle( -127 , kullanımlar0 ); //Geriye doğru %50 hızla dümdüz ilerle
            delay(2000); //2 saniye bekle
            droid.ilerle( -255 , 0 ); //Geriye doğru tam gaz dümdüz ilerle
            delay(2000); //2 saniye bekle
        }
        
        /*
            Bu örnekte ilerle( int hız , int direksiyon ) metodunun kullanımı gösterilmiştir. 
            İlerle metodundaki değerlerin 255 değerinden büyük veya -255 değerinden küçük olamayacağını
            unutmayınız. Hız parametresinde + değer ileriyi, - değer ise geriyi bu değerin büyüklüğü ise 
            motorun dönme hızını ifade eder. Direksiyon parametresinde ise sürücü hızına göre otomatik 
            olarak dönüş için gerekli olan şiddeti ayarlar ve + değerler sağa dönüşü, - değerler ise 
            sola dönüşü ifade eder. 0 değeri dümdüz aracın dümdüz gitmesini ifade eder.
        */
        
Motor Kütüphanesi
=================
+döndür( int güç ) veya throttle( int th );
Döndür fonksiyonu motorun belirtilen güç ve yönde dönmesini sağlar.

Örnek kullanım : 

        #include <Motor.h>
        
        RMotorDriver motor( 7 , 8 , 9 ); //7 InA(1), 8 InB(2) , 9 PWM

        void setup() {  }

        void loop() {
            motor.döndür( 127 ); //Motor saat yönünde %50 hızla döndür
            delay(2000); //2 saniye bekle
            motor.döndür( 255 ); //Motor saat yönünde tam gaz döndür
            delay(2000); //2 saniye bekle
            motor.döndür( 0 ); //Motoru durdur
            delay(2000); //2 saniye bekle
            motor.döndür( -185 ); //Motoru saat yönünün tersine %75 güçle döndür
            delay(2000); //2 saniye bekle
            motor.döndür( -255 ); //Motoru saat yönünün tersine %100 güçle döndür
            delay(2000); //2 saniye bekle
        }
        
        /*
            Bu örnekte döndür( int hız ) metodunun kullanımı gösterilmiştir. Döndür 
            metodundaki hız parametresinin 255 değerinden büyük veya -255 değerinden
            küçük olamayacağını unutmayınız. Hız parametresinde + değer saat yönünde, 
            - değer ise saat yönünün tersini, bu değerin büyüklüğü ise motorun dönme
            hızını ifade eder. 0 ise motoru durdurur.
        */

 Haberleşme 
======

Hız Testi
==================
5 parametreli bir komutu yorumlaması yaklaşık 104 mikrosaniyede tamamlanır. Dolayısıyla işlemcimiz böyle bir komutu saniyede 9615 defa işleyebilir. Parametre içermeyen bir komutu yorumlaması ise yaklaşık 8 mikrosaniye almaktadır, bu da saniyede 125000 tane komutu işleyebileceği anlamına gelir.

Bu testler 115200 baudrate hızın uygulanmıştır.

Bu hızla binary iletişimdeki kadar hızlı ve verimli olmuyucaktır fakat veri aktarım hızının çok önemli olmadığı projelerde rahatlıkla kullanılabilir, anlaşılması ve uygulanması kolaydır.
 
==============
        /*SimpleSerial kullanımı*/
        
        #include <SimpleSerial.h>

        void komutGeldi(uint8_t);

        SimpleSerial seri(&Serial,komutGeldi);

        void setup() {
            Serial.begin(115200); //Seri bağlantı başlatılıyor.
        }

        void loop() {
            seri.check(); //Herhangi bir komutun gelip gelmediği kontrol ediliyor.
            //Gelen komutların yorumlanabilmesi için bu fonksiyonu sürekli çağırmanız gerekmektedir.
        }

        void commandCallback(uint8_t code){
            Serial.print("Komut alındı, KOD : ");
            Serial.println(code);
            
            int arg1 = seri.readIntArg();
            int arg2 = seri.readIntArg();
            String arg3 = seri.readStrArg();
            
            Serial.println("Parametreler ");
            Serial.print("Parametre 1 : ");
            Serial.print(arg1);
            Serial.print(" Parametre 2 : ");
            Serial.print(arg2);
            Serial.print(" Parametre3 : ");
            Serial.println(arg3);
        }
        
        /*
            This example listen Serial and reads the arguments from Serial input.
            Bu örnek seri portu dinleyip argümanları okumaktadır.
            
            {1233,144,HELLO} serial monitor üzerinden mikroişlemciye gönderdiğiniz takdirde çalıştığını görebilirsiniz.
            
            Gönderilen -> {1233,144,Merhaba}
            Serial Monitörde Görülen -> Komut Alındı : 49 Arg1 : 233 Arg2 : 144 Arg3 : Merhaba

        */
