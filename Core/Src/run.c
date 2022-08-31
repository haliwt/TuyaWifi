#include "run.h"
#include "wifi_fun.h"

#include "dht11.h"
#include "fan.h"
#include "tim.h"
#include "cmd_link.h"
#include "special_power.h"
#include "wifi.h"
#include "single_mode.h"

 


//static CProcess1 cprocess;
RUN_T run_t; 
uint8_t times;
 




/**********************************************************************
*
*Functin Name: void Initial_Ref(void)
*Function : be check key of value 
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Initial_Ref(void)
{
  
  run_t.gPlasma=0;
  run_t.gDry =0;
 
  run_t.gFan_counter=0;
 

}


/**********************************************************************
*
*Function Name:void Decode_RunCmd(void)
*Function: receive usart touchkey of command 
*Input Ref:NO
*Return Ref:NO
*
**********************************************************************/
void Decode_RunCmd(void)
{

 uint8_t cmdType_1=inputCmd[0],cmdType_2 = inputCmd[1];
    
  switch(cmdType_1){
  
      case 'P': //power 
        
        
       if(cmdType_2 == 0x00){ //power off
          
		 
		  PowerOff();
		  run_t.gPower_On=0;
		  run_t.SingleMode = 0;
		  wifiUpdate_Power_Status(0);
			
       
       } 
       else if(cmdType_2 ==1){ //power on
       

	        PowerOn();
	        run_t.gPower_On=1;
		    run_t.SingleMode = 1;
		    wifiUpdate_Power_Status(1);

	   }       
      
          
      break;
      
      case 'A': //AI function ->wifi ->indicate Fun
        
        if(run_t.gPower_On==1){
			
			 //Single_ReceiveCmd(cmdType_2);
			if(run_t.SingleMode  ==1 )
        	     Single_Usart_ReceiveData(cmdType_2);
			
        }

      break;

	  case 'Z' :
	    if(run_t.gPower_On==1){

		    if(cmdType_2== 'Z'){//turn off AI
			    Buzzer_On();
			}
		}

	    break;
 	}
    
}
/**********************************************************************
	*
	*Functin Name: void Single_ReceiveCmd(uint8_t cmd)
	*Function : resolver is by usart port receive data  from display panle  
	*Input Ref:  usart receive data
	*Return Ref: NO
	*
**********************************************************************/
void Single_ReceiveCmd(uint8_t cmd)
{
    switch(cmd){

      case 0x11: //wifi key command turn off
       
        if(wifi_t.wifiPowerOn_flag==1){
             wifi_t.wifi_cmd = 0x11;
             run_t.globe_setPriority = 0;
        }
        else{
        	  run_t.Single_cmd=0x11;
        	  run_t.globe_setPriority = 1;
           }

      break;

     case 0x01://wifi key command turn on
     	if(wifi_t.wifiPowerOn_flag==1){
             wifi_t.wifi_cmd = 0x01;
             run_t.globe_setPriority = 0;
        }
        else{
           run_t.Single_cmd = 0x01;
           run_t.globe_setPriority = 1;
       }
     break;

     //AI key
     case 0x08: //AI key command turn on
     	if(wifi_t.wifiPowerOn_flag==1){
             wifi_t.wifi_cmd = 0x08;
             run_t.globe_setPriority =0;
        }
        else{
          run_t.Single_cmd = 0x08;
          run_t.globe_setPriority =1;
         // run_t.gAi = AIENABLE;

         }

     break;

     case 0x18: //AI turn off
        if(wifi_t.wifiPowerOn_flag==1){
             wifi_t.wifi_cmd = 0x18;
             run_t.globe_setPriority =0;
        }
        else{
            run_t.Single_cmd = 0x18;
            run_t.globe_setPriority =1;
            //run_t.gAi = AIDISABLE;
        }
      break;

     //dry key
     case 0x02:
        if(wifi_t.wifiPowerOn_flag==1){
             wifi_t.wifi_cmd = 0x02;
             run_t.globe_setPriority =0;
        }
        else{ 
     	  run_t.Single_cmd = 0x02;
     	  run_t.globe_setPriority =1;
     	 }
     break;

     case 0x12:
        if(wifi_t.wifiPowerOn_flag==1){
             wifi_t.wifi_cmd = 0x12;
             run_t.globe_setPriority =0;
        }
        else{
     	  run_t.Single_cmd = 0x12;
     	  run_t.globe_setPriority =1;
        }
     break;

     //kill key

     case 0x04:
        if(wifi_t.wifiPowerOn_flag==1){
             wifi_t.wifi_cmd = 0x04;
             run_t.globe_setPriority =0;
        }
        else{ 
     	  run_t.Single_cmd = 0x04;
     	  run_t.globe_setPriority =1;
     	}
     break;

     case 0x14:
        if(wifi_t.wifiPowerOn_flag==1){
             wifi_t.wifi_cmd = 0x14;
             run_t.globe_setPriority =0;
        }
        else{
     	  run_t.Single_cmd = 0x14;
     	  run_t.globe_setPriority =1;
        }
     break;

     default:
          wifi_t.wifi_cmd = 0;
         run_t.Single_cmd = 0;
     break;


    }

}

/**********************************************************************
	*
	*Functin Name: void RunCommand_Mode(unit8_t sig)
	*Function : wifi functio AI 
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
void AI_Function(uint8_t sig)
{
   static uint8_t wifi_s=0xff,wifi_a=0xff,ai_off=0xff,ai_on=0xff;
   static uint8_t dry_on =0xff, dry_off = 0xff,ster_on=0xff,ster_off=0xff;

	switch(sig){
   
	case 0x01: //wifi Mode AP (single -> Fan Mode)

	    if(wifi_t.getNet_flag ==0){
          if(wifi_s !=run_t.wifi_key){
          	  wifi_s = run_t.wifi_key;
              run_t.wifi_key++;

               run_t.kill_key_off++;
               run_t.kill_key++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.ai_key++;
			   run_t.ai_key_off++;
              
                mcu_set_wifi_mode(0);//wifi be detector AP mode,slowly
		 }
		 if(wifi_t.gTimer_500ms ==0){
			  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
		   }
		  else if(wifi_t.gTimer_500ms>0){
			   if(wifi_t.gTimer_500ms >1)wifi_t.gTimer_500ms=0;
			   HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
		  }
	     }
     
     break;
           
     case 0x11 : //wifi Mode  smart
           if(wifi_t.getNet_flag ==0){
           	if(wifi_a != run_t.wifi_key_off){
           	   wifi_a = run_t.wifi_key_off;
               run_t.wifi_key_off++;

               run_t.kill_key_off++;
               run_t.kill_key++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.ai_key++;
			   run_t.ai_key_off++;

               mcu_set_wifi_mode(0);//wifi be detector smart mode,fast
              
			}
			if(wifi_t.gTimer_1s ==0)
			        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
			    else if(wifi_t.gTimer_1s > 0){
					 if(wifi_t.gTimer_1s >1)wifi_t.gTimer_1s=0;
			    	 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
			}
				
           }
         
     break;
     /*-------------------------------WIFI FUNCTION----------------------------------*/  
     //wifi function   
     case 0x04: //kill turn on
         if(run_t.globe_sub_flag != kill){
       
         if(ster_on !=run_t.kill_key && (run_t.gAi ==AIDISABLE || wifi_t.wifi_itemAi==1)){
	   	    ster_on = run_t.kill_key;
           
            

			  run_t.globe_sub_flag = kill;
              run_t.kill_key_off++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.ai_key++;
			   run_t.ai_key_off++;

			   run_t.wifi_key_off++;
			   run_t.wifi_key++;
			  
			  
			Buzzer_On();
	   
		
	       run_t.gPlasma =0;
	
		   run_t.gFan_continueRun =0;
		   wifiUpdate_Kill_Status(1);
	       SterIlization(0); //turn on
		   
            }
	   
        }
     break;
         
    case 0x14: //kill turn off
        
          if(run_t.globe_sub_flag != notkill){
          if((ster_off !=run_t.kill_key_off && (run_t.gAi == AIDISABLE || wifi_t.wifi_itemAi==1))){
               ster_off = run_t.kill_key_off;
		
			  run_t.globe_sub_flag = notkill;
			   
			   run_t.kill_key++;
			  
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			  
			   	
			   run_t.ai_key++;
			   run_t.ai_key_off++;
			   
			   run_t.wifi_key_off++;
			   run_t.wifi_key++;
			   
	    	 
			  
			     Buzzer_On();
       
            run_t.gPlasma =1; //turn off plasma 
			wifiUpdate_Kill_Status(0);
		
           SterIlization(1); //turn off kill function
			 if( run_t.gDry ==1){
			 
				  run_t.gFan_counter =0;
				 run_t.gFan_continueRun =1;
			 }

            }
        }
    
    break;


    case 0x02: //dry turn 0n
        if(run_t.globe_sub_flag != dry){
        if((dry_on != run_t.dry_key && (run_t.gAi == AIDISABLE || wifi_t.wifi_itemAi==1))){
			      dry_on = run_t.dry_key;

			  
				run_t.globe_sub_flag = dry;

		            run_t.dry_key_off++;
			
				   run_t.kill_key++;
				   run_t.kill_key_off++;
				   
				   run_t.ai_key++;
				   run_t.ai_key_off++;

				   run_t.wifi_key_off++;
			       run_t.wifi_key++;

             	
			   Buzzer_On();
			  
            
             run_t.gDry = 0;
          
	
			 run_t.gFan_continueRun =0;
			 wifiUpdate_Dry_Status(1);
			 Dry_Function(0);
			 
         }
             
        }
    break;
         
    case 0x12 : //dry turn off
          if(run_t.globe_sub_flag !=notdry){
          if((dry_off != run_t.dry_key_off && (run_t.gAi ==AIDISABLE ||  wifi_t.wifi_itemAi==1))){
			  dry_off = run_t.dry_key_off;
			  

			  run_t.globe_sub_flag = notdry;
			        run_t.dry_key++;
			  
		           run_t.kill_key++;
				   run_t.kill_key_off++;
				   
				   run_t.ai_key++;
				   run_t.ai_key_off++;

				   run_t.wifi_key_off++;
			       run_t.wifi_key++;
			   

			    Buzzer_On();
			  
        
             run_t.gDry =1;
		 	
			wifiUpdate_Dry_Status(0);
		    Dry_Function(1) ;//Display_Function_OnOff();
		    
             if(run_t.gPlasma ==1){ //plasma turn off flag

                
				 run_t.gFan_counter =0;
				 run_t.gFan_continueRun =1;

             }
		    
           }
          }
    break;

	case 0x08: //wifi AI and Single AI-> AI tunr ON

	    if(ai_on != run_t.ai_key){
		      ai_on = run_t.ai_key;
		      
		       run_t.gAi = AIENABLE;
               wifi_t.wifi_itemAi=AIENABLE;
            
			   run_t.ai_key_off++;

		       run_t.kill_key++;
			   run_t.kill_key_off++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;

			   run_t.wifi_key_off++;
			   run_t.wifi_key++;
			  
               wifi_t.wifi_itemAi=0;
			 
				 
		
		   Buzzer_On();
	      
		   run_t.gFan_continueRun =0;
         
            run_t.gPlasma =0;
            run_t.gDry =0;
            wifiUpdate_AI_Status(0);//wifi APP turn on
      
                
                FAN_CCW_RUN();
                PLASMA_SetHigh(); //
                HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
                PTC_SetHigh();
			
             
				
		}
		
	  break;

	 case 0x18: //wifi AI and Single AI turn off
	      if(ai_off != run_t.ai_key_off){
		      ai_off = run_t.ai_key_off;
		            run_t.ai_key++;

		           run_t.gAi = AIDISABLE;
                   wifi_t.wifi_itemAi=AIDISABLE;
              
		           run_t.kill_key++;
				   run_t.kill_key_off++;
				   run_t.dry_key++;
				   run_t.dry_key_off++;

				   run_t.wifi_key_off++;
				   run_t.wifi_key++;

				  
				 wifiUpdate_AI_Status(1);

		  }

	 break;
           
   

	default:
     sig = 0;

	break;
    }
 }


/**********************************************************************
	*
	*Functin Name: void RunCommand_Order(void)
	*Function : be check key of value 
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
void RunCommand_Order(void)
{
    
    static uint8_t wifidisp;
    
    if(run_t.sendtimes> 5 || run_t.gPower_flag == 1){ // display humidity and temperature value
		run_t.sendtimes=0;
        times++;
        wifidisp++;
        if(times > 49)run_t.gPower_flag++;
	     Display_DHT11_Value(&DHT11);

	   if(wifi_work_state == WIFI_CONNECTED || wifi_work_state ==  WIFI_CONN_CLOUD){

                 wifi_t.getNet_flag =1;
                 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
       }
         
       if(wifidisp > 3){
        	wifidisp = 0;
	    if(wifi_work_state == WIFI_CONNECTED || wifi_work_state ==  WIFI_CONN_CLOUD){
              wifiDisplayTemperature_Humidity();
         }
        }
        
	}
    if(run_t.gPower_On==0)times=0;
	
	if((run_t.gPower_On ==0 || wifi_t.wifiPowerOn_flag==0) && run_t.gFan_continueRun ==1){ //Fan be stop flag :0 -Fan works 
        
         if(run_t.gFan_counter < 61){
         
             FAN_CCW_RUN();
         }        
       
        if(run_t.gFan_counter >= 60){ //60s
        
	     run_t.gFan_counter=0;
	  
         run_t.gFan_continueRun++;
		  FAN_Stop();
	   }
	  }
	
	 if(run_t.gFan_continueRun ==1 && (run_t.gPower_On ==1 || wifi_t.wifiPowerOn_flag==1 )){
          
                if(run_t.gFan_counter < 61){
          
                       FAN_CCW_RUN();
                  }       

	           if(run_t.gFan_counter > 59){
		           
				   run_t.gFan_counter=0;
				
				   run_t.gFan_continueRun++;
				   FAN_Stop();
	           }
	  }
	  if((run_t.gPower_On !=0 || wifi_t.wifiPowerOn_flag !=0) && run_t.gFan_continueRun ==0){

	      FAN_CCW_RUN();
      }
      
      

}

