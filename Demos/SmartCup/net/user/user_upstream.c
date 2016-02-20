/**
******************************************************************************
* @file    user_main.c 
* @author  Eshen Wang
* @version V1.0.0
* @date    14-May-2015
* @brief   user main functons in user_main thread.
******************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MXCHIP Inc. SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2014 MXCHIP Inc.</center></h2>
******************************************************************************
*/ 

#include "mico.h"
#include "MicoFogCloud.h"
#include "If_MO.h"
#include "DeviceMonitor.h"
#include "TimeUtils.h"
#include "SendJson.h"
#include "user_debug.h"


/* User defined debug log functions
 * Add your own tag like: 'USER_UPSTREAM', the tag will be added at the beginning of a log
 * in MICO debug uart, when you call this function.
 */
#ifdef DEBUG
  #define user_log(M, ...) custom_log("USER_UPSTREAM", M, ##__VA_ARGS__)
  #define user_log_trace() custom_log_trace("USER_UPSTREAM")
#else
#ifdef USER_DEBUG
  #define user_log(M, ...) user_debug("USER_UPSTREAM", M, ##__VA_ARGS__)
  #define user_log_trace() (void)0
#endif
#endif
  
/* Message upload thread
 */
void user_upstream_thread(void* arg)
{
  user_log_trace();
  app_context_t *app_context = (app_context_t *)arg;
  OSStatus err = kUnknownErr;
  //uint8_t ret = 0;
    
  require(app_context, exit);
  
  /* thread loop */
  while(1){

    if(app_context->appStatus.fogcloudStatus.isCloudConnected == false) {
        user_log("user_upstream_thread: cloud disconnected");
        mico_thread_sleep(2);
        continue;
    }
  }

exit:
  if(kNoErr != err){
    user_log("ERROR: user_uptream exit with err=%d", err);
  }
  mico_rtos_delete_thread(NULL);  // delete current thread
}







