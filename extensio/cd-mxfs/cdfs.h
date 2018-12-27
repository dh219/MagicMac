/*
	@(#)CD-FS/cdfs.h
	
	Julian F. Reschke, 1. Mai 1997
*/

/**** Device structures ****/

#define BLOCKSIZE			2048L
#define LONGNAMELENGTH		128

typedef struct
{
	/* start of length of primary and associated file */
	struct {
		unsigned long start, length;
	} pri;
	struct {
		unsigned long start, length;
	} ass;

	/* internal index */
	unsigned long	iindex;

	/* other user visible file attributes */
	unsigned int	mode;
	unsigned int	adate, atime;
	unsigned int	cdate, ctime;
	unsigned int	mdate, mtime;
	unsigned int 	nlink, uid, gid;
	unsigned char	tosattr, fsprivate;
	char			longname[LONGNAMELENGTH];
	char			truncname[14];
	long			type, creator;
} DIRENTRY;

/* File structure, 8 longs max */
typedef struct
{
	unsigned long	start, size, offset, iindex, de_end;
	unsigned int	dev, dirflg;
} MYFILE;

#if sizeof (MYFILE) > 32
#error MYFILE structure too big for MetaDOS
#endif

typedef struct
{
	long	(*get_root)(struct logical_dev *, unsigned long, int);
	long	(*get_direntry)(struct logical_dev *, unsigned long *,
				unsigned long dirend, DIRENTRY *);
	long	(*readfile)(struct logical_dev *, long start, long offset,
				long size, long iindex, long cnt, char *buffer);
	long	(*label)(struct logical_dev *, char *str, int size, int rw);
	long	(*pathconf)(struct logical_dev *, int mode);
} FILESYSTEM;

typedef struct
{
	unsigned char	data[BLOCKSIZE];
	unsigned long	timestamp, blkno;
	unsigned int	device;
} CACHEENTRY;

typedef struct logical_dev
{
	int 			metadevice;
	int				fspreference;
	FILESYSTEM		fs;
	char			scratch[2352];
	int				fsprivate;
	char			fslabel[34];
	unsigned long	blocksize, totalsize;
	unsigned long	rootdir, rootdirsize;
	unsigned long	mediatime;
	unsigned int	mount_date, mount_time;
	union {
		struct {
			unsigned long partoffset;
			unsigned long allocstart;
			unsigned long blocksize;
			struct {
				unsigned int StABN, NumABlks;
			} catalogextents[3], overflowextents[3];
		} hfs;
	} p;
	struct {
		DIRENTRY		de;
		char 			name[512];
		char			*tail;
		unsigned long	parentstart;
		unsigned int	inuse;
		unsigned long	index;
	} lastde;
} LOGICAL_DEV;


/**** Cache control ****/

#define DEFAULTCACHESIZE	8

/* clear all cache entries for the logical device */
void DCClear (LOGICAL_DEV *ldp);

/* read from a logical device */
long DCRead (LOGICAL_DEV *ldp, unsigned long adr, unsigned long cnt,
	void *buffer);

/* size of cache in blocks */
extern int DCSize;

/* pointer to cache entries */
extern CACHEENTRY *DCCache;


/**** CD lib kernel ****/

/* initialize the device */
int DKInitVolume (LOGICAL_DEV *ldp);

/* convert DIRENTRY structure to XATTR structure */
void DKDirentry2Xattr (LOGICAL_DEV *ldp, DIRENTRY *de, int drive,
	XATTR *xap);

/* convert filename to 8+3 format */
void DKTosify (char *dst, const char *src);

/* flip filesystem type preference */
void DKFlipPreferred (LOGICAL_DEV *ldp);

/* set to # of open files supported by the kernel if not unlimited */
extern long DKMaxOpenFiles;

/**** to be supplied by FS specific part ****/

/* convert Unix time to DOS time */
unsigned long DMDosTime (unsigned long t);

/**** internal stuff ****/

#define MEDIADELAY	400

