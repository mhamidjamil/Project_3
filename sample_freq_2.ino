void setup()
{

    TCCR0B = TCCR0B & B11111000 | B00000001; // for PWM frequency of 62500.00 Hz

    TCCR0B = TCCR0B & B11111000 | B00000010; // for PWM frequency of 7812.50 Hz

    TCCR0B = TCCR0B & B11111000 | B00000011; // for PWM frequency of 976.56 Hz (The DEFAULT)

    TCCR0B = TCCR0B & B11111000 | B00000100; // for PWM frequency of 244.14 Hz

    TCCR0B = TCCR0B & B11111000 | B00000101; // for PWM frequency of 61.04 Hz

    TCCR2B = TCCR2B & B11111000 | B00000001; // for PWM frequency of 31372.55 Hz
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