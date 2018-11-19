#ifndef MUSIC_INFO_H
#define MUSIC_INFO_H


#include "typedef.h"
#include "music_api.h"

void * music_get_file_id3(u32 len);
void music_file_info(MUSIC_OP_API *m_op_api);
u8 get_floder_name(char* ptr,u32 filecount);
void get_floder_totalfile(u32 filecount);

#endif
