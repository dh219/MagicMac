/*
 * macxfs.h
 */

#define ELINK -300

#include <aliases.h>
#include "GlobalTypes.h"

typedef struct {
/*
     long xfs_sync_entry;
     long xfs_pterm_entry;
     long xfs_drv_open_entry;
     long xfs_drv_close_entry;
     long xfs_path2DD_entry;
     long xfs_sfirst_entry;
     long xfs_snext_entry;
     long xfs_fopen_entry;
     long xfs_fdelete_entry;
     long xfs_link_entry;
     long xfs_xattr_entry;
     long xfs_attrib_entry;
     long xfs_fchown_entry;
     long xfs_fchmod_entry;
     long xfs_dcreate_entry;
     long xfs_ddelete_entry;
     long xfs_DD2name_entry;
     long xfs_dopendir_entry;
     long xfs_dreaddir_entry;
     long xfs_drewinddir_entry;
     long xfs_dclosedir_entry;
     long xfs_dpathconf_entry;
     long xfs_dfree_entry;
     long xfs_wlabel_entry;
     long xfs_rlabel_entry;
     long xfs_symlink_entry;
     long xfs_readlink_entry;
     long xfs_dcntl_entry;
     
     short xfs_disp[6];
*/
     void *xfs_sync;
     void *xfs_pterm;
     void *xfs_drv_open;
     void *xfs_drv_close;
     void *xfs_path2DD;
     void *xfs_sfirst;
     void *xfs_snext;
     void *xfs_fopen;
     void *xfs_fdelete;
     void *xfs_link;
     void *xfs_xattr;
     void *xfs_attrib;
     void *xfs_fchown;
     void *xfs_fchmod;
     void *xfs_dcreate;
     void *xfs_ddelete;
     void *xfs_DD2name;
     void *xfs_dopendir;
     void *xfs_dreaddir;
     void *xfs_drewinddir;
     void *xfs_dclosedir;
     void *xfs_dpathconf;
     void *xfs_dfree;
     void *xfs_wlabel;
     void *xfs_rlabel;
     void *xfs_symlink;
     void *xfs_readlink;
     void *xfs_dcntl;
} _ataridos;


typedef struct {
 /*
     long dev_close_entry;
     long dev_read_entry;
     long dev_write_entry;
     long dev_stat_entry;
     long dev_seek_entry;
     long dev_datime_entry;
     long dev_ioctl_entry;
     long dev_getc_entry;
     long dev_getline_entry;
     long dev_putc_entry;
     
     short dev_disp[6];
*/
     void *dev_close;
     void *dev_read;
     void *dev_write;
     void *dev_stat;
     void *dev_seek;
     void *dev_datime;
     void *dev_ioctl;
     void *dev_getc;
     void *dev_getline;
     void *dev_putc;
     void *dev_pread;		// parallel lesen
     void *dev_pwrite;		// parallel schreiben
} _macdev;

#define NDRVS  32

extern  Boolean drv_changed[NDRVS];
extern  Boolean drv_must_eject[NDRVS];
extern	_ataridos ataridos;
extern	_macdev macdev;
extern	long xfs_drvbits;


OSErr xfs_init (void);
long cnverr (OSErr err);

typedef enum {
	NoMacXFS,
	MacDir,
	MacDrive
} MacXFSDrvType;

typedef union {
	long		dummy;		// NoMacXFS
	AliasHandle	dirAlias;	// MacDir
	MacDrvRef	drvRef;		// MacDrive
} MacXFSDrvDesc;

OSErr VolumeToDrvRef (FSSpec *spec, MacDrvRef *drvRef);
void SetXFSDrive (short drv, MacXFSDrvType drvType, AliasHandle alias, MacDrvRef *drvrRef, Boolean longnames, Boolean reverseDirOrder);
Boolean GetXFSRootDir (short drv, short *vRefNum, long *dirID);
ulong DriveToDeviceCode (short drv);
long EjectDevice (short opcode, long device);
Boolean	GetPathFromFSSpec (FSSpec *spec, char* path, short pathSize);	// !TT 28.10.95
void XFSCheckForNewDrives (void);
void XFSVolUnmounted (ParmBlkPtr pb0);

// EOF
