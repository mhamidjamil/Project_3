#include <Adafruit_LiquidCrystal.h>

// int seconds = 0;
int analogPin = A3;
int analogPin_2 = A2;

int output_pin_1 = 3;
int output_pin_2 = 11;
// resistros values setting (start)
//---------------------------------
int duty_decrement = 930;
int Fstep = 930;

int duty_increment = 852;
int duty_step = 852;

int frequency_decrement = 787;
int present = 787;

int frequency_increment = 731;
//---------------------------------
// resistros values setting (end)

int glob_frequency = 1;
int glob_duty = 1;

int glob_analaog_1 = 0;
int glob_analaog_2 = 0;

int softMargin = 20;

int freq_index = 0;
int duty_index = 0;
bool in_flow = false;

int frequency_steps[5] = {1, 10, 100, 1000, 10000};
int duty_steps[3] = {1, 5, 10};

Adafruit_LiquidCrystal lcd_1(0);
void incrementer(int input, int *parameter_match, int *to_beChanged, int to_be_add);
void setup()
{
    pinMode(output_pin_1, OUTPUT);
    pinMode(output_pin_2, OUTPUT);
    lcd_1.begin(16, 2);

    lcd_1.setBacklight(1);
    lcd_1.print("PROMAX by H2G");
    delay(500);
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
        if ((glob_analaog_2 >= (Fstep - softMargin) && glob_analaog_2 <= (Fstep + softMargin)))
        {
            if (freq_index < 5)
            {
                glob_frequency = frequency_steps[freq_index];
                freq_index++;
            }
            else if (freq_index >= 5)
            {
                freq_index = 0;
                glob_frequency = frequency_steps[freq_index];
                freq_index++;
            }
            lcd_1.setCursor(0, 1);
            delay(100);
        }
        else if ((glob_analaog_2 >= (duty_step - softMargin) && glob_analaog_2 <= (duty_step + softMargin)))
        {
            if (duty_index < 3)
            {
                glob_duty = duty_steps[duty_index];
                duty_index++;
            }
            else if (duty_index >= 3)
            {
                duty_index = 0;
                glob_duty = duty_steps[duty_index];
                duty_index++;
            }
            lcd_1.setCursor(0, 1);
            // lcd_1.print("Frq :" + String(glob_frequency) + "Hz" + " D : " + String(glob_duty) + "%  ");
            delay(100);
        }
        else if ((glob_analaog_2 >= (present - softMargin) && glob_analaog_2 <= (present + softMargin)))
        {
            glob_duty = 50;
            glob_frequency = 1000;
            delay(10);
            // lcd_1.setCursor(0, 1);
            // lcd_1.print("Fr:" + String(glob_frequency) + "Hz" + " D:" + String(glob_duty) + "%    ");
        }
    }
    if (!in_flow)
    {
        lcd_1.setCursor(0, 1);
        lcd_1.print("                 ");
        in_flow = true;
    }
    lcd_1.setCursor(0, 1);
    lcd_1.print("Fr:" + String(glob_frequency) + "Hz" + " D:" + String(glob_duty) + "%      ");
    
}
void incrementer(int input, int *parameter_match, int *to_beChanged, int to_be_add)
{
    if ((input >= (*parameter_match - softMargin) && input <= (*parameter_match + softMargin)))
    {
        *to_beChanged += to_be_add;
        if (!in_flow)
        {
            lcd_1.setCursor(0, 1);
            lcd_1.print("                 ");
            in_flow = true;
        }
        lcd_1.setCursor(0, 1);
        lcd_1.print("Fr:" + String(glob_frequency) + "Hz" + " D:" + String(glob_duty) + "%      ");
        delay(100);
    }
}