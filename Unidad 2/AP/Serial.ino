void setup(){
    Serial.begin(115200);
    Serial.println("Hola Bienvenido");
}

void loop(){
    if(Serial.available()){
        String data = Serial.readStringUntil('\n');
        if(data == '+')
        {
            //por hacer
        } 
        else if (data == '-')
        {
            /* code */
        }
        else {
            Serial.println("Invalid Command");
        }
        
    }
}