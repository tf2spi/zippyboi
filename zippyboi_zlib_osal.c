#include "zippyboi.h"

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

#include <stdio.h>
#include <stdlib.h>

typedef int osal_handle; 
struct osal_disk
{
	char *reopen_name;
	int handle;
	int flags;
	int mode;
};

static zippyboi_size osal_disk_read(void *disk, void *buf, zippyboi_size len)
{
	return osal_read(((struct osal_disk *)disk)->handle, buf, len);
}

static zippyboi_size osal_disk_write(void *disk, void *buf, zippyboi_size len)
{
	return osal_write(((struct osal_disk *)disk)->handle, buf, len);
}

static zippyboi_off osal_disk_seek(void *disk, zippyboi_off off, int whence)
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
	return osal_seek(((struct osal_disk *)disk)->handle, off, osal_whence);
}

static int osal_disk_open(struct osal_disk *disk, const char *name, int mode, int flags)
{
	return -1;
}

static struct zippyboi_vtable osal_vtable =
{
	ZIPPYBOI_NULL, // reopen
	ZIPPYBOI_NULL, // close
	osal_disk_write, // write
	osal_disk_read, // read
	osal_disk_seek, // seek
	(zippyboi_realloc)realloc, // realloc
	free, // free
	ZIPPYBOI_NULL, // codec_alloc
	ZIPPYBOI_NULL, // codec_free
	ZIPPYBOI_NULL, // codec_bufsize
	ZIPPYBOI_NULL, // codec_exchange
	ZIPPYBOI_NULL, // codec_seek
	ZIPPYBOI_NULL, // lock_alloc
	ZIPPYBOI_NULL, // lock
	ZIPPYBOI_NULL, // lock_free
};
