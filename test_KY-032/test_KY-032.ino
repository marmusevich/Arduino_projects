#define  avoidPin  A1 // задаем имя для порта с датчиком
#define  ledPin  13     // задаем имя для порта со светодиодом

int  avoid;

void setup() {
   Serial.begin(9600);  // инициализация монитора порта

   pinMode(avoidPin, INPUT);
   pinMode(ledPin, OUTPUT);
}

void loop() {

   avoid = digitalRead(avoidPin);  // получаем данные с датчика препятствий

   Serial.print("Avoid Sensor - ");  // выводим данные с датчика на монитор
   Serial.println(avoid);

   if (avoid == HIGH)
      digitalWrite(ledPin, HIGH);
   else
      digitalWrite(ledPin, LOW);


delay(300);      
}
