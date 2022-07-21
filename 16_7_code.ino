#include <Adafruit_LiquidCrystal.h>

// int seconds = 0;
int deadZone = 0;
bool button_status_changed = false;
int analogPin = A3;
int analogPin_2 = A2;

int output_pin_1 = 3;
int output_pin_2 = 10;

int output_1 = 0;
int output_2 = 0;
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

int glob_frequency = 3500;
int glob_duty = 50;

int glob_analaog_1 = 0;
int glob_analaog_2 = 0;

int softMargin = 20;

int freq_index = 0;
int duty_index = 0;

int frequency_steps[5] = {1, 10, 100, 1000, 10000};
int duty_steps[3] = {1, 5, 10};

void display_line_2();
Adafruit_LiquidCrystal lcd_1(0);
void incrementer(int input, int *parameter_match, int *to_beChanged, int to_be_add);
void setup()
{
    TCCR1A = (TCCR1A & 0x0F) | 0xB0; // set pin 10 inverted
    int deadZone = 2;
    pinMode(output_pin_1, OUTPUT);
    pinMode(output_pin_2, OUTPUT);
    lcd_1.begin(16, 2);

    lcd_1.setBacklight(1);
    lcd_1.print("PROMAX by H2G");
    delay(5000);
    lcd_1.setCursor(0, 0);
    lcd_1.print("Freq        Duty");
    glob_frequency = 3000;
    glob_duty = 50;
    display_line_2();
    delay(2000);
    // lcd_1.clear();
}

void loop()
{

    if (glob_analaog_1 != analogRead(analogPin) || glob_analaog_2 != analogRead(analogPin_2))
    {
        glob_analaog_1 = analogRead(analogPin);
        glob_analaog_2 = analogRead(analogPin_2);
        // if any button state changes glob_analaog_1/2 will get reading for further process
        incrementer(glob_analaog_1, &frequency_increment, &glob_frequency, 1);
        incrementer(glob_analaog_1, &frequency_decrement, &glob_frequency, -1);
        incrementer(glob_analaog_1, &duty_increment, &glob_duty, 1);
        incrementer(glob_analaog_1, &duty_decrement, &glob_duty, -1);
        // upper four lines uses a function to increment or decrement in frequency and duty
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
            // lcd_1.setCursor(0, 1);
            // delay(100);
            if (!button_status_changed)
            {
                lcd_1.setCursor(0, 0);
                lcd_1.print("Fstep      Dstep");
                button_status_changed = true;
            }
            display_line_2();
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
            if (!button_status_changed)
            {
                lcd_1.setCursor(0, 0);
                lcd_1.print("Fstep      Dstep");
                button_status_changed = true;
            }
            display_line_2();
        }
        else if ((glob_analaog_2 >= (present - softMargin) && glob_analaog_2 <= (present + softMargin)))
        {
            glob_duty = 50;
            glob_frequency = 1000;
            if (!button_status_changed)
            {
                lcd_1.setCursor(0, 0);
                lcd_1.print("Fstep      Dstep");
                button_status_changed = true;
            }
            display_line_2();
        }
    }
    display_line_2();
    output_1 = map(glob_duty, 1, 100, 0, 255);
    output_2 = map(glob_duty, 1, 100, 0, 255);
    if (glob_frequency == 10)
    {
        TCCR2B = TCCR2B & B11111000 | B00000111;
    }
    else if (glob_frequency == 100)
    {
        TCCR2B = TCCR2B & B11111000 | B00000110;
    }
    else if (glob_frequency == 1000)
    {
        TCCR2B = TCCR2B & B11111000 | B00000011;
    }
    // deadZoned managed

    analogWrite(output_pin_1, output_1);

    analogWrite(output_pin_2, output_2 + deadZone);
    //
}
void incrementer(int input, int *parameter_match, int *to_beChanged, int to_be_add)
{
    if ((input >= (*parameter_match - softMargin) && input <= (*parameter_match + softMargin)))
    {
        *to_beChanged += to_be_add;
        if (!button_status_changed)
        {
            lcd_1.setCursor(0, 0);
            lcd_1.print("Fstep      Dstep");
            button_status_changed = true;
        }
        display_line_2();
    }
}
void display_line_2()
{
    lcd_1.setCursor(0, 1);
    lcd_1.setCursor(0, 1);
    int temp_size = (String(glob_frequency).length());
    int temp_size_2 = temp_size;
    if (temp_size > 3)
    {
        lcd_1.print(String(glob_frequency / 1000));
        lcd_1.print("K");
    }
    else if (temp_size > 6)
    {
        lcd_1.print(String(glob_frequency / 100000));
        lcd_1.print("M");
    }
    else
    {
        lcd_1.print(String(glob_frequency));
    } // upper part manage frequency output
    // lower part will manage Duty ouput
    temp_size = (String(glob_duty).length());
    if (glob_frequency == 1)
    {
        for (int j = 1 + (String(glob_duty).length()); j < 16; j++)
        {
            lcd_1.print(" ");
        }
        lcd_1.print(String(glob_duty));
    }
    else if ((glob_frequency >= 10 && glob_frequency <= 99) || (glob_frequency >= 1000 && glob_frequency <= 9999))
    {
        for (int j = 2 + (String(glob_duty).length()); j < 16; j++)
        {
            lcd_1.print(" ");
        }
        lcd_1.print(String(glob_duty));
    }
    else if (temp_size_2 >= 4 || (glob_frequency >= 100 && glob_frequency <= 999))
    {
        for (int j = 3 + (String(glob_duty).length()); j < 16; j++)
        {
            lcd_1.print(" ");
        }
        lcd_1.print(String(glob_duty));
    }
}