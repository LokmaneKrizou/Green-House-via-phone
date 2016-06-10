
/*
  Green House Project
  Reads the temperature ,humidity,light and level of water in the ground and choose the required actions acording to the selected plant via phone app (I plant).
  
 This example code is written by Krizou Lokmane and BOUDRAA Abdelouaheb
  */
  
 #include <Servo.h> 
Servo myservo; // create servo object to control a servo 
String string;
int pos = 0;
int x;
int y;
int z;
int temp1;
int temp2;
int temp3;
int temp4;
int humi2;
int humi1;
char command;
int tmprf=0;
int humirf=0;
int lm35=4;           // Analog Pin sensor of the LDR  is connected to A0      
int pot=2;           // Analog Pin sensor of the LDR  is connected to A0      
int SOIL=3;          // Analog Pin sensor Of the soil moisture is connected to A2
int LDR=0;           // Analog Pin sensor of the LDR  is connected to A0      
int value=0;         // variable integer used for calculation initiated with value =0
int LIGHT=5;         // Digital Pin sensor of the Light Source is connected to D03
int OVEN=4;         // Digital Pin sensor of the Heater is connected to D11
int motor=7;        // Digital Pin sensor of FUN Cooller is connected to D10
int humidifier=3;    // Digital Pin sensor of Humidifier is connected to D8

void setup(){
myservo.attach(9); // attaches the servo on pin 9 to the servo object 
 pinMode(OVEN,OUTPUT);  //Define PIN represented by OVEN as an Output
 pinMode(motor,OUTPUT); //Define PIN represented by motor as an Output
 pinMode(LIGHT,OUTPUT); //Define PIN represented by LIGHT as an Output
 pinMode(humidifier,OUTPUT); //Define PIN represented by humidifier as an Output
 Serial.begin(9600);
 
}//end "setup()"
int tl (int f)
{
int arry [9];
arry[0]=0;
arry[1]=0;
arry[2]=0;
arry[3]=0;
arry[4]=0;
arry[5]=0;
arry[6]=0;
arry[7]=0;
arry[8]=0;

  int i=0;
      if (Serial.available() > 0)
           {string = "";}
      while(Serial.available() > 0)
      
      {
       command = ((byte)Serial.read());
    if(command == '.')
              {
                break;
              }
  else if (command != ';'){
        string += command;
       }
   else  {
      arry[i]=string.toInt();
       string="";
       if (i<9)
       i++;
       else
       i=0;
       }
delay(1);       
    
 }
int x=arry[0],q=arry[1] ,p=arry[2], n=arry[3] ,k=arry[4], m=arry[5],b=arry[6],w=arry[7],s=arry[8];
   if( f==1)
  return x;
   else if (f==2)
   return q;
   else if (f==3)
   return p;
   else if (f==4)
   return n;
   else if (f==5)
   return k;
 else if (f==6)
   return m;
   else if (f==7)
   return b;
   else if (f==8)
   return w;
    else  return s;
  
}

 
void Function (int x,int y,int z,int temp2,int temp1,int temp4,int temp3,int hmd2,int hmd1)
{ 
  // the range of light (y-x) 
  // the soil in the ground must be greater then z  
  // the morning temperature has range(temp1-temp2) 
  // the night temperature has range (temp3-temp4)
  // the range of light (hmd1-hmd2) 
  
  //DHT.read11(dht_apin);
value= analogRead(LDR);
tmprf= analogRead(lm35)*0.48828125 ;
int humi= analogRead(pot);
humirf= map(humi,0,1023,0,100);
//Serial.println(value); 

// REGULATE THE TEMPERATURE IN THE MORNING (30-35)
if(tmprf<temp2 && value>25)
{digitalWrite(motor,LOW);
  digitalWrite(OVEN,HIGH);
}
else if(tmprf>temp1 && value>25)
{digitalWrite(motor,HIGH);
digitalWrite(OVEN,LOW);
}
// REGULATE THE TEMPERATURE AT NIGHT (15-20)

else if(tmprf<temp4 && value<25)
{digitalWrite(motor,LOW);
  digitalWrite(OVEN,HIGH);
}
else if(tmprf>temp3 && value<25)
{digitalWrite(motor,HIGH);
digitalWrite(OVEN,LOW);
}
else
{digitalWrite(motor,LOW);
digitalWrite(OVEN,LOW);
}
if(value<x || value>y)
digitalWrite(LIGHT,LOW);
else 
digitalWrite(LIGHT,HIGH);

int soil= analogRead(SOIL);
int soilrf=map(soil,0,1023,0,100);

if( soilrf>z )
{for(pos = 0; pos < 90; pos += 1) // goes from 0 degrees to 180 degrees 
{ // in steps of 1 degree 
myservo.write(pos); // tell servo to go to position in variable
// ‘pos’ 
//delay(2000);// waits 15ms for the servo to reach the 
// position 
if (pos==0)
pos=90;
} } 
else { 
for(pos = 90; pos>=1; pos-=1) // goes from 180 degrees to 0 degrees 
{ 
myservo.write(pos); // tell servo to go to position in variable
// ‘pos’ 
//delay(2000); // waits 15ms for the servo to reach the 
// position 
if (pos==90)
pos=00;
} 
}
if(humirf<hmd1 && humirf>hmd2)
{ digitalWrite(humidifier,LOW);
}
else
{
digitalWrite(humidifier,HIGH);
}

Serial.println(humirf);
Serial.println("humirf");
Serial.println(tmprf);
Serial.println("tmprf");
Serial.println(soilrf);
Serial.println("soilrf");
Serial.println(value);
Serial.println("value");

}

void loop(){
const int a=tl(1);
const int q=tl(2);
const int r=tl(3);
const int m=tl(4);
const int p=tl(5);
const int n=tl(6);
const int u=tl(7);
const int w=tl(8);
const int h=tl(9);
if (a>0)
 x=a;
if (q>0)
 y=q;
if (r>0)
 z=r;
if (m>0)
 temp1=m;
if (p>0)
 temp2=p;
if (n>0)
 temp3=n;
if (u>0)
 temp4=u;
if (w>0)
 humi1=w;
if (h>0)
 humi2=h;
 
delay(2000);

Serial.println("x");
Serial.println(x);
Serial.println("y");
Serial.println(y);
Serial.println("z");
Serial.println(z);
Serial.println("temp1");
Serial.println(temp1);
Serial.println("temp2");
Serial.println(temp2);
Serial.println("temp3");
Serial.println(temp3);
Serial.println("temp4");
Serial.println(temp4);
Serial.println("humi1");
Serial.println(humi1);
Serial.println("humi2");
Serial.println(humi2);

 
  //Start of Program 
  /* Function(range of light <a,range of light >b,range of soil<c,
   * morning temp<d,morning temp>e,night temp<f,night temp<h,range of Humidity<m,range of Humidity >p ) */
Function (x,y,z,temp2,temp1,temp4,temp3,humi2,humi1);      
}

