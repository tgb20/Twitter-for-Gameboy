#define CLOCK_PIN 3
#define SO_PIN 6
#define SI_PIN 5

int volatile data = 0;
int volatile counter = 0;
int volatile val = 0;

unsigned volatile long lastReceive = 0;

// MAX OF 40 CHAR IN SINGLE MESSAGE

void setup()
{
    pinMode(SO_PIN, OUTPUT);
    digitalWrite(SO_PIN, LOW);

    pinMode(SI_PIN, INPUT);

    pinMode(CLOCK_PIN, OUTPUT);
    digitalWrite(CLOCK_PIN, HIGH);

    Serial.begin(9600);

    attachInterrupt(0, readSerialClock, RISING);
}

void readSerialClock()
{
    unsigned long t = 0;

    if (lastReceive > 0)
    {
        if (micros() - lastReceive > 120) // too long, must be a new sequence (takes about 120 microsecs for a bit)
        {
            counter = 0;
            val = 0;
        }
    }

    data = digitalRead(SI_PIN);

    if (data == HIGH)
        val |= (1 << (7 - counter));

    if (counter == 7)
    {
        Serial.println(val, DEC);
        val = 0;
        counter = -1;
    }

    counter++;
    lastReceive = micros();
}

void writeByte(byte dataToSend)
{
    Serial.println(dataToSend);
    byte counter = 0;
    for (counter = 0; counter < 8; counter++)
    {
        if (dataToSend & 0x80)
        {
            // Write 1
            digitalWrite(SO_PIN, HIGH);
            digitalWrite(CLOCK_PIN, LOW);
            delayMicroseconds(50);
            digitalWrite(CLOCK_PIN, HIGH);
            delayMicroseconds(50);
        }
        else
        {
            // Write 0
            digitalWrite(SO_PIN, LOW);
            digitalWrite(CLOCK_PIN, LOW);
            delayMicroseconds(50);
            digitalWrite(CLOCK_PIN, HIGH);
            delayMicroseconds(50);
        }

        dataToSend = dataToSend << 1;
    }
    delay(100);
}

void loop()
{
    if (Serial.available())
    {
        String input = Serial.readString();

        char bytesOut[input.length()];
        input.toCharArray(bytesOut, input.length());

        for (int i = 0; i < sizeof(bytesOut); i++)
        {
            writeByte(bytesOut[i]);
        }
        writeByte(8); // End Message
        memset(bytesOut, 0, sizeof(bytesOut));
    }
}
