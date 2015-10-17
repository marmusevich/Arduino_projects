#include <LiquidCrystal.h>
#include "pitches.h"
#include <DHT.h>
#include <DS1302.h> // Подключение библиотеки часов.
#include <cstdio>

// Инициализация пинов часов
DS1302 rtc(3, 1, 0);


// DHT
#define DHTTYPE DHT11
DHT dht(2,DHTTYPE);


// LCD
LiquidCrystal  lcd (8,9,4,5,6,7);
//Key message
char msgs[5][15] = {"Right Key OK ",
                    "Up Key OK    ",
                    "Down Key OK  ",
                    "Left Key OK  ",
                    "Select Key OK"
                   };
int  adc_key_val[5] = {30, 150, 360, 535, 760 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;


// Musik
int melody[] = { NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4 };
int noteDurations[] = { 4, 8, 8, 4,4,4,4,4 };
int musikPin = 12;

void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
/*
    lcd.write("ARDUINO-UA.COM");
    lcd.setCursor(0,2);
    lcd.write("press a key");
    delay(1000);
    lcd.setCursor(0,2);
    lcd.write("            ");
*/

   // lcd.cursor();
   // lcd.blink();
	
	// Запуск часов
	rtc.halt(false);
	rtc.writeProtect(false);	

    // Три нижние строчки в первый раз раскомментированы, в них указываем текущую дату и время. Второй раз - закомментруем.
    //rtc.setDOW(SATURDAY); // День недели, если пятница, то FRIDAY на русском не писать!
    //rtc.setTime(17, 07, 0); // Часы, минуты, секунды 24-часовой формат.
    //rtc.setDate(24, 1, 2015); // Дата. ЦИФРАМИ!!! Ноль перед одиночной цифрой можно не ставить!
 

    dht.begin();
    
}
void loop()
{
 

  
	// Display time centered on the upper line
	lcd.setCursor(0, 0); // Устанавливаем курсор для печати времени в верхней строчке
	lcd.print(rtc.getTimeStr()); // Печатаем время

	// Display abbreviated Day-of-Week in the lower left corner
	lcd.setCursor(0, 1); // Устанавливаем курсор слева внизу для печати дня недели
	lcd.print(rtc.getDOWStr(FORMAT_SHORT)); // Печатаем день недели полностью, благо экран позволяет.
	lcd.print("  "); 
	lcd.print(rtc.getDateStr()); // Печатаем дату

	delay (2000); 
	lcd.clear();
	
	
	float h = dht.readHumidity();
        float t = dht.readTemperature();
	
	if( !(isnan(t) || isnan(h)) )
	{
          lcd.setCursor(0,0);  //line=2, x=0
  	  lcd.print("T = ");
          lcd.print( t, DEC);
  	  lcd.setCursor(0,2);  //line=2, x=0
          lcd.print("H = ");
          lcd.print( h, DEC );
	}

	delay (2000);
	lcd.clear();


/*   
   float h = dht.readHumidity();
    float t = dht.readTemperature();

    adc_key_in = analogRead(0);    // читаем значение из аналогового входа
    key = get_key(adc_key_in); // конвертируем в нажатие кнопки
    if (key != oldkey)     // если книпка нажата
    {
        delay(50);		// ждем чтоб устранить дребезг
        adc_key_in = analogRead(0);  //читаем значение из аналогового входа
        key = get_key(adc_key_in);	// конвертируем в нажатие кнопки
        if (key != oldkey)
        {
            oldkey = key;
            if (key >=0)
            {
                lcd.setCursor(0,2);  //line=2, x=0
                lcd.write(msgs[key]);
            }

            if(key == 4)
                playMusic();

            if(key == 1)
            {
                lcd.setCursor(0,2);  //line=2, x=0
                if (!isnan(t))
                {
                    lcd.print("Temperature: ");
                    lcd.print( t, DEC);
                }    
            }

            if(key == 2)
            {
                lcd.setCursor(0,2);  //line=2, x=0
                if (!isnan(h))
                {
                    lcd.print("Humidity: ");
                    lcd.print( h, DEC );
                }
            }
        }
    }
*/    
}

// конвертируем аналоговое значение в код кнопки
int get_key(unsigned int input)
{
    int k;
    for (k = 0; k < NUM_KEYS; k++)
    {
        if (input < adc_key_val[k])
            return k;
    }
    if (k >= NUM_KEYS)
        k = -1;     // пришло некорректное значение
    return k;
}

void playMusic()
{
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {
        int noteDuration = 1000/noteDurations[thisNote];
        tone(musikPin, melody[thisNote],noteDuration);
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(musikPin);
    }
}
