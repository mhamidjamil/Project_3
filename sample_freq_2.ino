void setup()
{

TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz

TCCR2B = TCCR2B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz

TCCR2B = TCCR2B & B11111000 | B00000011; // for PWM frequency of 980.39 Hz

TCCR2B = TCCR2B & B11111000 | B00000100; // for PWM frequency of 490.20 Hz (The DEFAULT)

TCCR2B = TCCR2B & B11111000 | B00000101; // for PWM frequency of 245.10 Hz

TCCR2B = TCCR2B & B11111000 | B00000110; // for PWM frequency of 122.55 Hz

TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 HzD
    pinMode(3, OUTPUT);
    // put your setup code here, to run once:
}

void loop()
{

    int val = analogRead(0);
    val = map(val, 0, 1023, 0, 255);
    analogWrite(9, val);

    analogWrite(3, 155);
    // put your main code here, to run repeatedly:
}