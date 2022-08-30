#include "single_mode.h"
#include "wifi_fun.h"
#include "run.h"

void Single_RunCmd(uint8_t sig)
{
   Ai_Fun(sig);
}


void Single_Mode(void)
{
   if(run_t.SingleMode ==1){
     
     Single_RunCmd(run_t.Single_cmd);

    }

}
