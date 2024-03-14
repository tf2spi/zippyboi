#ifndef ZIPPYBOI_H
#define ZIPPYBOI_H

#if defined(_MSC_VER) || defined(__SYMBIAN32__)
typedef unsigned char zippyboi_u8;
typedef   signed char zippyboi_i8;
typedef unsigned short zippyboi_u16;
typedef   signed short zippyboi_i16;
typedef unsigned int   zippyboi_u32;
typedef   signed int   zippyboi_i32;
typedef unsigned __uint64 zippyboi_i64;
typedef   signed __int64 zippyboi_i64;
#else
#include <stdint.h>
typedef uint8_t zippyboi_u8;
typedef int8_t zippyboi_i8;
typedef uint16_t zippyboi_u16;
typedef int16_t  zippyboi_i16;
typedef uint32_t zippyboi_u32;
typedef int32_t  zippyboi_i32;
typedef uint64_t zippyboi_u64;
typedef int64_t zippyboi_i64;
#endif

typedef zippyboi_i32 zippyboi_size;
typedef zippyboi_i32 zippyboi_bool;
#define ZIPPYBOI_FALSE 0
#define ZIPPYBOI_TRUE 1

enum zippyboi_file_seek
{
	ZIPPYBOI_SEEK_BEGIN = -1,
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
typedef void *(*zippyboi_reopen)(void *file);
typedef void (*zippyboi_close)(void *file);
typedef zippyboi_size (*zippyboi_write)(void *file, void *mem, zippyboi_size size);
typedef zippyboi_size (*zippyboi_read)(void *file, void *mem, zippyboi_size cap);
typedef zippyboi_off (*zippyboi_seek)(void *file, zippyboi_off off, int whence);
typedef void *(*zippyboi_realloc)(void *mem, zippyboi_size size);
typedef void (*zippyboi_free)(void *mem);
typedef void *(*zippyboi_codec_alloc)(int codec, int level);
typedef void (*zippyboi_codec_free)(void *codec);
typedef zippyboi_size (*zippyboi_codec_feed)(void *codec, void *mem, zippyboi_size size);
typedef zippyboi_size (*zippyboi_codec_barf)(void *codec, void *mem, zippyboi_size cap);
typedef void (*zippyboi_codec_seek)(void *codec, int whence);
typedef void *(*zippyboi_lock_alloc)(void);
typedef void (*zippyboi_lock)(void *lock);
typedef void (*zippyboi_unlock)(void *lock);
typedef void (*zippyboi_lock_free)(void *lock);

struct zippyboi_vtable
{
	zippyboi_reopen reopen;
	zippyboi_close close;
	zippyboi_write write;
	zippyboi_read read;
	zippyboi_seek seek;
	zippyboi_realloc realloc;
	zippyboi_free free;
	zippyboi_codec_alloc codec_alloc;
	zippyboi_codec_free codec_free;
	zippyboi_codec_feed codec_feed;
	zippyboi_codec_barf codec_barf;
	zippyboi_codec_seek codec_seek;
	zippyboi_lock_alloc lock_alloc;
	zippyboi_lock lock;
	zippyboi_lock_free lock_free;
};

struct zippyboi_header
{
	zippyboi_off data_offset;
	zippyboi_i64 decode_size;
	zippyboi_u32 crc32;
	zippyboi_u16 compression;

	// Unnecessary for reading the file
#ifndef ZIPPYBOI_REPO_ONLY
	zippyboi_u16 date;
	zippyboi_u16 time;
	zippyboi_u16 flags;
	zippyboi_u16 internal;
	zippyboi_u32 external;
	zippyboi_u16 version;
	zippyboi_u16 version_needed;
	zippyboi_off lfh_offset;
	zippyboi_i64 encode_size;
#endif
};

struct zippyboi_footer
{
	zippyboi_i64 count;
	zippyboi_i64 size;
	zippyboi_off offset;
	zippyboi_u16 version;
	zippyboi_u16 needed;
};

struct zippyboi_map
{
	char *strtable;
	const char **mapping;
	struct zippyboi_header *headers;
};

struct zippyboi
{
	struct zippyboi_vtable *vtable;
	void *lock;
	zippyboi_u32 reference_count;
	struct zippyboi_map map;
	void **handles;
	struct zippyboi_footer footer;
};

struct zippyboi_stream
{
	struct zippyboi_vtable *vtable;
	void *lock;
	void *codec;
	void *file;
	zippyboi_off begin;
	zippyboi_off end;
	zippyboi_off current;
	zippyboi_i64 decode_progress;
	zippyboi_i64 decode_size;
	struct zippyboi *package;
	zippyboi_u32 reference_count;
	zippyboi_u32 crc32;
};

#ifdef ZIPPYBOI_IMPLEMENTATION

enum zippyboi_pk_signature
{
	ZIPPYBOI_PK_EOCD = 0x06054b50,
	ZIPPYBOI_PK_CFH = 0x02014b50,
	ZIPPYBOI_PK_LFH = 0x04034b50,
	ZIPPYBOI_PK_EOCD64 = 0x07064b50,
	ZIPPYBOI_PK_LOCATOR = 0x06064b50,
};

#endif // ZIPPYBOI_IMPLEMENTATION

#endif // ZIPPYBOI_H
