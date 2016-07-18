// code developed at design lab
//Koc University
//by Mohammed Asif Chand under the guidance of Oguz Turan Buruk
//RPG Gadget 
//components used ledstrip Neo Pixel and MMA7361 accelerometer



//Accelerometer connections
//ST - pin12
//GESL - pin10
//0GD- pin11
//SLP-  pin13
//XOUT- A0
//YOUT- A1
//ZOUT- A2
//GND - GND
//VCC - 3.3V
//The above mentioned connections on the accelerometer are with respect to the Arduino Uno
//Connections may vary if some other board is used
//To use with other boards library changes are required respectively


//Connections of NeoPixel On arduino Uno
//GND - GND
//Din -  PIN6
//VCC - 5V
//////////////////////////
//PIN value of 6 can be changed by the changing the value at #define PIN '6'
#include <Adafruit_NeoPixel.h>
#include <AcceleroMMA7361.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
// define the pins for the 25 pixels


//acclelerometer variables
AcceleroMMA7361 accelero;
int x;
int y;
int z;
int x_offset = 4;
// offset values are ued to clear if any error 
//Please check for discrepencies before using the acceleromter
int y_offset= -3;
int z_offset = -100;
float t = 15;
boolean success = false ;
boolean success2 = false;
// accel variables
long p = 0;

void setup() {
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(5); //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW); //sets the sensitivity to +/-6G
  accelero.calibrate();
  Serial.print("\n INITIALIZING RPG GADGET\n");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);

}
void loop(){ //Standby state
  

  for( float j = 0; j<200; j++){
    for( uint16_t i =0; i<strip.numPixels(); i++){
      uint32_t white = strip.Color(j,j,j);
      strip.setPixelColor(i,white);
      delay(2);
      
    }
    strip.show();
  }
  for( float j = 199; j>0; j--){
    for( uint16_t i =0; i<strip.numPixels(); i++){
      uint32_t white = strip.Color(j,j,j);
      strip.setPixelColor(i,white);
      delay(1);
      
    }
    strip.show();
  }
  


  while(Serial.available())
  {
    if( Serial.read() == 's')
    { 
      // when the character 's' is pressed
      // the loop starts working on the main program
      // main program used here is to program single attack
      // several main programs can be used to develop multitude sets of moves
      
      t=15;
      for( int k=0; k< 1000; k++)
      {
        clearLed();// Function to clear pixels
        ledGlowfirst(0);// Function to execute functionalities
      }  
    }
    else if ( Serial.read() == 'p')
    {
      //not defined yet
      // can define power attack when character 'p' is pressed
      
    }
  }
}

//ledGlowfirst() is the first function called by mainloop
//It verifies the value along z direction
//transfers the value of  z to the precision function
//precision function estimates the precision points based on the position of led


void ledGlowfirst(int wait){
  for ( int i = 0; i < strip.numPixels(); i++)
  {
    for ( float j=0; j<256; j+=t)
    {
      int k = 0;
      uint32_t color = strip.Color(j,j,j);
      strip.setPixelColor(i,color);
      if (t<21)
        t+=0.002;//t variable alters the speed 
      else 
        t+=0.00002;
      Serial.println(t);
      z = (accelero.getZAccel() + z_offset) ;
      //x = (accelero.getXAccel() + x_offset);
      //Serial.println(x);
      //delay(500); //check
      if (abs(z)> 50)
      {
        success = true;
        Serial.println("the value of the z");
        Serial.println(abs(z));
        delay(500);
         PrecisionFormula(i,j);
        t=13; // point calculator
        //t gradually increases the rate of incrementation
        //Serial.println("The value of the z");
        //Serial.println(z);
        //Serial.println("The value of the i");
        //Serial.println(i);
        //Serial.println("The value of the j");
        //Serial.println(j);
        success = !success;// state of the success is altered
      }
      strip.show();
      delay(wait);
      
      // this dims the i-1 led everytime
      
     uint32_t sideColor = strip.Color(255-j,255-j,255-j);
      strip.setPixelColor( i-1,sideColor);
      strip.show();
      delay(wait);


    }
  }
}


long PrecisionFormula(int r ,float s){
  // specify both i and j from the code

  // while ( Serial.available()){

  //   if ( Serial.read() == '1'){
  //delay(1000);
  while(success)
  {
 
    //delay(1000);
    switch(r){
    case 0:
    delay(1000);
    Serial.println("precision value of first led");
    Serial.println(s);
    p = s;
    p = map(p,0,765,0,255);
   //for (int i =0 ; i < 2;i++)//
    lineFunction(p);//can remoce
    clearLed();//re
    return p;


      case 1:
      delay(1000);
      Serial.println("precision value of 2nd led");
      p = (255+s);
      Serial.println(p);
      p = map(p,0,765,0,255);
      //for (int i =0 ; i < 2;i++)//r
          lineFunction(p);//can remoce
      clearLed();//re
      return p; 


             case 2:
            delay(1000);
            Serial.println("precision value of the 3rd led");    
            p = (510+s);
            Serial.println("precision value of the s");
            Serial.println(s);
            Serial.println(p);
            p = map(p,0,765,0,255);
           // for (int i =0 ; i < 2;i++)//r
            lineFunction(p);//can remoce
            clearLed();//rem
            return p;



                      case 3:
                      delay(1000);
                      Serial.println("precision value of the 4th led");
                      p = (755-s);
                      Serial.println(755-s);
                      p = map(p,0,765,0,255);
                      // for (int i =0 ; i < 2;i++)//r
                      lineFunction(p);//can remoce
                      clearLed();//rem
                      return p;



                                case 4 :
                                delay(1000);
                                Serial.println(" Precision value of the 5th led");
                                Serial.println(510-s);
                                p = (510-s);
                                p = map(p,0,765,0,255);
                                // for (int i =0 ; i <2;i++)//r
                               lineFunction(p);//can remoce
                               clearLed();//rem
                               return p;

    }
    //                  }
    //                  }
  } 
}
/////////////////

// clear led function
//used to clear all the led's 
//clearing dims the led
void clearLed(){
  uint32_t color = strip.Color(0,0,0);
  for( int m=0; m<5; m++)
  {
    strip.setPixelColor(m,0);
  }
  strip.show();
}  


////
//all lit function can be used to lit all the led's
// lits by taking single input value
//color ranges from max at green to min at red
// always use 'strip.show();' after this function is called
void allLit(int b){
  for ( int i =0;i < 5; i++)
  {
    uint32_t Color = strip.Color(255-b,b,0);
    strip.setPixelColor(i,Color);
  }
}

//Function to calculate the impact 
// Takes input in the form of p that is the precisionColor
// Gives output in the form of mapped values of x,y,z
//d is the value of precision points
// v is the value of axis
//Max is the maximum value to be mapped 
//Max value is calculated by adding the p and 3x
//factor of multiplier to be multiplied
void impactCalculator( int d, int v, int Max,int f)
{

  int impactValue;
  impactValue = (((abs(v)*f)/2)+ d); 
  impactValue = map(impactValue,0,Max,0,255);
  Serial.println("the value of the IV");
  Serial.println(impactValue);
  Serial.println("the value of the Max");
  Serial.println(Max);
  Serial.println("the value of the x is");
  Serial.println(v);
  clearLed();
  //del9ay(1000);
  for(int i=0;i<8;i++)
  {  
    // allLit(impactValue);
    // strip.show();
    //delay(1000);
    EndColor(impactValue);
    // explantion is given below
  }
}

//////////////////////////
//end color function 
//estimates the end color after all the program execution
//used at the end of the second phase
//helps visualizing the level of performance through the impact value calculation


void EndColor(int b){

  uint32_t red = strip.Color(255-b,b,0);
  for (uint16_t i=0; i< 5;i++)
  {
    strip.setPixelColor( i, red);
    strip.setPixelColor( 4-i,red);
    strip.show();
    delay(150);
    strip.setPixelColor(i,0);
    strip.setPixelColor(4-i,0);
  }
}


//////////////////
//Line function
//takes value from precision function
// value is used to degrade the led one by one 
//after transferring value to other functions which are called later


void lineFunction(int m){

  allLit(m);  
  strip.show();
  delay(200);
  for( int j=2;j<3;j++){
    strip.setPixelColor(j,0);
    strip.show();
    delay(200);
    for(int i =0;i<500; i++)
    {
      secondLedCheck(j,m);
    }
    // allLit(m);
    //strip.show();
    //code to check the condition of the j and calculate the IF
    //
  }
}


//other function to estimate the total pointer 
// secondledchecks the condition of degradation from the line function at led 3
//then transfers the execution routine to the other function
//the other function which is endled test is used to check acceleration value at combinations of 2and 4, 1 and 5
//end ledtest function mentioned next to this function can also
//map the values to calculate the impact factor
void secondLedCheck(int l, int p){
  // for ( int q = 1; q< 100; q++)    
  // {
  if ( l =2){
    // success2 = true;
    //  if (success2 =true){
    x = (accelero.getXAccel() + x_offset);
    // accelerometer value is verified
    if( x>40)
    {
      
      Serial.println("value of the x in second phase when position of led is 3");
      Serial.println(x);
    //Explanation for the impactfactor is given above
      impactCalculator(p,x,555,3);
      //  break;

    }
    
    //else if ( x>= 100 && x<=120)
    //{
    // impactCalculator(p,x,555,3);
    // break;
    //}
    else 
    {
      for (int  m = 1; m <3;m++)
      {
        strip.setPixelColor(l+m,0);
        strip.setPixelColor(l-m,0);
        strip.show();
        delay(100);
        for (int i =0; i<100;i++)   //loop to check the condition
        {
          endLedTest(l,m,p);
          // end test for the led combinations of 
          // 2 and 4
          // 1 and 5
          // this function evaluates the current location 
          //during the degradation
          //and utilizes the location to find the impact factor
        }  
      }
    }  



    }
  }

void  endLedTest(int i ,int j,int q)
{
  int k = i+j;
  int l = i-j;

  if (k=3)
  {
    x = (accelero.getXAccel() + x_offset);
    if ( x>40)
    {
      impactCalculator(q,x,555,2);
      Serial.println("value of the x in second phase when position of led is 2 and 4");
      Serial.println(x);
    }
  }
    // if ( x >= 100 && x <= 120)
    //{
    // impactCalculator(q,x,555,2);
    // }
    //} 
    else if ( k=4)
    {
      x= (accelero.getXAccel() + x_offset);
      if ( x>40 )
      {
        impactCalculator(q,x,555,1);
         Serial.println("value of the x in second phase when position of led is 1 and 5");
        Serial.println(x);
    

      }
      // if ( x >= 100 && x <= 120)
      //{
      //impactCalculator(q,x,555,1);
      //}
      // the above codes were used to test the working along x limits
     

    } 
  }   






