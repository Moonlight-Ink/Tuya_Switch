#include "application.h"

/*******************�ⲿ����***************************/
extern uint8_t Key1_Scan(void);
extern uint8_t Key2_Scan(void);
/*******************�ⲿ����***************************/

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
    if(EventFlag == Event_None || EventFlag == Timing_Event)       //�����ڶ�ʱ״̬�£����°���ȡ����ʱ״̬
		{
      EventFlag = Key1_Event;
    }
  }
	else 
	{
    if(EventFlag == Key1_Event)
		{
			if(Key_Short_Flag)           //����key1
			{
   
      }
			else if(Key_Short_Flag)          //�̰�key1
			{

      }	
      EventFlag = Event_None;
    }	
  }
	 
	if(Key2_Scan())
	{
    if(EventFlag == Event_None || EventFlag == Timing_Event)            //�����ڶ�ʱ״̬�£����°���ȡ����ʱ״̬
		{
      EventFlag = Key2_Event;
    }
  }
	else 
	{
    if(EventFlag == Key2_Event)
		{
			if(Key_Short_Flag)           //����key2
			{
   
      }
			else if(Key_Short_Flag)          //�̰�key2
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
		case Key1_Event:                         //����1�¼�
			  if(1 < *count < 100)              //1s��
				{
	        Key_Short_Flag = 1; 				
				}
        else if(*count > 300)             //3s����
				{
          Key_Long_Flag = 1;
        }					
		     break;
				
		case Key2_Event:                           //����2�¼�
			  if(10 < *count < 100)            //1s��
				{
	        Key_Short_Flag = 1; 				
				}
        else if(*count > 300)          //3s����
				{
          Key_Long_Flag = 1;
        }					
		     break;	
				
		case Timing_Event:                      //��ʱ���¼�			
          if(!Timing_Cnt)
				  {
						EventFlag = Event_None;                                       //�ڶ�ʱ״̬�£��а�������ʱ�Ƿ�ȡ����ʱ

/****************��ʱʱ�䵽,������������*******************************************************/
				



						
/*********************************************************************************************/						
          }
			    Timing_Cnt--;					
		     break;
		
		default:
			   count=0;
			 break;
	}
}