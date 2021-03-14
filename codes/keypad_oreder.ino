#include <Keypad.h>
#include <LiquidCrystal.h>

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 

/*-------------------------------MOtor pin-------------*/
int in1 = 2; 
int in2 = 3; 
int EnA = 10; 
int in3 = 11; 
int in4 = 12; 
int EnB = 13; 

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);


const byte ROWS = 4; 
const byte COLS = 3; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {22, 24, 26, 28}; 
byte colPins[COLS] = {30, 32, 34}; 

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

String order[2];
int quan[2];
int tag[2];
int pric[2];
int remain[2];
int rate[2];

String item[2]= {"Coke","Dews"};
int tagid [2]={1,2};
int quantity[2]={5,5};
int price[2]={5,5};

uint8_t buffer[14] ;
uint8_t* buffer_at1;
uint8_t* buffer_end1 = buffer + sizeof(buffer);
uint8_t* buffer_at2;
uint8_t* buffer_end2 = buffer + sizeof(buffer);

const uint32_t user1 = 134744072 ;
 
String checksum1;
boolean tagfound1 = false;

int balance =100;
int a=0;
int amount =0;
void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial3.begin(115200);
  Serial2.begin(115200);
  pinMode(in1, OUTPUT); //Declaring the pin modes, obviously they're outputs
  pinMode(in2, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(in3, OUTPUT); //Declaring the pin modes, obviously they're outputs
  pinMode(in4, OUTPUT);
  pinMode(EnB, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  lcd.begin(16, 2);
 home();
}
void TurnMotorA(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(EnA,255);
}
void TurnOFFA(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(EnA,0);
 
}
void TurnMotorB(){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(EnB,255);
}
void TurnOFFB(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(EnB,0);
}
void loop() {
last:
//   memset(item, NULL, sizeof(item));
//   memset(tagid, NULL, sizeof(tagid));
//   memset(quantity, NULL, sizeof(quantity));
//   memset(price, NULL, sizeof(price));
//   Get_Data_from_NodeMCU();
//   home();
   char key1 = keypad.getKey();
//   while(key1 == NO_KEY){
//   key1 = keypad.getKey();
//    }
  if (key1 != NO_KEY)//if we press any key program start
  {
    int i = (int)key1 - 48; //makeing it intiger
    //Serial.println(i);
    if (i == 1)
    {
      order[a]= item[0];
      tag[a]=tagid[0];
      rate[a] = price[0];
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(item[0]);
      lcd.setCursor(0,1);
      lcd.print("Quantity :: ");
    }
    else if (i == 2)
    {
       order[a]= item[1];
       tag[a]=tagid[1];
       rate[a]=price[1];
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(item[1]);
      lcd.setCursor(0,1);
      lcd.print("Quantity :: ");
    }
    else{
      goto last;
      }
    delay(500);

    //wait for quantity
quantity:
    char key2 = keypad.getKey();

    if (key2 == NO_KEY)
    {
      goto quantity;//if no key press
    }
    else
      {
        int q =(int)key2 -48;
/*------------------------------------------------------view order----------------------------------------------*/
        if (key2 == '#')
      {
        lcd.clear(); 
        lcd.begin(16, 2);

        lcd.setCursor(0,0);
        for(int p = 0;p<=1;p++){
        if(order[p] != NULL){
        lcd.setCursor(0,p);
        lcd.print(order[p]);
        lcd.print(" ---> ");
        lcd.print(quan[p]);
        lcd.print("no.s");
        }
        }
        goto quantity;
      }
/*---------------------------------------add order-----------------------------------------------------------*/
      else if (q==9)
      {
          home();
          goto last;
        }
/*---------------------------------------confirm order-----------------------------------------------------------*/
        else if (q==0)
        {
        for(int p = 0;p<=1;p++){
            if(order[p] != NULL){
            amount = price[p]*quan[p]+amount;
            Serial.println(amount);
        }
        }
        
          a=0;
           
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Order Confirmed");
          lcd.setCursor(0,1);
          lcd.print("Amount: Rs");
          lcd.print(amount);
          delay(2000);
          senddata(amount);/*------------------data sens and recieve from    raspberry pi---------------------*/
           SEND_TO_NodeMCU();
        delay(1000);

            /*--------------------------MOtor Run---------------------------*/     
         for(int p = 0;p<=1;p++){
        if(order[p] != NULL){
       
          if(tag[p] == 1){
                
                int a =quan[p];
                while(a!=0){
                  Serial.println("MotorA");
                
                Serial.println(a);
                TurnMotorA();  //Sequence: turning on low speed, stop, turning again in high speed and stop
                delay(1355);
                TurnOFFA();
                delay(100);
                a = a-1;
                }
          }
           if(tag[p] == 2){;
                int a =quan[p];
               while(a!=0){
                  Serial.println("MotorB");
                
                Serial.println(a);
                TurnMotorB();  //Sequence: turning on low speed, stop, turning again in high speed and stop
                delay(1400);
                TurnOFFB();
                a = a-1;
                }
          }
             
            }
          }
          amount = 0;
          memset(order, NULL, sizeof(order));
          memset(quan, NULL, sizeof(quan));
          memset(tag, NULL, sizeof(tag));
          memset(pric, NULL, sizeof(pric));
          memset(rate, NULL, sizeof(rate));
          memset(remain, NULL, sizeof(remain));
          home();
          goto last;
          
        
        }
/*---------------------------------------cancel order-----------------------------------------------------------*/
          else if(q==6)
          {
            memset(rate, NULL, sizeof(rate));
            memset(order, NULL, sizeof(order));
            memset(quan, NULL, sizeof(quan));
            memset(tag, NULL, sizeof(tag));
            memset(pric, NULL, sizeof(pric));
            memset(remain, NULL, sizeof(remain));
            a=0;
            home();
          goto last; 
          }
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
      else{
        int i = (int)key2 - 48;
             quan[a] = i;
             Serial.println(quan[a]);
             pric[a] = i * price[a];
             remain[a] = quantity[a] - quan[a];
             a++;
        
        lcd.setCursor(13, 1);
        lcd.print(i);
        goto quantity;
      }
    } 
    }

}
/*-----------------------------------------Home Screen of LCD--------------------------------------------------------------------*/
void home(){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("1) ");
          lcd.print(item[0]);
          lcd.setCursor(10,0);
          lcd.print("Rs.");
          lcd.print(price[0]);
          lcd.setCursor(0,1);
          lcd.print("2) ");
          lcd.print(item[1]);
          lcd.setCursor(10,1);
          lcd.print("Rs.");
          lcd.print(price[1]);
  }
/*--------------------Serial Com. between Due and Rasp---------------------------------------------*/
 void senddata(int amount){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter Cash:");
          lcd.print("Rs.");
          lcd.print(amount);
          lcd.setCursor(0,1);
          lcd.print("1) Cash");
          lcd.print(" ");
          lcd.print("2) Card");
  qwert:
          char ke = keypad.getKey();

            if (ke == NO_KEY)
            {
              goto qwert;//if no key press
            }
            else
              {
                int q =(int)ke -48;
                
                if(q == 1){
                    Serial.println(amount);
                    lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Enter Cash");
                    SerialUSB.println(amount);
                    delay(2000);
                   while(!SerialUSB.available()){
                        ;
                        }
                       char confirm = SerialUSB.read();   
                     if(confirm == 'a'){
                      lcd.clear();
                      lcd.setCursor(0,0);
                      lcd.print("Thanks!!");
                      
                      delay(5000);
                          }
                     }
                if (q == 2){
                 lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Enter Card");
                 RFID_TO_NodeMCU();
                  if(amount < balance){
                  balance = balance - amount;
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("Thanks!!");    
                   delay(5000);
                  }
                  else{
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("Insufficient");    
                   delay(5000);
                    }
                 }
              
         
         }
          
  }
 /*--------------------------------Get Data From Nodemcu------------------------------------------- */
 void Get_Data_from_NodeMCU(){
   int p=0;
  int w=1;
  int a=0;
  Serial3.print('#');
  for(int i=0;i<9;i++){
    if(i==8){
      goto bot;
      }
     while (!Serial3.available()) {
      Serial3.print('#');
    ; // wait for serial port to connect. Needed for native USB port only
  }
  while (Serial3.available()) {
top:  String ch = Serial3.readStringUntil('@'); 
      if(p==0){
              p++;
          goto top;
           
        }
        if (ch == NULL){
          goto top;
          }
     if (ch != NULL){
      if(w>4){
        a++;
        w=1;
        }
     }
    //Serial.println(ch);
    switch (w){
      case 1:
             item[a] = ch.substring(0,4);
              w++;
             break;
      case 2:
             tagid[a] = ch.toInt();
              w++;
             break;

      case 3:
             quantity[a] =ch.toInt();
              w++;
             break;
      case 4:
             price[a] = ch.toInt();
              w++;
             break;
             
    }
 
  }
  }
bot: 
  for(int i=0;i<2;i++){
    
    Serial.print(tagid[i]);
    Serial.print(item[i]);
    Serial.print(price[i]);
    Serial.println(quantity[i]);
    }
   
 }
/*-----------------------------Send To NodeMCU------------------------------------------------------------*/
void SEND_TO_NodeMCU(){
  for(int i=0;i<3;i++){
if(order[i] != NULL){
  Serial1.print('@');
  Serial1.print(tag[i]);
  Serial1.print('@');
  Serial1.print(order[i]);
  Serial1.print('@');
  Serial1.print(quan[i]);
  Serial1.print('@');
  Serial1.print(pric[i]);
  Serial1.print('@');
  Serial1.print(remain[i]);
  Serial1.print('@');
  Serial1.print(rate[i]);
  Serial1.print('@');
    }
  } 
 }
/*-----------------------------------RFID check-------------------------------------------------*/
 void RFID_TO_NodeMCU(){
    while(!Serial2.available()){
      ;
      }
    if (Serial2.available())
    {
        Serial.println();
        Serial.println("---------------------------------------------------------------");
        Serial.println("                Processing rfid1");
        buffer_at1 = buffer;
        delay(10);
        while ( buffer_at1 < buffer_end1 )
        {
            *buffer_at1++ = Serial2.read();
        }
        tagfound1 = true;
        Serial2.end();
        Serial2.begin(9600);
        delay(20);
    }
 
    if (tagfound1)
    {  
        Serial.println("------tag 1 found------");
        
        buffer_at1 = buffer;
        uint32_t result1 = 0;
 
        // Skip the preamble  -  intial bit position
        ++buffer_at1;
        // Accumulate the checksum, starting with the first value
        uint8_t checksum1 = rfid_get_next1();
        // We are looking for 4 more values
        int i = 4;
        while(i--)
        {
            // Grab the next value
            uint8_t value1 = rfid_get_next1();
            // Add it into the result
                  result1 <<= 8;
                  result1 |= value1;
            // Xor it into the checksum
            checksum1 ^= value1;
        }
        // Pull out the checksum from the data
        uint8_t data_checksum1 = rfid_get_next1();
 
        // Print the result
        Serial.print("RFID_reader_Tag1: ");
        Serial.print(result1);
        delay(5);
        
        if ( checksum1 == data_checksum1 )
            Serial.println(" OK ");
        else
            Serial.println(" CHECKSUM FAILED");
        // We're done processing, so there is no current value
       
       delay(10);
        if(result1 == user1)
        {
              
              Serial.println(" : User-1 detected ");
              Serial.print(" : Your balance is:  "); // add bill code
              Serial.println(balance);
        }
       
    tagfound1 = false;
    }

 Serial.flush();
 }


 uint8_t rfid_get_next1(void)
{
    // sscanf needs a 2-byte space to put the result but we
    // only need one byte.
    uint16_t hexresult1;
    // Working space to assemble each byte
    static char byte_chars1[3];
    // Pull out one byte from this position in the stream
    snprintf(byte_chars1,3,"%c%c",buffer_at1[0],buffer_at1[1]);
    sscanf(byte_chars1,"%x",&hexresult1);
    buffer_at1 += 2;
    return static_cast<uint8_t>(hexresult1);
}
