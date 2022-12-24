#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
 #include <ESPAsyncTCP.h>
#include <LedControl.h>
#include <WebSocketsServer.h>

int DIN = 16; // D0
int CS =  5;  // D1
int CLK = 4;  // D2

  byte zero[8] = {0x3c,0x7e,0xc3,0xc3,0xc3,0xc3,0x7e,0x3c} ; 
    byte one[8] = {0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x3c};     
    byte two[8] = {0xfc,0xfc,0x0c,0x18,0x30,0x60,0x7e,0x7e} ;  
    byte three[8] ={0x7c,0x7c,0x04,0x18,0x18,0x0c,0x7c,0x7c};  
    byte four[8] = {0x60,0x60,0x60,0x6c,0x6c,0x7e,0x7e,0x0c};    
    byte five[8] = {0x3e,0x3e,0x30,0x3c,0x0c,0x0c,0x7c,0x7c};  
    byte six[8] = {0x06,0x0c,0x18,0x30,0x78,0x44,0x44,0x7c}; 
    byte seven[8] = {0x7f,0x7f,0x0e,0x1c,0x38,0x70,0xe0,0xc0}; 
    byte eight[8] ={0x7e,0xc3,0xc3d,0xfe,0x7e,0xc3,0xc3,0x7e};     
    byte nine[8] = {0x7f,0x43,0x43,0x7f,0x3f,0x03,0x7f,0x7f};
    byte angry[8]={0x3c,0x42,0xa5,0xa5,0x81,0xbd,0x42,0x3c};
LedControl lc=LedControl(DIN,CLK,CS,0);

WebSocketsServer websockets(81);
AsyncWebServer server(80); // server port 80


void printByte(byte character []){
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
};
void counter(){
    printByte(zero);
    delay(1000);
   printByte(one);
    delay(1000);
    printByte(two);
    delay(1000);
    printByte(three);
    delay(1000);
     printByte(four);
    delay(1000);
    printByte(five);
    delay(1000);
    printByte(six);
    delay(1000);
     printByte(seven);
    delay(1000);
    printByte(eight);
    delay(1000);
    printByte(nine); 
    delay(1000);
}
void digits(int num){
while(num!=0){
  int last=num%10;
  switch(last){
    case 0:printByte( zero); delay(1000); break;
    case 1:printByte( one); delay(1000); break;
    case 2:printByte(two); delay(1000); break;
    case 3:printByte(three); delay(1000); break;
    case 4:printByte(four); delay(1000); break;
    case 5:printByte(five); delay(1000); break;
    case 6:printByte(six); delay(1000); break;
    case 7:printByte(seven); delay(1000); break;
    case 8:printByte(eight); delay(1000); break;
    case 9:printByte(nine); delay(1000); break;
   default: Serial.print("error");
   }
  num=num/10;
  }
}
//void Stringdigit(String num){
// for(int i=0;i<num.length();i++){
//   if(strcmp(num[i],'0')==0){
//    printByte(zero);
//    delay(1000);
//    break;
//   }
//   else if(strcmp(num[i],'1')==0){
//    printByte(one);
//    delay(1000);
//    break;
//   }
//    else if(strcmp(num[i],"2")==0){
//    printByte(two);
//    delay(1000);
//    break;
//   } else if(strcmp(num[i],"3")==0){
//    printByte(three);
//    delay(1000);
//    break;
//   } else if(strcmp(num[i],"4")==0){
//    printByte(four);
//    delay(1000);
//    break;
//   } else if(strcmp(num[i],"5")==0){
//    printByte(five);
//    delay(1000);
//    break;
//   } else if(strcmp(num[i],"6")==0){
//    printByte(six);
//    delay(1000);
//    break;
//   } else if(strcmp(num[i],"7")==0){
//    printByte(seven);
//    delay(1000);
//    break;
//   } else if(strcmp(num[i],"8")==0){
//    printByte(eight);
//    delay(1000);
//    break;
//   } else if(strcmp(num[i],"9")==0){
//    printByte(nine);
//    delay(1000);
//    break;
//   }
//   }
 


 const char* input_parameter1="integerInput";

 
char webpage[] PROGMEM = R"=====(
 <!DOCTYPE html>
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
       h3{
        color:azure;
        font-size: 30px;
        margin-bottom:25px;  
        background-color:#1A1918;
        border:1px solid white;
        opacity: 0.9;
       } 
     *{margin: 0;
        padding: 0;
        box-sizing: border-box;}
     .input{ padding: 10px 20px;
         display: flex;}
     #put{font-size: 15px;
        border-top-left-radius:30px;
        border-bottom-left-radius:30px;
        flex-grow: 1;
        padding: 15px;
        margin-right: 10px;}
          #btn{background-color: orange;
            padding: 20px;
            border-top-right-radius:30px;
           border-bottom-right-radius:30px;}
          #btn:hover{padding-right: 40px;
            background-color: green;
            color: aliceblue;
            background-color: orange;}
     body{display: flex;
        justify-content: center;
        height: 100vh;
        text-align: center;
        align-items: center;
        //background:url('https://images.unsplash.com/photo-1597851065532-055f97d12e47?ixlib=rb-4.0.3&ixid=MnwxMjA3fDB8MHxwaG90by1wYWdlfHx8fGVufDB8fHx8&auto=format&fit=crop&w=2070&q=80')no-repeat center center/ cover
        background: linear-gradient(#e66465, #9198e5);
        }
     .cont2{ border-radius: 20px;
        height: 160px;
        width: 400px;
    background-color: #242221;
    opacity: 0.9;}
     #counter{
        margin-top: 20px;
       padding:20px;
       border-radius: 10px;
       color:white;
       background-color: green;}
     #counter:hover{
        background-color: white;
        color:green;}
    </style>
</head>
<body>
<div class="container">
    <h3>ledControl project</h3>
    <div class="cont2">
    <form id="form">
        <input type="number" id="put" placeholder="enter a number" value="name"  >
        <input type="button" onclick="getDate()" id="btn" value="submit"/> 
        </form>
    <div>
        <input type="button" onclick=counter() id="counter" value="counter"/> 
    </div>
</div>
</div>
<script>
    var connection =new WebSocket('ws://'+location.hostname+':81/');

    function counter(){
       connection.send("counter")
    }
     function getDate(){
        let number=document.getElementById('put');
        console.log(number.value);
        connection.send(number.value.toString().split("").reverse().join(""));
        number.value="";
    }
</script>
</body>
</html>
)=====";



void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}




void webSocketEvent(uint8_t num,WStype_t type, uint8_t * payload, size_t length) {

  switch (type) 
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        websockets.sendTXT(num, "Connected from server");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      String message = String((char*)( payload));
      Serial.println(message);

      if(message == "counter"){
        counter();
      }
             
 for(int i=0;i<message.length();i++){
      if(isDigit(message.charAt(i))){
      digits(message[i]);
      }
     
  }
}
}



void setup(){
   Serial.begin(115200);
  
  WiFi.softAP("yahiahamdan", "");
  Serial.println("softap");

  Serial.println("");
  Serial.println(WiFi.softAPIP());

 server.on("/", [](AsyncWebServerRequest * request)
  {  
  request->send_P(200, "text/html", webpage);
  });
   server.on("/counter/on",[](AsyncWebServerRequest * request)
  { 
       String message="its the counter page";
  request->send_P(200, "text/html",webpage );
     //counter();
      
  });
   server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String input_message;
    String input_parameter;


if (request->hasParam(input_parameter1)) {
 // const char* input_parameter1=integerInput;
      input_message = request->getParam(input_parameter1)->value();
      input_parameter = input_parameter1;
      digits(input_message.toInt());
    }
    else {
      input_message = "No message sent";
      input_parameter = "none";
    }
     request->send(200, "text/html", webpage);
   Serial.println(input_message);
  });
   
  server.onNotFound(notFound);
  server.begin();  // it will start webserver

 websockets.begin();
  websockets.onEvent(webSocketEvent);

  lc.shutdown(0,false);     //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0,7);     // Set the brightness to maximum value
  lc.clearDisplay(0);        // and clear the display
}

int num=1506588;
void loop() {

 websockets.loop();
}
