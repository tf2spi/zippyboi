// Definition in implementation
typedef struct zippyboi_archive *zippyboi_archive;
typedef int zippyboi_disk;
typedef struct zippyboi_lock *zippyboi_lock;
typedef struct zippyboi_codec *zippyboi_codec;

#define ZIPPYBOI_ARCHIVE_INVALID ZIPPYBOI_NULL
#define ZIPPYBOI_DISK_INVALID -1
#define ZIPPYBOI_LOCK_INVALID ZIPPYBOI_NULL
#define ZIPPYBOI_CODEC_INVALID ZIPPYBOI_NULL

// Not a required function but is a useful helper
zippyboi_archive osal_archive_open(const char *fname, int mode, int flags);

#ifdef ZIPPYBOI_IMPLEMENTATION

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <io.h>
#include <malloc.h>
#include <stdlib.h>
#define osal_open _open
#define osal_write _write
#define osal_read _read
#define osal_seek _lseeki64

#else // _WIN32

#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#define osal_open open
#define osal_write write
#define osal_read read
#define osal_seek lseek

#endif // _WIN32

#include <stdlib.h>
#include <stdio.h>

struct zippyboi_archive
{
	char *reopen_name;
	int flags;
	int mode;
};

struct zippyboi_codec
{
	char _dummy;
};

struct zippyboi_lock
{
	char _dummy;
};

zippyboi_archive zippyboi_archive_create(const char *name, int flags, int mode)
{
	return ZIPPYBOI_ARCHIVE_INVALID;
}

zippyboi_size zippyboi_disk_read(zippyboi_disk disk, void *buf, zippyboi_size len)
{
	return osal_read(disk, buf, len);
}

zippyboi_size zippyboi_disk_write(zippyboi_disk disk, const void *buf, zippyboi_size len)
{
	return osal_write(disk, buf, len);
}

zippyboi_off zippyboi_disk_seek(zippyboi_disk disk, zippyboi_off off, int whence)
{
	int osal_whence = -1;
	switch (whence)
	{
		case ZIPPYBOI_SEEK_SET:
			osal_whence = SEEK_SET;
			break;
		case ZIPPYBOI_SEEK_CUR:
			osal_whence = SEEK_CUR;
			break;
		case ZIPPYBOI_SEEK_END:
			osal_whence = SEEK_END;
			break;
	}
	return osal_seek(disk, off, osal_whence);
}

zippyboi_disk zippyboi_disk_open(zippyboi_archive archive, zippyboi_u32 disk)
{
	return ZIPPYBOI_DISK_INVALID;
}

void *zippyboi_realloc(void *mem, zippyboi_size size)
{
	return realloc(mem, size);
}

void zippyboi_free(void *mem)
{
	free(mem);
}

void zippyboi_codec_deinit(zippyboi_codec codec)
{
}

zippyboi_codec zippyboi_codec_init(int codetype, int level)
{
	return ZIPPYBOI_CODEC_INVALID;
}

zippyboi_size zippyboi_codec_bufsize(zippyboi_codec codec)
{
	return 32768;
}

zippyboi_bool zippyboi_codec_exchange(zippyboi_codec codec,
		const void *in, zippyboi_size *incount,
		void *out, zippyboi_size *outcount)
{
	return ZIPPYBOI_FALSE;
}

zippyboi_bool zippyboi_codec_seek(zippyboi_codec codec, int whence)
{
	return ZIPPYBOI_FALSE;
}

void zippyboi_lock_deinit(zippyboi_lock lock)
{
}

zippyboi_lock zippyboi_lock_init(void)
{
	return ZIPPYBOI_LOCK_INVALID;
}

void zippyboi_lock_acquire(zippyboi_lock lock)
{
}

void zippyboi_lock_release(zippyboi_lock lock)
{
}

#endif // ZIPPYBOI_IMPLEMENTATION
