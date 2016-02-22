


/***

History:
2015-11-30: Ted: Create

*/

#ifndef _IF_MO_H
#define _IF_MO_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "Object_int.h"
#include "stdbool.h"
   
//
// DEVICE-1
//
typedef struct SDevice_t {
    u8      power;
    i16     signalStrength;
    float   tfCapacity;
    float   tfFree;
    bool    lowPowerAlarm;
    bool    powerOnDisplay;
    bool    tfStatus;
} SDevice;

//
// LIGHTS-1
//
typedef struct SLedConf_t {
    u8      red;
    u8      green;
    u8      blue;
} SLedConf;


typedef struct SLight_t {
    SLedConf ledConf;
    u8      brightness;
    bool    enableNotifyLight;
    bool    ledSwitch;
} SLight;

//
// MUSIC-1
//
typedef struct SMusic_t {
    u8      volume;
    u8      downLoadRate;
    u16     trackNumber;
    u16     delTrack;
    char*   urlPath;
} SMusic;


typedef struct STrack_t {
    u16     trackIdx;
    char*   trackName;
} STrack;

//
// HEALTH-1
//
typedef struct SNoDisturbingTime_t {
    u8      startHour;
    u8      endHour;
    u8      startMinute;
    u8      endMinute;
} SNoDisturbingTime;

typedef struct SHealth_t {
    SNoDisturbingTime noDisturbingTime;
    bool    drinkStamp;
    bool    putDownStamp;
    bool    ifNoDisturbing;
} SHealth;


#define MAX_DEPTH_PICKUP    8

typedef struct SPickup_t {
    u16     selTrack;
    bool    enable;
} SPickup;


#define MAX_DEPTH_PUTDOWN   5

typedef struct SPutdown_t {
    u16     remindDelay;
    u16     selTrack;
    bool    enable;
} SPutdown;


#define MAX_DEPTH_IMMEDIATE     1

typedef struct SImmediate_t {
    u16     selTrack;
    bool    enable;
} SImmediate;


#define MAX_DEPTH_SCHEDULE  5

typedef struct SSchedule_t {
    u16     selTrack;
    u8      remindHour;
    u8      remindMinute;
    u8      remindTimes;
    bool    enable;
} SSchedule;

//
// HEATER-1
//
typedef struct SAppoint_t {
    u8      Hour;
    u8      Minute;
} SAppoint;

typedef struct SHeater_t {
    SAppoint appoint;
    i8      temperature;
    i8      targetTemp;
    bool    tempSwitch;
    bool    ifHeaterWorking;
} SHeater;


void MOInit();

//DEVICE-1
void SetPower(u8 power);
u8 GetPower();
bool IsPowerChanged();

void SetLowPowerAlarm(bool flag);
bool GetLowPowerAlarm();
bool IsLowPowerAlarmChanged();

void SetSignalStrengh(i16 value);
i16 GetSignalStrengh();
bool IsSignalStrenghChanged();

void SetPowerOnDisplay(bool flag);
bool GetPowerOnDisplay();
bool IsPowerOnDisplayChanged();

void SetTFStatus(bool flag);
bool GetTFStatus();
bool IsTFStatusChanged();

void SetTFCapacity(float value);
float GetTFCapacity();
bool IsTFCapacityChanged();

void SetTFFree(float value);
float GetTFFree();
bool IsTFFreeChanged();

//LIGHTS-1
void SetEnableNotifyLight(bool flag);
bool GetEnableNotifyLight();
bool IsEnableNotifyLightChanged();

void SetLedSwitch(bool flag);
bool GetLedSwitch();
bool IsLedSwitchChanged();

void SetBrightness(u8 brightness);
u8 GetBrightness();
bool IsBrightnessChanged();

void SetRedConf(u8 value);
u8 GetRedConf();
void SetGreenConf(u8 value);
u8 GetGreenConf();
void SetBlueConf(u8 value);
u8 GetBlueConf();
bool IsLedConfChanged();

//MUSIC-1
void SetVolume(u8 value);
u8 GetVolume();
bool IsVolumeChanged();

void SetDownLoadRate(u8 value);
u8 GetDownLoadRate();
bool IsDownLoadRateChanged();

//HEALTH-1
void SetDrinkStamp(bool flag);
bool GetDrinkStamp();
bool IsDrinkStampChanged();

void SetPutDownStamp(bool flag);
bool GetPutDownStamp();
bool IsPutDownStampChanged();

void SetIfNoDisturbing(bool flag);
bool GetIfNoDisturbing();
bool IsIfNoDisturbingChanged();

void SetNoDisturbingStartHour(u8 starthour);
u8 GetNoDisturbingStartHour();
void SetNoDisturbingEndHour(u8 endhour);
u8 GetNoDisturbingEndHour();
void SetNoDisturbingStartMinute(u8 startminute);
u8 GetNoDisturbingStartMinute();
void SetNoDisturbingEndMinute(u8 endminute);
u8 GetNoDisturbingEndMinute();
bool IsNoDisturbingTimeChanged();

void SetPickUpEnable(u8 index, bool enable);
bool GetPickUpEnable(u8 index);
void SetPickUpSelTrack(u8 index, u16 track);
u16 GetPickUpSelTrack(u8 index);
bool IsPickupChanged(u8 index);

void SetPutDownEnable(u8 index, bool enable);
bool GetPutDownEnable(u8 index);
void SetPutDownSelTrack(u8 index, u16 track);
u16 GetPutDownSelTrack(u8 index);
void SetPutDownRemindDelay(u8 index, u16 delay);
u16 GetPutDownRemindDelay(u8 index);
bool IsPutdownChanged(u8 index);

void SetImmediateEnable(u8 index, bool enable);
bool GetImmediateEnable(u8 index);
void SetImmediateSelTrack(u8 index, u16 track);
u16 GetImmediateSelTrack(u8 index);
bool IsImmediateChanged(u8 index);

void SetScheduleEnable(u8 index, bool enable);
bool GetScheduleEnable(u8 index);
void SetScheduleSelTrack(u8 index, u16 track);
u16 GetScheduleSelTrack(u8 index);
void SetScheduleRemindHour(u8 index, u8 rh);
u8 GetScheduleRemindHour(u8 index);
void SetScheduleRemindMinute(u8 index, u8 rm);
u8 GetScheduleRemindMinute(u8 index);
void SetScheduleRemindTimes(u8 index, u8 value);
u8 GetScheduleRemindTimes(u8 index);
bool IsScheduleChanged(u8 index);

//HEATER-1
void SetTemperature(float value);
float GetTemperature();
bool IsTemperatureChanged();

void SetTempSwitch(bool flag);
bool GetTempSwitch();
bool IsTempSwitchChanged();

void SetTargetTemp(i8 value);
i8 GetTargetTemp();
bool IsTargetTempChanged();

void SetAppointmentHour(u8 hour);
u8 GetAppointmentHour();
void SetAppointmentMinute(u8 minute);
u8 GetAppointmentMinute();
bool IsAppointmentChanged();

void SetIfHeaterWorking(bool flag);
bool GetIfHeaterWorking();
bool IsIfHeaterWorkingChanged();


   
#ifdef __cplusplus
}
#endif

#endif // _IF_MO_H

// end of file


