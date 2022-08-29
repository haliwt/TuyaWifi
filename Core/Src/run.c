#include "run.h"
#include "wifi_fun.h"

#include "dht11.h"
#include "fan.h"
#include "tim.h"
#include "cmd_link.h"
#include "special_power.h"
#include "wifi.h"

 


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
  run_t.gFan = 0;
  run_t.gPlasma=0;
  run_t.gAi =0;
  run_t.gDry =0;
  run_t.gFan_flag =0;
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
			
       
       } 
       else if(cmdType_2 ==1){ //power on
       

	        PowerOn();

	   }       
      
          
      break;
      
      case 'A': //AI function ->wifi ->indicate Fun
        
        if(run_t.gPower_On==1){
			if(cmdType_2== 0x81){//turn off AI
			  
			 mcu_set_wifi_mode(1);//wifi be detector AP mode
			 

			}
			else if(cmdType_2== 0x71){//tunr on AI
			   mcu_set_wifi_mode(0);//wifi be detector smart mode

			}
			
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
	*Functin Name: void RunCommand_Mode(unit8_t sig)
	*Function : wifi functio AI 
	*Input Ref:  key of value
	*Return Ref: NO
	*
**********************************************************************/
void AI_Function(uint8_t sig)
{
   static uint8_t fan_on=0xff,fan_off=0xff;
   static uint8_t dry_on =0xff, dry_off = 0xff,ster_on=0xff,ster_off=0xff;
   if(run_t.gPower_On==1 || wifi_t.wifiPowerOn_flag==1){  //WT.EDIT 2022.08.29
	switch(sig){
   
	case 0x08: //fan on
            if(fan_on !=run_t.fan_key){
				fan_on = run_t.fan_key ;
			
		
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			
			   run_t.fan_key_off++;
	            
			    Buzzer_On();
	            run_t.gFan =0;
		        run_t.gFan_flag = 0;
			    run_t.gFan_counter =0;
		        FAN_CCW_RUN();
				
				
            }
             
     break;
           
     case 0x18 : //Fan of
           if(fan_off != run_t.fan_key_off){
		   	   fan_off = run_t.fan_key_off;
		   	
	          
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;

			    Buzzer_On();
			
                run_t.gFan =1;
	          
	           run_t.gDry = 1;
			   run_t.gPlasma =1;
				  
			   Dry_Function(1);
			   SterIlization(1);
			   FAN_Stop();
			   run_t.gFan_flag = 1; //Fan be stop flag :0 -Fan works
	           run_t.gFan_counter =0;
			   
           }
         
     break;
        
     //wifi function   
     case 0x04: //kill turn on
	   if(ster_on !=run_t.ster_key || (wifi_t.wifi_kill == 1 && wifi_t.wifi_itemAi==wifi_notAI)){
	   	    ster_on = run_t.ster_key;
           wifi_t.wifi_kill=2;
	 
               run_t.ster_key_off++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;

			    Buzzer_On();
	   
		   run_t.gFan = 0; //FAN on
	       run_t.gPlasma =0;
		   run_t.gFan_flag = 0;
		   run_t.gFan_counter =0;
	       SterIlization(0); //turn on
		   

	   	}
	   
     break;
         
    case 0x14: //kill turn off
            if(ster_off !=run_t.ster_key_off|| (wifi_t.wifi_kill == 0 && wifi_t.wifi_itemAi==wifi_notAI)){
               ster_off = run_t.ster_key_off;
			  wifi_t.wifi_kill = 2;
		
		       run_t.ster_key++;
			  
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;
			   
	    	
	           run_t.gPlasma =1;
			     Buzzer_On();
            
             if(run_t.gDry == 0){
                 run_t.gFan = 0;
                 FAN_CCW_RUN();
			      run_t.gFan_flag = 0;
				 run_t.gFan_counter =0;
             }
			 else{
				run_t.gFan =1;
                FAN_Stop();
			    run_t.gFan_flag = 1; //Fan be stop flag :0 -Fan works
			     run_t.gFan_counter =0;

			 }
			 SterIlization(1); //turn off kill function
			

            }
    
    break;


    case 0x02: //dry turn 0n
             if(dry_on != run_t.dry_key || (wifi_t.wifi_dry ==1&& wifi_t.wifi_itemAi==wifi_notAI)){
			    dry_on = run_t.dry_key;
				wifi_t.wifi_dry = 2;
		
		
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			   
			 
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;
			    Buzzer_On();
			  
            
             run_t.gDry = 0;
             run_t.gFan =0;
	         run_t.gFan_flag = 0;
			run_t.gFan_counter =0;
			 Dry_Function(0);
			 

             }
    break;
         
    case 0x12 : //dry turn off
            if(dry_off != run_t.dry_key_off || (wifi_t.wifi_dry==0 && wifi_t.wifi_itemAi==wifi_notAI)){
			  dry_off = run_t.dry_key_off;
			  wifi_t.wifi_dry=2;
			  
			
		
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			   
			   run_t.dry_key++;
			  
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;

			    Buzzer_On();
			  
        
             run_t.gDry =1;
		 	
             if(run_t.gPlasma ==0){

                 run_t.gFan =0;
                 FAN_CCW_RUN();
			     run_t.gFan_flag = 0;
				 run_t.gFan_counter =0;

             }
			 else{

                 run_t.gFan =1;
                 FAN_Stop();
			     run_t.gFan_flag = 1; //Fan be stop flag :0 -Fan works
			     run_t.gFan_counter =0;
			 }

		    Dry_Function(1) ;//Display_Function_OnOff();
		    
           }

    break;

	case 0x01: //AI tunr ON

	    if(wifi_t.wifi_ai ==1){
		 
		 wifi_t.wifi_ai =2;
			
		
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;
		  
		  Buzzer_On();
	      
		  run_t.gFan_continueRun =0;
         if(run_t.gFan ==0 && run_t.gPlasma ==0 && run_t.gDry ==0){

             run_t.gAi = 1;
             run_t.gFan =1;
             run_t.gPlasma =1;
             run_t.gDry =1;
          
             
            PLASMA_SetLow(); //
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
            PTC_SetLow();
            FAN_Stop();
            run_t.gFan_flag = 1; //Fan be stop flag :0 -Fan works
            run_t.gFan_counter =0;
             
           }
            else{
               run_t.gAi = 0;
               run_t.gFan =0;
               run_t.gPlasma =0;
               run_t.gDry =0;
              
                
                FAN_CCW_RUN();
                PLASMA_SetHigh(); //
                HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
                PTC_SetHigh();
				run_t.gFan_flag = 0; //Fan be stop flag :0 -Fan works
                run_t.gFan_counter =0;
				

				
            }
			
	    }
			
    break;
           
    case 0x11: //AI turn off

	        if(wifi_t.wifi_ai==0){
				

			   wifi_t.wifi_ai=2;
			
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			 
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;
		       Buzzer_On();
				
         
		
            if(run_t.gFan ==1 && run_t.gPlasma ==1 && run_t.gDry ==1){

                run_t.gAi = 0;
				run_t.gFan =0;
			    run_t.gPlasma =0;
				run_t.gDry =0;
				
				
                FAN_CCW_RUN();
                PLASMA_SetHigh(); //
                HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
                PTC_SetHigh();
				run_t.gFan_flag = 0; //Fan be stop flag :0 -Fan works
                run_t.gFan_counter =0;
			}    
            else{

              run_t.gAi = 1;
              run_t.gFan =1;
              run_t.gPlasma =1;
              run_t.gDry =1;
            
                
            PLASMA_SetLow(); //
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
            PTC_SetLow();
            FAN_Stop();
			run_t.gFan_flag = 1; //Fan be stop flag :0 -Fan works
		    run_t.gFan_counter =0;
			
              
           }
			
	      }
        
    break;

	default:

	break;
    }
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
    
    if(run_t.sendtimes> 4 || run_t.gPower_flag == 1){ // display humidity and temperature value
		run_t.sendtimes=0;
        times++;
        if(times > 49)run_t.gPower_flag++;
	    Display_DHT11_Value(&DHT11);

        
	}
    if(run_t.gPower_On==0)times=0;
	
	if((run_t.gPower_On ==0) && run_t.gFan_continueRun ==1){ //Fan be stop flag :0 -Fan works 
        
         if(run_t.gFan_counter < 61){
         
             FAN_CCW_RUN();
         }        
       
        if(run_t.gFan_counter >= 60){ //60s
        
	     run_t.gFan_counter=0;
	     run_t.gFan_flag =0; 
         run_t.gFan_continueRun++;
		  FAN_Stop();
	   }
	  }
	
	  if(run_t.gFan_continueRun ==1 && run_t.gPower_On ==1){
          
                if(run_t.gFan_counter < 61){
          
                       FAN_CCW_RUN();
                  }       

	           if(run_t.gFan_counter > 59){
		           
				   run_t.gFan_counter=0;
				   run_t.gFan_flag =0; 
				   run_t.gFan_continueRun++;
				   FAN_Stop();
	           }
	  }
	  
	  

      if(run_t.gPower_On !=0 && run_t.gFan_continueRun ==0){

	      FAN_CCW_RUN();
      }

}



