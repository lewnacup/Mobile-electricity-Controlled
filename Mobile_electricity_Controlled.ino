#define BLYNK_TEMPLATE_ID "ENTER_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "ENTER_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN "ENTER_AUTH_TOKEN"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "ชื่อไวไฟ";
char pass[] = "รหัสไวไฟ";
BlynkTimer timer;
#define button_pin 12
#define relay_pin 13
int relay_state = 0;
#define button_vpin V1
BLYNK_CONNECTED() {
Blynk.syncVirtual(button_vpin);
}
//--------------------------------------------------------------------------
BLYNK_WRITE(button_vpin) {
relay_state = param.asInt();
digitalWrite(relay_pin, relay_state);
}
//--------------------------------------------------------------------------
void setup()
{
// Debug console
Serial.begin(115200);
//--------------------------------------------------------------------
pinMode(button_pin, INPUT_PULLUP);
//--------------------------------------------------------------------
pinMode(relay_pin, OUTPUT);
//--------------------------------------------------------------------
digitalWrite(relay_pin, HIGH);
//--------------------------------------------------------------------
Blynk.begin(auth, ssid, pass);
//--------------------------------------------------------------------
}
void loop()
{
Blynk.run();
timer.run();
listen_push_button();
}
void listen_push_button(){
//--------------------------------------------------------------------------
if(digitalRead(button_pin) == LOW){
delay(200);
control_relay();
Blynk.virtualWrite(button_vpin, relay_state);
}
//--------------------------------------------------------------------------
}
void control_relay(){
relay_state = !relay_state;
digitalWrite(relay_pin, relay_state);
Serial.print("Relay State = ");
Serial.println(relay_state);
delay(50);
}
