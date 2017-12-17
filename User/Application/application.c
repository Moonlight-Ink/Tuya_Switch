#include "application.h"

/*******************外部函数***************************/
extern uint8_t Key1_Scan(void);
extern uint8_t Key2_Scan(void);
/*******************外部函数***************************/

uint8_t EventFlag = Event_None;
uint8_t EventFlag_Pre = Event_None;
uint8_t Key_Long_Flag = 0;
uint8_t Key_Short_Flag = 0;
uint8_t Delay_10ms_Cnt = 0; 
uint32_t Timing_Cnt = 0;




uint8_t Delay_10ms()
{
  Delay_10ms_Cnt = 1;	
	while(Delay_10ms_Cnt);
}


uint8_t Key_Event(void)
{	 
	
	if(Key1_Scan())
	{
    if(EventFlag == Event_None || EventFlag == Timing_Event)       //若处在定时状态下，则按下按键取消定时状态
		{
      EventFlag = Key1_Event;
    }
  }
	else 
	{
    if(EventFlag == Key1_Event)
		{
			if(Key_Short_Flag)           //长按key1
			{
   
      }
			else if(Key_Short_Flag)          //短按key1
			{

      }	
      EventFlag = Event_None;
    }	
  }
	 
	if(Key2_Scan())
	{
    if(EventFlag == Event_None || EventFlag == Timing_Event)            //若处在定时状态下，则按下按键取消定时状态
		{
      EventFlag = Key2_Event;
    }
  }
	else 
	{
    if(EventFlag == Key2_Event)
		{
			if(Key_Short_Flag)           //长按key2
			{
   
      }
			else if(Key_Short_Flag)          //短按key2
			{

      }	
      EventFlag = Event_None;
    }	
  } 	
}





void TimeIsrCallback(uint16_t *count)
{
	
	if(Delay_10ms_Cnt)
	{
    Delay_10ms_Cnt--;
  }
	
	 switch(EventFlag)
	{
		case Key1_Event:                         //按键1事件
			  if(1 < *count < 100)              //1s内
				{
	        Key_Short_Flag = 1; 				
				}
        else if(*count > 300)             //3s以上
				{
          Key_Long_Flag = 1;
        }					
		     break;
				
		case Key2_Event:                           //按键2事件
			  if(10 < *count < 100)            //1s内
				{
	        Key_Short_Flag = 1; 				
				}
        else if(*count > 300)          //3s以上
				{
          Key_Long_Flag = 1;
        }					
		     break;	
				
		case Timing_Event:                      //定时器事件			
          if(!Timing_Cnt)
				  {
						EventFlag = Event_None;                                       //在定时状态下，有按键按下时是否取消定时

/****************定时时间到,触发动作函数*******************************************************/
				



						
/*********************************************************************************************/						
          }
			    Timing_Cnt--;					
		     break;
		
		default:
			   count=0;
			 break;
	}
}