#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SPI.h>    
#include <OSCMessage.h>
#include <OSCBundle.h>

#include "setup_ethernet.h"

#define ON HIGH
#define OFF LOW

//definición de los pines de los faders´
#define CANT_FADERS 6
#define FADER_1 A0
#define FADER_2 A1
#define FADER_3 A2
#define FADER_4 A3
#define FADER_5 A4
#define FADER_6 A5
//rangos
const unsigned int rangoMin[CANT_FADERS] = {500, 200, 350, 100, 600, 400};
const unsigned int rangoMax[CANT_FADERS] = {530, 230, 380, 130, 630, 430};

//delay sin detener la placa


const unsigned int GameNumber = 11;
bool gameRunning = false;

const unsigned int reles[2] = {2,3};

String start_str;
const char * start_routename;

String end_str;
const char * end_routename;
String reset_str;
const char * reset_routename;
String rele_str;
String door_str;
const char * door_routename;

String door_all_str;
const char * door_all_routename;

void setup() {
  //reles
  pinMode(reles[0], OUTPUT);
  pinMode(reles[1], OUTPUT);

  //faders
  pinMode(FADER_1, INPUT);
  pinMode(FADER_2, INPUT);
  pinMode(FADER_3, INPUT);
  pinMode(FADER_4, INPUT);
  pinMode(FADER_5, INPUT);

  Serial.begin(9600);
  while (!Serial) {
  ;  // wait for serial port to connect. Needed for native USB port only
  }

  setup_ethernet();

  start_str = "/game/" + String(GameNumber) + "/start";
  start_routename = start_str.c_str();

  end_str = "/game/" + String(GameNumber) + "/end";
  end_routename = end_str.c_str();

  reset_str = "/game/all/reset";
  reset_routename = reset_str.c_str();

  door_str = "/game/" + String(GameNumber) + "/door";
  door_routename = door_str.c_str();

  door_all_str = "/game/all/door";
  door_all_routename = door_all_str.c_str();
    
}

void loop() {


  OSCMessage messageIN;
  int size;
  
  if( (size = Udp.parsePacket())>0){
    while(size--)
      messageIN.fill(Udp.read());

    if(messageIN.hasError()){
      Serial.println("OSC message has error");
    }
      
    messageIN.route(start_routename, routeStart);
    messageIN.route(end_routename, routeEnd);
    messageIN.route(reset_routename, routeReset);
    messageIN.route(door_routename, route_door);
    messageIN.route(door_all_routename, route_all_door);

  }

  if (gameRunning) {
    //lógica juego
    if (check_card(0) && check_card(1) && check_card(2) && check_card(3) && check_card(4) && check_card(5)) { //comprobación similar (modificar)
      Serial.print("game DONE!!!");
      sendresult(1);
      gameRunning = false;
    }
  }


        
}

void routeStart(OSCMessage &msg, int addrOffset ){
  Serial.println("Starting");
  gameRunning = true;
}

void routeEnd(OSCMessage &msg, int addrOffset ){
  Serial.println("Ending");
  gameRunning = false;
}
void routeReset(OSCMessage &msg, int addrOffset ){
  Serial.println("Reseting");
  gameRunning = false;
}

void route_door(OSCMessage &msg, int addrOffset ){
  if (msg.isInt(0)){
    if (msg.getInt(0)== 0){
      digitalWrite(reles[0], OFF);
      sendoor(msg.getInt(0));
      Serial.println("puerta off");
    } else if (msg.getInt(0)== 1) {
      digitalWrite(reles[0], ON);
      sendoor(msg.getInt(0));
      Serial.println("puerta on");
    }
  }

}

void route_all_door(OSCMessage &msg, int addrOffset ){
  if (msg.isInt(0)){
    if (msg.getInt(0)== 0){
      digitalWrite(reles[0], OFF);
      sendoor(msg.getInt(0));
      Serial.println("puerta off");
    } else if (msg.getInt(0)== 1) {
      digitalWrite(reles[0], ON);
      sendoor(msg.getInt(0));
      Serial.println("puerta on");
    }
  }

}

void sendresult(int result) {
  //the message wants an OSC address as first argument
  String result_str;
  result_str = "/game/" + String(GameNumber) + "/done";
  const char * result_routename = result_str.c_str();
  
  OSCMessage msg(result_routename);
  msg.add(result);
  
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message
}

void sendreset(int result) {
  //the message wants an OSC address as first argument
  String result_str;
  result_str = "/game/" + String(GameNumber) + "/reset";
  const char * result_routename = result_str.c_str();
  
  OSCMessage msg(result_routename);
  msg.add(result);
  
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message
}
void sendoor(int result) {
  //the message wants an OSC address as first argument
  String result_str;
  result_str = "/game/" + String(GameNumber) + "/door";
  const char * result_routename = result_str.c_str();
  
  OSCMessage msg(result_routename);
  msg.add(result);
  
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message
}
void sendrele(int result) {
  //the message wants an OSC address as first argument
  String result_str;
  result_str = "/game/" + String(GameNumber) + "/rele";
  const char * result_routename = result_str.c_str();
  
  OSCMessage msg(result_routename);
  msg.add(result);
  
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message
}