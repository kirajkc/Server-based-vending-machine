#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>

WiFiClient client;

const char* server= "  192.168.43.33";
const char* ssid = "A";
const char* password ="01010101";
/*------------------------------Send to Server---------------------------------*/
String item[3];
int tagid[3];
int quantity[3];
int price[3];
int remain[3];
int rate[3];

String itemm[2];
int tagidd[2];
int quantityy[2];
int pricee[2];
int alert =0;

String readString;
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {Serial.print('.');
    delay(200);
  }
  Serial.print("Coonn");
  Serial.flush();
}

// the loop function runs over and over again forever
void loop() {
  
             
               Getting_From_phpmyadmindatabse(); 

              
             alert =0;
             for(int i=0;i<2;i++){
                if(itemm[i] != NULL){
                if(quantityy[i] < 2){
                  alert =2;
                  }
                  Serial.print("1");
                 Alert_To_phpmyadmindatabase(alert); 
                }
             }   
             Serial.flush();
  ////////////////////////////////
             while(!Serial.available()){
              delay(5000);
              }
             if(Serial.available()){ 
               getting_from_due();
               for(int i=0;i<2;i++){
    if(item[i] != NULL){
    Serial.print(tagid[i]);
    Serial.print(item[i]);
    Serial.print(quantity[i]);
    Serial.println(price[i]);
    Serial.println(remain[i]);
     Sending_To_phpmyadmindatabase();
     Update_To_phpmyadmindatabase(); 
    }
    }   
  }


}

/*-------------------------------------------------------Sending data to database-----------------------------------------------------------------*/
 void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
  for(int i=0;i<5;i++){
   if(item[i] != NULL){
   if (client.connect(server, 8080)) {
   Serial.println("connected");
    // Make a HTTP request:
   Serial.println("GET /testcode/sold1.php?tagid=");
   client.print("GET /testcode/sold1.php?tagid=");     //YOUR URL
    Serial.println(tagid[i]);
    client.print(tagid[i]);
    
    client.print("&item=");
    Serial.println("&item=");
    client.print(item[i]);
    Serial.println(item[i]);

    client.print("&quantity=");
    Serial.println("&quantity=");
    client.print(quantity[i]);
    Serial.println(quantity[i]);

    client.print("&price=");
    Serial.println("&price=");
    client.print(price[i]);
    Serial.println(price[i]);
    
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host:   192.168.43.33");
    client.println("Connection: close");
    client.println();
    
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  client.stop();
  }
  }
}
/*-----------------------------------------------Updating item table/server---------------------------------------*/
void Update_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
  for(int i=0;i<5;i++){
   if(item[i] != NULL){
   if (client.connect(server, 8080)) {
   Serial.println("connected");
    // Make a HTTP request:
   Serial.println("GET /testcode/vend1.php?tagid=");
   client.print("GET /testcode/vend1.php?tagid=");     //YOUR URL
    Serial.println(tagid[i]);
    client.print(tagid[i]);
    
    client.print("&item=");
    Serial.println("&item=");
    client.print(item[i]);
    Serial.println(item[i]);

    client.print("&quantity=");
    Serial.println("&quantity=");
    client.print(remain[i]);
    Serial.println(remain[i]);

    client.print("&price=");
    Serial.println("&price=");
    client.print(rate[i]);
    Serial.println(rate[i]);
    
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host:   192.168.43.33");
    client.println("Connection: close");
    client.println();
    
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  client.stop();
  }
  }
}


 /*--------------------------------------------Read From Due----------------------------*/
 void getting_from_due(){
  int p=0;
  int w=1;
  int a=0;
  for(int i=0;i<10;i++){
     while (!Serial.available()) {
     delay(1000) ;
     break;//delay(1000); // wait for serial port to connect. Needed for native USB port only
  }
  while (Serial.available()) {
top:  String ch = Serial.readStringUntil('@'); 
      if(p==0){
              p++;
          goto top;
           
        }
        if (ch == NULL){
          goto top;
          }
     if (ch != NULL){
      if(w>6){
        a++;
        w=1;
        }
     }
    Serial.println(ch);
    Serial.println("----");
    switch (w){
      case 1:
             tagid[a] = ch.toInt();
             w++;
             break;
      case 2:
              item[a] = ch;
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
      case 5:
             remain[a] = ch.toInt();
              w++;
             break;
      case 6:
             rate[a] = ch.toInt();
              w++;
             break;
             
    }
  }
  }
Serial.println("...........");

  //  Serial.flush();
}
/*-----------------------------------------------------------------------------------------*/
/*-------------------------------------------------------Getting data From database-----------------------------------------------------------------*/
void Getting_From_phpmyadmindatabse(){
  if (client.connect(server, 8080)) {
    client.print("GET /testcode/read.php?");     //YOUR URL
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host:  192.168.43.33");
    client.println("Connection: close");
    client.println();
    
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  int i =0 ;
    int c=0;
    int a=0;
    int q=1;
  while (client.available()) {
        String ch = client.readStringUntil('@');
        i++;
        if(i>1){
        
          if (c>=4){
            c=0;
            q=1;
            a++;
          }
          Serial.print("@");
          Serial.println(ch);
          switch (q){
            case 1:
                   itemm[a] = ch;
                   break;
            case 2:
                   tagidd[a] = ch.toInt();
                   break;
            case 3:
                   quantityy[a] = ch.toInt();
                   break;
            case 4:
                   pricee[a] = ch.toInt();
                   break;
            
            }
          c++;
          q++;
           }
       }
       client.stop();
 }
/*-----------------------------------------------Alert/server---------------------------------------*/
void Alert_To_phpmyadmindatabase(int alert)   //CONNECTING WITH MYSQL
 {
  for(int i=0;i<5;i++){
   if(item[i] != NULL){
   if (client.connect(server, 8080)) {
  // Serial.println("connected");
    // Make a HTTP request:
 //  Serial.println("GET /testcode/alert.php?value=");
   client.print("GET /testcode/alert.php?value=");     //YOUR URL
   // Serial.println(alert);
    client.print(alert);
    
    
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host:  192.168.43.33");
    client.println("Connection: close");
    client.println();
    
  } 
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  client.stop();
  }
  }
}
