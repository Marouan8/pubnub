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
//Initialisation du moniteur série
Serial.begin(9600);
//Initialisation d'Internet
while (!Ethernet.begin(mac))
{
Serial.println("Ethernet setup error");
delay(1000);
}
Serial.println("Parametrage d'Ethernet");
//Initialisation de Pubnub
PubNub.begin(pubkey, subkey);
Serial.println("Parametrage de PubNub");
}
void loop()
{
//Ethernet.maintain();//Demande au serveur DHCP de maintenir l'adresse IP
EthernetClient *client;
Serial.println("Publication d'un Message");
client = PubNub.publish(channel, "{\"BONJOUR\": \"Je suis BENBAZZA\"}");
if (!client) {
Serial.println("publishing error");
delay(1000);
return;
}
// Récupération de la chaine de retour de la plateforme PubNub
while (client->connected()) {
while (client->connected() && !client->available()) ; // wait
char c = client->read();
Serial.print(c);
}
client->stop();
Serial.println();
delay(10000);
}

