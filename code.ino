#include <Adafruit_LiquidCrystal.h>

// int seconds = 0;
int analogPin = A3;
int analogPin_2 = A2;

int duty_decrement = 930;
int Fstep = 930;

int duty_increment = 852;
int duty_step = 852;

int frequency_decrement = 787;
int present = 787;

int frequency_increment = 731;

int glob_frequency = 1;
int glob_duty = 1;

int glob_analaog_1 = 0;
int glob_analaog_2 = 0;

int softMargin = 20;

int frequency_steps[5] = {1, 10, 100, 1000, 10000};
int duty_steps[3] = {1, 5, 10};

Adafruit_LiquidCrystal lcd_1(0);
void incrementer(int input, int *parameter_match, int *to_beChanged, int to_be_add);
void setup()
{
    lcd_1.begin(16, 2);

    lcd_1.setBacklight(1);
    lcd_1.print("PROMAX by H2G");
    delay(5000);
    lcd_1.setCursor(0, 0);
    lcd_1.print("Default setting : ");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Freq:" + String(glob_frequency) + "Hz" + " Duty:" + String(glob_duty) + "%");
    delay(3000);
    // lcd_1.clear();
}

void loop()
{

    // if (analogRead(analogPin) > 100 || analogRead(analogPin_2) > 100)
    // {
        if (glob_analaog_1 != analogRead(analogPin) || glob_analaog_2 != analogRead(analogPin_2))
        {
            // lcd_1.clear();
            // lcd_1.setCursor(0, 0);
            // lcd_1.print("Setting changed ");
            glob_analaog_1 = analogRead(analogPin);
            glob_analaog_2 = analogRead(analogPin_2);
            // lcd_1.setCursor(0, 1);
            // lcd_1.print(glob_analaog_1);
            // lcd_1.setCursor(5, 1);
            // lcd_1.print(glob_analaog_2);
            incrementer(glob_analaog_1, &frequency_increment, &glob_frequency, 1);
            incrementer(glob_analaog_1, &frequency_decrement, &glob_frequency, -1);
            incrementer(glob_analaog_1, &duty_increment, &glob_duty, 1);
            incrementer(glob_analaog_1, &duty_decrement, &glob_duty, -1);
        }
    // }

    delay(500); // Wait for 500 millisecond(s)
    // lcd_1.setBacklight(0);
    // delay(500); // Wait for 500 millisecond(s)
    // seconds += 1;
}
void incrementer(int input, int *parameter_match, int *to_beChanged, int to_be_add)
{
    if ((input >= (*parameter_match - softMargin) && input <= (*parameter_match + softMargin)))
    {
        *to_beChanged += to_be_add;
        lcd_1.setCursor(0, 1);
        lcd_1.print("Fr :" + String(glob_frequency) + "Hz" + " D : " + String(glob_duty) + "%  ");
        delay(100);
    }
}