#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

Servo servo;
const byte servo_pin PROGMEM=3;
const byte satir PROGMEM=4;
const byte sutun PROGMEM=4;
struct pinler {
  const byte pinler[1] PROGMEM={2};
  byte satir_pinler[satir]={11,10,9,8}; 
  byte sutun_pinler[sutun]={7,6,5,4};
};
struct pinler pin;
char tus_takimi[satir][sutun]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
LiquidCrystal_I2C lcd(0x27,16,2);
Keypad tuslar=Keypad(makeKeymap(tus_takimi),pin.satir_pinler,pin.sutun_pinler,satir,sutun);
char hafiza[4];
char yon_karakterleri[4]={'<','>','H','E'}; //A SOL B SAG C TEMİZLE D EVET
bool bayrak=false;
bool tus=false;
int gelen_tus;
unsigned long zaman=0;
byte sayac=7; // blink olacak kısım seçilir
byte hafiza_sayaci=0;
char sifre[]="1998";
bool cikis_sifre=false;
int karar=0;
void setup()
{
  Serial.begin(9600);
  servo.attach(servo_pin);servo.write(0);
  ekran_baslatma();
}

void loop()
{
  ekran_yonetimi();
  delay(1);
 
  
}
void ekran_baslatma() {
  if(!bool(0))
  {
    lcd.init();lcd.backlight();lcd.setCursor(0,0);
    lcd.print("GENC KORUMA SIS.");
    lcd.setCursor(4,1);
    for(int i=1; i<=8; i++) 
    {
      lcd.print("*");delay(80); 
    }
    delay(1000);lcd.clear();
  }
}
void ekran_yonetimi() {
  
  if(!bool(0))
  {
    if(bayrak==false)
    {
      ilk_sayfa();
      bayrak=!bayrak;
    }
    if(bayrak==true)
    {
      buradan2:
      if(millis()-zaman>2500)
      {
        zaman=millis();
    lcd.setCursor(sayac,1);lcd.blink();
      }
      gelen_tus=tuslar.getKey();
      lcd.setCursor(sayac,1);
      if(gelen_tus=='A' or gelen_tus=='B' or gelen_tus=='C' or gelen_tus=='D')
      {
        if(gelen_tus=='A') // sol yön tusu
        {
          sayac--;
          if(sayac<6) sayac=7;           
        }
        if(gelen_tus=='B')
        {
          sayac++;
          if(sayac>8) sayac=6;
        }       
        if(gelen_tus=='D' and sayac==8)
        {
          buradan:
          sayac=7;
          lcd.clear();
          lcd.setCursor(0,1);lcd.print(yon_karakterleri[0]);
          lcd.setCursor(6,1);lcd.print(yon_karakterleri[2]);
          lcd.setCursor(8,1);lcd.print(yon_karakterleri[3]);
          lcd.setCursor(15,1);lcd.print(yon_karakterleri[1]);
          lcd.setCursor(2,0);
          lcd.print("SIFRE GIRINIZ");
          do
          { 
            gelen_tus=tuslar.getKey();
            lcd.setCursor(sayac,1);
            if(gelen_tus=='A')
            {
              sayac--;
              if(sayac<6) sayac-=5;
              else if(sayac==14) sayac=8;
            }
            if(gelen_tus=='B')
            {
              sayac++;
              if(sayac>8) sayac+=6;
              else if(sayac==1) sayac=6;
            }
            if(gelen_tus=='D' and sayac==8)
            {
              ikinci_sayfa();
            if(atoi(hafiza)==atoi(sifre))
              {
                lcd.clear();lcd.print("SIFRE DOGRU");
                delay(500);lcd.clear();
                lcd.print("KAPI ACILIYOR");
                servo.write(90);
                delay(3000);
                lcd.clear();lcd.print("KITLENIYOR");
                delay(1000);
                ilk_sayfa();
                break;
              }
              else
              {
                lcd.clear();lcd.print("SIFRE YANLIS");
                delay(1000);
                ilk_sayfa();
                goto buradan2;
              }
            }
            if(gelen_tus=='D' and sayac==6)
            {
              ilk_sayfa();
              break;
            }
            if(gelen_tus=='D' and sayac==15)
            {
              sayac=7;
              lcd.clear();lcd.setCursor(0,0);
              lcd.print(F("SIFRE DEGISTIRME"));
              lcd.setCursor(0,1);lcd.print(yon_karakterleri[0]);
              lcd.setCursor(6,1);
              for(int i=2; i<=3; i++)
              {
                lcd.print(yon_karakterleri[i]);lcd.print(" ");
              }
              if(!bool(0))
              {
                while(true)
                {
                  gelen_tus=tuslar.getKey();
                  if(gelen_tus=='A')
                  {
                    sayac--;
                    if(sayac<6) sayac=0;
                  }
                  if(gelen_tus=='B')
                  {
                    sayac++;
                    if(sayac>8) sayac=7;
                    else if(sayac==1) sayac=7;
                  }
                  if(gelen_tus=='D' and sayac==0)
                  {
                     sayac=7;
                     goto buradan;
                  }
                  if(gelen_tus=='D' and sayac==6)
                  {
                    sayac=7;
                    goto buradan;
                  }
                  if(gelen_tus=='D' and sayac==8)
                  {
                    ucuncu_sayfa();
                    delay(2000);
                    sayac=7;
                    ilk_sayfa();
                    goto buradan2;
                  }
                  lcd.setCursor(sayac,1);
                  delay(1);
                }
                
              }
            }
            if(gelen_tus=='D' and sayac==0)
            {
              sayac=7;
              ilk_sayfa();
              break;
            }
            delay(5);
            
          }while(!bool(0));
        }
      }
    }
  }
}
void ilk_sayfa() {
  servo.write(0);lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("ANA SAYFA");lcd.setCursor(6,1);
  for(int i=0; i<4; i++) 
  {
    if(i!=2 and i!=3)
    {
      lcd.print(yon_karakterleri[i]);lcd.print(" ");
    }
    delay(1);
  }
  lcd.blink();
}

void ikinci_sayfa() {
  lcd.clear();lcd.noBlink();
  lcd.setCursor(2,0);
  lcd.print("SIFRE GIRINIZ");
  hafiza_sayaci=0;
  if(!bool(0))
  {
    while(hafiza_sayaci<4)
    {
      char gelen_karakter=tuslar.getKey();
      if(gelen_karakter)
      {
        lcd.setCursor(hafiza_sayaci+5,1);
        lcd.print("*");
        hafiza[hafiza_sayaci]=gelen_karakter;
        hafiza_sayaci++;
      }
      delay(1);
    }
    hafiza_sayaci=0;
    sayac=7;
    delay(300);
  }
}
void ucuncu_sayfa() {
  hafiza_sayaci=0;
  lcd.clear();lcd.noBlink();
  lcd.clear();lcd.print("MEVCUT SIFRE");
  while(hafiza_sayaci<4)
  {
      char gelen_karakter=tuslar.getKey();
      if(gelen_karakter)
      {
        lcd.setCursor(hafiza_sayaci+5,1);
        lcd.print("*");
        hafiza[hafiza_sayaci]=gelen_karakter;
        hafiza_sayaci++;
      }
      delay(1);
  }
  delay(300);
  if(atoi(sifre)==atoi(hafiza))
  {
    hafiza_sayaci=0;
    lcd.clear();lcd.print("SIFRE DOGRU");
    delay(1000);
    lcd.clear();lcd.print("YENI SIFRE");
    while(hafiza_sayaci<4)
    {
      char gelen_karakter=tuslar.getKey();
      if(gelen_karakter)
      {
        lcd.setCursor(hafiza_sayaci+5,1);
        lcd.print("*");
        hafiza[hafiza_sayaci]=gelen_karakter;
        hafiza_sayaci++;
      }
      delay(1);
    }
    for(int i=0; i<4; i++)
    {
      sifre[i]=hafiza[i];
    }
    delay(300);
    hafiza_sayaci=0;
    delay(500);
    lcd.clear();lcd.setCursor(2,0);
    lcd.print("SIFRE DEGISTI");sayac=7;
  }
  else
  {
    lcd.clear();lcd.print("SIFRE HATALI");
    delay(1000);sayac=7;
    ilk_sayfa();
  }
}
