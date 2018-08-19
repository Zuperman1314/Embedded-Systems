#define LEDA LED1
#define LEDB LED2

volatile int state = HIGH;
volatile int flag = LOW;
int count = 0;

void setup()
{
   pinMode(LEDA, OUTPUT);
   pinMode(LEDB, OUTPUT);     
   pinMode(PUSH2, INPUT_PULLUP);
  attachInterrupt(PUSH2, blink, FALLING); // Interrupt is fired whenever button is pressed
}

void loop()
{
if(flag) {
 digitalWrite(LEDA, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(LEDA, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a secon
  digitalWrite(LEDB, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(LEDB, LOW);    // turn the LED off by making the voltage LOW
  delay(500);     
 flag = LOW;
  }
}

void blink()
{
  state = !state;
  flag = HIGH;
}

