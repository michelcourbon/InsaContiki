/*
 * mem_id.c
 *
 *  Created on: Sep 19, 2012
 *      Author: user
 */

#include "mem-id.h"
#include <string.h>

unsigned char memory_id[8];

int
memory_id_init(void) {
  unsigned char *uid;
  uid = (unsigned char *) 0x7ff0;
  memcpy(memory_id, uid, sizeof(memory_id));
  return 1;
}


