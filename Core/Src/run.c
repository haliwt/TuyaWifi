#include "run.h"
#include "wifi_fun.h"

#include "dht11.h"
#include "fan.h"
#include "tim.h"
#include "cmd_link.h"
#include "special_power.h"

 


//static CProcess1 cprocess;
RUN_T run_t; 
uint8_t times;
 
static void AI_Function(uint8_t sig);




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
 // PowerOn_Host(SetPowerOn_ForDoing);
 // PowerOff_Host(SetPowerOff_ForDoing);

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
           #if 0
            Buzzer_On();
            run_t.gPower_flag = 0;
	        run_t.gFan_counter=0;
			run_t.gFan_continueRun =1; //turn off machine 
            PLASMA_SetLow(); //
            HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
            PTC_SetLow();
            FAN_Stop();
			
            run_t.gPower_On=0;
            Initial_Ref();
		  #endif 
		 
		  PowerOff();
			
       
       } 
       else if(cmdType_2 ==1){ //power on
       
//                Buzzer_On();
//				run_t.gFan_counter=0;
//                run_t.gPower_flag = 1; //turn on power
//	            run_t.gFan_continueRun =0;
//                FAN_CCW_RUN();
//                PLASMA_SetHigh(); //
//                HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//ultrasnoic ON 
//                PTC_SetHigh();
//                run_t.gPower_On=1;
	        PowerOn();

			
				
				
       }       
      
          
      break;
      
      case 'A': //AI function 
        
        if(run_t.gPower_On==1){
			if(cmdType_2== 0x81){//turn off AI
			   //don't buzzer sound
			  // AI_AutoOff(); //turn off PTC
			  run_t.gDry =1;
			  PTC_SetLow();
			 

			}
			else if(cmdType_2== 0x71){//tunr on AI
			  //don't buzzer sound
              //AI_AutoOn(); turn on PTC
              run_t.gDry =0;
			  PTC_SetHigh();

			}
			else{
				
		   		AI_Function(cmdType_2);
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
*Function : be check key of value 
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void AI_Function(uint8_t sig)
{
   static uint8_t ai_on= 0xff,ai_off=0xff,fan_on=0xff,fan_off=0xff;
   static uint8_t dry_on =0xff, dry_off = 0xff,ster_on=0xff,ster_off=0xff;
   if(run_t.gPower_On==1){
	switch(sig){

     case 0x08: //fan on
            if(fan_on !=run_t.fan_key){
				fan_on = run_t.fan_key ;
				run_t.Ai_key =1;
				run_t.ai_key++;
				run_t.ai_key_off++;
		
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
		   	
	           run_t.Ai_key=2;

               run_t.ai_key++;
               run_t.ai_key_off++;
		
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

	case 0x04: //kill turn on 
	   if(ster_on !=run_t.ster_key){
	   	   ster_on = run_t.ster_key;
	       run_t.Ai_key=3;
           run_t.ai_key++;
		   run_t.ai_key_off++;
		
			
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
	       SterIlization(0);
		   

	   	}
	   
     break;
         
    case 0x14: //don't kill turn off 
            if(ster_off !=run_t.ster_key_off){
			  ster_off = run_t.ster_key_off;
			   run_t.ai_key++;
		       run_t.ai_key_off++;
		
			   run_t.ster_key++;
			  
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;
			   
	    	   run_t.Ai_key=4;
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
			 SterIlization(1);
			

            }
    
    break;


    case 0x02: //dry
             if(dry_on != run_t.dry_key){
			    dry_on = run_t.dry_key;
			   run_t.ai_key++;
			   run_t.ai_key_off++;
		
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			   
			 
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;
			    Buzzer_On();
			  
             run_t.Ai_key=5;
             run_t.gDry = 0;
             run_t.gFan =0;
	         run_t.gFan_flag = 0;
			run_t.gFan_counter =0;
			 Dry_Function(0);
			 

             }
    break;
         
    case 0x12 : //don't dry
            if(dry_off != run_t.dry_key_off){
			  dry_off = run_t.dry_key_off;
			  
			  run_t.ai_key_off++;
			  run_t.ai_key++;
		
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			   
			   run_t.dry_key++;
			  
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;

			    Buzzer_On();
			  
            run_t.Ai_key=6;
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

	case 0x01: //AI ON

	    if(ai_on != run_t.ai_key){
		  ai_on = run_t.ai_key;
		 
			   run_t.ai_key_off++;
		
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			   
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;
		  
		  Buzzer_On();
	      run_t.Ai_key=7;
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
           
    case 0x11: //don.t AI

	        if(ai_off != run_t.ai_key_off){
				ai_off = run_t.ai_key_off;

			    run_t.ai_key++;
			
			   run_t.ster_key++;
			   run_t.ster_key_off++;
			 
			   run_t.dry_key++;
			   run_t.dry_key_off++;
			   	
			   run_t.fan_key++;
			   run_t.fan_key_off++;
		       Buzzer_On();
				
            run_t.Ai_key=8;
		
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
         
       if(run_t.gFan_counter > 59 && run_t.gFan_continueRun ==1){ //60s
         FAN_Stop();
	     run_t.gFan_counter=0;
	     run_t.gFan_flag =0; 
         run_t.gFan_continueRun++;
	   }
	   else if((run_t.gFan_flag == 1 && run_t.gPower_On ==1) && run_t.gFan_counter > 59){
	           FAN_Stop();
			   run_t.gFan_counter=0;
			   run_t.gFan_flag =0; 
	  }
	  else{

            FAN_CCW_RUN();
	   }

	}


}
