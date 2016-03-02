
/***

History:
2016-02-27: Ted: Create

*/

#include "mico.h"
#include "TransProtocol.h"


#ifdef DEBUG
  #define user_log(M, ...) custom_log("TransProtocol", M, ##__VA_ARGS__)
  #define user_log_trace() custom_log_trace("TransProtocol")
#else
#ifdef USER_DEBUG
  #define user_log(M, ...) user_debug("TransProtocol", M, ##__VA_ARGS__)
  #define user_log_trace() (void)0
#endif
#endif


#define MAGIC   0x5A
#define TAIL    0xAA


struct STransProto
{
    u8          magic;
    ETransProto cmd;
    u16         data_len;
    u8          data_checksum;
    u8          tail;
};


/*
 *  data_len: sizeof(u8) length
 */
void SendTransProto(ETransProto cmd, u8 *data, u16 data_len)
{
    u16 idx = 0;
    u8 checksum = 0;
    u16 msg_len = data_len + sizeof(struct STransProto);
    u8 *buffer = malloc(msg_len);
    if(buffer == NULL) {

    }

    for(idx = 0; idx < data_len; idx++) {
        checksum += *(data + idx);
    }

    (struct STransProto*)buffer->magic = MAGIC;
    (struct STransProto*)buffer->cmd = cmd;
    (struct STransProto*)buffer->data_len = data_len;
    (struct STransProto*)buffer->data_checksum = checksum;
    (struct STransProto*)buffer->tail = TAIL;

    memcpy(buffer + sizeof(struct STransProto), data, data_len);
    // TODO: send through spi interface

    user_log("[DBG]SendTransProto: buffer as follow");
    for(idx = 0; idx < msg_len; idx++) {
        if((idx % 16) == 0) {
            user_log("[DBG]SendTransProto:");
        }
        if((idx % 4) == 0) {
            printf(" ");
        }
        printf("%x", *(buffer + idx));
    }

    if(buffer != NULL) free(buffer);
}




// end of file