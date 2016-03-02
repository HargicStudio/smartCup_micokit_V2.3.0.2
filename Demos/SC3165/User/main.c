/******************************************************************************
* @file    main.c 
* @author  Jianguang Hu
* @version V1.0.0
* @date    5-sept-2015
* @brief   Smart cup main.
*******************************************************************************/


#include "MiCO.h" 
#include "syscom.h"
#include "MICOAppDefine.h"
#include "user_debug.h"


#ifdef DEBUG
  #define user_log(M, ...) custom_log("MAIN", M, ##__VA_ARGS__)
  #define user_log_trace() custom_log_trace("MAIN")
#else
#ifdef USER_DEBUG
  #define user_log(M, ...) user_debug("MAIN", M, ##__VA_ARGS__)
  #define user_log_trace() (void)0
#endif
#endif


extern OSStatus net_main( app_context_t * const app_context );
static void Mp3Init();


extern mico_semaphore_t semaphore_getup;
extern mico_semaphore_t semaphore_putdown;


//�ᱭ�ͷű�������
static void  KEY_irq_handler( void* arg )
{
  (void)(arg);

   if ( KEY_getValue() == KEY_UP) {
        user_log("[DBG]KEY_irq_handler: key up");
        mico_rtos_set_semaphore(&semaphore_putdown);
   } 
   else {
        user_log("[DBG]KEY_irq_handler: key down");
        mico_rtos_set_semaphore(&semaphore_putdown);
   }
    
}

#if 0 // comment by Ted
/* �ƹ⴦���߳� */
void LED_handleThread(void *inContext)
{
    u8  ledValue = 0;
    u8  playLedTimes = 0; //�޲�������ʱ����ʾLED����
    
    printf( "This is LED_handleThread.\r\n");
    LED_openRGB(0, 0, 0); //��ʼ���ر����е�
    LED_closeRGB();
#if 0 
    while(1)
    {
          printf("Playing led ........\r\n");

          for (ledValue = 0; ledValue < 100; ledValue++)
          {
              LED_openRGB(100 - ledValue, ledValue, ledValue);
              mico_thread_msleep(15);
          }
          mico_thread_msleep(1000);
          
          for (ledValue = 100; ledValue > 0; ledValue--)
          {
              LED_openRGB(100 - ledValue, ledValue, ledValue);
              mico_thread_msleep(15);
          } 
           LED_openRGB(0, 0, 0);
          mico_thread_msleep(1000);

          
          LED_openRGB(100, 0, 0);
          mico_thread_msleep(1000);
          LED_openRGB(0, 0, 0);
          
          LED_openRGB(0, 100, 0);
          mico_thread_msleep(1000);
          LED_openRGB(0, 0, 0);
          
          LED_openRGB(0, 0, 100);
          mico_thread_msleep(1000);
          LED_openRGB(0, 0, 0);
          mico_thread_msleep(1000);
          
          /* ���� */
          LED_openRGB(50, 50, 50);
          mico_thread_msleep(500);
          LED_openRGB(0, 0, 0);
          mico_thread_msleep(500); 
    
    }
#endif
    
     while(mico_rtos_get_semaphore(&cupTimeObj.playLed_sem, MICO_WAIT_FOREVER) == kNoErr)
    {
        
       while(mico_rtos_get_semaphore(&cupTimeObj.stopLed_sem, MICO_NO_WAIT) != kNoErr \
           && cupTimeObj.playMode != PLAY_ONLY_MP3)
       {
          //printf("Playing led ........\r\n");
#if 0
          for (ledValue = 0; ledValue < 100; ledValue++)
          {
              LED_openRGB(100 - ledValue, ledValue, ledValue);
              mico_thread_msleep(15);
          }
          mico_thread_msleep(100);
          
          for (ledValue = 100; ledValue > 0; ledValue--)
          {
              LED_openRGB(100 - ledValue, ledValue, ledValue);
              mico_thread_msleep(15);
          } 
          mico_thread_msleep(100);
#else
          /* ���� */
          LED_openRGB(50, 50, 50);
          mico_thread_msleep(500);
          LED_openRGB(0, 0, 0);
          mico_thread_msleep(500);
#endif
          
          /* ֻ��LEDģʽʱ��LEDֻ��ʾ���� */
          if (cupTimeObj.playMode == PLAY_ONLY_LED)
          {
              playLedTimes++;
              if (playLedTimes == 3 || KEY_getValue() == KEY_UP)
              {
                  playLedTimes = 0; 
                  break;
              }
          }
       }
       
       LED_openRGB(0, 0, 0);
       LED_closeRGB();
     
    }
}
#endif

#if 0 // comment by Ted
/* MP3���ִ����߳� */
void MP3_handleThread(void *inContext)
{
    SD_sizeInfo sdSizeInfo;
    u8 ret = 0;
    u8  *pMp3FileName;
    u16 mp3FileNum = 0, i;
    
     /* ����Ƿ����SD�� */
     if (MP3_sdCardDetect() == 0)
    {
        while(1)
       {
         printf( "sdCard not insert !!!!!\r\n");
         mico_thread_sleep( 1 );
       }
    }

     /* MP3��ʼ����*/   
    if (MP3_init() == 0)
    {
        while(1)
       {
         printf( "mp3 init failed !!!!!\r\n");
         mico_thread_sleep( 1 );
       }
    }

    /* ��ȡSD��������Ϣ */
    MP3_getSdSize(&sdSizeInfo);
    printf("%d MB total drive space.\r\n" "%d MB available.\r\n",
           sdSizeInfo.totalSize, sdSizeInfo.availableSize);
 
    /* ��ȡMP3�ļ����� */
    ret = MP3_getMp3FileNum("0:/");
    printf("mp3FileNum=%d\r\n", ret);

#if 0
    /* д�ļ� */
    pBuf = malloc(512);
    if (pBuf != NULL)
    {
      memset(pBuf, 0x5a, 512); 
      ret = MP3_writeSong("0:/MUSIC/hujg.mp3", 0, pBuf, 512);
      printf("ret0=%d\r\n", ret);
      memset(pBuf, 0xa5, 512);
      ret = MP3_writeSong("0:/MUSIC/hujg.mp3", 512, pBuf, 512);
      printf("ret1=%d\r\n", ret);
      free(pBuf);
    }
  
     /* ɾ���ļ� */
     ret = MP3_removeSong("0:/MUSIC/hujg_bak.mp3");
    if (ret == 1)
    {
       printf("remove mp3 file success!\r\n");
    }
    else
    {
       printf("remove mp3 file failed !\r\n");
    }
#endif

    /* ����ָ���������������� */
    while(mico_rtos_get_semaphore(&cupTimeObj.playMp3_sem, MICO_WAIT_FOREVER) == kNoErr)
    {
#if 1   // comment by Ted
       if (cupTimeObj.playMode != PLAY_ONLY_LED)  //������ǵ��������Ѻ�ˮʱ
       {
         MP3_setVolume(25);
         printf("MP3_getVolume=%d\r\n", MP3_getVolume());

         ret = MP3_playSong("0:/��ˮ.mp3");  //����ָ������
         printf("play over!!!!ret=%d\r\n", ret);
         mico_rtos_set_semaphore(&cupTimeObj.stopLed_sem);  //ֹ֪ͨͣ��LED��
       }
      // mp3_play();
#endif
    }
}

#endif

static void Mp3Init()
{
    u32 ret = 0;
    
    /* ����Ƿ����SD�� */
    if (MP3_sdCardDetect() == 0) {
        while(1) {
            user_log("[ERR]Mp3Init: sdCard not insert");
            mico_thread_sleep( 1 );
        }
    }

    /* MP3��ʼ����*/   
    if (MP3_init() == 0) {
        while(1) {
            user_log("[ERR]Mp3Init: mp3 init failed");
            mico_thread_sleep( 1 );
        }
    }
    
    /* ��ȡMP3�ļ����� */
    ret = MP3_getMp3FileNum("0:/");
    user_log("[DBG]Mp3Init: mp3FileNum = %d", ret);
}

#if 0 // comment by Ted
/* ��������߳� */
void BAT_handleThread(void *inContext)
{

    printf( "This is BAT_handleThread.\r\n");
    while(1)
    {
        mico_thread_msleep(5000); /* �͵���ʱ�������ϴ�ƽ̨ */
    }
}
#endif

/* user main function, called by AppFramework after system init done && wifi
 * station on in user_main thread.
 */
OSStatus user_main( app_context_t * const app_context )
{
  OSStatus err = kNoErr;
   
  require(app_context, exit);


  UserDebug_Init();

#if 0
  /* Create a new thread */
  err = mico_rtos_create_thread(NULL, MICO_APPLICATION_PRIORITY, "MP3_PLAY", MP3_handleThread, 1024, NULL );
  require_noerr_string( err, exit, "ERROR: Unable to start the MP3 PLAY thread" ); 

  err = mico_rtos_create_thread(NULL, MICO_APPLICATION_PRIORITY, "BAT_DETECT", BAT_handleThread, 500, NULL );
  require_noerr_string( err, exit, "ERROR: Unable to start the BAT DETECT thread ." );
#endif
  
  KEY_Init(KEY_irq_handler); //������ʼ��
  Mp3Init();
  
  // by Ted
#if 1
  net_main(app_context);
#endif

  while(1) {
#if 1
      mico_thread_sleep(MICO_WAIT_FOREVER);
#else
      mico_thread_sleep(5);

      MP3_setVolume(22);
      MP3_playSong("0:/���Ѽ�ʱ��ˮ.mp3");
      
      mico_thread_sleep(5);

      MP3_setVolume(22);
      MP3_playSong("0:/american_goldfinch.wav");
#endif

  }
  
exit:
  if(kNoErr != err){
    user_log("[ERR]user_main: user_main thread exit with err = %d", err);
  }
  mico_rtos_delete_thread(NULL);
  return kNoErr;  
}


