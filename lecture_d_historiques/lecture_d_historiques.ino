#include <SPI.h>
#include <Ethernet2.h>
#include <PubNub.h>
// Prendre l'adresse MAC indiquée sur la carte ou prendre
// une adresse MAC arbitraire (voir l'enseignant)
byte mac[] = { 0x90, 0xA2, 0xDA, 0x11, 0x00, 0x36 };
// Mettre vos clés, ne pas utiliser celles-ci
char pubkey[] = "";
char subkey[] = "";
char channel[] = "ChannelMTI10";
void setup()
{
Serial.begin(9600);
while (!Ethernet.begin(mac))
{
Serial.println("Ethernet setup error");
delay(1000);
}
Serial.println("Parametrage d'Ethernet");
PubNub.begin(pubkey, subkey);
Serial.println("Parametrage de PubNub");
 EthernetClient *client;
 Serial.println("Recuperation des messages stockés");
 client=PubNub.history(channel);
 if(!client){
 Serial.println("history error");
 delay(1000);
 return;
 }
 while(client->connected()){
 while(client->connected() && !client->available());
 char c=client->read();
 Serial.print(c);
 if(c=='}')
 Serial.println();
 }
 client->stop();
 Serial.println();
}
void loop()
{
}

