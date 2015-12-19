/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Raghunath Reddy
 * ECEN 5613, Graphic LCD 
 * Fall 2016,Prof. Mc Clure
 * University of Colorado at Boulder
 * ---------------------------------------
 * This file helps the user to contrrol TG12864H3-05A which has option for displaying cursor, this library also contains functions which are application specific
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */





/* Gloabalized variables------------------------------------------------------- */
//Did not inculude pointer to pointer decelat=ration so had to use 5 variables for 5 dfifferent values assingned with timer and most of these variable are used side main function
int alaram1sec=0;                                                        //Has the value of the alaram 1 in sec 
int alaram2sec=0;
int alaram3sec=0;
int alaram4sec=0;
int alaram5sec=0;
unsigned char string_count;                                              
unsigned char page[8] = {3,2,1,0,7,6,5,4};                              //page values are matched with what can be exactly seen on LCD , for better and easy understanding  
unsigned char column;                                                   //stores the current value of the column 
unsigned char pagevalue;                                                //Store the current valuee of the page
unsigned char glo_line;                                                 //Store the value of the character that is entered on the keypad
unsigned char lcd_timer_flag=0;                                         //Timer to be displayed based on this flag
unsigned char lcd_cursor_column_flag=1;                                 //Cursor to be displayed in the next column based on this flag
unsigned char lcd_cursorblink_flag=0;                                   //Based this flag cursor may or may not be displayed
unsigned char alaram_count;                                             //Counts the number of alarams set
unsigned char alaram1_occured_flag=0;                                   //Indication if the alaram has occured or not
unsigned char alaram2_occured_flag=0;
unsigned char alaram3_occured_flag=0;
unsigned char alaram4_occured_flag=0;
unsigned char alaram5_occured_flag=0;
unsigned char main_username[5]={'R','A','G','H','U'};                   //Login credentials
unsigned char main_password[5]={'R','A','G','H','U'};                   //Login credentials
unsigned char loginstatus;

unsigned char alaram_time1_h;                                            //Contains the number hours entered by the user for the alaram1
unsigned char alaram_time1_m;                                            //Contains the number minutes entered by the user for the alaram1
unsigned char alaram_time1_d;                                            //Contains the number days entered by the user for the alaram1
unsigned char alaram_time1_o;                                            //Contains the number months entered by the user for the alaram1
unsigned char lcd_refresh=0;

unsigned char alaram_time2_h;
unsigned char alaram_time2_m;
unsigned char alaram_time2_d;
unsigned char alaram_time2_o;

unsigned char alaram_time3_h;
unsigned char alaram_time3_m;
unsigned char alaram_time3_d;
unsigned char alaram_time3_o;

unsigned char alaram_time4_h;
unsigned char alaram_time4_m;
unsigned char alaram_time4_d;
unsigned char alaram_time4_o;

unsigned char alaram_time5_h;
unsigned char alaram_time5_m;
unsigned char alaram_time5_d;
unsigned char alaram_time5_o;

unsigned char alaram_des_1[20];                                                 //Stores the description alloted to alaram1
unsigned char alaram_des_2[20];
unsigned char alaram_des_3[20];
unsigned char alaram_des_4[20];
unsigned char alaram_des_5[20];

unsigned char desc_count;                                                       //store the number of words associated with the descriprion 1
unsigned char desc_count2;
unsigned char desc_count3;
unsigned char desc_count4;
unsigned char desc_count5;

unsigned char alaram1_lcd_flag=0;                                              //Tells the controller to display the alaram information on the LCD or not
unsigned char alaram2_lcd_flag=0;
unsigned char alaram3_lcd_flag=0;
unsigned char alaram4_lcd_flag=0;
unsigned char alaram5_lcd_flag=0;

unsigned char alaram_time_delete=0;
unsigned char touchpressed_done2_flag=0;                                     //Flag to indicate whether done button on touch screen is pressed or not
int nextpage;                                                              

unsigned char alaram1_flag;                                                  
unsigned char alaram2_flag;
unsigned char alaram3_flag;
unsigned char alaram4_flag;
unsigned char alaram5_flag;


unsigned char alaram_time_1_2[3];                                           //Store the ascii values of the hours enetered                                            
unsigned char alaram_time_1_1[3];                                           //Store the ascii values of the minutes enetered    
unsigned char alaram_time_1_4[3];                                           //Store the ascii values of the days enetered    
unsigned char alaram_time_1_3[3];                                           //Store the ascii values of the months enetered    

unsigned char alaram_time_2_2[3];
unsigned char alaram_time_2_1[3];
unsigned char alaram_time_2_4[3];
unsigned char alaram_time_2_3[3];

unsigned char alaram_time_3_2[3];
unsigned char alaram_time_3_1[3];
unsigned char alaram_time_3_4[3];
unsigned char alaram_time_3_3[3];

unsigned char alaram_time_4_2[3];
unsigned char alaram_time_4_1[3];
unsigned char alaram_time_4_4[3];
unsigned char alaram_time_4_3[3];

unsigned char alaram_time_5_2[3];
unsigned char alaram_time_5_1[3];
unsigned char alaram_time_5_4[3];
unsigned char alaram_time_5_3[3];

unsigned char touchpressed_add_flag=0;                                                 //indicates the status whether add button on the touchscreen is pressed or not
unsigned char touchpressed_delete_flag=0;                                              //indicates the status whether add button on the touchscreen is pressed or not



unsigned char lcdbuffer[1530]=               //BITMAP OF THE LCD inclues A-Z 0-9 and few special characters used in the application
{
0x00,0x00,0x00,0x00,0x00,0x00,//0x00
0x00,0x01,0x01,0x01,0x01,0x01,//0x01
0x00,0xFF,0xFF,0xFF,0xFF,0xFF,//0x02
0x00,0x00,0x00,0x00,0x00,0x00,//0x03
0x00,0x00,0x00,0x00,0x00,0x00,//0x04
0x00,0x00,0x00,0x00,0x00,0x00,//0x05
0x00,0x00,0x00,0x00,0x00,0x00,//0x06
0x00,0x00,0x00,0x00,0x00,0x00,//0x07
0x00,0x00,0x00,0x00,0x00,0x00,//0x08
0x00,0x00,0x00,0x00,0x00,0x00,//0x09
0x00,0x00,0x00,0x00,0x00,0x00,//0x0A
0x00,0x00,0x00,0x00,0x00,0x00,//0x0B
0x00,0x00,0x00,0x00,0x00,0x00,//0x0C
0x00,0x00,0x00,0x00,0x00,0x00,//0x0D
0x00,0x00,0x00,0x00,0x00,0x00,//0x0E
0x00,0x00,0x00,0x00,0x00,0x00,//0x0F
0x00,0x00,0x00,0x00,0x00,0x00,//0x10
0x00,0x00,0x00,0x00,0x00,0x00,//0x11
0x00,0x00,0x00,0x00,0x00,0x00,//0x12
0x00,0x00,0x00,0x00,0x00,0x00,//0x13
0x00,0x00,0x00,0x00,0x00,0x00,//0x14
0x00,0x00,0x00,0x00,0x00,0x00,//0x15
0x00,0x00,0x00,0x00,0x00,0x00,//0x16
0x00,0x00,0x00,0x00,0x00,0x00,//0x17
0x00,0x00,0x00,0x00,0x00,0x00,//0x18
0x00,0x00,0x00,0x00,0x00,0x00,//0x19
0x00,0x00,0x00,0x00,0x00,0x00,//0x1A
0x00,0x00,0x00,0x00,0x00,0x00,//0x1B
0x00,0x00,0x00,0x00,0x00,0x00,//0x1C
0x00,0x00,0x00,0x00,0x00,0x00,//0x1D
0x00,0x00,0x00,0x00,0x00,0x00,//0x1E
0x00,0x00,0x00,0x00,0x00,0x00,//0x1F
0x00,0x00,0x00,0x00,0x00,0x00,//0x20
0x00,0x00,0x00,0x00,0x00,0x00,//0x21
0x00,0x00,0x00,0x00,0x00,0x00,//0x22
0x00,0x00,0x00,0x00,0x00,0x00,//0x23
0x00,0x00,0x00,0x00,0x00,0x00,//0x24
0x00,0x00,0x00,0x00,0x00,0x00,//0x25
0x00,0x00,0x00,0x00,0x00,0x00,//0x26
0x00,0x00,0x00,0x00,0x00,0x00,//0x27
0x00,0x00,0x00,0x00,0x00,0x00,//0x28
0x00,0x00,0x00,0x00,0x00,0x00,//0x29
0x00,0x22,0x14,0x3C,0x14,0x22,//0x2A
0x00,0x00,0x00,0x00,0x00,0x00,//0x2B
0x00,0x00,0x00,0x00,0x00,0x00,//0x2C
0x00,0x00,0x00,0x00,0x00,0x00,//0x2D
0x00,0x00,0x00,0x00,0x00,0x00,//0x2E
0x00,0x20,0x10,0x08,0x04,0x02,//0x2F--/
0x00,0x3e,0x45,0x49,0x51,0x3e,//0x30--0
0x00,0x00,0x11,0x31,0x7F,0x01,//0x31--1
0x00,0x21,0x43,0x45,0x49,0x31,//0x32--2
0x00,0x42,0x41,0x51,0x69,0x46,//0x33--3
0x00,0x0c,0x14,0x24,0x7F,0x04,//0x34--4
0x00,0x71,0x51,0x51,0x51,0x4E,//0x35--5
0x00,0x3E,0x49,0x49,0x49,0x06,//0x36--6
0x00,0x40,0x47,0x48,0x50,0x60,//0x37--7
0x00,0x36,0x49,0x49,0x49,0x36 ,//0x38--8
0x00,0x30,0x49,0x49,0x49,0x3E ,//0x39--9
0x00,0x00,0x00,0x24,0x00,0x00,//0x3A--:-37
0x00,0x00,0x00,0x00,0x00,0x00,//0x3B
0x00,0x00,0x00,0x00,0x00,0x00,//0x3C
0x00,0x00,0x00,0x00,0x00,0x00,//0x3D
0x00,0x00,0x00,0x00,0x00,0x00,//0x3E
0x00,0x00,0x00,0x00,0x00,0x00,//0x3F
0x00,0x00,0x00,0x00,0x00,0x00,//0x40
 0x00,0x3f,0x44,0x44,0x44,0x3F,    //A-0x41
0x00,0x7f,0x49,0x49,0x49,0x36,   //B-0x42
 0x00,0x3e,0x41,0x41,0x41,0x22,    //C-0x43
 0x00,0x7F,0x41,0x41,0x22,0x1c,    //D-0x44
 0x00,0x7F,0x49,0x49,0x49,0x41,    //E-0x45
 0x00,0x7F,0x48,0x48,0x48,0x40,   //F-0x46
 0x00,0x3e,0x41,0x49,0x49,0x2e,  //G-0x47
 0x00,0x7f,0x08,0x08,0x08,0x7f ,  //H-0x48
 0x00,0x41,0x41,0x7F,0x41,0x41,   //I-0x49
 0x00,0x02,0x41,0x41,0x7e,0x40 ,   //J-0x4a
 0x00,0x7f,0x08,0x14,0x22,0x41,    //K-0x4b
 0x00,0x7F,0x01,0x01,0x01,0x01,    //L-0x4c
  0x00,0x7f,0x20,0x18,0x20,0x7f,   //M-0x4d
  0x00,0x7f,0x10,0x08,0x04,0x7f,  //N-0x4e
  0x00,0x3e,0x41,0x41,0x41,0x3e,   //O-0x4f
  0x00,0x7f,0x48,0x48,0x48,0x30,   //P-0x50
  0x00,0x3e,0x41,0x45,0x42,0x3f,  //Q-0x51
  0x00,0x7f,0x48,0x4c,0x4a,0x31,   //R-0x52
  0x00,0x31,0x49,0x49,0x49,0x46,   //S-0x53
  0x00,0x40,0x40,0x7f,0x40,0x40,  //T-0x54
  0x00,0x7e,0x01,0x01,0x01,0x7e,  //U-0x55
  0x00,0x7C,0x02,0x01,0x02,0x7C,   //V-0x56
  0x00,0x7e,0x01,0x0e,0x01,0x7e,   //W-0x57
  0x00,0x63,0x14,0x08,0x14,0x63,   //X-0x58
  0x00,0x70,0x08,0x07,0x08,0x70,   //Y-0x59
  0x00,0x43,0x45,0x49,0x51,0x61,   //Z-0x5A
  0x00,0x00,0x00,0x00,0x00,0x00,  
  0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,

  0x00,0x00,0x00,0x00,0x00,0x00,   //a
  0x00,0x00,0x00,0x00,0x00,0x00,   //b
  0x00,0x3e,0x41,0x41,0x41,0x22,   //c
  0x00,0x00,0x00,0x00,0x00,0x00,   //d
  0x00,0x7F,0x49,0x49,0x49,0x41,   //e
  0x00,0x00,0x00,0x00,0x00,0x00,   //f
  0x00,0x00,0x00,0x00,0x00,0x00,   //g
  0x00,0x00,0x00,0x00,0x00,0x00,   //h
  0x00,0x00,0x00,0x00,0x00,0x00,   //i
  0x00,0x00,0x00,0x00,0x00,0x00,   //j
  0x00,0x00,0x00,0x00,0x00,0x00,   //k
  0x00,0x00,0x00,0x00,0x00,0x00,   //l
  0x00,0x00,0x00,0x00,0x00,0x00,   //m
  0x00,0x00,0x00,0x00,0x00,0x00,   //n
  0x00,0x3e,0x41,0x41,0x41,0x3e,   //o
  0x00,0x00,0x00,0x00,0x00,0x00,   //p
  0x00,0x00,0x00,0x00,0x00,0x00,   //q
  0x00,0x00,0x00,0x00,0x00,0x00,   //r
  0x00,0x00,0x00,0x00,0x00,0x00,   //s
  0x00,0x00,0x00,0x00,0x00,0x00,   //t
 
  0x00,0x00,0x00,0x00,0x00,0x00,   //u
   0x00,0x7C,0x02,0x01,0x02,0x7C,   //v
  0x00,0x00,0x00,0x00,0x00,0x00,   //w
  0x00,0x00,0x00,0x00,0x00,0x00,   //x
  0x00,0x00,0x00,0x00,0x00,0x00,   //y
  0x00,0x00,0x00,0x00,0x00,0x00   //z

};



/* Prototypes ---------------------------------------------------- */
 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * Initialize_lcd_pinouts()
  * Purpose:     Initializing the LCD pins 
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void initialize_lcd_pinouts();

 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * Initialize_lcd_pinouts()
  * Purpose:     Initializing the LCD and power supply to the LCD
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void initialize_lcd();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_cmd()
  * Purpose:     To send a command to the LCD
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_cmd(unsigned char);

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_data()
  * Purpose:     To send a data to the LCD by making A0 high
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_data(unsigned char);

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * dealy_us_lcd()
  * Purpose:     A particular delay set after several trial and error methods
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void delay_us_lcd();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_clear()
  * Purpose:     Clears the entire LCD
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_clear();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_write_character()
  * Purpose:     write the character on to the LCDbased on the input provided expexting ascii values in that
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_write_character(unsigned char line);


/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * cursor_blink()
  * Purpose:     Special character included for the cursor display as it not part of the LCD hardware
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void cursor_blink();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * column_change()
  * Purpose:     Changes the column in which lcd is currently in by looking at the value of column
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void column_change();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * check_column()
  * Purpose:     Checks if the LCD as reached the end of th column if yes changes it to the next row/Page
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void check_column();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_clear1()
  * Purpose:     Clears the LCD but not the RTC
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_clear1();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_changelocation()
  * Purpose:     changes the value of the location of lcd by using the page value and column function
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_changelocation();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_write_character()
  * Purpose:     write the character on to the LCDbased on the input provided expexting ascii values in that
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_write_string(unsigned char);

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_color_red()
  * Purpose:     Changes the background color to red
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_color_red();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_color_green()
  * Purpose:     Changes the background color of LCD to green
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_color_green();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * lcd_color_green()
  * Purpose:     Changes the background color of LCD to red
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void lcd_color_blue();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * alaram1()
  * Purpose:     Sets the value of the alaram by taking the user inputs for the page3
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void alaram1();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * alaram2()
  * Purpose:     Sets the value of the alaram by taking the user inputs for the page3
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void alaram2();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * alaram3()
  * Purpose:     Sets the value of the alaram by taking the user inputs for the page3
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void alaram3();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * alaram4()
  * Purpose:     Sets the value of the alaram by taking the user inputs for the page3 
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void alaram4();




void lcd_color_red()
{
  LPC_GPIO2 -> FIOCLR |= (1<<0);
  LPC_GPIO2 -> FIOSET |= (1<<1);
  LPC_GPIO2 -> FIOSET |= (1<<2); 
    
}

void lcd_color_blue()
{
  LPC_GPIO2 -> FIOSET |= (1<<0);
  LPC_GPIO2 -> FIOSET |= (1<<1);
  LPC_GPIO2 -> FIOCLR |= (1<<2);   
    
}

void lcd_color_green()
{
  LPC_GPIO2 -> FIOSET |= (1<<0);
  LPC_GPIO2 -> FIOCLR |= (1<<1);
  LPC_GPIO2 -> FIOSET |= (1<<2);   
    
}


void lcd_changelocation()
{
    unsigned char i;
    if(lcd_cursorblink_flag==0)                                //To check the corner conditions as in cursor blink should occur during the column change
    {
    if(lcd_cursor_column_flag==1)
    {
           for(i=0;i<6;i++)
    {
     lcd_data(lcdbuffer[i+(6*0x00)]);                        //as there is a column change make sure the previous cursor is erased and moved to the new location
    }
    }
    }           
        lcd_cmd(0xB0 | page[pagevalue]);
        column_change();                                    //function to change the column
   if(lcd_cursor_column_flag==1)
    {
          cursor_blink();                                   //display the cursor in new position
    } 
}

void lcd_write_string(unsigned char *lcdstring)
{
    unsigned char i;
    for(i=0;i<string_count;i++)
    {
        lcd_write_character(lcdstring[i]);                 //to write the value of string on to the lcd by using the lcd_write_character function
    }
    
}

void lcd_write_character(unsigned char line)
{
 if(lcd_timer_flag==0)
 {
 glo_line=line;
 }
 unsigned char i;
 for(i=0;i<6;i++)
 {
     //lcd_data(0xff);
     lcd_data(lcdbuffer[i+(6*line)]);                                             //use lcddata to write one column at a time
     column++;                                                                    // keep track of the column
 }
     check_column();
     if(lcd_cursorblink_flag == 0)
     {
     cursor_blink();  
     }  
  
}

void check_column()
{

    if(column==126)                                        //checking the end of the column
    {
            if(pagevalue == 7)                             //checking the end of the pages
             {
               pagevalue = 0;
             }
            else
            {
                pagevalue=pagevalue+1;
            }
        lcd_cmd(0xB0 | page[pagevalue]);
        column=0x00;
        column_change();
        
    }

    
}



void initialize_lcd()
{
     
  lcd_color_green();
  LPC_GPIO0 -> FIOCLR |= (1<<4);              //Reset condition--L
  wait(.5);                                   //500ms suggested by the datasheet for initializing the system
  LPC_GPIO0 -> FIOSET |= (1<<4);              //Reset condition--H 
  lcd_cmd(0xA3);                              //LCD bias 1/7th
  wait(0.1);                                  //100msec delay
  lcd_cmd(0xA0);                              //ADC select 0-normal
  wait(0.1);
  lcd_cmd(0xC0);                              //SHL select 0-normal direction
  wait(0.1);
  lcd_cmd(0x40);                              //Initial display line
  wait(0.1);                                 
  lcd_cmd(0x2C);                              //voltage regulator
  wait(.5);
  lcd_cmd(0x2e);                              //voltage regulator
  wait(.5);
  lcd_cmd(0x2f);                               //voltage regulator
  wait(.5);
  lcd_clear();
  lcd_cmd(0xAF);                                //Display ON
  wait(.2);
  pagevalue=2;
  column=0x78;
  lcd_changelocation();

}

void column_change()
{
    unsigned char columnh;
    unsigned char columnl;
    columnh= column & 0xf0;
    columnh= columnh >> 4;
    columnl= column & 0x0f;
    lcd_cmd( 0x10 | columnh);
    lcd_cmd( 0x00 | columnl);
 
}
 
void initialize_lcd_pinouts()
{
    LPC_PINCON -> PINSEL3 &= ~((1<<5)|(1<<4));
    LPC_GPIO1-> FIODIR |= (1<<18);
    
    LPC_PINCON -> PINSEL0&= ~((1<<9)|(1<<8));                                  // /RST
    LPC_PINCON -> PINSEL0&= ~((1<<11)|(1<<10));                                // A0
    LPC_PINCON -> PINSEL0&= ~((1<<20)|(1<<21));                                //SID
    LPC_PINCON -> PINSEL0&= ~((1<<23)|(1<<22));                                //SCLK
    LPC_GPIO0-> FIODIR |= (1<<4);                                              //output 
    LPC_GPIO0-> FIODIR |= (1<<5);                                              //output 
    LPC_GPIO0-> FIODIR |= (1<<10);                                             //output 
    LPC_GPIO0-> FIODIR |= (1<<11);                                             //output   
    
    
    //RGB outputs for the LCD SCREEN 
    LPC_GPIO2-> FIODIR |= (1<<0);//output                                      //R
    LPC_GPIO2-> FIODIR |= (1<<1);//output                                      //G
    LPC_GPIO2-> FIODIR |= (1<<2);//output                                      //B

 
}


//Bit banging to that data can be send to the LCD on the SDI line on the low to high transition of sclk
void lcd_cmd (unsigned char cmdvalue)
{
    unsigned char k;
    unsigned char i;
    unsigned char j;
    k = 0x80;
    LPC_GPIO0 -> FIOCLR |= (1<<5);       //making A0 low as we are sending command
    for (i=0;i<=7;i++)
    {
    j = (cmdvalue & k);
    
    LPC_GPIO0 -> FIOCLR |= (1<<11);      //clearing the clock
    delay_us_lcd();                      //calculated delay for efficent operation of LCD
    if(j==0)
    {
    LPC_GPIO0 -> FIOCLR |= (1<<10);       //SID line cleared
    }
    else
    {
        LPC_GPIO0 -> FIOSET |= (1<<10);   //SID line high
    }
    delay_us_lcd();
    LPC_GPIO0 -> FIOSET |= (1<<11);      //setting the clock
    delay_us_lcd();
    k = k >> 1;
    }
}

//same procedure as lcd_cmd expect for A0 line is made high
void lcd_data (unsigned char datavalue)
{
    unsigned char k;
    unsigned char i;
    bool j;
    k = 0x80;
    LPC_GPIO0 -> FIOSET |= (1<<5);                                                  //A0 is set
    for (i=0;i<=7;i++)
    {
    j = (datavalue & k);
    LPC_GPIO0 -> FIOCLR |= (1<<11);
    delay_us_lcd();
    if(j==0)
    {
        LPC_GPIO0 -> FIOCLR |= (1<<10);
    }
    else
    {
        LPC_GPIO0 -> FIOSET |= (1<<10);
    }
    delay_us_lcd();
    LPC_GPIO0 -> FIOSET |= (1<<11);
    delay_us_lcd();
    k = k >> 1;
    }
}

void delay_us_lcd()
{
    unsigned char i;
    for(i=0;i<=1;i++)
    {
    }
    
}
void lcd_clear()
{
  unsigned char p, c;
  unsigned char temp;
  temp=0xB0;
  for(p = 0; p < 8; p++) 
  {
     
     lcd_cmd(temp);
     lcd_cmd(0x10);
     lcd_cmd(0x00);
     for(c = 0; c < 130; c++) 
     {
       lcd_data(0x0);                                                  //writting zero to all columns in all pages
     }
     temp=temp+1;

  }

}



//similar to lcd expext that rtc timer is not cleared
void lcd_clear1()
{
  unsigned char p, c;
  unsigned char temp;
  temp=0xB0;
  for(p = 0; p < 8; p++) 
  {
     if(temp !=  0xB4)
     {
     lcd_cmd(temp);
     lcd_cmd(0x10);
     lcd_cmd(0x00);
     for(c = 0; c < 127; c++) 
     {
       lcd_data(0x0); 
     }
     
     }
     else
     {
     lcd_cmd(temp);
     lcd_cmd(0x10);
     lcd_cmd(0x00);
     for(c = 0; c <42 ; c++) 
     {
       lcd_data(0x0);                          //RTC not cleared other than RTC others are cleared
     }
         
     }
     temp=temp+1;
  }


}
 
 
 
//TEST CODE FOR Troubelshooting
void lcd_test()
{        
      lcd_write_character(0);
 lcd_write_character(0);
  lcd_write_character(1);
  lcd_write_character(1);
  lcd_write_character(2);
  lcd_write_character(3);
  lcd_write_character(4);
   lcd_write_character(5);
  lcd_write_character(6);
  lcd_write_character(7);
  lcd_write_character(8);
   lcd_write_character(9);
   lcd_cmd(0xB2);
   lcd_cmd(0x10);
   lcd_cmd(0x00);
   lcd_write_character(10);
   lcd_write_character(11);
   lcd_write_character(12);
   lcd_write_character(13);
   lcd_write_character(14);
   lcd_write_character(15);
   lcd_write_character(16);
   lcd_write_character(17);
   lcd_write_character(18);
   lcd_write_character(19);
   lcd_cmd(0xB1);
   lcd_cmd(0x10);
   lcd_cmd(0x00);
   lcd_write_character(20);
   lcd_write_character(21);
   lcd_write_character(22);
   lcd_write_character(23);
   lcd_write_character(24);
   lcd_write_character(25);
   lcd_write_character(26);
   lcd_write_character(27);
   lcd_write_character(28);
   lcd_write_character(29);
   lcd_write_character(30);
   lcd_write_character(31);
   lcd_write_character(32);
   lcd_write_character(33);
   lcd_write_character(34);
   lcd_write_character(35);
}
void cursor_blink()
{

  lcd_cmd(0xE0);                    //stop column address from incrementing
   unsigned char i;
   for(i=0;i<6;i++)
    {
     //lcd_data(0xff);
     lcd_data(lcdbuffer[i+(6*0x01)]);
    }
  lcd_cmd(0xEE);                   //start column address from incrementinf

}

// This is one very huge function with many conditional statements included and this function every 60 seconds by using  repeteive interrupt 
//as my declarations did not use pointer there are five similar sets of code
void lcd_time_display()
{
    char *q;
    unsigned char temp1;
    unsigned char temp2;
    unsigned char i;
    unsigned char lcd_touch_alaramout;
    unsigned char j;
    unsigned char k;
    unsigned char temp;
    lcd_refresh=1;
    temp1=column;
    temp2=pagevalue;
    column=42;
    pagevalue=7;
   lcd_cmd(0xB0|page[pagevalue]);
    column_change();
    i=0;
    time_t seconds = time(NULL);                // This function is taken from mbed library
    q=ctime(&seconds);                          //current value of time is stored
    while( *q != 0x00 )
    {  
     temp=*q;
     timevalue[i]=temp;                       // read the time value in tis format 2015 nov 29  17:21:22 
     q++;
     i++;
    }

     i=3;
    for(i=3;i<16;i++)
    {
      lcd_timer_flag=1;
      lcd_write_character(timevalue[i]);    //display only nov 29 12:21 format on LCD     
    }
    i=0;

//    time_t seconds = time(NULL);
    lcd_timer_flag=0;
    column=temp1;   
    pagevalue=temp2;
    lcd_cursor_column_flag=1;
    lcd_changelocation();
    lcd_cursor_column_flag=0; 
           if ((seconds == (alaram1sec+2)) || (seconds == (alaram2sec+2)) || (seconds == (alaram3sec+2)) || (seconds == (alaram4sec+2)) || (seconds == (alaram5sec+2)))
      {
       //Check if any alaram occured
       
        if (seconds == (alaram1sec+2)) //check which alaram occured
        {
            alaram1_occured_flag =1;
        }
        if (seconds == (alaram2sec+2))
        {
            alaram2_occured_flag =1;
        }
        if (seconds == (alaram3sec+2))
        {
            alaram3_occured_flag =1;
        }
        if (seconds == (alaram4sec+2))
        {
            alaram4_occured_flag =1;
        }
        if (seconds == (alaram5sec+2))
        {
            alaram5_occured_flag =1;
        }
        
        lcd_cmd(0xAE);                                   //Display OFF
        wait(.1);
        xcor=0;
        ycor=0;
        lcd_touch_alaramout=0;                          
        while(lcd_touch_alaramout==0)                  //Wait till touch screen is pressed at any plce
        {
            LPC_GPIO2 -> FIOSET |= (1<<4);
            lcd_color_red();                           //Flashing of LCD background color
            for(j=0;j<5;j++)
            {
              for(k=0;k<3;k++)
               {
                  for(i=0;i<5;i++)
                    {
                       adc_read();                   //read the value of adc connected to touchscreen
                    }
            if(((xcor > 0x1000 )&&(ycor >0x1000)))
           {
            lcd_touch_alaramout=1;
            goto endalaram;
           }
        }
        
            }
            //printf("\n\r i am out of red \r\n");
            LPC_GPIO2 -> FIOCLR |= (1<<4);
            lcd_color_blue();
            for(j=0;j<5;j++)
            {
              for(k=0;k<3;k++)
               {
                  for(i=0;i<5;i++)
                    {
                       adc_read();
                    }
            if(((xcor > 0x1000 )&&(ycor >0x7100)))
           {
            printf("\n\rsuccess\n\r");
            //touchpressed_done_flag=1;
            lcd_touch_alaramout=1;
            goto endalaram;
            }
            }
            
        
            }           
            //printf("\n\r i am out of blue \r\n");
            //LPC_GPIO2 -> FIOSET |= (1<<4);
            lcd_color_green();
            for(j=0;j<5;j++)
            {
              for(k=0;k<3;k++)
               {
                  for(i=0;i<5;i++)
                    {
                       adc_read();
                    }
            if(((xcor > 0x1000 )&&(ycor >0x7100)))
           {
            printf("\n\rsuccess\n\r");
            //touchpressed_done_flag=1;
            lcd_touch_alaramout=1;
            goto endalaram;
           }
               }
        
            }
           // printf("\n\r i am out of green \r\n");
        }
      }
      if(lcd_touch_alaramout==1)                           //Once the alaram is done it is important to clear it and trafer the previous alaram to its position
      {
       endalaram:
       LPC_GPIO2 -> FIOCLR |= (1<<4);
       lcd_color_green();
        lcd_cmd(0xAF);                                //Display ON
         wait(.2);
       printf("\r\niam out\r\n");
       lcd_touch_alaramout=0;
 
       if(alaram1_occured_flag==1)
       {
           
            if(alaram_count == 1)
            {
             alaram1_lcd_flag = 0;                // make the flag for alarm 1 zer0
             alaram1sec=0;                        // make the alaram1 zero
             alaram_count--;                      //decreement alarm count
            }
           if(alaram_count == 2)
           {
            desc_count=desc_count2;
            for(i=0;i<desc_count2;i++)
            {
            alaram_des_1[i]=alaram_des_2[i];    //exchange the descriptions between 1 and 2 asciivalue
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_1[i]=alaram_time_2_1[i];  //exchange the alaram between 1 and 2 hours  ascii value
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_2[i]=alaram_time_2_2[i];  //exchange the alaram between 1 and 2 minutes  asciivalue
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_3[i]=alaram_time_2_3[i];  //exchange the alaram between 1 and 2 Months asciivalue
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_4[i]=alaram_time_2_4[i];  //exchange the alaram between 1 and 2 Day ascii value
            }
            alaram_time1_h=alaram_time2_h;      //decimal values of hour exchanged between alaram 1 and alaram2
            alaram_time1_m=alaram_time2_m;      //decimal values of minutes exchanged between alaram 1 and alaram2
            alaram_time1_d=alaram_time2_d;      //decimal values of days exchanged between alaram 1 and alaram2
            alaram_time1_o=alaram_time2_o;      //decimal values of months exchanged between alaram 1 and alaram2
            alaram_count--;
            alaram2sec=0;
            alaram2_lcd_flag = 0;
            alaram1();                          //reload the value of alaram1
           } 
            if(alaram_count == 3)
           {    
            desc_count=desc_count2;
            for(i=0;i<desc_count2;i++)
            {
            alaram_des_1[i]=alaram_des_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_1[i]=alaram_time_2_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_2[i]=alaram_time_2_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_3[i]=alaram_time_2_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_4[i]=alaram_time_2_4[i];
            }
            alaram_time1_h=alaram_time2_h;
            alaram_time1_m=alaram_time2_m;
            alaram_time1_d=alaram_time2_d;
            alaram_time1_o=alaram_time2_o;
            
            
            desc_count2=desc_count3;
            for(i=0;i<desc_count3;i++)
            {
            alaram_des_2[i]=alaram_des_3[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_1[i]=alaram_time_3_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_2[i]=alaram_time_3_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_3[i]=alaram_time_3_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_4[i]=alaram_time_3_4[i];
            }
            alaram_time2_h=alaram_time3_h;
            alaram_time2_m=alaram_time3_m;
            alaram_time2_d=alaram_time3_d;
            alaram_time2_o=alaram_time3_o;
            alaram_count--;
            alaram3sec=0;
            alaram1();
            alaram2();
            alaram3_lcd_flag = 0;
           } 
        
       
            if(alaram_count == 4)
           {    
            desc_count=desc_count2;
            for(i=0;i<desc_count2;i++)
            {
            alaram_des_1[i]=alaram_des_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_1[i]=alaram_time_2_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_2[i]=alaram_time_2_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_3[i]=alaram_time_2_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_4[i]=alaram_time_2_4[i];
            }
            alaram_time1_h=alaram_time2_h;
            alaram_time1_m=alaram_time2_m;
            alaram_time1_d=alaram_time2_d;
            alaram_time1_o=alaram_time2_o;
            
            
            desc_count2=desc_count3;
            for(i=0;i<desc_count3;i++)
            {
            alaram_des_2[i]=alaram_des_3[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_1[i]=alaram_time_3_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_2[i]=alaram_time_3_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_3[i]=alaram_time_3_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_4[i]=alaram_time_3_4[i];
            }
            alaram_time2_h=alaram_time3_h;
            alaram_time2_m=alaram_time3_m;
            alaram_time2_d=alaram_time3_d;
            alaram_time2_o=alaram_time3_o;
            
        
            desc_count3=desc_count4;
            for(i=0;i<desc_count4;i++)
            {
            alaram_des_3[i]=alaram_des_4[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_1[i]=alaram_time_4_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_2[i]=alaram_time_4_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_3[i]=alaram_time_4_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_4[i]=alaram_time_4_4[i];
            }
            alaram_time3_h=alaram_time4_h;
            alaram_time3_m=alaram_time4_m;
            alaram_time3_d=alaram_time4_d;
            alaram_time3_o=alaram_time4_o;
            alaram_count--;
            alaram4sec=0;
            alaram1();
            alaram2();
            alaram3();
            alaram4_lcd_flag = 0;
           } 
           
            if(alaram_count == 5)
           {    
            desc_count=desc_count2;
            for(i=0;i<desc_count2;i++)
            {
            alaram_des_1[i]=alaram_des_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_1[i]=alaram_time_2_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_2[i]=alaram_time_2_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_3[i]=alaram_time_2_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_1_4[i]=alaram_time_2_4[i];
            }
            alaram_time1_h=alaram_time2_h;
            alaram_time1_m=alaram_time2_m;
            alaram_time1_d=alaram_time2_d;
            alaram_time1_o=alaram_time2_o;
            
            
            desc_count2=desc_count3;
            for(i=0;i<desc_count3;i++)
            {
            alaram_des_2[i]=alaram_des_3[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_1[i]=alaram_time_3_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_2[i]=alaram_time_3_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_3[i]=alaram_time_3_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_4[i]=alaram_time_3_4[i];
            }
            alaram_time2_h=alaram_time3_h;
            alaram_time2_m=alaram_time3_m;
            alaram_time2_d=alaram_time3_d;
            alaram_time2_o=alaram_time3_o;
            
        
            desc_count3=desc_count4;
            for(i=0;i<desc_count4;i++)
            {
            alaram_des_3[i]=alaram_des_4[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_1[i]=alaram_time_4_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_2[i]=alaram_time_4_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_3[i]=alaram_time_4_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_4[i]=alaram_time_4_4[i];
            }
            alaram_time3_h=alaram_time4_h;
            alaram_time3_m=alaram_time4_m;
            alaram_time3_d=alaram_time4_d;
            alaram_time3_o=alaram_time4_o;
            
                    
            desc_count4=desc_count5;
            for(i=0;i<desc_count5;i++)
            {
            alaram_des_4[i]=alaram_des_5[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_1[i]=alaram_time_5_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_2[i]=alaram_time_5_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_3[i]=alaram_time_5_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_4[i]=alaram_time_5_4[i];
            }
            alaram_time4_h=alaram_time5_h;
            alaram_time4_m=alaram_time5_m;
            alaram_time4_d=alaram_time5_d;
            alaram_time4_o=alaram_time5_o;
            
            
            
            alaram_count--;
            alaram5sec=0;
            
            
            
            alaram1();
            alaram2();
            alaram3();
            alaram4();
            alaram5_lcd_flag = 0;
           } 
           
           
           
       } 
       
       
       
       
       if(alaram2_occured_flag==1)
       {           
           if(alaram_count == 2)
           {
            alaram_count--;
            alaram2sec=0;
            alaram2_lcd_flag = 0;
           // alaram1();
           } 
            if(alaram_count == 3)
           {    

            desc_count2=desc_count3;
            for(i=0;i<desc_count3;i++)
            {
            alaram_des_2[i]=alaram_des_3[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_1[i]=alaram_time_3_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_2[i]=alaram_time_3_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_3[i]=alaram_time_3_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_4[i]=alaram_time_3_4[i];
            }
            alaram_time2_h=alaram_time3_h;
            alaram_time2_m=alaram_time3_m;
            alaram_time2_d=alaram_time3_d;
            alaram_time2_o=alaram_time3_o;
            alaram_count--;
            alaram3sec=0;
            //alaram1();
            alaram2();
            alaram3_lcd_flag = 0;
           } 
        
       
            if(alaram_count == 4)
           {                
            desc_count2=desc_count3;
            for(i=0;i<desc_count3;i++)
            {
            alaram_des_2[i]=alaram_des_3[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_1[i]=alaram_time_3_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_2[i]=alaram_time_3_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_3[i]=alaram_time_3_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_4[i]=alaram_time_3_4[i];
            }
            alaram_time2_h=alaram_time3_h;
            alaram_time2_m=alaram_time3_m;
            alaram_time2_d=alaram_time3_d;
            alaram_time2_o=alaram_time3_o;
            
        
            desc_count3=desc_count4;
            for(i=0;i<desc_count4;i++)
            {
            alaram_des_3[i]=alaram_des_4[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_1[i]=alaram_time_4_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_2[i]=alaram_time_4_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_3[i]=alaram_time_4_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_4[i]=alaram_time_4_4[i];
            }
            alaram_time3_h=alaram_time4_h;
            alaram_time3_m=alaram_time4_m;
            alaram_time3_d=alaram_time4_d;
            alaram_time3_o=alaram_time4_o;
            alaram_count--;
            alaram4sec=0;
           // alaram1();
            alaram2();
            alaram3();
            alaram4_lcd_flag = 0;
           } 
           
            if(alaram_count == 5)
           {    
                        
            desc_count2=desc_count3;
            for(i=0;i<desc_count3;i++)
            {
            alaram_des_2[i]=alaram_des_3[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_1[i]=alaram_time_3_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_2[i]=alaram_time_3_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_3[i]=alaram_time_3_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_2_4[i]=alaram_time_3_4[i];
            }
            alaram_time2_h=alaram_time3_h;
            alaram_time2_m=alaram_time3_m;
            alaram_time2_d=alaram_time3_d;
            alaram_time2_o=alaram_time3_o;
            
        
            desc_count3=desc_count4;
            for(i=0;i<desc_count4;i++)
            {
            alaram_des_3[i]=alaram_des_4[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_1[i]=alaram_time_4_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_2[i]=alaram_time_4_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_3[i]=alaram_time_4_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_4[i]=alaram_time_4_4[i];
            }
            alaram_time3_h=alaram_time4_h;
            alaram_time3_m=alaram_time4_m;
            alaram_time3_d=alaram_time4_d;
            alaram_time3_o=alaram_time4_o;
            
                    
            desc_count4=desc_count5;
            for(i=0;i<desc_count5;i++)
            {
            alaram_des_4[i]=alaram_des_5[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_1[i]=alaram_time_5_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_2[i]=alaram_time_5_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_3[i]=alaram_time_5_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_4[i]=alaram_time_5_4[i];
            }
            alaram_time4_h=alaram_time5_h;
            alaram_time4_m=alaram_time5_m;
            alaram_time4_d=alaram_time5_d;
            alaram_time4_o=alaram_time5_o;
            
            
            
            alaram_count--;
            alaram5sec=0;
            //alaram1();
            alaram2();
            alaram3();
            alaram4();
            alaram5_lcd_flag = 0;
           } 
       }    
       
       
        if(alaram3_occured_flag==1)
       {
           
            if(alaram_count == 3)
           {    
            alaram_count--;
            alaram3sec=0;
            //alaram1();
            //alaram2();
            alaram3_lcd_flag = 0;
           } 
        
       
            if(alaram_count == 4)
           {                
                    
            desc_count3=desc_count4;
            for(i=0;i<desc_count4;i++)
            {
            alaram_des_3[i]=alaram_des_4[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_1[i]=alaram_time_4_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_2[i]=alaram_time_4_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_3[i]=alaram_time_4_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_4[i]=alaram_time_4_4[i];
            }
            alaram_time3_h=alaram_time4_h;
            alaram_time3_m=alaram_time4_m;
            alaram_time3_d=alaram_time4_d;
            alaram_time3_o=alaram_time4_o;
            alaram_count--;
            alaram4sec=0;
           // alaram1();
           // alaram2();
            alaram3();
            alaram4_lcd_flag = 0;
           } 
           
            if(alaram_count == 5)
           {    
                        

            
        
            desc_count3=desc_count4;
            for(i=0;i<desc_count4;i++)
            {
            alaram_des_3[i]=alaram_des_4[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_1[i]=alaram_time_4_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_2[i]=alaram_time_4_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_3[i]=alaram_time_4_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_3_4[i]=alaram_time_4_4[i];
            }
            alaram_time3_h=alaram_time4_h;
            alaram_time3_m=alaram_time4_m;
            alaram_time3_d=alaram_time4_d;
            alaram_time3_o=alaram_time4_o;
            
                    
            desc_count4=desc_count5;
            for(i=0;i<desc_count5;i++)
            {
            alaram_des_4[i]=alaram_des_5[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_1[i]=alaram_time_5_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_2[i]=alaram_time_5_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_3[i]=alaram_time_5_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_4[i]=alaram_time_5_4[i];
            }
            alaram_time4_h=alaram_time5_h;
            alaram_time4_m=alaram_time5_m;
            alaram_time4_d=alaram_time5_d;
            alaram_time4_o=alaram_time5_o;
            
            
            
            alaram_count--;
            alaram5sec=0;
            //alaram1();
            //alaram2();
            alaram3();
            alaram4();
            alaram5_lcd_flag = 0;
           } 
       }    
       
       
       
       
              if(alaram4_occured_flag==1)
       {
           
            if(alaram_count == 4)
           {                
                    
 
            alaram_count--;
            alaram4sec=0;
           // alaram1();
           // alaram2();
           // alaram3();
            alaram4_lcd_flag = 0;
           } 
           
            if(alaram_count == 5)
           {    
                        

            desc_count4=desc_count5;
            for(i=0;i<desc_count5;i++)
            {
            alaram_des_4[i]=alaram_des_5[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_1[i]=alaram_time_5_1[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_2[i]=alaram_time_5_2[i];
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_3[i]=alaram_time_5_3[i];  
            }
            for(i=0;i<2;i++)
            {
             alaram_time_4_4[i]=alaram_time_5_4[i];
            }
            alaram_time4_h=alaram_time5_h;
            alaram_time4_m=alaram_time5_m;
            alaram_time4_d=alaram_time5_d;
            alaram_time4_o=alaram_time5_o;
            
            
            
            alaram_count--;
            alaram5sec=0;
            alaram4();
            alaram5_lcd_flag = 0;
           } 
       }  



       if(alaram5_occured_flag==1)
       {
            if(alaram_count == 5)
           {    
            alaram_count--;
            alaram5sec=0;
            alaram5_lcd_flag = 0;
           } 
       }    
             
     }
    //Printf("\r\n i am going out\n\r");
}






