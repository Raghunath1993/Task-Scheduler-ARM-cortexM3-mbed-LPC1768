/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Raghunath Reddy
 * ECEN 5613, 4 wire resistive touch screen
 * Fall 2016,Prof. Mc Clure
 * University of Colorado at Boulder
 * ---------------------------------------
 * This file lets the user interface a four wire resistive touch screen by using the ADC.
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
int xcor;
int ycor;
char timevalue[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int readX()
{  
  AnalogIn yaxis2(A3);
  DigitalOut xaxis1(P0_23); //Port 0, pin 10
  AnalogIn yaxis3(A1);
  DigitalOut xaxis2(P0_25); //Port 0, pin 10
  xaxis2=0;//make x2 low
  xaxis1=1;//make x1 high
  wait_ms(5); //pause to allow lines to power up
  int adcy2= yaxis2.read_u16();
  return adcy2;  
}

int readY(){
  int adcx2;
  AnalogIn x1(A0);
  DigitalOut y2(P0_26); //Port 0, pin 10
  AnalogIn x2(A2);
  DigitalOut y3(P0_24); //Port 0, pin 10
  y2=0;//make y1 low
  y3=1;//make y2 high
  wait_ms(5); //pause to allow lines to power up
  adcx2= x2.read_u16();
  return adcx2;
}

void adc_read()
{
  int xtemp[5];
  int ytemp[5];
  int x=0;
  int y=0;
  unsigned char i=0;
  int temp_check;
  temp_check =readX();
  while(i<5 && temp_check > 200)
  {
  xtemp[i] = readX();
  ytemp[i] = readY();
  i++;
  if(i==5)
  {
  for(i=0;i<5;i++)
  {
      x=x+xtemp[i];
      y=y+ytemp[i];
  }
  x=x/5;
  y=y/5;
  xcor=x;
  ycor=y;
  }

  }
  i=0;
  x=0;
  y=0;
}
