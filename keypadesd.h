/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Raghunath Reddy
 * ECEN 5613, Keypad (4*3) using scanning algorithm
 * Fall 2016,Prof. Mc Clure
 * University of Colorado at Boulder
 * ---------------------------------------
 * This file helps the user to use keypad not only to enter numbers but also alphabets by changing modes using *,# and also touchscreens certain functions are 
 included in this file.
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */


/* Gloabalized variables------------------------------------------------------- */

 unsigned char changemode=0;                          //Indicates the mode of the keypad.
 unsigned char keypress_count=0;                      //Counts the number of keypressed
 unsigned char page2_flag=0;                          //Page2_flag  tells you if the code is in page 2 of the main code
 unsigned char touchpressed_done_flag=0;              //Tells us if the done button is pressed on the touchscreen using touchscreen.h

 /* Prototypes ---------------------------------------------------- */
 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * keypad_init()
  * Purpose:     Initializing the keypad with 3pins as output and 4 pins as inputs
  * Algorithm:   Initialize pin5,pin6,pin7 as outputs and pin8,pin9,pin10,pin11 as inputs for performing a scanning function in the later part of code
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
 void keypad_init();

 
 void keypress();
 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * keypress()
  * Purpose:     Waits for the key to pressed and than updates using scanning algorithm 
  * Algorithm:   
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
 
 void adc_read();

void keypad_init()
{
 
    LPC_PINCON -> PINSEL3 &= ~((1<<5)|(1<<4));                                                //Pin to LED1 by mbed development board initalizes it as gpio
    LPC_GPIO1-> FIODIR |=     (1<<18);                                                        //Make LED1 as output
    LPC_GPIO1-> FIODIR |= (1<<20);                                                            //output 
   
    LPC_PINCON -> PINSEL0&= ~((1<<19)|(1<<18));                                               //Pin5 as gpio                                    
    LPC_PINCON -> PINSEL0&= ~((1<<17)|(1<<16));                                               //Pin6 as gpio
    LPC_PINCON -> PINSEL0&= ~((1<<15)|(1<<14));                                               //Pin7 as gpio
    
    
    LPC_PINCON -> PINSEL0 &= ~((1<<13)|(1<<12));                                              //Pin8 as gpio
    LPC_PINCON -> PINSEL0 &= ~((1<<1)|(1<<0));                                                //Pin9 as gpio
    LPC_PINCON -> PINSEL0 &= ~((1<<2)|(1<<3));                                                //Pin10 as gpio
    LPC_PINCON -> PINSEL1 &= ~((1<<5)|(1<<4));                                                //Pin11 as gpio
    
    
    LPC_GPIO0-> FIODIR |= (1<<9);                                                             //Pin5 as output 
    LPC_GPIO0-> FIODIR |= (1<<8);                                                             //Pin6 as output 
    LPC_GPIO0-> FIODIR |= (1<<7);                                                             //Pin7 as input 
 
 
    LPC_GPIO0-> FIODIR &= ~(1<<6);                                                            //Pin8 as input
    LPC_GPIO0-> FIODIR &= ~(1<<0);                                                            //Pin9 as input
    LPC_GPIO0-> FIODIR &= ~(1<<1);                                                            //Pin10 as input
    LPC_GPIO0-> FIODIR &= ~(1<<18);                                                           //Pin11 as input
    
    LPC_GPIO0 -> FIOCLR |= (1<<9);                                                            //Pin5 is made low initially
    LPC_GPIO0 -> FIOCLR |= (1<<8);                                                            //Pin6 is made low initally
    LPC_GPIO0 -> FIOCLR |= (1<<7);                                                            //Pin7 is made low initally
    
    
    LPC_GPIO0-> FIODIR |= (1<<17);                                                            //Mode0 LED as an output 
    LPC_GPIO0-> FIODIR |= (1<<15);                                                            //Mode1 LED as an output 
    LPC_GPIO0-> FIODIR |= (1<<16);                                                            //Mode2 LED as an output 
    LPC_GPIO2-> FIODIR |= (1<<3);                                                             //Mode3 LED as an output 
    
    
    LPC_GPIO2-> FIODIR |= (1<<4);//output 
    LPC_GPIO2 -> FIOCLR |= (1<<4);
    
    
    //mode 0
    LPC_GPIO0 -> FIOSET |= (1<<17);                                                            //Making Mode 0 LED high                                                 
    LPC_GPIO0 -> FIOCLR |= (1<<15);
    LPC_GPIO0 -> FIOCLR |= (1<<16);
    LPC_GPIO2 -> FIOCLR |= (1<<3);

    
}

/*
void key_press
Algorithm:
1.Initally make all the input pins low 
2.check if there is an input in any of them if yes than implement the software debounce
which is checking input after a certain delay, if no than bo back and wait for the input.
3.Now check if the value1 is still present.If yes
i.   Make colum1 zero and again check if the value at row1 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
ii.  Make colum2 zero and again check if the value at row1 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
ii.  Make colum3 zero and again check if the value at row1 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.

4.Now check if the value2 is still present.If yes
i.   Make colum1 zero and again check if the value at row2 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
ii.  Make colum2 zero and again check if the value at row2 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
ii.  Make colum3 zero and again check if the value at row2 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.

5.Now check if the value3 is still present.If yes
i.   Make colum1 zero and again check if the value at row3 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
ii.  Make colum2 zero and again check if the value at row3 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
ii.  Make colum3 zero and again check if the value at row3 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.

6.Now check if the value4 is still present.If yes
i.   Make colum1 zero and again check if the value at row4 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
ii.  Make colum2 zero and again check if the value at row4 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
ii.  Make colum3 zero and again check if the value at row4 if the value still exists we can update the value in the global variable and change the keypress count with an 
inital inspection of which mode it is in and the next step is point7.
7.Led indication of exiting loop
*/

void key_press()

{
    unsigned char Value1;                                                                    //Value1 helps in telling if there is any input at row1
    unsigned char Value2;                                                                    //Value2 helps in telling if there is any input at row2
    unsigned char Value3;                                                                    //Value3 helps in telling if there is any input at row3
    unsigned char Value4;                                                                    //Value4 helps in telling if there is any input at row4
    unsigned char keypress=0;                                                                //Flag to check if the keypressed is pressed
    unsigned char i; 
    
    while(keypress==0)
    {
      //Make column1,column2,column3 as inputs
      LPC_GPIO0 -> FIOCLR |= (1<<9);                                                          
      LPC_GPIO0 -> FIOCLR |= (1<<8);                                                       
      LPC_GPIO0 -> FIOCLR |= (1<<7);
      
      //Read the four columns
      Value1 = ((LPC_GPIO0 -> FIOPIN & (1<<6)) >> 6);
      Value2 = ((LPC_GPIO0 -> FIOPIN & (1<<0)) >> 0);
      Value3 = ((LPC_GPIO0 -> FIOPIN & (1<<1)) >> 1);
      Value4 = ((LPC_GPIO0 -> FIOPIN & (1<<18)) >> 18);
    
      //check if any key is pressed 
      if((Value1 && Value2 && Value3 && Value4) == 0 )  
      { 
        //give a delay of certain time and read the values of the rows   
        wait(0.1);
        Value1 = ((LPC_GPIO0 -> FIOPIN & (1<<6)) >> 6);
        Value2 = ((LPC_GPIO0 -> FIOPIN & (1<<0)) >> 0);
        Value3 = ((LPC_GPIO0 -> FIOPIN & (1<<1)) >> 1);
        Value4 = ((LPC_GPIO0 -> FIOPIN & (1<<18)) >> 18);
        //Check if the key is still pressed 
        if ((Value1 && Value2 && Value3 && Value4) == 0 ) 
          {
          if(Value1 == 0)                                                              //check if any key in row1 is pressed.
            { //Make only column3 low 
              LPC_GPIO0 -> FIOSET |= (1<<7);                                                                                
              LPC_GPIO0 -> FIOSET |= (1<<8); 
              LPC_GPIO0 -> FIOCLR |= (1<<9);                                           //column 1 low
              
              
              Value1 = ((LPC_GPIO0 -> FIOPIN & (1<<6)) >> 6);                          //read row1 value again
              if (Value1 == 0)                                                         //check if key1  is pressed
              {
                if (changemode == 1)                                                   //check the mode of the keypad
                {
                    if(column==0)                                                      //backspace function 
                    {
                        // if back space is pressed when it is at the end of the page during the cornrer conditions
                        column = 126;                                                  
                        if(pagevalue == 0)                                            
                        {
                            pagevalue = 7;
                            lcd_cmd(0xB0| page[pagevalue]); 
                        }
                        else
                        {
                            pagevalue = pagevalue - 1;
                            lcd_cmd(0xB0| page[pagevalue]); 
                        }
                        
                    }
                    
                
                    column=column-6;                                                     //changes te position of the cursor
                    lcd_cursor_column_flag=1;                                            //Flag to indicate that we dont require any cursor blink
                    lcd_changelocation();                                                
                    lcd_cursor_column_flag=0;
                    lcd_write_character(0x00);                                           //0x00 is written into the LCD has cursor blink can be erased
                    
                }   
                else if(changemode == 0)
                {
                lcd_write_character('1');                                                //if mode 0 than print 1 on to the LCD
                keypress=1;                                          
                }
                else if(changemode ==2)                                                  //Mode 2 : enter next line
                {
                 if(pagevalue == 7)
                 {
                     pagevalue=0;                                                        //corner conditions
                 } 
                 else
                 {
                     pagevalue=pagevalue+1;                       
                 }
                 lcd_cmd(0xB0|page[pagevalue]);
                 column=0x00;
                 column_change();   
                }
                else if(changemode ==3)                                                  //Mode3: write 1 into the LCD
                {
                    lcd_write_character('1');    
                    keypress=1;
                }
              }
              else
              {
               //Check the column2 keys are pressed
               LPC_GPIO0 -> FIOCLR |= (1<<8);
               LPC_GPIO0 -> FIOSET |= (1<<7);
               LPC_GPIO0 -> FIOSET |= (1<<9);
               Value1 = ((LPC_GPIO0 -> FIOPIN & (1<<6)) >> 6);                           //read value of colum2
               if (Value1 == 0)
                  {
                     keypress=1;                                                         
                     if(changemode==0)                                                  // to enter charcter 2
                     {
                       lcd_write_character('2');
                     }
                     else if (changemode==1)                                            // to enter charcter A
                     {
                        lcd_write_character('A');
                     }
                     else if (changemode==2)                                            // to enter charcter B
                     {
                        lcd_write_character('B');                                   
                     }
                     else if (changemode==3)                                             // to enter charcter C
                     {
                        lcd_write_character('C');
                     }
                  }
               else
                  {  
                  //clear column3
                     LPC_GPIO0 -> FIOCLR |= (1<<7);
                     LPC_GPIO0 -> FIOSET |= (1<<8);
                     LPC_GPIO0 -> FIOSET |= (1<<9);
                     Value1 = ((LPC_GPIO0 -> FIOPIN & (1<<6)) >> 6); //read the value od row1
                       {
                         keypress=1;
                         if(changemode==0)
                     {
                       lcd_write_character('3');                                            // to enter charcter 3
                     }
                     else if (changemode==1)
                     {
                        lcd_write_character('D');                                            // to enter charcter D
                     }
                     else if (changemode==2)
                     {
                        lcd_write_character('E');                                            // to enter charcter E
                     }
                     else if (changemode==3)
                     {
                        lcd_write_character('F');                                            // to enter charcter F
                     }

                   }
                  }
               }
             }
             //This similar to value1 equal to zero ,i.e check if row2 pressed if yes what make the column1,column2,column3 zero in the same order as it is 
             //done for value1=0
             else if(Value2 == 0)
            {  
              LPC_GPIO0 -> FIOSET |= (1<<7);  
              LPC_GPIO0 -> FIOSET |= (1<<8);
               LPC_GPIO0 -> FIOCLR |= (1<<9);
              
              Value2 = ((LPC_GPIO0 -> FIOPIN & (1<<0)) >> 0);
              if (Value2 == 0)
              {
                keypress=1;
                
                if(changemode==0)
                     {
                       lcd_write_character('4');                                                         // to enter charcter 4
                     }
                     else if (changemode==1)
                     {
                        lcd_write_character('G');                                                        // to enter charcter G
                     }
                     else if (changemode==2)
                     {
                        lcd_write_character('H');                                                        // to enter charcter H
                     }
                     else if (changemode==3)
                     {
                        lcd_write_character('I');                                                        // to enter charcter I
                     }

              }
              else
              {
               
               LPC_GPIO0 -> FIOCLR |= (1<<8);
               LPC_GPIO0 -> FIOSET |= (1<<7);
               LPC_GPIO0 -> FIOSET |= (1<<9);
               Value2 = ((LPC_GPIO0 -> FIOPIN & (1<<0)) >> 0);
               if (Value2 == 0)
                  {
                     keypress=1;
                     if(changemode==0)
                     {
                       lcd_write_character('5');                                 // to enter charcter 5 on LCD
                     }
                     else if (changemode==1)
                     {
                        lcd_write_character('J');                                // to enter charcter J on LCD
                     }
                     else if (changemode==2)
                     {
                        lcd_write_character('K');                                // to enter charcter K on LCD
                     }
                     else if (changemode==3)
                     {
                        lcd_write_character('L');                                 // to enter charcter L on LCD
                     }
                  }
               else
                  { 
                     LPC_GPIO0 -> FIOCLR |= (1<<7);
                     LPC_GPIO0 -> FIOSET |= (1<<8);
                     LPC_GPIO0 -> FIOSET |= (1<<9);
                     Value2 = ((LPC_GPIO0 -> FIOPIN & (1<<0)) >> 0);
                     if (Value2 == 0)
                       {
                         keypress=1;
                         if(changemode==0)
                     {
                       lcd_write_character('6');                                  // to enter charcter 6 on LCD
                     }
                     else if (changemode==1)
                     {
                        lcd_write_character('M');                                 // to enter charcter M on LCD
                     }
                     else if (changemode==2)
                     {
                        lcd_write_character('N');                                  // to enter charcter N on LCD
                     }
                     else if (changemode==3)
                     {
                        lcd_write_character('O');                                   // to enter charcter 0 on LCD
                     }
                       }
                  }
               }
             }
             //This similar to value1 equal to zero ,i.e check if row2 pressed if yes what make the column1,column2,column3 zero in the same order as it is 
             //done for value1=0
            else if(Value3 == 0)
            {  
              LPC_GPIO0 -> FIOSET |= (1<<7);  
              LPC_GPIO0 -> FIOSET |= (1<<8);
              LPC_GPIO0 -> FIOCLR |= (1<<9);              
              Value3 = ((LPC_GPIO0 -> FIOPIN & (1<<1)) >> 1);
              if (Value3 == 0)
              {
                keypress=1;
                if(changemode==0)
                {
                  lcd_write_character('7');                                                      // to enter charcter 0 on LCD                         
                }
                else if (changemode==1)
                {
                  lcd_write_character('P');                                                      // to enter charcter P on LCD
                }
                else if (changemode==2)
                {
                        lcd_write_character('R');                                               // to enter charcter R on LCD
                }
                     else if (changemode==3)
                     {
                        lcd_write_character('S');                                               // to enter charcter S on LCD
                     }
              }
              else
              {
               
               LPC_GPIO0 -> FIOCLR |= (1<<8);
               LPC_GPIO0 -> FIOSET |= (1<<7);
               LPC_GPIO0 -> FIOSET |= (1<<9);
               Value3 = ((LPC_GPIO0 -> FIOPIN & (1<<1)) >> 1);
               if (Value3 == 0)
                  {
                     keypress=1;
                     if(changemode==0)
                     {
                       lcd_write_character('8');                                                // to enter charcter 8 on LCD
                     }
                     else if (changemode==1)
                     {
                        lcd_write_character('T');                                               // to enter charcter T on LCD
                     }
                     else if (changemode==2)
                     {
                        lcd_write_character('U');                                              // to enter charcter U on LCD
                     }
                     else if (changemode==3)
                     {
                        lcd_write_character('V');                                             // to enter charcter V on LCD
                     }
                     //LPC_GPIO1 -> FIOSET |= (1<<18);
                     //wait(1);
                     //LPC_GPIO1 -> FIOCLR |= (1<<18);
                  }
               else
                  { 
                     LPC_GPIO0 -> FIOCLR |= (1<<7);
                     LPC_GPIO0 -> FIOSET |= (1<<8);
                     LPC_GPIO0 -> FIOSET |= (1<<9);
                     Value3 = ((LPC_GPIO0 -> FIOPIN & (1<<1)) >> 1);
                     if (Value3 == 0)
                       {
                         keypress=1;
                         if(changemode==0)
                     {
                       lcd_write_character('9');                                              // to enter charcter 9 on LCD
                     }
                     else if (changemode==1)
                     {
                        lcd_write_character('W');                                             // to enter charcter W on LCD
                     }
                     else if (changemode==2)
                     {
                        lcd_write_character('X');                                             // to enter charcter X on LCD
                     }
                     else if (changemode==3)
                     {
                        lcd_write_character('Y');                                            // to enter charcter Y on LCD
                     }
                         
                       }
                  }
               }
             }
            
            else if(Value4 == 0)
            {  
              LPC_GPIO0 -> FIOSET |= (1<<7);  
              LPC_GPIO0 -> FIOSET |= (1<<8);
               LPC_GPIO0 -> FIOCLR |= (1<<9);
              
              Value4 = ((LPC_GPIO0 -> FIOPIN & (1<<18)) >> 18);
              if (Value4 == 0)
              {
                if(changemode ==0)                                                           //Mode change buttons
                {
                 changemode=1;
                     //mode 1    LEDs change color based on Mode
                   LPC_GPIO0 -> FIOCLR |= (1<<17);
                   LPC_GPIO0 -> FIOSET |= (1<<15);
                   LPC_GPIO0 -> FIOCLR |= (1<<16);
                   LPC_GPIO2 -> FIOCLR |= (1<<3);   
                 
                }
                else
                {   
                changemode=0;
                    //mode 0
                 LPC_GPIO0 -> FIOSET |= (1<<17);
                 LPC_GPIO0 -> FIOCLR |= (1<<15);
                 LPC_GPIO0 -> FIOCLR |= (1<<16);
                 LPC_GPIO2 -> FIOCLR |= (1<<3);
                }

              }
              else
              {
               
               LPC_GPIO0 -> FIOCLR |= (1<<8);
               LPC_GPIO0 -> FIOSET |= (1<<7);
               LPC_GPIO0 -> FIOSET |= (1<<9);
               Value4 = ((LPC_GPIO0 -> FIOPIN & (1<<18)) >> 18);
                   
                 if (Value4 == 0)
                  {
                     
                     
                     if(changemode==0)
                     {
                       lcd_write_character('0');
                       keypress=1;
                     }
                     else if (changemode==1)
                     {
                        lcd_write_character('Q');                                       // to enter charcter Q on LCD
                        keypress=1;
                     }
                     else if (changemode==2)
                     {
                        lcd_write_character('Z');                                       // to enter charcter Z on LCD
                        keypress=1;
                     }
                     else if (changemode==3)
                     {
                        lcd_write_character(0x00);                                       // to enter charcter space on LCD
                        keypress=1;
                     }
                  }
               else
                  { 
                     
                     LPC_GPIO0 -> FIOCLR |= (1<<7);
                     LPC_GPIO0 -> FIOSET |= (1<<8);
                     LPC_GPIO0 -> FIOSET |= (1<<9);
                     Value4 = ((LPC_GPIO0 -> FIOPIN & (1<<18)) >> 18);
                     
                  if (Value4 == 0)                                                    //changing the mode from mode2, mode3
                     {
                            LPC_GPIO1 -> FIOCLR |= (1<<18);  
                            wait(0.1);
                           LPC_GPIO1 -> FIOSET |= (1<<18);  
                           wait(0.1);
                      
                       if(changemode == 2)
                         {
                           changemode=3;
                               //mode 3
                            LPC_GPIO0 -> FIOCLR |= (1<<17);
                            LPC_GPIO0 -> FIOCLR |= (1<<15);
                            LPC_GPIO0 -> FIOCLR |= (1<<16);
                            LPC_GPIO2 -> FIOSET |= (1<<3);
                              
                         }
                       else 
                         {   
                           changemode=2;
                               //mode 2
                            LPC_GPIO0 -> FIOCLR |= (1<<17);
                            LPC_GPIO0 -> FIOCLR |= (1<<15);
                            LPC_GPIO0 -> FIOSET |= (1<<16);
                            LPC_GPIO2 -> FIOCLR |= (1<<3);
                         }       
                         
                       }
                  }
               }
             }
            }
         }
         
         
         
        // Check if the done button the touch screen is pressed
        xcor=0;
         ycor=0;
         
         if(page2_flag==1)       //only when keypress dunction is used in page2
     {            
        for(i=0;i<5;i++)
        {
          adc_read();
          if(((xcor > 0x5200 && xcor< 0x7400)&&(ycor >0x7100 && ycor< 0x7C00)))  //Previously determined x nd y coordinates for done button on touchscreen
          {
           touchpressed_done_flag=1;
           goto endloop1;
          }
       }   
       }

}
 
        
        endloop1:
        
        //LED indication for verifiacation
        LPC_GPIO1 -> FIOCLR |= (1<<18);  
        wait(0.1);
        LPC_GPIO1 -> FIOSET |= (1<<18);  
        wait(0.1);
        LPC_GPIO1 -> FIOCLR |= (1<<18);  
        wait(0.1);
    

}




