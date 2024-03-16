enum zippyboi_pk_signature
{
	ZIPPYBOI_PK_EOCD = 0x06054b50,
	ZIPPYBOI_PK_CFH = 0x02014b50,
	ZIPPYBOI_PK_LFH = 0x04034b50,
	ZIPPYBOI_PK_EOCD64 = 0x07064b50,
	ZIPPYBOI_PK_LOCATOR = 0x06064b50,
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
	const char **fnames;
	void **cfhs;
	void *cdir;
};

struct zippyboi_package
{
	struct zippyboi_vtable *vtable;
	void *lock;
	zippyboi_u32 reference_count;
	struct zippyboi_map map;
	void **handles;
	struct zippyboi_footer footer;
	void (*debugbreak)(void);
};

struct zippyboi_stream
{
	zippyboi_lock *lock;
	zippyboi_codec *codec;
	zippyboi_disk *main;
	zippyboi_disk **disks;
	void *codec_buffer;
	zippyboi_size codec_bufsize;
	zippyboi_size codec_bufidx;
	zippyboi_off begin;
	zippyboi_off end;
	zippyboi_off current;
	zippyboi_i64 decode_progress;
	zippyboi_i64 decode_size;
	struct zippyboi *package;
	zippyboi_u32 reference_count;
	zippyboi_u32 crc32;
};

static void zippyboi_break(zippyboi_package *pkg)
{
	if (pkg->debugbreak != ZIPPYBOI_NULL)
		pkg->debugbreak();
}
