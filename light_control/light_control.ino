const int switch_pin = 2; // Pin 2 is required to attach external interrupt 0
const int leds_pin = 9;

#define OFF 0
#define ON_LOW 1
#define ON_MEDIUM 2
#define ON_HIGH 3
#define ON_MODULATED 4

#define DELTA_PW 1 // about 0,2%
#define DELTA_TIME 50 // 50 ms period of pw variation

volatile int mode = OFF;
volatile unsigned int pw = 0;

void setup()
{
  pinMode(leds_pin, OUTPUT);
  attachInterrupt(0, change_mode, RISING);
  Serial.begin(9600);
}

void loop()
{
  switch (mode)
  {
    case ON_MODULATED :
    modulation(); // 1% variation up or down
    delay(DELTA_TIME);
    break;
    
    case OFF :
    pw = 0; // OFF
    break;
  
    case ON_LOW:
    pw = 51; // Pulse width = 20 %
    break;
    
    case ON_MEDIUM:
    pw = 127; // Pulse width = 50 %
    break;
    
    case ON_HIGH:
    pw = 255; // Pulse width = 100 %
    break;
  }  
  analogWrite(leds_pin, pw);
}

void change_mode()
{
  switch (mode)
  {
    case OFF :
      mode = ON_LOW;
      Serial.println("Mode switched to = ON_LOW");
      break;
      
    case ON_LOW :
      mode = ON_MEDIUM;
      Serial.println("Mode switched to = ON_MEDIUM");
      break;
    
    case ON_MEDIUM :
      mode = ON_HIGH;
      Serial.println("Mode switched to = ON_HIGH");
      break;
    
    case ON_HIGH :
      mode = ON_MODULATED;
      Serial.println("Mode switched to = ON_MODULATED");
      pw = 0;
      break;
      
    case ON_MODULATED :
      mode = OFF;
      Serial.println("Mode switched to = OFF");
      break;
  }
}

void modulation()
{
  static boolean up = true;
  if (pw == 255)
  {
    up = false;
  }
  
  if (pw == 0)
  {
    up = true;
  }
  
  if (up)
  {
    pw += DELTA_PW;
  }
  else
  {
    pw -= DELTA_PW;
  }
  Serial.print("pw = ");
  Serial.println(pw);
  
}
  

