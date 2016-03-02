


/***

History:
2015-12-22: Ted: Create

*/


#include "MusicMonitor.h"
#include "If_MO.h"
#include "user_debug.h"


#ifdef DEBUG
  #define user_log(M, ...) custom_log("MusicMonitor", M, ##__VA_ARGS__)
  #define user_log_trace() custom_log_trace("MusicMonitor")
#else
#ifdef USER_DEBUG
  #define user_log(M, ...) user_debug("MusicMonitor", M, ##__VA_ARGS__)
  #define user_log_trace() (void)0
#endif
#endif


typedef struct SPlaylTrack_t {
    u16 trackNum;
} SPlayTrack;

#define MAX_WAITING_TRACK_NUM   5

#define STACK_SIZE_MUSIC_THREAD          0x400


static mico_thread_t music_monitor_thread_handle = NULL;
static mico_queue_t track_queue = NULL;


static void music_thread(void* arg);
static char* SongIndexMap(u16 trackindex);


OSStatus MusicInit()
{
    OSStatus err;

    err = mico_rtos_init_queue(&track_queue, "TrackQueue", sizeof(u16), MAX_WAITING_TRACK_NUM);
    require_noerr_action(err, exit, user_log("[ERR]MusicInit: track_queue initialize failed"));
    require(track_queue, exit);
    user_log("[DBG]MusicInit: track_queue initialize success");
    
#if 1
    // start the music monitor thread
    err = mico_rtos_create_thread(&music_monitor_thread_handle, MICO_APPLICATION_PRIORITY, "music_monitor", 
                                  music_thread, STACK_SIZE_MUSIC_THREAD, 
                                  NULL );
    require_noerr_action( err, exit, user_log("[ERR]MusicInit: create music thread failed") );
    user_log("[DBG]MusicInit: create music thread success");
#endif
    
exit:
    return err;
}

static void music_thread(void* arg)
{
    // avoid compiling warning
    arg = arg;
    user_log_trace();

    SPlayTrack track = {0};
    char name[_MAX_LFN];
    char pathname[_MAX_LFN];

    if(GetPowerOnDisplay() == true) {
        MP3_playSong("提醒及时喝水.mp3");
    }
  
    /* thread loop */
    while(1) {
        if(kNoErr == mico_rtos_pop_from_queue(&track_queue, &track, MICO_WAIT_FOREVER)) {
            // TODO: playing the song in while, get the track number by " *track "

            user_log("[DBG]music_thread: play song index(%d)", track.trackNum);

            MP3_getMp3FileName("0:/", (u8)track.trackNum, (u8*)name);
            sprintf(pathname, "0:/%s\0", name);
            user_log("[DBG]music_thread: start play song %s", pathname);
            MP3_playSong(pathname);  //播放指定歌曲
            
//            sprintf(name, "0:/%s\0", SongIndexMap(track.trackNum));
//            MP3_playSong(name);  //播放指定歌曲
            user_log("[DBG]music_thread: play song finished");
        }
    }

//    mico_rtos_delete_thread(NULL);  // delete current thread
}

static char* SongIndexMap(u16 trackindex)
{
    char* str = NULL;
    switch(trackindex) {
        case 1: str = "1.mp3"; break;
        case 2: str = "2.mp3"; break;
        case 3: str = "3.mp3"; break;
        case 4: str = "4.mp3"; break;
        case 5: str = "5.mp3"; break;
        case 6: str = "6.mp3"; break;
        case 7: str = "7.mp3"; break;
        case 8: str = "8.mp3"; break;
        case 9: str = "电池没电了.mp3"; break;
        case 10: str = "提醒及时喝水.mp3"; break;
        case 11: str = "喝水.mp3"; break;
        default: str = NULL; break;
    }

    return str;
}

OSStatus PlayingSong(u16 tracknum)
{
    OSStatus err;
    SPlayTrack track = {0};

    user_log("[DBG]PlayingSong: get song index %d", tracknum);
    track.trackNum = tracknum;
    err = mico_rtos_push_to_queue(&track_queue, &track, MICO_WAIT_FOREVER);

    return err;
}

// end of file


