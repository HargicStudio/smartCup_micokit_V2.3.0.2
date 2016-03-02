
/***

History:
2016-02-27: Ted: Create

*/

#ifndef _TRANSPROTOCOL_H
#define _TRANSPROTOCOL_H

#ifdef __cplusplus
 extern "C" {
#endif 


#include "Object_int.h"
#include "stdbool.h"
    

typedef enum ETransProto_t {
	TRACKNUM = 0x11,
	TRACKLIST = 0x12,
	TRACKPLAY = 0x13
} ETransProto;



#ifdef __cplusplus
}
#endif

#endif // _TRANSPROTOCOL_H

// end of file