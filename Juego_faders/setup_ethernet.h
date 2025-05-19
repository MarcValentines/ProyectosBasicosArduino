IPAddress myIp(10, 16, 3, 12); //modificar ip (último número)
//destination IP
IPAddress outIp(10, 16, 3, 2);
EthernetUDP Udp;

 byte mac[] = {  //modificar
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x02 }; // you can find this written on the board of some Arduino Ethernets or shields

//port numbers
const unsigned int outPort = 6006;
const unsigned int inPort = 6007;

void setup_ethernet() {
// start the Ethernet connection:
  Serial.println("Initialize Ethernet...:");
  Ethernet.begin(mac, myIp);
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
  } else if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  
  Udp.begin(inPort);
}
