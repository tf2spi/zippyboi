#ifndef ZIPPYBOI_H
#define ZIPPYBOI_H


#ifdef ZIPPYBOI_CUSTOM_STDINT
#include "stdint.h"
#else
#include <stdint.h>
#endif

typedef uint8_t zippyboi_u8;
typedef int8_t zippyboi_i8;
typedef uint16_t zippyboi_u16;
typedef int16_t  zippyboi_i16;
typedef uint32_t zippyboi_u32;
typedef int32_t  zippyboi_i32;
typedef uint64_t zippyboi_u64;
typedef int64_t zippyboi_i64;
typedef intptr_t zippyboi_iptr;
typedef uintptr_t zippyboi_uptr;

typedef zippyboi_i32 zippyboi_size;
typedef zippyboi_i32 zippyboi_bool;
#define ZIPPYBOI_FALSE 0
#define ZIPPYBOI_TRUE 1

#ifdef ZIPPYBOI_CUSTOM_STDDEF
#include "stddef.h"
#else
#include <stddef.h>
#endif

#define ZIPPYBOI_NULL NULL
#define ZIPPYBOI_NULLN ((void *)~(zippyboi_iptr)ZIPPYBOI_NULL)

enum zippyboi_disk_seek
{
	ZIPPYBOI_SEEK_SET = -1,
	ZIPPYBOI_SEEK_CUR = 0,
	ZIPPYBOI_SEEK_END = 1,
};
enum zippyboi_codec_level
{
	ZIPPYBOI_LEVEL_D = -1,
	ZIPPYBOI_LEVEL_0 = 0,
	ZIPPYBOI_LEVEL_1 = 1,
	ZIPPYBOI_LEVEL_2 = 2,
	ZIPPYBOI_LEVEL_3 = 3,
	ZIPPYBOI_LEVEL_4 = 4,
	ZIPPYBOI_LEVEL_5 = 5,
	ZIPPYBOI_LEVEL_6 = 6,
	ZIPPYBOI_LEVEL_7 = 7,
	ZIPPYBOI_LEVEL_8 = 8,
	ZIPPYBOI_LEVEL_9 = 8,
};
#define ZIPPYBOI_LEVEL_DECOMPRESS -1
#define ZIPPYBOI_LEVEL_WORST 0
#define ZIPPYBOI_LEVEL_BEST 9
enum zippyboi_codec_type
{
	ZIPPYBOI_CODEC_STORED = 0,
	ZIPPYBOI_CODEC_DEFLATE = 8,
};

typedef zippyboi_i64 zippyboi_off;

#ifdef ZIPPYBOI_USER
#include "zippyboi_user.h"
#else
#include "zippyboi_osal.h"
#endif

zippyboi_disk zippyboi_disk_open(zippyboi_archive archive, zippyboi_u32 disk);
void zippyboi_disk_close(zippyboi_disk disk);
zippyboi_size zippyboi_disk_write(zippyboi_disk disk, const void *buf, zippyboi_size len);
zippyboi_size zippyboi_disk_read(zippyboi_disk disk, void *buf, zippyboi_size len);
zippyboi_off zippyboi_disk_seek(zippyboi_disk disk, zippyboi_off off, int whence);
void *zippyboi_realloc(void *mem, zippyboi_size size);
void zippyboi_free(void *mem);
zippyboi_codec zippyboi_codec_init(int codetype, int level);
void zippyboi_codec_deinit(zippyboi_codec codec);
zippyboi_size zippyboi_codec_bufsize(zippyboi_codec codec);
zippyboi_bool zippyboi_codec_exchange(zippyboi_codec codec, const void *in, zippyboi_size *incount, void *out, zippyboi_size *outcount);
zippyboi_bool zippyboi_codec_seek(zippyboi_codec codec, int whence);
zippyboi_lock zippyboi_lock_init(void);
void zippyboi_lock_deinit(zippyboi_lock lock);
void zippyboi_lock_acquire(zippyboi_lock lock);
void zippyboi_lock_release(zippyboi_lock lock);

typedef struct zippyboi_package zippyboi_package;
typedef struct zippyboi_stream zippyboi_stream;

#endif // ZIPPYBOI_H

#ifdef ZIPPYBOI_IMPLEMENTATION
#include "zippyboi_impl.c"
#endif // ZIPPYBOI_IMPLEMENTATION
