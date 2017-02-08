#define setLedBlue(i)   analogWrite(6, i)
#define setLedRed(i)    analogWrite(23, i)
#define setLedGreen(i)  analogWrite(5, i)
#define clearLedBlue()  analogWrite(6, 0)
#define clearLedRed()   analogWrite(23, 0)
#define clearLedGreen() analogWrite(5, 0)
#define initLed()       pinMode(23, OUTPUT); \
                        pinMode(5, OUTPUT); \
                        pinMode(6, OUTPUT);

typedef enum {
    WHITE,
    RED,
    BLUE,
    GREEN,
    MAGENTA,
    YELLOW,
    CYAN,
    BLACK
} color;

void setRGB(color c, uint8_t intensity)
{
    switch(c)
    {
        case WHITE:
            setLedBlue(intensity);
            setLedRed(intensity);
            setLedGreen(intensity);
            break;
        case RED:
            setLedRed(intensity);
            clearLedBlue();
            clearLedGreen();
            break;
        case BLUE:
            setLedBlue(intensity);
            clearLedRed();
            clearLedGreen();
            break;
        case GREEN:
            setLedGreen(intensity);
            clearLedRed();
            clearLedBlue();
            break;
        case MAGENTA:
            setLedRed(intensity);
            setLedBlue(intensity);
            clearLedGreen();
            break;
        case CYAN:
            setLedBlue(intensity);
            setLedGreen(intensity);
            clearLedRed();
            break;
        case YELLOW:
            setLedGreen(intensity);
            setLedRed(intensity);
            clearLedBlue();
            break;
        case BLACK:
            clearLedBlue();
            clearLedRed();
            clearLedGreen();
            break;
    }
}

void setup(void)
{
    initLed();
}

void loop(void)
{
    setRGB(BLUE, 50);
    delay(1000);
    setRGB(RED, 50);
    delay(1000);
    setRGB(GREEN, 50);
    delay(1000);
    setRGB(YELLOW, 50);
    delay(1000);
    setRGB(CYAN, 50);
    delay(1000);
    setRGB(MAGENTA, 50);
    delay(1000);
    setRGB(WHITE, 50);
    delay(1000);
    setRGB(BLACK, 50);
    delay(1000);
}
