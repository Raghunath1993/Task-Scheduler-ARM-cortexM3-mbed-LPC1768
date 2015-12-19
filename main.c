/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * Raghunath Reddy
 * ECEN 5613, Task scheduler
 * Fall 2016,Prof. Mc Clure
 * University of Colorado at Boulder
 * ---------------------------------------
 * This file is an application specific file which uses other .h files to control LCD, keypad,touch screen.This is used to make dedicated embedded device name
 task scheduler to work
 embed.h is developed by Mihail Stoyano ,which i am using for system initalization and RTC
 * ------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
#include "mbed.h"                                                                      //Already present in the mbed complier used for RTC,ADC
#include "touchscreen.h"
#include "lcdes.h"
#include "keypadesd.h"
Ticker lcd_time1;                                                                      //repetetive interrupt


/* Prototypes ---------------------------------------------------- */
 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void login
  * Purpose:     Waits for the user to input the data and the matches with already existing username and password if it matches than goes into page or else erroer
    condition is displayed
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void login();

 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void page1
  * Purpose:     Page 1 is the home screen where the description of all the alarams , time for the alaram is also displayed
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void page1();


 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void login_user
  * Purpose:     Checks if  the enetered data matches whith the existing dat of username and password
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void login_user();

 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void initalize_rtc
  * Purpose:     This is written once to set the RTC
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void initialize_rtc();


 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void hide_character
  * Purpose:     While entering the password after a certain delay the character is turned to * for security reasons
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void hide_character();

 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void page2
  * Purpose:     This page is waits for the user to enter the descripeion of the task
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void page2();

 /*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void page3
  * Purpose:     This page allows tghe user to enter the time and day for the alaram
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */

void page3();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void page3
  * Purpose:     This page allows tghe user to enter the time and day for the alaram
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void page4();
void test_buzzer();
void adc_check_done();

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  * void page3
  * Purpose:     Below all the functions named write are functions to write into LCD example: write_error writes the word error on the LCD
  * Calcuations: None
  * Return:      None
  *---------------------------------------------------------------- */
void login_write_error();
void login_write();
void login_write_login();
void login_write_username();
void login_write_password();
void lcd_write_string();
void lcd_write_add();
void lcd_write_delete();
void lcd_write_done();
void lcd_write_describe();
void lcd_write_description();
void lcd_write_description2();
void lcd_write_description3();
void lcd_write_description4();
void lcd_write_description5();
void lcd_write_settime();
void lcd_write_timeformat();
void lcd_write_reset();
void lcd_write_time1();
void lcd_write_time2();
void lcd_write_time3();
void lcd_write_time4();
void lcd_write_time5();
void lcd_write_deletetask();


int main()
{
  initialize_lcd_pinouts();
  initialize_lcd();
  keypad_init();
  lcd_time_display();
  lcd_time1.attach(&lcd_time_display,60.0);
  login();
    while(1)
    {
    page1();
    if(touchpressed_add_flag==1)
    {
    page2();
    page3();
    }
    else if(touchpressed_delete_flag==1)
    {
    page4();
    }
    }
  }
}

void page4()
{
      unsigned char i;

      changemode=0;                                          // change mode to zero
      LPC_GPIO0 -> FIOSET |= (1<<17);                        //Mode 0 led set
      LPC_GPIO0 -> FIOCLR |= (1<<15);                        //Mode 1 Led reset
      LPC_GPIO0 -> FIOCLR |= (1<<16);                        //Mode 2 Led reset
      LPC_GPIO2 -> FIOCLR |= (1<<3);                         //Mode 3 Led reset
      //alaram1_lcd_flag = 0;
      lcd_clear1();
      pagevalue=6;
      column=48;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_done();
      pagevalue=3;
      column=00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_deletetask();                                //deletetask

     for(keypress_count=0;keypress_count<1;keypress_count++)
      {
       if (keypress_count==0)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();                               //wait  till the the number of the task to be deleted entered
        if (keypress_count==0)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_delete = glo_line;
      }

       alaram_time_delete = (alaram_time_delete-0x30);          //converting into decimal
     //  printf("alaram time1_delete is %d",alaram_time_delete);
      if (alaram_time_delete > alaram_count)                  //corner conditions id the user wrond number
      {
          lcd_color_red();
          wait(1);
          lcd_color_green();
          goto endpage4;
      }
       // From here this functions is similat to the function in the LCds.h named ldc_time_display()
       if(alaram_time_delete==1)
       {

            if(alaram_count == 1)
            {
             alaram1_lcd_flag = 0;
             alaram1sec=0;
             alaram_count--;
            }
           if(alaram_count == 2)
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
            alaram_count--;
            alaram2sec=0;
            alaram2_lcd_flag = 0;
            alaram1();
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




              if(alaram_time_delete==2)
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


        if(alaram_time_delete==3)
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




              if(alaram_time_delete==4)
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
            //alaram1();
            //alaram2();
            //alaram3();
            alaram4();
            alaram5_lcd_flag = 0;
           }
       }
       if(alaram_time_delete==5)
       {
            if(alaram_count == 5)
           {
            alaram_count--;
            alaram5sec=0;
            alaram5_lcd_flag = 0;
           }
       }
       xcor=0;
       ycor=0;
       touchpressed_done2_flag=0;
       while(touchpressed_done2_flag == 0)
       {
        for(i=0;i<5;i++)
        {
          adc_read();
          if(((xcor > 0x5200 && xcor< 0x7400)&&(ycor >0x7100 && ycor< 0x7C00)))
          {
           printf("\n\rsuccess\n\r");
           touchpressed_done2_flag=1;
           //goto endloop1;
          }
        }
       }
       endpage4:
       printf("\n\r i am here 6\n\r");

       }


void test_buzzer()
{
    LPC_GPIO2 -> FIOSET |= (1<<4);
    wait(2);
    LPC_GPIO2 -> FIOCLR |= (1<<4);
}

void initialize_rtc()
{
set_time(1449510960);  // seconds for dec 7 5:47 pm
}

void alaram1()
{

       struct tm t;
        t.tm_sec = 00;    // 0-59
        t.tm_min = alaram_time1_m;    // 0-59
       t.tm_hour = alaram_time1_h;   // 0-23
       t.tm_mday = alaram_time1_d;;   // 1-31
       t.tm_mon = (alaram_time1_o - 1);     // 0-11
       t.tm_year = 115;  // year since 1900
       time_t seconds = mktime(&t);
       alaram1sec= seconds;
       printf("Minutes = %d\n", alaram_time1_m);
       printf("Hours = %d\n", alaram_time1_h);
       printf("Time as seconds since January 1, 1970 33 = %d\n", seconds);
       printf("alaram1 value is %d \n\r ",alaram1);
       alaram1_flag=1;

}

void alaram2()
{

       struct tm t;
        t.tm_sec = 00;    // 0-59
        t.tm_min = alaram_time2_m;    // 0-59
       t.tm_hour = alaram_time2_h;   // 0-23
       t.tm_mday = alaram_time2_d;;   // 1-31
       t.tm_mon = (alaram_time2_o - 1);     // 0-11
       t.tm_year = 115;  // year since 1900
       time_t seconds = mktime(&t);
       alaram2sec= seconds;
       printf("Minutes = %d\n", alaram_time2_m);
       printf("Hours = %d\n", alaram_time2_h);
       printf("Time as seconds since January 1, 1970 33 = %d\n", seconds);
       printf("alaram1 value is %d \n\r ",alaram2);
       alaram2_flag=1;

}


void alaram3()
{

       struct tm t;
        t.tm_sec = 00;    // 0-59
        t.tm_min = alaram_time3_m;    // 0-59
       t.tm_hour = alaram_time3_h;   // 0-23
       t.tm_mday = alaram_time3_d;;   // 1-31
       t.tm_mon = (alaram_time3_o - 1);     // 0-11
       t.tm_year = 115;  // year since 1900
       time_t seconds = mktime(&t);
       alaram3sec= seconds;
       printf("Minutes = %d\n", alaram_time3_m);
       printf("Hours = %d\n", alaram_time3_h);
       printf("Time as seconds since January 1, 1970 33 = %d\n", seconds);
       printf("alaram1 value is %d \n\r ",alaram3);
       alaram3_flag=1;

}

void alaram4()
{

       struct tm t;
        t.tm_sec = 00;    // 0-59
        t.tm_min = alaram_time4_m;    // 0-59
       t.tm_hour = alaram_time4_h;   // 0-23
       t.tm_mday = alaram_time4_d;;   // 1-31
       t.tm_mon = (alaram_time4_o - 1);     // 0-11
       t.tm_year = 115;  // year since 1900
       time_t seconds = mktime(&t);
       alaram4sec= seconds;
       printf("Minutes = %d\n", alaram_time4_m);
       printf("Hours = %d\n", alaram_time4_h);
       printf("Time as seconds since January 1, 1970 33 = %d\n", seconds);
       printf("alaram1 value is %d \n\r ",alaram4);
       alaram4_flag=1;

}


void alaram5()
{

       struct tm t;
        t.tm_sec = 00;    // 0-59
        t.tm_min = alaram_time5_m;    // 0-59
       t.tm_hour = alaram_time5_h;   // 0-23
       t.tm_mday = alaram_time5_d;;   // 1-31
       t.tm_mon = (alaram_time5_o - 1);     // 0-11
       t.tm_year = 115;  // year since 1900
       time_t seconds = mktime(&t);
       alaram5sec= seconds;
       printf("Minutes = %d\n", alaram_time5_m);
       printf("Hours = %d\n", alaram_time5_h);
       printf("Time as seconds since January 1, 1970 33 = %d\n", seconds);
       printf("alaram1 value is %d \n\r ",alaram5);
       alaram5_flag=1;

}







void page1()
{     //
      page1start:
      lcd_clear1();
      pagevalue=6;
      column=0x00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_add();
      pagevalue=6;
      column=78;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_delete();

      // from here alaramx_lcd_flag tells if the alaram has been assigned if yes than it prints out on the LCD
      if(alaram1_lcd_flag == 1)
      {
      pagevalue=0;
      column=00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_description(); //write the description on the LCD
      pagevalue=0;
      column=60;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_time1();        //write the value of the time on the LCD
      }


      if(alaram2_lcd_flag == 1)
      {
      pagevalue=1;
      column=00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_description2();
      pagevalue=1;
      column=60;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_time2();
      }

       if(alaram3_lcd_flag == 1)
      {

      pagevalue=2;
      column=00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_description3();
      pagevalue=2;
      column=60;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_time3();

      }

      if(alaram4_lcd_flag == 1)
      {

      pagevalue=3;
      column=00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_description4();
      pagevalue=3;
      column=60;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_time4();

      }


      if(alaram5_lcd_flag == 1)
      {

      pagevalue=4;
      column=00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_description5();
      pagevalue=4;
      column=60;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_time5();

      }



      touchpressed_add_flag=0;
      touchpressed_delete_flag=0;

      while (touchpressed_add_flag==0 && touchpressed_delete_flag==0 ) //wait till either add or delete button is touched on the screen
      {
        adc_read();
       if(((xcor > 0x1700 && xcor< 0x2F00)&&(ycor >0x7A00 && ycor< 0x8500)))
       {
        printf("\n\rsuccess\n\r");
        touchpressed_add_flag=1;
        alaram_count++;
        if(alaram_count > 5)
        {
            alaram_count=0;
        }
       }
        adc_read();
       if(((xcor > 0x7800 && xcor< 0xA600)&&(ycor >0x6A00 && ycor< 0x7D00)))
       {
        printf("\n\rsuccess\n\r");
        touchpressed_delete_flag=1;
       }
       if(lcd_refresh == 1)
       {
        lcd_refresh=0;
        goto page1start;
        }
       }
}



void page2()
{
      unsigned char i;
      touchpressed_done_flag=0;
      lcd_clear1();
      pagevalue=0;
      column=0x00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_describe();
      pagevalue=6;
      column=48;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_done();
      pagevalue=1;
      column=00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      xcor=0;
      ycor=0;
      touchpressed_done_flag=0;
      wait(1);
      page2_flag=1;
      if(alaram_count ==1 )
      {
      for(keypress_count=0;keypress_count<9;keypress_count++)
      {
       key_press();
       alaram_des_1[keypress_count]= glo_line;
       if(touchpressed_done_flag==1)
       {
        goto nextpage;
       }
      }
      nextpage:
      desc_count = keypress_count;
      touchpressed_done_flag=0;
      for(i=0;i<desc_count;i++)
      {
       printf("Entered string is %c",alaram_des_1[i]);
      }
      }
      if(alaram_count == 2 )
      {
      for(keypress_count=0;keypress_count<13;keypress_count++)
      {
       key_press();
       alaram_des_2[keypress_count]= glo_line;
       if(touchpressed_done_flag==1)
       {
        goto nextpage2;
       }
      }
      nextpage2:
      desc_count2 = keypress_count;
      touchpressed_done_flag=0;
      for(i=0;i<desc_count2;i++)
      {
       printf("Entered string is %c",alaram_des_2[i]);
      }
      }


      if(alaram_count == 3 )
      {
      for(keypress_count=0;keypress_count<13;keypress_count++)
      {
       key_press();
       alaram_des_3[keypress_count]= glo_line;
       if(touchpressed_done_flag==1)
       {
        goto nextpage3;
        }
      }
      nextpage3:
      desc_count3 = keypress_count;
      touchpressed_done_flag=0;
      for(i=0;i<desc_count3;i++)
      {
       printf("Entered string is %c",alaram_des_3[i]);
      }
      }


     if(alaram_count == 4 )
      {
      for(keypress_count=0;keypress_count<13;keypress_count++)
      {
       key_press();
       alaram_des_4[keypress_count]= glo_line;
       if(touchpressed_done_flag==1)
       {
        goto nextpage4;
        }
      }
      nextpage4:
      desc_count4 = keypress_count;
      touchpressed_done_flag=0;
      for(i=0;i<desc_count4;i++)
      {
       printf("Entered string is %c",alaram_des_4[i]);
      }
      }

     if(alaram_count == 5 )
      {
      for(keypress_count=0;keypress_count<13;keypress_count++)
      {
       key_press();
       alaram_des_5[keypress_count]= glo_line;
       if(touchpressed_done_flag==1)
       {
        goto nextpage5;
        }
      }
      nextpage5:
      desc_count5 = keypress_count;
      touchpressed_done_flag=0;
      for(i=0;i<desc_count5;i++)
      {
       printf("Entered string is %c",alaram_des_5[i]);
      }
      }

}

void page3()
{
      unsigned char touchpressed_done_flag2;
      unsigned char i;
      page3start:
      changemode=0;
      LPC_GPIO0 -> FIOSET |= (1<<17);
      LPC_GPIO0 -> FIOCLR |= (1<<15);
      LPC_GPIO0 -> FIOCLR |= (1<<16);
      LPC_GPIO2 -> FIOCLR |= (1<<3);
      lcd_clear1();
      pagevalue=0;
      column=0x00;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_settime();
      pagevalue=3;
      column=18;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_timeformat();
      pagevalue=6;
      column=48;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_write_done();
      pagevalue=3;
      column=18;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      keypress_count=0;

      if(alaram_count == 1)
      {
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_1_3[keypress_count]= glo_line;
      }
       alaram_time1_d = ((alaram_time_1_3[0]-0x30)*10) + (alaram_time_1_3[1]-0x30);
       printf("alaram time1_d is %d",alaram_time1_d);

      pagevalue=3;
      column=36;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_1_4[keypress_count]= glo_line;
      }
       alaram_time1_o = ((alaram_time_1_4[0]-0x30)*10) + (alaram_time_1_4[1]-0x30);
       printf("alaram time1_o is %d",alaram_time1_o);
      pagevalue=3;
      column=54;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_1_1[keypress_count]= glo_line;
      }
       alaram_time1_h = ((alaram_time_1_1[0]-0x30)*10) + (alaram_time_1_1[1]-0x30);
       printf("alaram time1_h is %d",alaram_time1_h);
      pagevalue=3;
      column=72;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;

      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
       key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_1_2[keypress_count]= glo_line;
      }
       alaram_time1_m = ((alaram_time_1_2[0]-0x30)*10) + (alaram_time_1_2[1]-0x30);
       printf("alaram time1_m is %d",alaram_time1_m);
       if( (alaram_time1_m > 60) || (alaram_time1_h > 23) || (alaram_time1_d > 31) || (alaram_time1_o > 12))
       {
        lcd_color_red();
        wait(1);
        lcd_color_green();
        goto    page3start;
       }

       }


      else if(alaram_count == 2)
      {

      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_2_3[keypress_count]= glo_line;
      }
       alaram_time2_d = ((alaram_time_2_3[0]-0x30)*10) + (alaram_time_2_3[1]-0x30);
       printf("alaram time2_d is %d",alaram_time2_d);
      pagevalue=3;
      column=36;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_2_4[keypress_count]= glo_line;
      }
       alaram_time2_o = ((alaram_time_2_4[0]-0x30)*10) + (alaram_time_2_4[1]-0x30);
       printf("alaram time2_o is %d",alaram_time2_o);
      pagevalue=3;
      column=54;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_2_1[keypress_count]= glo_line;
      }
       alaram_time2_h = ((alaram_time_2_1[0]-0x30)*10) + (alaram_time_2_1[1]-0x30);
       printf("alaram time2_h is %d",alaram_time2_h);
      pagevalue=3;
      column=72;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;

      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
       key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_2_2[keypress_count]= glo_line;
      }
       alaram_time2_m = ((alaram_time_2_2[0]-0x30)*10) + (alaram_time_2_2[1]-0x30);
       printf("alaram time2_m is %d",alaram_time2_m);

        if( (alaram_time2_m > 60) || (alaram_time2_h > 23) || (alaram_time2_d > 31) || (alaram_time2_o > 12))
       {
        lcd_color_red();
        wait(1);
        lcd_color_green();
        goto    page3start;
       }

       }


      else if(alaram_count == 3)
      {
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_3_3[keypress_count]= glo_line;
      }
       alaram_time3_d = ((alaram_time_3_3[0]-0x30)*10) + (alaram_time_3_3[1]-0x30);
       printf("alaram time3_d is %d",alaram_time3_d);

      pagevalue=3;
      column=36;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_3_4[keypress_count]= glo_line;
      }
       alaram_time3_o = ((alaram_time_3_4[0]-0x30)*10) + (alaram_time_3_4[1]-0x30);
       printf("alaram time3_o is %d",alaram_time3_o);
      pagevalue=3;
      column=54;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_3_1[keypress_count]= glo_line;
      }
       alaram_time3_h = ((alaram_time_3_1[0]-0x30)*10) + (alaram_time_3_1[1]-0x30);
       printf("alaram time3_h is %d",alaram_time3_h);
      pagevalue=3;
      column=72;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;

      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
       key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_3_2[keypress_count]= glo_line;
      }
       alaram_time3_m = ((alaram_time_3_2[0]-0x30)*10) + (alaram_time_3_2[1]-0x30);
       printf("alaram time3_m is %d",alaram_time3_m);

        if( (alaram_time3_m > 60) || (alaram_time3_h > 23) || (alaram_time3_d > 31) || (alaram_time3_o > 12))
       {
        lcd_color_red();
        wait(1);
        lcd_color_green();
        goto    page3start;
       }
       }

    else if(alaram_count == 4)
      {
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_4_3[keypress_count]= glo_line;
      }
       alaram_time4_d = ((alaram_time_4_3[0]-0x30)*10) + (alaram_time_4_3[1]-0x30);
       printf("alaram time4_d is %d",alaram_time4_d);

      pagevalue=3;
      column=36;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_4_4[keypress_count]= glo_line;
      }
       alaram_time4_o = ((alaram_time_4_4[0]-0x30)*10) + (alaram_time_4_4[1]-0x30);
       printf("alaram time4_o is %d",alaram_time4_o);
      pagevalue=3;
      column=54;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_4_1[keypress_count]= glo_line;
      }
       alaram_time4_h = ((alaram_time_4_1[0]-0x30)*10) + (alaram_time_4_1[1]-0x30);
       printf("alaram time4_h is %d",alaram_time4_h);
      pagevalue=3;
      column=72;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;

      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
       key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_4_2[keypress_count]= glo_line;
      }
       alaram_time4_m = ((alaram_time_4_2[0]-0x30)*10) + (alaram_time_4_2[1]-0x30);
       printf("alaram time4_m is %d",alaram_time4_m);
        if( (alaram_time4_m > 60) || (alaram_time4_h > 23) || (alaram_time4_d > 31) || (alaram_time4_o > 12))
       {
        lcd_color_red();
        wait(1);
        lcd_color_green();
        goto    page3start;
       }
       }


      else if(alaram_count == 5)
      {
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_5_3[keypress_count]= glo_line;
      }
       alaram_time5_d = ((alaram_time_5_3[0]-0x30)*10) + (alaram_time_5_3[1]-0x30);
       printf("alaram time5_d is %d",alaram_time5_d);

      pagevalue=3;
      column=36;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_5_4[keypress_count]= glo_line;
      }
       alaram_time5_o = ((alaram_time_5_4[0]-0x30)*10) + (alaram_time_5_4[1]-0x30);
       printf("alaram time5_o is %d",alaram_time5_o);
      pagevalue=3;
      column=54;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      keypress_count=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
        key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_5_1[keypress_count]= glo_line;
      }
       alaram_time5_h = ((alaram_time_5_1[0]-0x30)*10) + (alaram_time_5_1[1]-0x30);
       printf("alaram time5_h is %d",alaram_time5_h);
      pagevalue=3;
      column=72;
      lcd_cursorblink_flag=1;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      lcd_cursorblink_flag=0;
      for(keypress_count=0;keypress_count<2;keypress_count++)
      {
       if (keypress_count==1)
       {
         lcd_cursorblink_flag=1;
       }
       key_press();
        if (keypress_count==1)
       {
         lcd_cursorblink_flag=0;
       }
       alaram_time_5_2[keypress_count]= glo_line;
       }
       alaram_time5_m = ((alaram_time_5_2[0]-0x30)*10) + (alaram_time_5_2[1]-0x30);
       printf("alaram time5_m is %d",alaram_time5_m);

        if( (alaram_time5_m > 60) || (alaram_time5_h > 23) || (alaram_time5_d > 31) || (alaram_time5_o > 12))
       {
        lcd_color_red();
        wait(1);
        lcd_color_green();
        goto    page3start;
       }

       }
       touchpressed_done_flag2=0;
       while(touchpressed_done_flag2==0)
       {
        xcor=0;
        ycor=0;
        for(i=0;i<5;i++)
        {
          adc_read();
          if(((xcor > 0x5200 && xcor< 0x7400)&&(ycor >0x7100 && ycor< 0x7C00)))
          {
           printf("\n\rsuccess\n\r");
           touchpressed_done_flag2=1;
           goto endloop1;
          }
       }
       }
       endloop1:
       if(alaram_count == 1)
       {
       alaram1_lcd_flag=1;
       alaram1();
       }
       else if(alaram_count == 2)
       {
       alaram2_lcd_flag=1;
       alaram2();
       }
       else if(alaram_count == 3)
       {
       alaram3_lcd_flag=1;
       alaram3();
       }

       else if(alaram_count == 4)
       {
       alaram4_lcd_flag=1;
       alaram4();
       }

       else if(alaram_count == 5)
       {
       alaram5_lcd_flag=1;
       alaram5();
       }
}

void login()
{
    while(loginstatus != 1)
    {
    lcd_clear1(); //clear the lcd diplay without clearing the RTC on LCD
    login_write();
    login_user();

    }
}

void lcd_write_settime()
{
    lcd_write_character('S');//S
    lcd_write_character('E');//E
    lcd_write_character('T');//T
    lcd_write_character(0x00);//space
    lcd_write_character('T');//T
    lcd_write_character('I');//I
    lcd_write_character('M');//M
    lcd_write_character('E');//E
}

void lcd_write_timeformat()
{
    lcd_write_character('D');//D
    lcd_write_character('D');//D
    lcd_write_character('/');//:
    lcd_write_character('M');//M
    lcd_write_character('M');//M
    lcd_write_character(0x00);//space
    lcd_write_character('H');//H
    lcd_write_character('H');//H
    lcd_write_character(':');//:
    lcd_write_character('M');//M
    lcd_write_character('M');//M

}

void  lcd_write_reset()
{
    lcd_write_character(0x02);//Block
    lcd_write_character('R');//R
    lcd_write_character('E');//E
    lcd_write_character('S');//S
    lcd_write_character('E');//E
    lcd_write_character('T');//T
    lcd_write_character(0x02);//Block
}






void  lcd_write_describe()
{

    lcd_write_character('D');//D
    lcd_write_character('E');//E
    lcd_write_character('S');//S
    lcd_write_character('C');//C
    lcd_write_character('R');//R
    lcd_write_character('I');//I
    lcd_write_character('B');//B
    lcd_write_character('E');//E

}

void  lcd_write_done()
{
    lcd_write_character(0x02);//Block
    lcd_write_character('D');//D
    lcd_write_character('O');//O
    lcd_write_character('N');//N
    lcd_write_character('E');//E
    lcd_write_character(0x02);//Block
}

void  lcd_write_add()
{
    lcd_write_character(0x02);//Block
    lcd_write_character('A');//A
    lcd_write_character('D');//D
    lcd_write_character('D');//D
    lcd_write_character(0x02);//Block
}

void  lcd_write_delete()
{
    lcd_write_character(0x02);//Block
    lcd_write_character('D');//D
    lcd_write_character('E');//E
    lcd_write_character('L');//L
    lcd_write_character('E');//E
    lcd_write_character('T');//T
    lcd_write_character('E');//E
    lcd_write_character(0x02);//Block
}

void login_write()
{
    pagevalue = 0;
    column=60;
      lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
    login_write_login();
    pagevalue = 2;
    column=00;
          lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;

    login_write_username();
    pagevalue = 4;
    column=00;
          lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;

    login_write_password();
}

void login_write_login()
{
    lcd_write_character('L');//l
    lcd_write_character('O');//o
    lcd_write_character('G');//g
    lcd_write_character('I');//i
    lcd_write_character('N');//n
}
void login_write_username()
{
    lcd_write_character('U');//u
    lcd_write_character('S');//s
    lcd_write_character('E');//e
    lcd_write_character('R');//r
    lcd_write_character('N');//n
    lcd_write_character('A');//a
    lcd_write_character('M');//m
    lcd_write_character('E');//e
    lcd_write_character(':');//:
}



void login_write_password()
{
    lcd_write_character('P');//p
    lcd_write_character('A');//a
    lcd_write_character('S');//s
    lcd_write_character('S');//s
    lcd_write_character('W');//w
    lcd_write_character('O');//o
    lcd_write_character('R');//r
    lcd_write_character('D');//d
    lcd_write_character(':');//:
}

void hide_character()
{
     column=column-6;
     lcd_changelocation();
     lcd_write_character('*');
}

void login_write_error()
{
    lcd_write_character('I');//i
    lcd_write_character('N');//n
    lcd_write_character('V');//v
    lcd_write_character('A');//a
    lcd_write_character('L');//l
    lcd_write_character('I');//i
    lcd_write_character('D');//d
    lcd_write_character(0x00);//space
    lcd_write_character('C');//c
    lcd_write_character('R');//r
    lcd_write_character('E');//e
    lcd_write_character('D');//d
    lcd_write_character('E');//e
    lcd_write_character('N');//n
    lcd_write_character('T');//t
    lcd_write_character('I');//i
    lcd_write_character('A');//a
    lcd_write_character('L');//l
    lcd_write_character('S');//s
}


void lcd_write_deletetask()
{
    lcd_write_character('D');//i
    lcd_write_character('E');//n
    lcd_write_character('L');//v
    lcd_write_character('E');//a
    lcd_write_character('T');//l
    lcd_write_character('E');//i
    lcd_write_character(0x00);//space
    lcd_write_character('T');//c
    lcd_write_character('A');//r
    lcd_write_character('S');//e
    lcd_write_character('K');//d
    lcd_write_character(':');//d
}

void login_user()
{

   unsigned char i;
   unsigned char username_enter[5];
   unsigned char password_enter[5];
   unsigned char count_username=0;
   unsigned char count_password=0;

    pagevalue = 2;
    column=60;
    lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;
      keypress_count=0;

    for(keypress_count=0;keypress_count<5;keypress_count++)
    {
       key_press();                                                       //wait till the key is pressed
       username_enter[keypress_count]= glo_line;                          //value of username is stored in the following
    }
     pagevalue = 4;
     column=60;
     lcd_cursor_column_flag=1;
      lcd_changelocation();
      lcd_cursor_column_flag=0;

    for(keypress_count=0;keypress_count<5;keypress_count++)
    {
       key_press();
       wait(.3);
       lcd_timer_flag=1;
       hide_character();
       lcd_timer_flag=0;
       password_enter[keypress_count]= glo_line;
    }

    for(i=0;i<5;i++)
    {
        if(main_username[i] == username_enter[i])
        {
            count_username++;
        }
    }

    for(i=0;i<5;i++)
    {
        if(main_username[i] == password_enter[i])
        {
            count_password++;
        }
    }


    if((count_username == 5) && (count_password ==5))
     {
        loginstatus=1;
     }
     else
     {
        pagevalue = 5;
        column=6;
        lcd_cursor_column_flag=1;
        lcd_changelocation();
        lcd_cursor_column_flag=0;
        login_write_error();
        lcd_color_red();
        wait(1);
        lcd_color_green();
//        wait(1);
     }

}

void lcd_write_description()
{
      unsigned char i;
      for(i=0;i<desc_count;i++)
      {
      lcd_write_character(alaram_des_1[i]);  //write the value of the description 1
      }

}

void lcd_write_description2()
{
      unsigned char i;

      for(i=0;i<desc_count2;i++)
      {
      lcd_write_character(alaram_des_2[i]);
      }

}

void lcd_write_description3()
{
      unsigned char i;

      for(i=0;i<desc_count3;i++)
      {
      lcd_write_character(alaram_des_3[i]);
      }

}

void lcd_write_description4()
{
      unsigned char i;
      for(i=0;i<desc_count4;i++)
      {
      lcd_write_character(alaram_des_4[i]);
      }

}

void lcd_write_description5()
{
      unsigned char i;
      for(i=0;i<desc_count5;i++)
      {
      lcd_write_character(alaram_des_5[i]);
      }

}

void lcd_write_time1()
{
      unsigned char i;
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_1_3[i]);    //value of the month of alaram1
      }
      lcd_write_character('/');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_1_4[i]);  //value of the day of alaram1
      }
      lcd_write_character(0x00);
     for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_1_1[i]);  //value of the hour of alaram1
      }
      lcd_write_character(':');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_1_2[i]);  //value of the minute of alaram1
      }

}

//Put the value of time 2 on the LCD screen
void lcd_write_time2()
{
      unsigned char i;
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_2_3[i]);
      }
      lcd_write_character('/');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_2_4[i]);
      }
      lcd_write_character(0x00);
     for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_2_1[i]);
      }
      lcd_write_character(':');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_2_2[i]);
      }

}

//Put the value of time 3 on the LCD screen
void lcd_write_time3()
{
      unsigned char i;
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_3_3[i]);
      }
      lcd_write_character('/');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_3_4[i]);
      }
      lcd_write_character(0x00);
     for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_3_1[i]);
      }
      lcd_write_character(':');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_3_2[i]);
      }

}

//Put the value of time 4 on the LCD screen
void lcd_write_time4()
{
      unsigned char i;
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_4_3[i]);
      }
      lcd_write_character('/');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_4_4[i]);
      }
      lcd_write_character(0x00);
     for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_4_1[i]);
      }
      lcd_write_character(':');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_4_2[i]);
      }

}

//Put the value of time 5 on the LCD screen
void lcd_write_time5()
{
      unsigned char i;
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_5_3[i]);
      }
      lcd_write_character('/');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_5_4[i]);
      }
      lcd_write_character(0x00);
     for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_5_1[i]);
      }
      lcd_write_character(':');
      for(i=0;i<2;i++)
      {
      lcd_write_character(alaram_time_5_2[i]);
      }

}
