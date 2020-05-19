#include <Arduino.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <relays.h>
LiquidCrystal_I2C lcd(0x27,16,2);

boolean showState[4] = {0,0,0,0};
boolean ProgramState = 0;
boolean clearScreen = 1;
boolean clearScreen2 = 1;



const int dhtpin0 = A0;
const int dhtpin1 = A1;
const int dhtpin2 = A2;
const int dhtpin3 = A3;

const int DHTTYPE = DHT11; 

DHT dht0(dhtpin0, DHTTYPE);
DHT dht1(dhtpin1, DHTTYPE);
DHT dht2(dhtpin2, DHTTYPE);
DHT dht3(dhtpin3, DHTTYPE);

unsigned long timeGet;

float t0 = 0.0, t1 = 0.0, t2 = 0.0, t3 = 0.0;
void lcdShow();
void buttonP();
void Program();



int button = 6;
unsigned long waitTime = 500;
boolean lastButtonStatus = 0; 
boolean buttonLongPress = 0;
unsigned long lastChangedTime;

unsigned long timeBase;
unsigned long timeCount;


void setup() {
  pinMode(button,INPUT);
  //pinMode(13,OUTPUT);
  //digitalWrite(13,HIGH);
  Serial.begin(9600);
  dht0.begin();
  dht1.begin();
  dht2.begin();
  dht3.begin();
  lcd.init();       
  lcd.backlight();
  timeGet = millis();

  pinDeclare();
  

  

}

void loop() {
  while (ProgramState == 1)
  {
    if (clearScreen2 == 1) {lcd.clear();clearScreen2 = 0;timeBase = millis();}
    Program();
    buttonP();
    
    if (clearScreen == 0) {clearScreen = 1;}
  }

  if (clearScreen == 1)
  {
    remoState();
    showState[0] = 0; showState[1] = 0; showState[2] = 0; showState[3] = 0; 
    lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("DO AN CN563");
    lcd.setCursor(1,1);
    lcd.print("NHOM 5 - LOP 1");
    clearScreen = 0;
    clearScreen2 = 1;
  }
  
  buttonP();

  

  

}


void lcdShow()
{
  //lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(t0,1);
  lcd.setCursor(4,0);
  if (showState[0] == 1) {lcd.print("o");} else {lcd.print("f");}
 

  lcd.setCursor(0,1);
  lcd.print(t1,1);
  lcd.setCursor(4,1);
  if (showState[1] == 1) {lcd.print("o");} else {lcd.print("f");}

  lcd.setCursor(6,0);
  lcd.print(t2,1);
  lcd.setCursor(10,0);
  if (showState[2] == 1) {lcd.print("o");} else {lcd.print("f");}

  lcd.setCursor(6,1);
  lcd.print(t3,1);
  lcd.setCursor(10,1);
  if (showState[3] == 1) {lcd.print("o");} else {lcd.print("f");}

  

  


 
  //timeCount = ((millis()/1000)/60)/60;
  timeCount= (millis() - timeBase)/1000; // doi ra giay
  lcd.setCursor(12,0);
  //lcd.print(timeCount);
  
  timeCount = timeCount/60; //doi ra phut
  timeCount = timeCount/60; // doi ra gio
  lcd.setCursor(12,1);
  lcd.print(timeCount);


}

void buttonP()
{
  boolean reading = digitalRead(button); // đọc giá trị của button
  if (reading != lastButtonStatus) { // Nếu bạn đang nhấn button rồi thả ra giữa chừng hoặc đang thả button rồi nhấn lại 
    lastButtonStatus = reading; //Cập nhập trạng thái cuối cùng.
    lastChangedTime = millis(); //Cập nhập thời gian
  } // Còn nếu bạn đang nhấn giữ button hoặc thả nó thời gian dài chỉ sẽ không ảnh hưởng đến việc này
  
  if (millis() - lastChangedTime > waitTime) { // Nếu sự chênh lệch giữa thời điểm đang xét và thời điểm cuối cùng thay đổi trạng thái của button lớn hơn thời gian đợi để tạo sự kiện nhấn giữ THÌ nó là một sự kiến nhấn giữ
    buttonLongPress = reading; // Cập nhập trạng thái của button = với trạng thái của button
    lastChangedTime = millis();
  }
  
  if (buttonLongPress == true) { // Nếu có sự kiện nhấn giữ, ta thay đổi trạng thái của đèn LED
    ProgramState = !ProgramState; //Dấu ! là dấu phủ định, 0 thành 1, 1 thành 0, tắt thành sáng, sáng thành tắt
    buttonLongPress = false; // Kết thúc sự kiện nhấn giữ
    
  }
}

void Program()
{
  if ( (unsigned long) (millis() - timeGet) > 1000)
  {
    t0 = dht0.readTemperature();
    t1 = dht1.readTemperature();
    t2 = dht2.readTemperature();
    t3 = dht3.readTemperature();

    checkState(&t0, &t1, &t2, &t3);
    sendState(&showState[0], &showState[1], &showState[2], &showState[3]);
    
    lcdShow();
    timeGet = millis();
    
  }
}



