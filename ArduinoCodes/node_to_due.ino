#include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266HTTPClient.h>

WiFiClient client;

const char* server= "192.168.0.107";
const char* ssid = "HiddenNetwork";
const char* password ="k3c3ngin33rs";
/*--------------------------Send To DUE-------------------------------*/
String item[2];
int tagid[2];
int quantity[2];
int price[2];

int alert;
String readString;
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
  }
}

// the loop function runs over and over again forever
void loop() {
             while(!Serial.available()){
              ;
              }
              char ch = Serial.read();
             if(ch == '#'){ 
               Getting_From_phpmyadmindatabse(); 
               ch = '&';
             }
              
             alert =0;
             for(int i=0;i<2;i++){
                if(item[i] != NULL){
                if(quantity[i] < 2){
                  alert =2;
                  }
                 Alert_To_phpmyadmindatabase(); 
                }
             }   
}
/*-------------------------------------------------------Getting data From database-----------------------------------------------------------------*/
void Getting_From_phpmyadmindatabse(){
  if (client.connect(server, 8080)) {
    client.print("GET /testcode/read.php?");     //YOUR URL
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.0.107");
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
                   item[a] = ch;
                   break;
            case 2:
                   tagid[a] = ch.toInt();
                   break;
            case 3:
                   quantity[a] = ch.toInt();
                   break;
            case 4:
                   price[a] = ch.toInt();
                   break;
            
            }
          c++;
          q++;
           }
       }
       client.stop();
 }
/*-----------------------------------------------Alert/server---------------------------------------*/
void Alert_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
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
    client.println("Host: 192.168.0.107");
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
