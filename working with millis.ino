#define INTERVAL_MESSAGE1 5000
#define INTERVAL_MESSAGE2 7000
#define INTERVAL_MESSAGE3 11000
#define INTERVAL_MESSAGE4 13000
 
unsigned long time_1 = 0;
unsigned long time_2 = 0;
unsigned long time_3 = 0;
unsigned long time_4 = 0;
 
 
void setup() {
    Serial.begin(115200);
}
 
void loop() {
    if(millis() >= time_1 + INTERVAL_MESSAGE1){
        time_1 =millis();
        Serial.print("time=");
        Serial.print(time_1);
      	Serial.print("  ");
        Serial.println("I'm message number one!");
    }
  
    if(millis() >= time_2 + INTERVAL_MESSAGE2){
        time_2 =millis();
      	Serial.print("time=");
        Serial.print(time_2);
      	Serial.print("  ");
        Serial.println("Hello, I'm the second message.");
    }
   
    if(millis() >= time_3 + INTERVAL_MESSAGE3){
        time_3 =millis();
      	Serial.print("time=");
        Serial.print(time_3);
      	Serial.print("  ");
        Serial.println("My name is Message the third.");
    }
   
    if(millis() >= time_4 + INTERVAL_MESSAGE4){
        time_4 = millis();
      	Serial.print("time=");
        Serial.print(time_4);
      	Serial.print("  ");
        Serial.println("Message four is in the house!");
    }
}

 