/*
** (TAB-Setting: 5)
** (Font = Chicago 12)
**
**
** Dies ist der MAC-Teil des MAC-XFS fuer MagiX
** Entwickelt mit MPW.
**
** (C) Andreas Kromke 1994-95
**
**
** Uebergabestrukturen:
**   ataridos       enthaelt die MAC-Seite des Dateisystems (XFS)
**   macdev         enthaelt die MAC-Seite des Dateitreibers (MX_FD)
**
*/

/*
Aenderungen von !TT:
- 30.5.95: Wenn Fdatime zum Setzen des Dateidatum aufgerufen wurde, wird beim Close
  neben dem Modification-Date auch das Creation-Date auf den selben Wert gesetzt,
  weil es sonst dazu kommen kann, dass Modif.-Date>Creation-Date ist, was nicht
  erlaubt ist (z.B. meckert Norton Disk Doctor dann dauernd).
- 13.6.95: Problem mit dem lesenden Oeffnen von schreibgeschuetzten Dateien geloest.
- 14.6.95: Eject-Funktionen eingebaut.
- 26.7.95: Damit Read-Only-Oeffnen von geschuetzten Dateien auf Servern sowie von CD-ROM
  klappt, Fehlerabfragecodes bei cnverr() erweitert und entspr. Aenderung bei xfs_open()
  vorgenommen.
- 27.7.95: Da Julian heute bei der v1.2.2b11 feststellte, dass Gemini bei Directory-
  Listings schon wieder wilde Laengen bei Ordnern anzeigte, ist eine FA_SUBDIR-Abfrage
  in cinfo_to_xattr impl. worden.
- 31.7.95: Verify-Codes in cnverr() hinzugefuegt.
*/
/*
13.9.95:
-	Dpathconf liefert jetzt korrekterweise 31 statt 32 fuer max.
	Dateinamenlaenge
-	Mac-Fehler "ungueltiger Name in Dateisystem" wird mit ERANGE statt
	EINTRN uebersetzt (fuer "Name zu lang").
-	Pufferlaengenabfrage bei readlabel korrigiert.
3.10.95:
-	Dpathconf unterstuetzt DP_MODEATTR und DP_XATTRBITS
-	Fopen/Fcreate kuerzt Dateinamen auf 8+3 und Gross-Schrift, wenn
	das Laufwerk keine langen Namen zulaesst.
-	Frename kuerzt Dateinamen auf 8+3 und Gross-Schrift, wenn
	das Laufwerk keine langen Namen zulaesst.
18.10.95
-	Dpathconf() korrigiert.
19.11.95
-	xfs_symlink implementiert
-	xfs_readlink implementiert
-	xfs_xattr dereferenziert Symlinks. Klappt bisher nur fuer
	solche, die auf ein Mac-Volume zeigen.
-	xfs_attrib dereferenziert Symlinks
-	xfs_fopen dereferenziert Symlinks
-	path2DD kann bisher _KEINE_ Symlinks beruecksichtigen.
	Daher Symlinks nur auf Dateien, nicht auf Pfade moeglich.
-	Bedingte Compilierung fuer alte Verzeichnissuche (ALT_SFIRST)
	entfernt.
28.10.95 (TT)
-	GetPathFromFSSpec() hinzugefuegt
07.04.96 (TT)
-	Wiederherstellung der ausgelieferten v.1.2.7 (siehe //	TT v1.2.7)
-	Dateiaenderungsdatum sollte nun beim dev_close() richtig uebernommen werden.
-	Vorschlag zur Verbesserung von Fsnext: bei ReadOnly-LWs das alte, schnellere Verfahren benutzen!
2.5.96 (TT)
-	3 Neue Fcntl-Funktionen (Open Resource Fork, Get & Set FInfo), uebernommen aus MacMiNT-Source,
	geliefert von Julian Reschke.
3.5.96 (TT)
-	drv_rvsDirOrder[] eingefuehrt - Verzeichnisse koennen nun auch wieder vorwaerts
	durchsucht werden.
-	NDRVS von 26 auf 32 erhoeht
-	In SetXFSDirByAlias wird drv_changed auf true gesetzt, weil sonst Aenderungen an den
	Mac-Verzeichnissen nicht von MagiC registriert wuerden.
-	drv_drvrRef und XFSCheckForNewDrives neu. Damit koennen Volumes als Laufwerke
	behandelt werden: Wenn in dem Laufwerk ein anderes Volume erscheint, wird dies
	anstatt des alten Vols benutzt.
-	In xfs_path2DD() die changed-Abfrage vor die vRefNum-Abfrage gesetzt, weil sie hoehere
	Prio haben sollte.
-	SetXFSDirByAlias in SetXFSDrive umbenannt
20.5.96 (TT)
-	Archiv-Bit wird behandelt
22.5.96 (TT)
-	Dcntls implementiert (mit Alias-Aufloesung)
-	alle fname[128] in fname[64] geaendert
-	Bei einigen PBGetCatInfo-Aufrufen wurde der err-Code danach nicht abgefragt.
2.6.96 (TT)
-	Type&Creator werden nun auch beim Ersetzen schon bestehender Dateien korrekt gesetzt.
3.6.96 (TT)
-	xfs_drv_close korrigiert, damit Eject klappt.
9.6.96
-	Umlautkonvertierung
15.6.96 (TT)
-	Korrig. Umlautkonv. v .Andreas uebernommen
2.7.96 (TT)
-	FRename und FSFirst kommen nun auch mit Umlauten in Suchnamen zurecht
16.9.96 (TT)
-	Aenderungen von Kromke uebernommen:
	1. Erzeugen eines Symlinks wird unterbunden, wenn bereits eine Datei
	   mit dem selben Namen existiert.
	2. Funktion & Aufrufe zu "fname_is_invalid" neu
2.10.96 (TT)
-	getArchiveMask(): erkennt auch dann die Datei als archiviert, wenn das
	Backup-Datum _nach_ dem modifik.-Datum liegt (bisher nur dann, wenn
	beide gleich waren).
23.1.97
-	xfs_link() reagiert korrekt mit ENSAME, wenn die Dateien auf
	unterschiedlichen Mac-Volumes liegen.
31.1.97
-	xfs_path2DD() gibt als zusaetzlichen Parameter das Laufwerk eines Alias zurueck.
	(Atari-Laufwerknummer 0..NDRVS-1).
	Bisher ging das Aufloesen des Alias nur auf demselben Mac-Volume.
	Aliase, die auf Atari-Laufwerke zeigen, sind leider immer noch nicht moeglich.
	Achtung: Es ist ein neuer MagiC-Kernel notwendig.
31.3.97 (TT)
- 	Nach Oeffnen/Schliessen von Rsrc-Files (OpenResFile) wird wieder das vorher
	aktive Rsrc-File aktiviert (per UseResFile).
13.7.97 (TT)
- 	Anpassung an neue Funktionsnamen d. MacOS-Header (CW Pro 1)
3.11.97 (AK)
-	xfs_link korrigiert: Das Verschieben und gleichzeitige
	Umbenennen ging schief, wenn der Name der
	Quelldatei im Zielverzeichnis existierte.
15.2.98 (AK)
-	dev_pread() und dev_pwrite() als asynchrone Variante von
	dev_read() bzw. dev_write() ergaenzt ("Hintergrund-I/O").
20.6.98 (AK)
-	xfs_pathconf() korrigiert: Setzt DP_FT_LNK in Modus 7
6.2.99 (AK)
-	xfs_symlink() beruecksichtigt den Fall, dass das Ziel ein Pfad ist, und
	setzt dann einen anderen type/creator, damit der Finder ein Ordnersymbol
	statt eines Dateisymbols anzeigt.
-	xfs_attrib() erlaubt das Verstecken von Ordnern.
19.2.99 (AK)
-	filename_match() fuer Fsfirst/-next(): Falsche Behandlung von FA_ARCHIVE
	entfernt. Das Flag wird jetzt (wie FA_RDONLY) nicht mehr bei den Abfragen
	beruecksichtigt.
*/


/*
	Hinweise:
	
	Da jederzeit das Root-Dir eines XFS-LWs durch den User veraendert (auch
	deaktiviert) werden kann, sollten alle XFS-Funktionen jedesmal
	"drv_fsspec[i].vRefNum" pruefen.
*/

//#include <stdio.h>
#include <stdlib.h>
#include <files.h>
#include <OSUtils.h>
#include <String.h>
#include <Strings.h>
#include <Memory.h>
#include <Errors.h>
#include <aliases.h>
#include <Finder.h>		/* Fuer die Finder-Flags */
#include <Gestalt.h>		/* Fuer MacOS-Version */

#include "MoreFilesExtras.h"
#include "PascalLib.h"
#include "MacEvents.h"
#include "Extensions.h"
#include "Intr.h"
#include "Config.h"
#include "mydefs.h"
#include "ATARI.h"
#include "mgx_xfs.h"
#include "macxfs.h"
#include "MHDI.h"
#include "TextConv.h"		// 9.6.96
#include "mac_xfs.h"		// TT: Mac-XFS-Erweiterungen

#ifndef ELINK
#define ELINK -300
#endif

/*
* NDRVS Laufwerke werden vom XFS verwaltet
* Fuer jedes Laufwerk gibt es einen FSSpec, der
* das MAC-Verzeichnis repraesentiert, das fuer
* "x:\" steht.
*/

// globale Variablen:
//Boolean		drv_must_eject[NDRVS];
Boolean		drv_changed[NDRVS];
_ataridos		ataridos;
_macdev		macdev;
long			xfs_drvbits = 0;	// wird in "cpath2DirID" und in "MacEvents.GetAvailableDrives" gesetzt.
FSSpec		drv_fsspec[NDRVS];	// => macSys, damit MagiC die volume-ID
							// ermitteln kann AK 21.3.98


// lokale Variablen:
// -----------------
static Boolean	has_2TBVols;		// unser OS hat PBXGetVolInfo
static	AliasHandle	xfs_alias[NDRVS];		// nur auswerten, wenn drv_valid = true
static	Boolean	drv_valid[NDRVS];			// zeigt an, ob alias gueltig ist.
static	CInfoPBRec	drv_pbrec[NDRVS];
static	long		drv_dirID[NDRVS];
static	Boolean	drv_longnames[NDRVS];			// initialisiert auf 0en
static	Boolean	drv_rvsDirOrder[NDRVS];
static	Boolean	drv_readOnly[NDRVS];
static	MacDrvRef	drv_drvrRef[NDRVS];
static	MacXFSDrvType	drv_type[NDRVS];

// Fuer jedes benutzte Mac-Volume genau ein ParamBlockRec,
// damit wir xfs_sync() pro Volume statt pro Atari-LW machen koennen:
// AK 29.3.98 die Struktur wird nicht mehr gebraucht
// static	ParamBlockRec drv_pbrec_volumes[NDRVS];	// AK 19.2.98

// prototypes
static void checkForNewDrive (short drv);

// Prototypen fuer Forward-Deklaration. AK: 25.10.96
static long xfs_attrib(WORD drv, LONG dirID, char *name, WORD rwflag, WORD attr);

/*
*
* Dies ist die Uebergabestruktur zwischen
* dem Atari- Teil des XFS und dem MAC-Teil.
* Der MAC- Teil bekommt seine Parameter
* "sauber" ueber den Stack, waehrend der Atari-Teil
* ueber Register mit dem MagiX-Kernel kommuniziert.
*
*/

typedef struct {
     char      sname[11];		/* Suchname */
     char      sattr;			/* Suchattribut */
     LONG      dirID;			/* Verzeichnis */
     LONG      index;			/* Verzeichnis (int) */
} _MAC_DTA;

typedef struct {
     MX_FD	fd;			/* allgemeiner Teil */
     WORD	refnum;		/* MAC-Teil: Handle */
     WORD	mod_time_dirty;	/* MAC-Teil: Fdatime war aufgerufen */
     WORD	mod_time[2];	/* MAC-Teil: Zeit fuer Fdatime (DOS-Codes) */
} MAC_FD;

typedef struct {
     MX_DHD	dhd;			/* allgemeiner Teil */
     LONG	dirID;			/* Verzeichniskennung */
     WORD	index;		/* Position des Lesezeigers */
     WORD	tosflag;		/* TOS-Modus, d.h. 8+3 und ohne Inode */
} MAC_DIRHANDLE;

typedef union {
     MX_DTA    mxdta;
     _MAC_DTA  macdta;
} MAC_DTA;

typedef struct {
  WORD	len;			/* Symlink-Laenge inklusive EOS, gerade */
  char		data[256];
} MX_SYMLINK;


/* Zur Rueckgabe an den MagiC-Kernel: */

static MX_SYMLINK mx_symlink;

/*****************************************************************
*
*  Wandelt Klein- in Grosschrift um
*
******************************************************************/

static char toupper( char c )
{
	static char lowers[] = {0x84,0x94,0x81,0x87,0x82,0x86,0x91,0xb4,0x85,0xc0,0xa4,0xb0,0xb3,0xb1,0};
	static char uppers[] = {0x8e,0x99,0x9a,0x80,0x90,0x8f,0x92,0xb5,0xb6,0xc1,0xa5,0xb7,0xb2,0xb8,0};
	char *found;

	if	(c >= 'a' && c <= 'z')
		return(c & 0x5f);
	if	((unsigned char)c >= 128 &&((found = strchr(lowers, c)) != NULL))
		return(uppers[found-lowers]);
	return(c);
}


/*****************************************************************
*
*  konvertiert Atari-Dateiname in Mac-Dateinamen und "vice versa"
*
******************************************************************/

static void AtariFnameToMacFname( unsigned char *src, unsigned char *dst)
{
	while	(*src)
		*dst++ = ConvToMacFilename[*src++];
	*dst = EOS;
}
static void MacFnameToAtariFname( unsigned char *src, unsigned char *dst)
{
	while	(*src)
		*dst++ = ConvToATARIFilename[*src++];
	*dst = EOS;
}


/*****************************************************************
*
*  konvertiert MAC-Datumsangaben in DOS- Angaben
*
******************************************************************/

static void date_mac2dos( unsigned long macdate, UWORD *time, UWORD *date)
{
	DateTimeRec dt;

	SecondsToDate(macdate, &dt);
	if	(time)
		*time = (dt.second >> 1) + (dt.minute << 5) + (dt.hour << 11);
	if	(date)
		*date = (dt.day)         + (dt.month  << 5) + ((dt.year - 1980) << 9);
}

/*****************************************************************
*
*  konvertiert DOS-Datumsangaben in Mac-Angaben
*
******************************************************************/

static void date_dos2mac( UWORD time, UWORD date, unsigned long *macdate)
{
	DateTimeRec dt;
	dt.second =  (time & 0x1f) << 1;
	dt.minute =  (time >> 5 ) & 0x3f;
	dt.hour   =  (time >> 11) & 0x1f;		// !TT korrigiert 26.3.95
	dt.day    =   date        & 0x1f;
	dt.month  =  (date >> 5 ) & 0x0f;
	dt.year   = ((date >> 9 ) & 0x7f) + 1980;
	DateToSeconds(&dt, macdate);
}

/*****************************************************************
*
*  Testet, ob ein Dateiname gueltig ist. Verboten sind Dateinamen, die
*  nur aus '.'-en bestehen.
*
******************************************************************/

static int fname_is_invalid( char *name)
{
	while((*name) == '.')		// fuehrende Punkte weglassen
		name++;
	return(!(*name));			// Name besteht nur aus Punkten
}


/*****************************************************************
*
*  konvertiert MAC-Fehlercodes in MagiC- Fehlercodes
*
******************************************************************/

LONG cnverr (OSErr err)
{
     switch(err)
          {
          case noErr:         return(E_OK);       /* 0      no error  */
          case nsvErr:        return(EDRIVE);     /* -35    no such volume */
          case fnfErr:        return(EFILNF);     /* -43    file not found */
          case dirNFErr:      return(EPTHNF);     // -120   directory not found
          case ioErr:         return(EREADF);     /* -36    IO Error */
          case gfpErr:                            /* -52    get file pos error */
          case rfNumErr:                          /* -51    Refnum error */
          case paramErr:                          /* -50    error in user parameter list */
          case fnOpnErr:      return(EINTRN);     /* -38    file not open */
          case bdNamErr:                          /* -37    bad name in file system (>31 Zeichen)*/
          case posErr:                            /* -40    pos before start of file */
          case eofErr:        return(ERANGE);     /* -39    end of file */
          case mFulErr:       return(ENSMEM);     /* -41    memory full */
          case tmfoErr:       return(ENHNDL);     /* -42    too many open files */
          case wPrErr:        return(EWRPRO);     /* -44    disk is write protected */
          case notAFileErr:                       /* -1302  is directory, no file! */
          case wrPermErr:                         /* -61    write permission error */

// !TT 26.7.95 neu:
          case afpAccessDenied:                   // -5000  AFP access denied
          case afpDenyConflict:                   // -5006  AFP
          case afpVolLocked:                      // -5031  AFP

          case permErr:                           /* -54    permission error */
          case opWrErr:                           /* -49    file already open with write permission */
          case dupFNErr:                          /* -48    duplicate filename */
          case fBsyErr:                           /* -47    file is busy */
          case vLckdErr:                          /* -46    volume is locked */
          case fLckdErr:      return(EACCDN);     /* -45    file is locked */
          case volOffLinErr:  return(EDRVNR);     /* -53    volume off line (ejected) */
          case badMovErr:     return ENSAME;      // -122   not same volumes or folder move from/to file

// !TT 31.7.95 neu:
          case dataVerErr:                        // read verify error
          case verErr:        return EBADSF;      // track format verify error
          }
     return(ERROR);
}


/*****************************************************************
*
*  vergleicht zwei Dateinamen im internen Format (11 Zeichen)
*  auf Uebereinstimmung (ohne Unterscheidung gr/kl)
*  Rueckgabe :	1      Namen gleich
*			0      Namen unterschiedlich
*
******************************************************************/

static int namecmp(char *s1, char *s2)
{
	register int i;
	register char c1,c2;

	for  (i = 10; i >= 0; i--)
		{
		c1 = toupper(*s1++);
		c2 = toupper(*s2++);
		if   (c1 != c2)
			return(FALSE);
		}
	return(TRUE);
}


/*********************************************************************
*
* Vergleicht ein 12- stelliges Dateimuster mit einem Dateinamen.
* Die Stelle 11 ist das Datei- Attribut(-muster).
* Rueckgabe : 1 = MATCH, sonst 0
*
* Regeln zum Vergleich der Attribute:
*    1) ReadOnly und Archive werden bei dem Vergleich NIEMALS
*       beruecksichtigt.
*    2) Ist das Suchattribut 8, werden genau alle Dateien mit gesetztem
*       Volume- Bit gefunden (auch versteckte usw.).
*    3) Ist das Suchattribut nicht 8, werden normale Dateien IMMER
*       gefunden.
*    4) Ist das Suchattribut nicht 8, werden Ordner nur bei gesetztem
*       Bit 4 gefunden.
*    5) Ist das Suchattribut nicht 8, werden Volumes nur bei gesetztem
*       Bit 3 gefunden.
*    6) Ist das Suchattribut nicht 8, werden versteckte oder System-
*       dateien (auch Ordner oder Volumes) NUR gefunden, wenn das
*       entsprechende Bit im Suchattribut gesetzt ist.
*
* Beispiele (die Bits ReadOnly und Archive sind ohne Belang):
*    8    alle Dateien mit gesetztem Bit 3 (Volumes)
*    0    nur normale Dateien
*    2    normale und versteckte Dateien
*    6    normale, versteckte und System- Dateien
*  $10    normale Dateien, normale Ordner
*  $12    normale und versteckte Dateien und Ordner
*  $16    normale und versteckte und System- Dateien und -Ordner
*   $a    normale und versteckte Dateien und Volumes
*   $e    normale, versteckte und System- Dateien und -Volumes
*  $1e    alles
*
***************************************************************************/

static int filename_match(char *muster, char *fname)
{
	register int i;
	register char c1,c2;


	if	(fname[0] == '\xe5')     /* Suche nach geloeschter Datei */
		return((muster[0] == '?') || (muster[0] == fname[0]));

	/* vergleiche 11 Zeichen */

	for	(i = 10; i >= 0; i--)
		{
		c1 = *muster++;
		c2 = *fname++;
		if	(c1 != '?')
			{
			if   (toupper(c1) != toupper(c2))
			     return(FALSE);
			}
		}

	/* vergleiche Attribut */

	c1 = *muster;
	c2 = *fname;

#if 0
	if	(c1 == FA_ARCHIVE)			// !AK 19.2.99
		return(c1 & c2);
#endif
	c2 &= FA_SUBDIR + FA_SYSTEM + FA_HIDDEN + FA_VOLUME;
	if	(!c2)
		return(TRUE);
	if	((c2 & FA_SUBDIR) && !(c1 & FA_SUBDIR))
		return(FALSE);
	if	((c2 & FA_VOLUME) && !(c1 & FA_VOLUME))
		return(FALSE);
	if	(c2 & FA_HIDDEN+FA_SYSTEM)
		{
		c2 &= FA_HIDDEN+FA_SYSTEM;
		c1 &= FA_HIDDEN+FA_SYSTEM;
		}
	return(c1 & c2);
}


/*********************************************************************
*
*  Das in <pathname> stehende, erste Pfadelement (vor '\' oder EOS)
*  wird ins interne Format gewandelt und nach <name> kopiert
*
* 7.9.95:  Funktion liefert TRUE zurueck, wenn das Pfadelement gekuerzt
*  wurde.
*
**********************************************************************/

static int conv_path_elem(const char *path, char *name)
{
	register int i;
	register char c;
	int truncated = FALSE;

	/* max. 8 Zeichen fuer Dateinamen kopieren */

	for	(i = 0; (i < 8) && (*path) &&
		 (*path != '\\') && (*path != '*') && (*path != '.') && (*path != ' '); i++)
		{
		*name++ = toupper(*path++);
		}

	/* Zeichen fuer das Auffuellen ermitteln */

	if	(i == 8)
		{
		while	((*path) && (*path != ' ') && (*path != '\\') && (*path != '.'))
			{
			path++;
			truncated = TRUE;
			}
		}
	c = (*path == '*') ? '?' : ' ';
	if	(*path == '*')
		path++;
	if	(*path == '.')
		path++;

	/* Rest bis 8 Zeichen auffuellen */

	for	(;i < 8; i++)
		{
		*name++ = c;
		}

	/* max. 3 Zeichen fuer Typ kopieren */

	for	(i = 0; (i < 3) && (*path) &&
		 (*path != '\\') && (*path != '*') && (*path != '.') && (*path != ' '); i++)
		{
		*name++ = toupper(*path++);
		}

	if	((*path) && (*path != '\\') && (*path != '*'))
		truncated = TRUE;

	/* Zeichen fuer das Auffuellen ermitteln */

	c = (*path == '*') ? '?' : ' ';

	/* Rest bis 3 Zeichen auffuellen */

	for	(;i < 3; i++)
		{
		*name++ = c;
		}

	return(truncated);
}


/*************************************************************
*
* Wandelt Mac-Dateinamen nach 8.3-Namen fuer GEMDOS.
* Wenn <flg_longnames> == TRUE ist, wird nicht nach Gross-Schrift
* konvertiert, das Format ist aber in jedem Fall 8+3.
* Zeichen ' ' (Leerstelle) und '\' (Backslash) werden weggelassen.
*
* Neu (6.9.95): Rueckgabe TRUE, wenn der Dateiname gekuerzt
* werden musste. Fsfirst/next sowie D(x)readdir koennen dann
* die entsprechende Datei ignorieren.
*
*************************************************************/

static int nameto_8_3 (const unsigned char *macname,
				unsigned char *dosname,
				Boolean flg_longnames, Boolean toAtari)
{
	register short i;
	int truncated = FALSE;


 	/* max. 8 Zeichen fuer Dateinamen kopieren */
 	i = 0;
	while	((i < 8) && (*macname) && (*macname != '.'))
		{
		if	((*macname == ' ') || (*macname == '\\'))
			{
			macname++;
			continue;
			}
		if	(toAtari)
			{
			if	(flg_longnames)
				*dosname++ = ConvToATARIFilename[*macname++];
			else	*dosname++ = toupper(ConvToATARIFilename[*macname++]);
			}
		else	{
			if	(flg_longnames)
				*dosname++ = *macname++;
			else	*dosname++ = toupper(*macname++);
			}
		i++;
		}

	while((*macname) && (*macname != '.'))
		{
		macname++;		// Rest vor dem '.' ueberlesen
		truncated = TRUE;
		}
	if	(*macname == '.')
		macname++;		// '.' ueberlesen
	*dosname++ = '.';			// '.' in DOS-Dateinamen einbauen

	/* max. 3 Zeichen fuer Typ kopieren */
	i = 0;
	while	((i < 3) && (*macname) && (*macname != '.'))
		{
		if	((*macname == ' ') || (*macname == '\\'))
			{
			macname++;
			continue;
			}
		if	(toAtari)
			{
			if	(flg_longnames)
				*dosname++ = ConvToATARIFilename[*macname++];
			else	*dosname++ = toupper(ConvToATARIFilename[*macname++]);
			}
		else	{
			if	(flg_longnames)
				*dosname++ = *macname++;
			else	*dosname++ = toupper(*macname++);
			}
		i++;
		}
	if	(dosname[-1] == '.')		// trailing '.'
		dosname[-1] = EOS;		//   entfernen
	else	*dosname = EOS;

	if	(*macname)
		truncated = TRUE;

	return(truncated);
}


/*************************************************************
*
* wandelt einen Pascal-String um in eine Zeichenkette.
* Benutzt dabei eine statischen Puffer!!
*
*************************************************************/

static char *ps(char *s)
{
	static char cs[512];

	strncpy(cs, s+1, s[0]);
	cs[s[0]] = EOS;
	return(cs);
}


/*************************************************************
*
* wandelt eine Zeichenkette um in einen Pascal-String.
* D.h. initialisiert das Laengenbyte.
*
*************************************************************/

static void sp(char *s)
{
	s[0] = strlen(s+1);
}


/*************************************************************
*
* Wandelt dirID, drv und Dateinamen in einen FSSpec um.
* Wenn das Dateisystem keine langen Namen unterstuetzt, wird
* der Name gekuerzt.
* Wenn <fromAtari> == TRUE, wird der Dateiname, d.h. Umlaute,
* konvertiert
*
*************************************************************/

static long cfss(int drv, long dirID, unsigned char *name, FSSpec *fs,
			Boolean fromAtari)
{
	if	(!drv_fsspec[drv].vRefNum)		// Abfrage eigentlich unnoetig
		return(EDRIVE);

	fs->vRefNum = drv_fsspec[drv].vRefNum;
	fs->parID = dirID;
	if	(drv_longnames[drv])
		{
		if	(fromAtari)
			AtariFnameToMacFname( name, fs->name+1);	// nur kopieren
		else	vstrcpy((char *) fs->name+1, (char *) name);
		}
								// bzw. in 8+3 wandeln
	else	{
		nameto_8_3(name, fs->name+1, drv_longnames[drv], FALSE);
		if	(fromAtari)
			AtariFnameToMacFname( fs->name+1, fs->name+1);
		}

	sp((char*)fs->name);

	// damit es erstmal weniger Probs gibt:
/*
	UprText (((char*)fs->name+1), fs->name[0]);
*/
	return(E_OK);
}


/*************************************************************
*
* Berechnet aus einer DirID wieder einen FSSpec.
* D.h. man kann den Parent und den Namen eines
* Unterverzeichnisses bestimmen.
*
*************************************************************/

static OSErr dir2fsspec( int drv, long dirID, FSSpec *fs )
{
	OSErr err;

	if	(!drv_fsspec[drv].vRefNum)
		return(E_CHNG);
	err = FSMakeFSSpec(drv_fsspec[drv].vRefNum, dirID, NULL, fs);
	return(err);
}


/*************************************************************
*
* initialisiert die Strukturen fuer Laufwerk <n> des XFS.
* Ein kompletter Pfad wird umgewandelt in eine DirID.
* Das erste Zeichen des Pfads muss frei sein.
*
*************************************************************/

static OSErr fsspec2DirID (int drv)
{
	OSErr err;
	FSSpec *fs;
	CInfoPBPtr pb;

	fs = drv_fsspec+drv;
	pb = drv_pbrec+drv;

	pb -> hFileInfo.ioVRefNum = fs -> vRefNum;
	pb -> hFileInfo.ioNamePtr = fs -> name;
	pb -> hFileInfo.ioFDirIndex = 0;
	pb -> hFileInfo.ioDirID = fs -> parID;
	if (pb->hFileInfo.ioNamePtr[0] == 0) pb->hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
	err = PBGetCatInfoSync (pb);
	if	(err)
		return(err);
	if	(!(pb -> hFileInfo.ioFlAttrib & 0x10))
		return(-1);    /* kein SubDir */
	drv_dirID[drv] = pb -> dirInfo.ioDrDirID;
	return(0);
}


static OSErr cpath2DirID( int drv, char *cpath )
{
	OSErr err;
	FSSpec *fs;

	c2pstr(cpath);
	fs = drv_fsspec+drv;
	err = FSMakeFSSpec(0, 0L, (unsigned char*)cpath, fs);
	if	(err)
		{
		fs->vRefNum = 0;
		return(err);
		}
	return fsspec2DirID (drv);
}


/*************************************************************
*
* Loest einen MagiC-Alias auf.
* Eingabe:
*		fs		FSSpec des Alias
*		buflen	max. Laenge des Symlink inkl. EOS
*		buf		NULL:
*					Der Symlink wird dereferenziert,
*					der Ziel-FSSpec wieder nach <fs>
*					geschrieben. Ggf. wird ELINK
*					geliefert und der mx_symlink
*					initialisiert.
*				Puffer fuer Symlink: (fuer Freadlink)
*					Der Symlink wird gelesen, wenn
*					er vom Finder erstellt war, wird
*					EACCDN geliefert.
*
* Rueckgabe:
*		fs		ggf. FSSpec der Datei
*		retcode	E_OK:	fs ist gueltig
*				ELINK: xfs_symlink ist gueltig
*				EACCDN: Datei ist kein Alias oder ein
*					(ungueltiger) Finder-Alias.
*
* Zurueckgegeben wird ein MagiC-Fehlercode
*
*************************************************************/

static LONG resolve_symlink( FSSpec *fs, WORD buflen, char *buf )
{
	short refnum;
	Handle myhandle;
	AliasHandle myalias;
	Boolean wasChanged;
	char *s;
	WORD len;
	OSErr err;
	LONG doserr;

	short saveRefNum = CurResFile ();	// TT 31.3.97 neu

	refnum = FSpOpenResFile(fs, fsRdPerm);
	if	(refnum == -1)
		return(EACCDN);

	/* Die Ressource #0 des Typs 'alis' holen	*/
	/* -------------------------------------	*/
	
	myhandle = Get1Resource('alis', 0);
	if	(myhandle)
		{
		myalias = (AliasHandle) myhandle;

		if	(!buf)
			{
			/* Der Mac soll den Alias dereferenzieren	*/
			/* ------------------------------------	*/
			err = ResolveAlias (NULL, myalias, fs, &wasChanged);
			doserr = cnverr(err);
			}
		else	doserr = EFILNF;

		if	(doserr)
			{
			/* Der Mac kann den Alias nicht dereferenzieren,	*/
			/* Wir holen deshalb den DOS-Pfad und geben ihn an	*/
			/* den MagiC-Kernel zurueck.					*/
			/* ------------------------------------------------	*/
			if	((*myalias)->userType == 'MgMc')
				{
				s = *myhandle + (*myalias)->aliasSize;
				len = strlen(s) +1;
				if	(!buf)
					{
					if	(len & 1)
						len++;
					buflen = 256;
					mx_symlink.len = len;
					buf = mx_symlink.data;
				/*	doserr = ELINK;	*/
					doserr = EFILNF;	// !AK: 2.11.96
					}
				else	doserr = E_OK;

				if	(len <= buflen)
					{
					vstrcpy(buf, s);
					}
				else	doserr = ERANGE;
				}
			else	doserr = EACCDN;
			}
		}
	else	doserr = EACCDN;		/* keine 'alis'-Ressource */

	CloseResFile(refnum);
	UseResFile (saveRefNum);	// TT 31.3.97 neu
	return(doserr);
}


/*************************************************************
*
* Laufwerk synchronisieren
*
* Der Aufrufer traegt in den ParamBlockRec bereits den Eintrag
* ioCompletion ein.
* Der Aufrufer stellt bereits sicher, dass die Routine nur einmal
* pro Mac-Volume aufgerufen wird.
*
* Rueckgabe:		0	OK
*			<0	Fehler
*			>0	in Arbeit.
* AK 25.3.98
*
*************************************************************/

static LONG xfs_sync(WORD drv, ParamBlockRec *pb)
{
	OSErr err;

	if	(!(pb->ioParam.ioRefNum = drv_fsspec[drv].vRefNum))
		return(EDRIVE);

	pb->ioParam.ioNamePtr = NULL;		// !!!
	if (UseAsynchronousDiskIO) {
		err = PBFlushVolAsync (pb);
	} else {
		err = PBFlushVolSync (pb);
	}
	return(cnverr(err));
}


/*************************************************************
*
* Ein Prozess ist terminiert.
*
*************************************************************/

static void xfs_pterm (PD *pd)
{
}


/*************************************************************
* xfs_drv_open
* ============
*
* "Oeffnet" ein Laufwerk.
* D.h. sieht nach, ob es als MAC-Pfad existiert. Wenn ja,
* wird ein Deskriptor geliefert (d.h. die DirID der "root").
*
* Fuer Calamus: Fuer M: wird immer 0 geliefert.
*
*************************************************************/

static AliasHandle gAlias;
static Boolean gOnlyMountedVols;
static FSSpec *gSpec;
static OSErr gErr;

static OSErr getInfo (CInfoPBPtr pb, FSSpec *fs)
{
	pb->hFileInfo.ioVRefNum = fs->vRefNum;
	pb->hFileInfo.ioNamePtr = fs->name;
	pb->hFileInfo.ioFDirIndex = 0;
	pb->hFileInfo.ioDirID = fs->parID;
	if (pb->hFileInfo.ioNamePtr[0] == 0) pb->hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
	return PBGetCatInfoSync (pb);
}

static void resAlias ()
{
	Boolean b;
	CInfoPBRec pb;
	short saveRefNum, fRefNum;
	AliasHandle alias = gAlias;
	do {
		// Schleife: Falls gewaehltes File wieder ein Alias ist, das auch aufloesen
		if (gOnlyMountedVols) {
			short matches = 1;
			long mode = kARMSearch | kARMSearchRelFirst | kARMMultVols | kARMNoUI;
		 	gErr = MatchAlias (&ThisPath, mode, alias, &matches, gSpec, &b, nil, nil);
		} else {
			gErr = ResolveAlias (&ThisPath, alias, gSpec, &b);
		}
		if (alias != gAlias) DisposeHandle ((Handle)alias);
		if (gErr || getInfo (&pb, gSpec) || (pb.hFileInfo.ioFlAttrib&16) || !(pb.hFileInfo.ioFlFndrInfo.fdFlags&0x8000)) {
			break;
		}
		saveRefNum = CurResFile ();
		fRefNum = FSpOpenResFile (gSpec, fsRdPerm);
		if (fRefNum == -1) { gErr = dirNFErr; break; }
		UseResFile (fRefNum);
		alias = (AliasHandle)GetResource ('alis', 0);
		DetachResource ((Handle)alias);
		CloseResFile (fRefNum);
		UseResFile (saveRefNum);
	} while (alias);
}

static LONG drv_open (WORD drv, Boolean onlyMountedVols, Boolean fromXFS)
{
	HVolumeParam pbh;

	checkForNewDrive (drv);

#ifdef CALAMUS
	if	(drv == 'M'-'A')
		return(E_OK);
#endif

	if	(!drv_valid[drv] || !xfs_alias[drv])
		return(EDRIVE);

	gAlias = xfs_alias[drv];
	gSpec = &drv_fsspec[drv];
	gOnlyMountedVols = onlyMountedVols;
	if (fromXFS) {
		ToUser ();		// switch Stack-Ptr & enter User Mode
		resAlias ();
		ToSuper ();		// restore Stack-Ptr, back to supervisor mode.
	} else {
		resAlias ();
	}
	if	(gErr)
		return(EDRVNR);

	fsspec2DirID (drv);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	// Ermitteln, ob Volume "locked" ist.
	pbh.ioVolIndex = 0;
	pbh.ioNamePtr = nil;
	pbh.ioVRefNum = drv_fsspec[drv].vRefNum;
	pbh.ioVAtrb = 0;
	PBHGetVInfoSync ((HParmBlkPtr)&pbh);
	drv_readOnly[drv] = (pbh.ioVAtrb & 0x8080) != 0;

	return E_OK;
}

static LONG xfs_drv_open (WORD drv, LONG *dir, LONG flg_ask_diskchange)
{
	static void *oldsp;
	LONG	err;

	if	(flg_ask_diskchange)		// Diskchange- Status ermitteln
		{
		if	(drv_changed[drv])
			return(E_CHNG);
		else	return(E_OK);
		}

	drv_changed[drv] = FALSE;		// Diskchange reset

	err = drv_open (drv, false, true);
	if	(err)
		return err;

	*dir = drv_dirID[drv];

	return(E_OK);
}


/*************************************************************
*
* Rechnet eine Volume-Nummer in ein Atari-Laufwerk um.
* Rueckgabe EDRIVE, wenn nicht gefunden
*
*************************************************************/

static LONG vRefNum2drv(short vRefNum, WORD *drv)	// !AK: 31.1.97
{
	register int i;

	for	(i = 0; i < NDRVS; i++)
		if	(drv_fsspec[i].vRefNum == vRefNum)
			{
			*drv = i;
			return(E_OK);
			}
	return(EDRIVE);
}


/*************************************************************
*
* "Schliesst" ein Laufwerk.
* mode =	0: Laufwerk schliessen oder EACCDN liefern
*		1: Laufwerk schliessen, immer E_OK liefern.
*
*************************************************************/

static LONG xfs_drv_close(WORD drv, WORD mode)
{
#ifdef CALAMUS
	if	(drv == 'M'-'A')
		return((mode) ? E_OK : EACCDN);
#endif
	if	(mode == 0 && drv_fsspec[drv].vRefNum == 0)    /* ungueltig */
		return(EDRIVE);

	if	(mode == 0 && drv_fsspec[drv].vRefNum == -1)
		{
		// Mac-Boot-Volume darf nicht ungemountet werden.
		return(EACCDN);
		}
	else
		{
		if (drv_type[drv] == MacDrive) drv_valid[drv] = false;	// macht Alias ungueltig
		drv_fsspec[drv].vRefNum = 0;
		return(E_OK);
		}
}


/*************************************************************
*
* Berechnet manuell einen FSSpec Schritt fuer Schritt, um auch
* Aliase aufloesen zu koennen.
* Der Pfad ist immer relativ und beginnt mit einem ':', sowohl
* das Laengenbyte ist eingetragen als auch der Pfad
* nullterminiert.
* Bei einem Befehl "chdir mist\schrott" wird der Mac-Pfad
* "mist:schrott" uebergeben. Wenn nun "schrott" ein Alias
* ist, wird der Alias von "schrott" zurueckgegeben.
*
*************************************************************/

static LONG MakeFSSpecManually( short vRefNum, long reldir,
					char *macpath,
					FSSpec *fs)
{
	Str63 dirname;
	char *s,*t;		// Laufzeiger
	int len;
	OSErr err;
	LONG doserr;
	CInfoPBRec pb;


	s = macpath+2;	// Laengenbyte und ':' ueberlesen
	while((t = strchr(s, ':')) != NULL)
		{
		len = t - s;
		vmemcpy(dirname+1, s, len);		// ein Pfadelement
		dirname[0] = len;
		s = t+1;

		/* Eine Verzeichnisebene durchsuchen */
		/* ---------------------------------- */

		err = FSMakeFSSpec(vRefNum, reldir, dirname, fs);
		if	(err)
			return(cnverr(err));		// darf eigentlich nicht passieren
		pb.hFileInfo.ioVRefNum = fs->vRefNum;
		pb.hFileInfo.ioNamePtr = fs->name;
		pb.hFileInfo.ioFDirIndex = 0;
		pb.hFileInfo.ioDirID = fs->parID;
		if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
		err = PBGetCatInfoSync (&pb);
		if	(err)
			return(cnverr(err));			// nix gefunden

		/* ggf. Alias aufloesen */
		/* ------------------- */

		if	(pb.hFileInfo.ioFlFndrInfo.fdFlags & kIsAlias)
			{
			doserr = resolve_symlink( fs, 0, NULL );
	
			if	(!doserr)		/* Der Mac hat dereferenziert! */
				{
				pb.hFileInfo.ioVRefNum = fs->vRefNum;
				pb.hFileInfo.ioNamePtr = fs->name;
				pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
				pb.hFileInfo.ioDirID = fs->parID;
				if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
				err = PBGetCatInfoSync (&pb);
				if	(err)
					return(cnverr(err));			// nix gefunden
				}
			else	return(doserr);		/* Fehler */
			}
		reldir = pb.hFileInfo.ioDirID;
		vRefNum = fs->vRefNum;
		}

	len = strlen(s);				// Restpfad
	vmemcpy(dirname+1, s, len);
	dirname[0] = len;
	err = FSMakeFSSpec(vRefNum, reldir, dirname, fs);
	return (cnverr(err));
}


/*************************************************************
*
* Rechnet einen Atari-Pfad um in einen MAC-Verzeichnis-Deskriptor.
* Das Laufwerk ist bereits vom MagiX-Kernel bearbeitet worden,
* d.h. der Pfad ist z.B.
*
*    "subdir1\magx_acc.zip".
*
* Die Datei liegt tatsaechlich in
*    "AWS 95:magix:MAGIX_A:subdir1:magx_acc.zip"
*
* Dabei ist
*    "AWS 95:magix:MAGIX_A"
* Das MAC-Aequivalent zu "A:\"
*
* <reldir> ist bereits die DirID des MAC-Verzeichnisses.
* mode	= 0: <name> ist Datei
*		= 1: <name> ist selbst Verzeichnis
*
*    Ausgabeparameter:
*
*     1. Fall: Es ist ein Fehler aufgetreten
*
*         Gib den Fehlercode als Funktionswert zurueck
*
*     2. Fall: Ein Verzeichnis (DirID) konnte ermittelt werden
*
*         Gib die DirID als Funktionswert zurueck.
*
*         Gib in <restpfad> den Zeiger auf den restlichen Pfad ohne
*            beginnenden '\' bzw. '/'
*
*     3. Fall: Das XFS ist bei der Pfadauswertung auf einen symbolischen
*             Link gestossen
*
*         Gib als Funktionswert den internen Mag!X- Fehlercode ELINK
*
*         Gib in <restpfad> den Zeiger auf den restlichen Pfad ohne
*            beginnenden '\' bzw. '/'
*
*         Gib in <symlink_dir> dir DirID des Pfades, in dem der symbolische
*                 Link liegt.
*
*         Gib in <symlink> den Zeiger auf den Link selbst. Ein Link beginnt
*                 mit einem Wort (16 Bit) fuer die Laenge des Pfads,
*                 gefolgt vom Pfad selbst.
*
*                 Achtung: Die Laenge muss INKLUSIVE abschliessendes
*                                Nullbyte und ausserdem gerade sein. Der Link
*                                muss auf einer geraden Speicheradresse
*                                liegen.
*
*                 Der Puffer fuer den Link kann statisch oder auch
*                 fluechtig sein, da der Kernel die Daten sofort
*                 umkopiert, ohne dass zwischendurch ein Kontextwechsel
*                 stattfinden kann.
*
*                 Wird <symlink> == NULL uebergeben, wird dem Kernel
*                 signalisiert, dass der Parent des
*                 Wurzelverzeichnisses angewaehlt wurde. Befindet sich
*                 der Pfad etwa auf U:\A, kann der Kernel auf U:\
*                 zurueckgehen.
*
* Moeglicherweise enthaelt diese Routine einen Fehler.
* Falls der Mac negative dirIDs zulaesst, kann MagiC nicht
* zwischen Fehlern und dirIDs unterscheiden. Dann muesste
* der Aufrufmechanismus geaendert werden. Leider habe ich
* keine Hinweise in der Online-Doku gefunden.
*
*************************************************************/

static LONG xfs_path2DD(WORD mode, WORD drv, LONG reldir, char *pathname,
                    char **restpfad, LONG *symlink_dir, char **symlink,
                    WORD *dir_drive )	// !AK: 31.1.97
{
	OSErr err;
	LONG doserr;
	FSSpec fs;
	CInfoPBRec pb;
	unsigned char macpath[256];
	register unsigned char *s,*t,*u;
	register unsigned char c;
	int get_parent;


	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)    /* ungueltig */
		return(EDRIVE);

	/* Hier schon einmal das Laufwerk setzen, das wir zurueckliefern	*/
	/* Wenn wir einen Alias verfolgen, kann sich das noch aendern	*/
	/* -------------------------------------------------------------	*/

	*dir_drive = drv;

	/* Der relative DOS-Pfad wird umgewandelt in einen relativen	*/
	/* MAC-Pfad. Eintraege "." und ".." werden beruecksichtigt.		*/
	/* ------------------------------------------------------------ */

	s = macpath+1;			// 1 Byte fuer Laenge lassen
	*s++ = ':';				// alle Pfade sind MAC-relativ
	t = (unsigned char *) pathname;
	u = s;
	while	(*pathname)
		{
		c = ConvToMacFilename[(unsigned char) (*pathname++)];	// 9.6.96
		if	(c == '\\')
			{
			if	((t[0] == '.') && ((unsigned char *) pathname == t+2))
				s -= 2;	// war Element "." => entfernen
			else
			if	((t[0] == '.') && (t[1] == '.') && ((unsigned char *) pathname == t+3))
				{		// war Element ".."
				s -= 3;	// zunaechst aus MAC-Pfad entfernen
				if	(s > macpath+2)
					{	// ich kann zurueckgehen
					s--;
					do	
						s--;
					while	(*s != ':');	// gehe zurueck
					}
				else	{	// ich kann nicht zurueckgehen
					if	(reldir == drv_dirID[drv])
						{	// bin schon root
						*restpfad = (char *) t;
						* symlink = NULL;
						return(ELINK);
						}
					err = dir2fsspec( drv, reldir, &fs );
					if	(err)
						goto was_doserr;
					reldir = fs.parID;		// parent anwaehlen
					}
				}
			t = (unsigned char *) pathname;	// letztes Element Atari
			u = s;						// letztes Element MAC ohne ':'
			*s++ = ':';
			}
		else
		if	(c == ':')
			return(EPTHNF);				// Doppelpunkt nicht erlaubt
		else
			*s++ = c;
		}
	*s = EOS;

	if	(!mode) 			/* Dateinamen noch nicht bearbeiten */
		*u = EOS;			/* Dateinamen abtrennen vom MAC-Pfad */
	else	{
		get_parent = FALSE;			// nicht den parent!
		if	((u[0] == ':') && (u[1] == '.') && (!u[2]))
			*u = EOS;				// letztes Element "." => abtrennen
		else
		if	((u[0] == '.') && (!u[1]))
			*u = EOS;				// einziges Element "." => abtrennen
		else
		if	((u[0] == ':') && (u[1] == '.') && (u[2] == '.') && (!u[3]))
			goto parent;			// letztes Element ".." => abtrennen
		else
		if	((u[0] == '.') && (u[1] == '.') && (!u[2]))
			{
			parent:
			*u = EOS;				// einziges Element "." => abtrennen
			get_parent = TRUE;
			}
		}

	sp((char *) macpath);

	/* Jetzt ist der Pfad in einen Mac-Pfad umgewandelt.	*/
	/* Wir versuchen zunaechst, die dirID mit nur		*/
	/* einem Aufruf zu bestimmen						*/
	/* ---------------------------------------------------	*/

	err = FSMakeFSSpec(drv_fsspec[drv].vRefNum, reldir,
					(unsigned char*) macpath, &fs);

	/* Wenn das Verzeichnis nicht gefunden wurde, kann	*/
	/* es sein, dass eines der Verzeichnisse ein Alias ist.*/
	/* ---------------------------------------------------	*/

	if	(err == dirNFErr)
		{
		doserr = MakeFSSpecManually(drv_fsspec[drv].vRefNum, reldir,
					(char*) macpath, &fs);
		if	(doserr)
			goto was_doserr2;
		if	(vRefNum2drv(fs.vRefNum, dir_drive))	// !AK: 31.1.97
			err = nsvErr;
		else	err = noErr;
		}

	if	(err)
		goto was_doserr;

	/* Wir holen uns jetzt die Informationen ueber das	*/
	/* letzte Pfadelement.							*/
	/* ---------------------------------------------------	*/

	pb.hFileInfo.ioVRefNum = fs.vRefNum;
	pb.hFileInfo.ioNamePtr = fs.name;
	pb.hFileInfo.ioFDirIndex = 0;
	pb.hFileInfo.ioDirID = fs.parID;
	if	(!pb.hFileInfo.ioNamePtr[0])
		pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
	err = PBGetCatInfoSync (&pb);
	if	(err)
		{
		was_doserr:
		doserr = cnverr(err);
		was_doserr2:
		if   (doserr == EFILNF)
		     doserr = EPTHNF;
		return(doserr);
		}

	/* ggf. Alias aufloesen */
	/* ------------------- */

	if	(pb.hFileInfo.ioFlFndrInfo.fdFlags & kIsAlias)
		{
		doserr = resolve_symlink( &fs, 0, NULL );

		if	(!doserr)		/* Der Mac hat dereferenziert! */
			{
			pb.hFileInfo.ioVRefNum = fs.vRefNum;
			pb.hFileInfo.ioNamePtr = fs.name;
			pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
			pb.hFileInfo.ioDirID = fs.parID;
			if	(!pb.hFileInfo.ioNamePtr[0])
				pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
			err = PBGetCatInfoSync (&pb);
			if	((!err) && (vRefNum2drv(fs.vRefNum, dir_drive)))	// !AK: 31.1.97
				err = nsvErr;
			if	(err)
				return(cnverr(err));			// nix gefunden
			}
		else	goto was_doserr2;		/* Fehler */
		}

	reldir = pb.hFileInfo.ioDirID;

	if	(mode)                                       /* Verzeichnis */
		{
		if	(!(pb.hFileInfo.ioFlAttrib & 0x10))
			return(EPTHNF);                         /* kein SubDir */
		*restpfad = pathname + strlen(pathname);     /* kein Restpfad */
		if	(get_parent)
			{
			if	(reldir == drv_dirID[drv])
				{	// bin schon root
				*symlink = NULL;
				return(ELINK);
				}
			err = dir2fsspec( drv, reldir, &fs );
			if	(err)
				goto was_doserr;
			reldir = fs.parID;		// parent anwaehlen
			}
		}
	else	{
		*restpfad = (char *) t;                               /* Restpfad */
		}

	return(reldir);
}


static char getArchiveMask (CInfoPBRec *pb)
{
	if 	((pb->hFileInfo.ioFlAttrib & ioDirMask) ||			// falls es ein Dir ist
		 (pb->hFileInfo.ioFlBkDat >= pb->hFileInfo.ioFlMdDat))	// oder seit der letzten Aenderung gesichert wurde
		{
		return 0;
		}
	 else	{
		return FA_ARCHIVE;		// Archiv-Bit wird bei ungesicherten Dateien gesetzt.
		}
}

static Byte mac2DOSAttr (CInfoPBRec *pb)
// Attribute von Mac nach DOS konvertieren
// 17.6.96: wertet nun auch hidden-flag aus
{
	Byte attr;
	attr = pb->hFileInfo.ioFlAttrib & (FA_RDONLY + FA_SUBDIR);
	attr |= getArchiveMask (pb);
	if	(pb->hFileInfo.ioFlFndrInfo.fdFlags & kIsInvisible)	// 17.6.96 invisible?
		attr |= FA_HIDDEN;
	return attr;
}

/*************************************************************
*
* Wird von xfs_sfirst und xfs_snext verwendet
* Unabhaengig von drv_longnames[drv] werden die Dateien
* immer in Gross-Schrift und 8+3 konvertiert.
* MiNT konvertiert je nach Pdomain() in Gross-Schrift oder nicht.
*
* 6.9.95:
* Lange Dateinamen werden nicht gefunden.
*
* 19.11.95:
* Aliase werden dereferenziert.
*
*************************************************************/

static long _snext(WORD drv, MAC_DTA *dta)
{
	FSSpec fs;		/* fuer Aliase */
	CInfoPBRec pb;
	LONG doserr;
	OSErr err;
	unsigned char macname[256];		// Pascalstring Mac-Dateiname
	char atariname[256];			// C-String Atari-Dateiname (lang)
	unsigned char dosname[14], cmpname[14];	// intern, 8+3
	Boolean first = !drv_rvsDirOrder[drv] && !drv_readOnly[drv];


	if	(!drv_fsspec[drv].vRefNum)    /* ungueltig */
		return(EDRIVE);

	/* suchen */
	/* ------ */

	pb.hFileInfo.ioNamePtr = macname;
	do	{
		again:

		/* Ende des Verzeichnisses erreicht (index == 0):	*/
		/* --------------------------------------------	*/

		if	(dta->macdta.index == 0)
			{
			dta->macdta.sname[0] = EOS;                  /* DTA ungueltig machen */
			return(EFILNF);
			}

		/* Verzeichniseintrag (PBREC) lesen.		*/
		/* --------------------------------	*/ 
    
		pb.hFileInfo.ioVRefNum = drv_fsspec[drv].vRefNum;
		pb.hFileInfo.ioFDirIndex = dta->macdta.index;
		pb.hFileInfo.ioDirID = dta->macdta.dirID;
		/* notwendige Initialisierung fuer Verzeichnisse (sonst Muell!) */
		pb.hFileInfo.ioFlLgLen = 0;
		pb.hFileInfo.ioFlPyLen = 0;
		err = PBGetCatInfoSync (&pb);
		if	(err)
			{
			dta->macdta.sname[0] = EOS;                  /* DTA ungueltig machen */
			return(cnverr(err));
			}

		if	(drv_rvsDirOrder[drv])
			{
			dta->macdta.index--;
			}
		else	{
			dta->macdta.index++;
			}

		/* Datei gefunden, passen Name und Attribut ? */
		/* geht nicht wegen Compilerfehler in 1.2.2: */
		/* conv_path_elem(cs(macname), dosname); */

		macname[macname[0]+1] = EOS;
		MacFnameToAtariFname(macname+1,
						(unsigned char *) atariname);	// Umlaute wandeln
		if	(conv_path_elem(atariname, (char *) dosname))		// Konvertier. fuer Vergleich
			goto again;			/* Dateiname zu lang */

		/* Schon hier muessen wir eventuelle Aliase	*/
		/* dereferenzieren, damit der Attributvergleich	*/
		/* moeglich ist (Attr aus Datei, nicht Alias!)	*/
		/* -----------------------------------------	*/

		if	(pb.hFileInfo.ioFlFndrInfo.fdFlags & kIsAlias)
			{
			/* FSSpec erstellen und Alias dereferenzieren	*/
			/* ----------------------------------------	*/
			cfss(drv, dta->macdta.dirID, macname+1, &fs, FALSE);

			doserr = resolve_symlink( &fs, 0, NULL );

			if	(!doserr)		/* Der Mac hat dereferenziert! */
				{
				pb.hFileInfo.ioVRefNum = fs.vRefNum;
				pb.hFileInfo.ioNamePtr = fs.name;
				pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
				pb.hFileInfo.ioDirID = fs.parID;
				if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
				err = PBGetCatInfoSync (&pb);
				if	(err)
					{
					dta->macdta.sname[0] = EOS;                  /* DTA ungueltig machen */
					return cnverr(err);
					}
				pb.hFileInfo.ioNamePtr = (unsigned char*)macname;
				}
			}

		dosname[11] = mac2DOSAttr (&pb);	// !TT 17.6.96
		
		if	(first)
			{
			first = false;
			if	(nameto_8_3(macname+1, cmpname, FALSE, TRUE))
				goto again;		// musste Dateinamen kuerzen!

			if	(!strncmp (dta->mxdta.dta_name, (char *) cmpname, 12))
				goto again;
			}
		}
	while(!filename_match(dta->macdta.sname, (char *) dosname));

	/* erfolgreich: DTA initialisieren. Daten liegen nur in der Data fork */
	/* ------------------------------------------------------------------ */

	if	(!drv_rvsDirOrder[drv] && !drv_readOnly[drv])
		--dta->macdta.index;		// letzten Eintrag das naechste Mal nochmal lesen!

	dta->mxdta.dta_attribute = dosname[11];
	dta->mxdta.dta_len = (dosname[11] & FA_SUBDIR) ? 0L : pb.hFileInfo.ioFlLgLen;
     /* Datum ist ioFlMdDat bzw. ioDrMdDat */
	date_mac2dos( pb.hFileInfo.ioFlMdDat,	(UWORD *) &(dta->mxdta.dta_time),
								(UWORD *) &(dta->mxdta.dta_date));
	nameto_8_3 (macname+1, (unsigned char *) dta->mxdta.dta_name, FALSE, TRUE);

/*
	dta->mxdta.dta_name[13] = EOS;
*/
	return(E_OK);
}


/*************************************************************
*
* Durchsucht ein Verzeichnis und merkt den Suchstatus
* fuer Fsnext.
* Der Mac benutzt fuer FA_SUBDIR und FA_RDONLY dieselben Bits.
*
*************************************************************/

static LONG xfs_sfirst(WORD drv, LONG dirID, char *name,
                    MAC_DTA *dta, WORD attrib)
{
	if	(drv_changed[drv])
		return(E_CHNG);
	if 	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	/* Unschoenheit im Kernel ausbuegeln: */
	dta->mxdta.dta_drive = drv;

	conv_path_elem(name, dta->macdta.sname);	// Suchmuster -> DTA
	dta->mxdta.dta_name[0] = 0;		//  gefundenen Namen erstmal loeschen
	dta->macdta.sattr = (char) attrib;			// Suchattribut
	dta->macdta.dirID = dirID;

	if	(drv_rvsDirOrder[drv])
		{
		CInfoPBRec pb;
		//Str255 name2;
		OSErr err;

		pb.hFileInfo.ioNamePtr = nil;	// !TT 3.5.96 statt = name2;
		pb.hFileInfo.ioVRefNum = drv_fsspec[drv].vRefNum;
		pb.hFileInfo.ioFDirIndex = -1; // get info of directory
		pb.hFileInfo.ioDirID = dirID;
		err = PBGetCatInfoSync (&pb);
		if	(err)
			{
			dta->macdta.sname[0] = EOS;                  // DTA ungueltig machen
			return cnverr (err);
			}
		dta->macdta.index = pb.dirInfo.ioDrNmFls;      // letzte Datei zuerst, dann weiter rueckwaerts
		}
	else
		{
		dta->macdta.index = (long) 1;				// erste Datei
		}
	
	return(_snext(drv, dta));
}


/*************************************************************
*
* Durchsucht ein Verzeichnis weiter und merkt den Suchstatus
* fuer Fsnext.
*
*************************************************************/

static long xfs_snext(int drv, MAC_DTA *dta)
{
	long err;


	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	if	(!dta->macdta.sname[0])
		return(ENMFIL);
	err = _snext(drv, dta);
	if	(err == EFILNF)
		err = ENMFIL;
	return(err);
}


/*************************************************************
*
* Oeffnet eine Datei.
* Liefert Fehlercode oder ioRefNum (eine Art Handle).
*
* fd.mod_time_dirty wird dabei automatisch vom Kernel
* auf FALSE gesetzt.
*
* Aliase werden dereferenziert.
* Seit 25.10.96 wird auch <attrib> ausgewertet, dazu benoetigt
* man allerdings unbedingt (!) einen neuen MagiC-Kernel (5.04)
*
*************************************************************/

static long xfs_fopen(char *name, WORD drv, LONG dirID,
			WORD omode, WORD attrib)		// !AK: 25.10.96
{
	FSSpec fs;
	FInfo finfo;
	OSErr err;
	LONG doserr;
	int perm;
	/* HParamBlockRec pb; */
	short refnum;
	unsigned char dosname[20];


	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	if	(fname_is_invalid(name))
		return(EACCDN);

	if	(!drv_longnames[drv])
		{	// keine langen Namen: nach Gross-Schrift und 8+3
		nameto_8_3 ((unsigned char *) name, dosname, FALSE, FALSE);
		name = (char *) dosname;
		}

	cfss(drv, dirID, (unsigned char *) name, &fs, TRUE);

	/* Datei erstellen, wenn noetig */
	/* ---------------------------- */

	if	(omode & O_CREAT)
		{
		// !TT 29.3.95
		ulong creator, type;
		GetTypeAndCreator ((char*)fs.name+1, &type, &creator);
		err = FSpCreate(&fs, creator, type, smSystemScript);

		if	(err == dupFNErr)        /* Datei existiert schon */
			{
			if	(omode & O_EXCL)
				return(EACCDN);
			err = FSpDelete(&fs);
			if	(!err)
				err = FSpCreate(&fs, creator, type, smSystemScript);	// !TT 2.6.96 (c&t!)
			}

		/* Dateiattribute aendern, wenn noetig */
		/* ----------------------------------- */

		if	((!err) && (attrib & (FA_RDONLY+FA_HIDDEN)))	// !AK: 25.10.96
			{
			err = xfs_attrib(drv, dirID, name, TRUE, attrib);
			if	(err >= 0)
				err = 0;
			}

		if	(err)
			return(cnverr(err));

		}


	/* Open-Modus festlegen. Problem: Der MAC hat unzureichende	*/
	/* Moeglichkeiten, den Modus zu spezifizieren. Deshalb z.B.:	*/

	/* exklusiv lesen, andere duerfen weder lesen noch schreiben	*/
	/* (OM_RPERM + OM_RDENY + OM_WDENY) => fsRdPerm			*/
	/*							(exklusiv lesen)		*/

	/* exklusiv schreiben, andere weder lesen noch schreiben		*/
	/* (OM_WPERM + OM_RDENY + OM_WDENY) => fsWrPerm		*/
	/*							(exclusive write)		*/

	/* gemeinsames Lesen, andere duerfen nicht schreiben		*/
	/* (OM_RPERM + OM_WDENY) => fsRdWrShPerm				*/
	/*	(!! ACHTUNG)				(shared read+write)	*/

	/*
		Genauer: Wenn der Atari nicht WDENY _und_ RDENY angibt, darf
		die Datei z.B. von anderen Prozessen gelesen werden.
		Deshalb wird dann immer fsRdWrShPerm ausgefuehrt. Damit sind
		saemtliche Sicherheitsmechanismen zum Teufel, da andere Prozesse
		nun auch schreiben duerfen.
	*/

	if	((omode & (OM_RDENY+OM_WDENY)) == (OM_RDENY+OM_WDENY))
		// niemand sonst darf Lesen oder Schreiben
		{
		if	(omode & (OM_WPERM+OM_RPERM) == OM_WPERM+OM_RPERM)
			perm = fsRdWrPerm;	// Lesen und Schreiben
		else
		if	(omode & OM_WPERM)
			perm = fsWrPerm;		// kein Lesen, nur Schreiben
		else	perm = fsRdPerm;		// nur Lesen, kein Schreiben
		}
	else
		// andere duerfen auch Lesen und/oder Schreiben
		{
		perm = fsRdWrShPerm;
		}

	/* Bevor wir irgendetwas treiben, muessen wir feststellen,	*/
	/* ob es sich bei der Datei um einen Alias handelt!		*/
	/* ------------------------------------------------------ */

	err = FSpGetFInfo (&fs, &finfo);
	if	(err)
		return(cnverr(err));
	if	(finfo.fdFlags & kIsAlias)
		{
		doserr = resolve_symlink( &fs, 0, NULL );
		if	(doserr)
			return(doserr);
		}

	err = FSpOpenDF(&fs, perm, &refnum);

/* 26.7.95 !TT alt:
	if	((err == permErr) && (perm == fsRdWrShPerm) && ((omode & OM_WPERM) == 0))
*/
	if	((cnverr (err) == EACCDN) && (perm == fsRdWrShPerm) && ((omode & OM_WPERM) == 0))
		// Datei ist entw. schreibgeschuetzt oder bereits zum exkl. Lesen/Schreiben geoeffnet.
		// Da der User nur lesen wollte, probieren wir es deshalb mal mit exkl. Lesen
		// fuer den Fall, dass die Datei lediglich schreibgeschuetzt ist (mehrere exkl.
		// Leser erlaubt das Mac-FS naemlich).
		{
		if	(FSpOpenDF(&fs, fsRdPerm, &refnum) == noErr)
			err = 0;	// hat geklappt!
		}

/*
	pb.ioParam.ioVRefNum = drv_fsspec[drv].vRefNum;
	pb.ioParam.ioNamePtr = fs.name;
	pb.ioParam.ioPermssn = perm;
	pb.ioParam.ioMisc = 0;
	pb.fileParam.ioDirID = dirID;
	err = PBHOpen(&pb, FALSE);
*/
	if	(err)
		return(cnverr(err));

	if	(omode & O_TRUNC)
		{
		err = SetEOF(refnum, 0L);
		if   (err)
		     {
		     FSClose(refnum);
		     return(cnverr(err));
		     }
		}
	
	return((unsigned short) (refnum));
}


/*************************************************************
*
* Loescht eine Datei.
*
* Aliase werden NICHT dereferenziert, d.h. es wird der Alias
* selbst geloescht.
*
*************************************************************/

static long xfs_fdelete(WORD drv, LONG dirID, char *name)
{
	FSSpec fs;
	OSErr err;

	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

 	cfss(drv, dirID, (unsigned char *) name, &fs, TRUE);
	err = FSpDelete(&fs);
	return(cnverr(err));
}


/*************************************************************
*
* Datei umbenennen und verschieben bzw. Hard Link erstellen.
*
*	mode == 1		Hardlink
*		== 0		Umbenennen ("move")
*
* Aliase werden NICHT dereferenziert, d.h. es wird der Alias
* selbst umbenannt.
*
* ACHTUNG: Damit <dst_drv> gueltig ist, muss ein neuer MagiC-
* Kernel verwendet werden, die alten uebergeben diesen
* Parameter nicht.
*
*************************************************************/

static long xfs_link(WORD drv, char *nam1, char *nam2,
               LONG dirID1, LONG dirID2, WORD mode, WORD dst_drv)
{
	unsigned char macname1[128];
	unsigned char macname2[128];
//	Str255 pmacname1,pmacname2;
	FSSpec fs1,fs2;
	FInfo	fi;
	Str63 name;
	OSErr err;
//	HParamBlockRec pbr;
	int diffnames;
	unsigned char *tempname = "\pmmac&&&";



	if	((drv_changed[drv]) || (drv_changed[dst_drv]))
		return(E_CHNG);
	if	((!drv_fsspec[drv].vRefNum) || (!drv_fsspec[dst_drv].vRefNum))
		return(EDRIVE);
	if	(drv_fsspec[drv].vRefNum != drv_fsspec[dst_drv].vRefNum)
		return(ENSAME);		// !AK: 23.1.97
	if	(fname_is_invalid(nam2))
		return(EACCDN);

	if	(mode)
		return(EINVFN);          // keine Hardlinks

	/* Beide Namen ins Mac-Format wandeln */

	if	(!drv_longnames[drv])
		{	// keine langen Namen: nach Gross-Schrift und 8+3
		nameto_8_3 ((unsigned char *) nam1, macname1, FALSE, FALSE);
		AtariFnameToMacFname(macname1, macname1);
		}
	else	{
		AtariFnameToMacFname((unsigned char *) nam1, macname1);
		}

	if	(!drv_longnames[dst_drv])
		{	// keine langen Namen: nach Gross-Schrift und 8+3
		nameto_8_3 ((unsigned char *) nam2, macname2, FALSE, FALSE);
		AtariFnameToMacFname(macname2, macname2);
		}
	else	{
		AtariFnameToMacFname((unsigned char *) nam2, macname2);
		}

	/* Das folgende klappt offenbar nur auf einem
	Server-Volume
	pbr.copyParam.ioVRefNum = drv_fsspec[drv].vRefNum;
	pbr.copyParam.ioNamePtr = pmacname1;
	pbr.copyParam.ioCopyName = pmacname2;
	pbr.copyParam.ioDirID = dirID1;
	pbr.copyParam.ioNewDirID = dirID2;
	pbr.copyParam.ioNewName = nil;
	err = PBHMoveRename(&pbr, false);
	*/

	fs1.vRefNum = drv_fsspec[drv].vRefNum;
	vstrcpy((char *) fs1.name+1, (char *) macname1);
	sp((char*)fs1.name);
	fs2.vRefNum = drv_fsspec[dst_drv].vRefNum;
	vstrcpy((char *) fs2.name+1, (char *) macname2);
	sp((char*)fs2.name);
	fs2.parID = dirID2;

	diffnames = strcmp((char *) macname1, (char *) macname2);

	again:
	fs1.parID = dirID1;		// Quellname

	if	(dirID1 == dirID2)			// rename
		{
		err = FSpRename (&fs1, fs2.name);

		// !TT T&C setzen:
		if	(!err)
			{
			FSpGetFInfo (&fs2, &fi);
			GetTypeAndCreator ((char*)fs2.name+1,
					&fi.fdType, &fi.fdCreator);
			FSpSetFInfo (&fs2, &fi);
			}

		}
	else	{					// move
		CMovePBRec r;


		// Bei unterschiedlichen Namen muessen wir erst testen,
		// ob die Zieldatei im Zielverzeichnis existiert
		// ----------------------------------------------------

		if	(diffnames)
			{
			err = FSpGetFInfo (&fs2, &fi);
			if	(err != fnfErr)		// file not found ??
				{
				if	(!err)			// Datei existiert => EACCDN
					err = permErr;
				goto ende;			// Aufruf abbrechen
				}
			}

		/* Wir verschieben jetzt die Quelldatei mit demselben Namen	*/
		/* ins neue Verzeichnis. Das kann natuerlich schief gehen. 		*/
		/* -----------------------------------------------------------	*/

		r.ioNamePtr = fs1.name;
		r.ioVRefNum = fs1.vRefNum;
		r.ioDirID = fs1.parID;
		r.ioNewName = nil;		// Zielverzeichnis: ioNewDirID
		r.ioNewDirID = dirID2;
		err = PBCatMoveSync (&r);

		if	(!diffnames)		// umbenennen ?
			goto ende;			// nein, wir sind fertig

		// Wenn beim Verschieben der Quellname im Zielverzeichnis
		// schon existiert, muessen wir erst die Quelldatei in
		// einen Temporaernamen umbenennen, sie dann in das
		// Zielverzeichnis schieben und dort umbenennen
		// ------------------------------------------------------

		if	(err == dupFNErr)
			{
			err = FSpRename (&fs1, tempname);
			if	(!err)
				{
				r.ioNamePtr = tempname;
				err = PBCatMoveSync (&r);

				if	(!err)
					{
					// Datei liegt mit Temporaernamen im Zielverzeichnis
					dirID1 = dirID2;
					vstrcpy((char *) fs1.name, (char *) tempname);	// Quellname
					goto again;
					}
				else	{

					// Verschieben ging nicht.
					// Datei wieder in fs1.name umbenennen
					// -----------------------------------

					vstrcpy((char *) name, (char *) fs1.name);
					vstrcpy((char *) fs1.name, (char *) tempname);
					FSpRename (&fs1, name);
					}
				}
			}

		// Wenn das Verschieben geklappt hat und die Zieldatei
		// einen anderen Namen als die Quelldatei hat, muessen wir
		// sie nach dem Verschieben noch umbenennen.
		// -------------------------------------------------------

		if	(!err)				// move and rename
			{
			dirID1 = dirID2;		// Quelldatei jetzt in dirID2
			goto again;			// zum Umbenennen
			}
		}
ende:
	return(cnverr(err));
}


/*************************************************************
*
* Wandelt CInfoPBRec => XATTR
*
* (Fuer Fxattr und Dxreaddir)
*
*************************************************************/

static void cinfo_to_xattr( CInfoPBRec * pb, XATTR *xattr, WORD drv)
{
	xattr->attr = mac2DOSAttr (pb);	// !TT 17.7.96

	if	(pb->hFileInfo.ioFlFndrInfo.fdFlags & kIsAlias)
		xattr->mode = S_IFLNK;			// symlink
	else
	if	(xattr->attr  & FA_SUBDIR)
		xattr->mode = S_IFDIR;			// subdir
	else	xattr->mode = S_IFREG;			// regular file

		

	xattr->mode |= 0777;				// rwx fuer user/group/world
	if	(xattr->attr & FA_RDONLY)
		xattr -> mode &= ~(0222);		// Schreiben verboten

	xattr->index = pb->hFileInfo.ioDirID;
	xattr->dev = pb->hFileInfo.ioVRefNum;
	xattr->reserved1 = 0;
	xattr->nlink = 1;
	xattr->uid = xattr->gid = 0;
#if 0
 !TT 27.7.95: FA_SUBDIR-Abfrage ist unbedingt noetig!
#endif
	xattr->size = (xattr->attr & FA_SUBDIR)? 0 : pb->hFileInfo.ioFlLgLen;	// Log. Laenge Data Fork
	xattr->blksize = 512;			// ?????
	xattr->nblocks = pb->hFileInfo.ioFlPyLen / 512;	// Phys. Laenge / Blockgroesse
	date_mac2dos(pb->hFileInfo.ioFlMdDat, &(xattr->mtime), &(xattr->mdate));
	xattr->atime = xattr->mtime;
	xattr->adate = xattr->mdate;
	date_mac2dos(pb->hFileInfo.ioFlCrDat, &(xattr->ctime), &(xattr->cdate));
	xattr->reserved2 = 0;
	xattr->reserved3[0] = xattr->reserved3[1] = 0;
}


/*************************************************************
*
* Fuer Fxattr
*
* MODE == 0: Folge Symlinks
*
*************************************************************/

static long xfs_xattr(WORD drv, LONG dirID, char *name,
				XATTR *xattr, WORD mode)
{
	FSSpec fs;
	CInfoPBRec pb;
	OSErr err;
	LONG doserr;
	unsigned char fname[64];


	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	if	(drv_longnames[drv])
		{
		if	((name[0] == '.') && (!name[1]))
			fname[1] = EOS;		// "." wie leerer Name
		else	AtariFnameToMacFname((unsigned char *) name, fname+1);
		}
	else	{
		nameto_8_3 ((unsigned char *) name, fname+1, FALSE, FALSE);
		AtariFnameToMacFname(fname+1, fname+1);
		}
	sp((char *) fname);

	pb.hFileInfo.ioVRefNum = drv_fsspec[drv].vRefNum;
	pb.hFileInfo.ioNamePtr = fname;
	pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
	pb.hFileInfo.ioDirID = dirID;
	/* notwendige Initialisierung fuer Verzeichnisse (sonst Muell!) */
	pb.hFileInfo.ioFlLgLen = 0;
	pb.hFileInfo.ioFlPyLen = 0;
	if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
	err = PBGetCatInfoSync (&pb);
	if	(err)
		return(cnverr(err));

	/* Im Modus 0 muessen Aliase dereferenziert werden	*/
	/* ------------------------------------------------	*/

	doserr = E_OK;
	if	((!mode) && (pb.hFileInfo.ioFlFndrInfo.fdFlags & kIsAlias))
		{

		/* FSSpec erstellen und Alias dereferenzieren	*/
		/* ----------------------------------------	*/

		cfss(drv, dirID, fname+1, &fs, FALSE);

		doserr = resolve_symlink( &fs, 0, NULL );

		if	(!doserr)		/* Der Mac hat dereferenziert! */
			{
			pb.hFileInfo.ioVRefNum = fs.vRefNum;
			pb.hFileInfo.ioNamePtr = fs.name;
			pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
			pb.hFileInfo.ioDirID = fs.parID;
			if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
			err = PBGetCatInfoSync (&pb);
			if	(err)
				return cnverr(err);
			}
		}

	if	(!doserr)
		cinfo_to_xattr( &pb, xattr, drv);
	return(doserr);
}


/*************************************************************
*
* Fuer Fattrib
*
* Wertet zur Zeit nur die DOS-Attribute
*	FA_RDONLY
*	FA_HIDDEN
*	FA_ARCHIVE
* aus.
*
* Aliase werden dereferenziert.
*
*************************************************************/

static long xfs_attrib(WORD drv, LONG dirID, char *name, WORD rwflag, WORD attr)
{
	FSSpec fs;
	CInfoPBRec pb;
	OSErr err;
	LONG doserr;
	unsigned char fname[64];
	int oldattr;

	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	if	(drv_longnames[drv])
		AtariFnameToMacFname((unsigned char *) name, fname+1);
	else	{
		nameto_8_3 ((unsigned char *) name, fname+1, FALSE, FALSE);
		AtariFnameToMacFname(fname+1, fname+1);
		}

	sp((char *) fname);
	pb.hFileInfo.ioVRefNum = drv_fsspec[drv].vRefNum;
	pb.hFileInfo.ioNamePtr = (unsigned char*)fname;
	pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
	pb.hFileInfo.ioDirID = dirID;
	if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
	err = PBGetCatInfoSync (&pb);
	if	(err)
		return(cnverr(err));

	/* Aliase muessen dereferenziert werden	*/
	/* -------------------------------------	*/

	if	(pb.hFileInfo.ioFlFndrInfo.fdFlags & kIsAlias)
		{
		cfss(drv, dirID, fname+1, &fs, FALSE);

		doserr = resolve_symlink( &fs, 0, NULL );

		if	(!doserr)		/* Der Mac hat dereferenziert! */
			{
			pb.hFileInfo.ioVRefNum = fs.vRefNum;
			pb.hFileInfo.ioNamePtr = fs.name;
			pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
			pb.hFileInfo.ioDirID = fs.parID;
			if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
			err = PBGetCatInfoSync (&pb);
			if	(err)
				return cnverr(err);
			}
		else	return(doserr);		/* Fehler */
		}

	/* Normale Datei, oder Alias ist dereferenziert	*/
	/* ------------------------------------------	*/

	oldattr = mac2DOSAttr (&pb);
	if	(rwflag)
		{
		if	(pb.hFileInfo.ioFlAttrib & ioDirMask)
			{			// !AK 4.10.98
			/* Bei Verzeichnissen ist nur HIDDEN aenderbar */
			if	((attr & ~FA_HIDDEN) != (oldattr & ~FA_HIDDEN))
				err = permErr;
			}

		pb.hFileInfo.ioDirID = pb.hFileInfo.ioFlParID;
		if	(!err && (oldattr & FA_RDONLY) != (attr & FA_RDONLY))	// !AK: 4.10.98
			{
			if	(attr & FA_RDONLY)
				err = PBHSetFLockSync((HParmBlkPtr)&pb);	// !TT 21.5.96 war: cfss(drv, dirID, name, &fs); FSpSetFLock(&fs); ("dirID" war bei Aliasen falsch!)
			else	err = PBHRstFLockSync((HParmBlkPtr)&pb);
			}
		
		// !TT Archiv-Bit:
		if	(!err && (oldattr & FA_ARCHIVE) != (attr & FA_ARCHIVE))
			{
			if	(attr & FA_ARCHIVE)
				{
				if (pb.hFileInfo.ioFlBkDat == pb.hFileInfo.ioFlMdDat)
					pb.hFileInfo.ioFlBkDat = 0;
				}
			else
				pb.hFileInfo.ioFlBkDat = pb.hFileInfo.ioFlMdDat;
			err = PBSetCatInfoSync (&pb);
			}
		
		// !AK 6.2.99: Hidden-Bit auch fuer Ordner
		if	(!err && (oldattr & FA_HIDDEN) != (attr & FA_HIDDEN))
			{
			if	(attr & FA_HIDDEN)
				pb.hFileInfo.ioFlFndrInfo.fdFlags |= kIsInvisible;
			else
				pb.hFileInfo.ioFlFndrInfo.fdFlags &= ~kIsInvisible;
			err = PBSetCatInfoSync (&pb);
			}
		}

	if	(err)
		return(cnverr(err));
	return((unsigned) oldattr);
}


/*************************************************************
*
* Fuer Fchown
*
*************************************************************/

static long xfs_fchown(WORD drv, LONG dirID, char *name,
                    WORD uid, WORD gid)
{
	return(EINVFN);
}


/*************************************************************
*
* Fuer Fchmod
*
*************************************************************/

static long xfs_fchmod(WORD drv, LONG dirID, char *name, WORD fmode)
{
	return(EINVFN);
}


/*************************************************************
*
* Fuer Dcreate
*
*************************************************************/

static long xfs_dcreate(WORD drv, LONG dirID, char *name)
{
	FSSpec fs;
	OSErr err;
	long ndirID;

	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);
	if	(fname_is_invalid(name))
		return(EACCDN);

	cfss(drv, dirID, (unsigned char *) name, &fs, TRUE);
	err = FSpDirCreate(&fs, -1, &ndirID);
	return(cnverr(err));
}


/*************************************************************
*
* Fuer Ddelete
*
* Aliase werden NICHT dereferenziert, d.h. es wird der Alias
* selbst geloescht.
*
*************************************************************/

static long xfs_ddelete(WORD drv, LONG dirID)
{
	FSSpec fs;
	OSErr err;

	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	err = dir2fsspec(drv, dirID, &fs);
	if   (!err)
	     err = HDelete(fs.vRefNum, fs.parID, fs.name);
	return(cnverr(err));
}


/*************************************************************
*
* Fuer Dgetpath
*
*************************************************************/

static LONG xfs_DD2name(WORD drv, LONG dirID, char *buf, WORD bufsiz)
{
	FSSpec fs;
	OSErr err;
	int len;

	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	if	(dirID == drv_dirID[drv])          /* root ? */
		{
		len = 1;
		if	(len > bufsiz)
			return(ERANGE);
		buf[0] = EOS;
		return(E_OK);
		}
	err = dir2fsspec(drv, dirID, &fs);
	if	(err)
		return(cnverr(err));			// AK 22.11.97
	len = fs.name[0];
	if	(len > bufsiz)
		return(ERANGE);
	err = xfs_DD2name(drv, fs.parID, buf, bufsiz - len);
	if	(err)
		return(err);					// AK 22.11.97
	if	(buf[strlen(buf)-1] != '\\')
	     strcat(buf, "\\");
	fs.name[fs.name[0]+1] = EOS;

// Umlaute konvertieren 9.6.96

	while(*buf)
		buf++;
	MacFnameToAtariFname(fs.name+1, (unsigned char *) buf);

//	alte Version: strcat(buf, (char*)fs.name+1);

	return(E_OK);
}


/*************************************************************
*
* Fuer Dopendir.
*
* Aliase brauchen hier nicht dereferenziert zu werden, weil
* dies bereits bei path2DD haette passieren muessen.
*
*************************************************************/

static LONG xfs_dopendir(MAC_DIRHANDLE *dirh, WORD drv, LONG dirID,
				WORD tosflag)
{
	dirh -> dirID = dirID;
	dirh -> tosflag = tosflag;

	if	(drv_rvsDirOrder[drv])
		{
		CInfoPBRec pb;
		//Str255 name2;
		OSErr err;
		
		pb.hFileInfo.ioNamePtr = nil;	// !TT 3.5.96 statt = name2;
		pb.hFileInfo.ioVRefNum = drv_fsspec[drv].vRefNum;
		pb.hFileInfo.ioFDirIndex = -1; // get info of directory
		pb.hFileInfo.ioDirID = dirID;
		err = PBGetCatInfoSync (&pb);
		if	(err)
			{
			return cnverr (err);
			}
		dirh -> index = pb.dirInfo.ioDrNmFls;      // letzte Datei zuerst, dann weiter rueckwaerts
		}
	else
		{
		dirh -> index = 1;
		}

	return(E_OK);
}


/*************************************************************
*
* Fuer D(x)readdir.
* dirh		Verzeichnis-Deskriptor
* size		Groesse des Puffers fuer Namen + ggf. Inode
* buf		Puffer fuer Namen + ggf. Inode
* xattr	Ist != NULL, wenn Dxreaddir ausgefuehrt wird.
* xr		Fehlercode von Fxattr.
*
* 6.9.95:
* Ist das TOS-Flag im <dirh> gesetzt, werden lange Dateinamen
* nicht gefunden.
*
*************************************************************/

static LONG xfs_dreaddir(MAC_DIRHANDLE *dirh, WORD drv,
		WORD size, char *buf, XATTR *xattr, LONG *xr)
{
	CInfoPBRec pb;
	OSErr err;
	unsigned char macname[256];


	if	(!drv_fsspec[drv].vRefNum)    /* ungueltig */
		return(EDRIVE);

	again:
	if	(dirh->index == 0)
		{
		return(ENMFIL);
		}
     
	/* suchen */
	/* ------ */

	pb.hFileInfo.ioNamePtr = (unsigned char*)macname;
	pb.hFileInfo.ioVRefNum = drv_fsspec[drv].vRefNum;
	if	(drv_rvsDirOrder[drv])
		pb.hFileInfo.ioFDirIndex = dirh->index--;
	else
		pb.hFileInfo.ioFDirIndex = dirh->index++;
	pb.hFileInfo.ioDirID = dirh->dirID;
	/* notwendige Initialisierung fuer Verzeichnisse (sonst Muell!) */
	pb.hFileInfo.ioFlLgLen = 0;
	pb.hFileInfo.ioFlPyLen = 0;
	err = PBGetCatInfoSync (&pb);		// hier spaeter mal asynchron
	if	(err)
		{
		dirh->index = 0;                  /* dirh ungueltig machen */
		return(cnverr(err));
		}

	macname[macname[0]+1] = EOS;
	if	(dirh->tosflag)
		{
		if	(size < 13)
			return(ERANGE);
		if	(nameto_8_3(macname+1, (unsigned char *) buf, FALSE, TRUE))
			goto again;		// musste Dateinamen kuerzen
		}
	else	{
		if	(size < macname[0] + 5)
			return(ERANGE);
		strncpy(buf, (char *) &(pb.hFileInfo.ioDirID), 4);
		buf += 4;
		MacFnameToAtariFname(macname+1, (unsigned char *) buf);		// 9.6.96
		}

	if	(xattr)
		{
		cinfo_to_xattr( &pb, xattr, drv);
		*xr = E_OK;
		}

	return(E_OK);
}


/*************************************************************
*
* Fuer Drewinddir
*
*************************************************************/

static LONG xfs_drewinddir(MAC_DIRHANDLE *dirh, WORD drv)
{
	if	(drv_rvsDirOrder[drv])
		return(xfs_dopendir(dirh, drv, dirh->dirID, dirh->tosflag));
	
	dirh -> index = 1;
	return(E_OK);
}


/*************************************************************
*
* Fuer Dclosedir
*
*************************************************************/

static LONG xfs_dclosedir(MAC_DIRHANDLE *dirh, WORD drv)
{
	dirh -> dirID = -1L;
	return(E_OK);
}


/*************************************************************
*
* Fuer Dpathconf
*
* mode = -1:   max. legal value for n in Dpathconf(n)
*         0:   internal limit on the number of open files
*         1:   max. number of links to a file
*         2:   max. length of a full path name
*         3:   max. length of an individual file name
*         4:   number of bytes that can be written atomically
*         5:   information about file name truncation
*              0 = File names are never truncated; if the file name in
*                  any system call affecting  this  directory  exceeds
*                  the  maximum  length (returned by mode 3), then the
*                  error value ERANGE is  returned  from  that  system
*                  call.
*
*              1 = File names are automatically truncated to the maxi-
*                  mum length.
*
*              2 = File names are truncated according  to  DOS  rules,
*                  i.e. to a maximum 8 character base name and a maxi-
*                  mum 3 character extension.
*         6:   0 = case-sensitiv
*              1 = nicht case-sensitiv, immer in Gross-Schrift
*              2 = nicht case-sensitiv, aber unbeeinflusst
*         7:   Information ueber unterstuetzte Attribute und Modi
*         8:   information ueber gueltige Felder in XATTR
*
*      If  any  of these items are unlimited, then 0x7fffffffL is
*      returned.
*
* Aliase brauchen hier nicht dereferenziert zu werden, weil
* dies bereits bei path2DD haette passieren muessen.
*
*************************************************************/

static LONG xfs_dpathconf(WORD drv, LONG dirID, WORD which)
{
	switch(which)
		{
		case	DP_MAXREQ:	return(DP_XATTRFIELDS);
		case	DP_IOPEN:	return(100);	// ???
		case	DP_MAXLINKS:	return(1);
		case	DP_PATHMAX:	return(128);
		case	DP_NAMEMAX:	return((drv_longnames[drv]) ? 31 : 12);
		case	DP_ATOMIC:	return(512);	// ???
		case	DP_TRUNC:	return((drv_longnames[drv]) ? DP_AUTOTRUNC : DP_DOSTRUNC);
		case	DP_CASE:		return((drv_longnames[drv]) ? DP_CASEINSENS : DP_CASECONV);
		case	DP_MODEATTR:	return(FA_RDONLY+FA_SUBDIR+FA_ARCHIVE+FA_HIDDEN
							+DP_FT_DIR+DP_FT_REG+DP_FT_LNK);
		case	DP_XATTRFIELDS:return(DP_INDEX+DP_DEV+DP_NLINK+DP_BLKSIZE
							+DP_SIZE+DP_NBLOCKS
							+DP_CTIME+DP_MTIME);
		}
	return(EINVFN);
}


/*************************************************************
*
* Fuer Dfree
*
* data = free,total,secsiz,clsiz
*
* Aliase brauchen hier nicht dereferenziert zu werden, weil
* dies bereits bei path2DD haette passieren muessen.
*
*************************************************************/

static LONG xfs_dfree(WORD drv, LONG dirID, LONG data[4])
{
	XVolumeParam xpb;		// fuer Platten > 2G
	union {
		unsigned long long bytes;
		UnsignedWide wbytes;
		} wbu;
	HVolumeParam pb;		// alte Version
	OSErr err;


	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	if	(has_2TBVols)
		{
		xpb.ioVolIndex = 0;       /* ioRefNum ist gueltig */
		xpb.ioVRefNum = drv_fsspec[drv].vRefNum;
		xpb.ioNamePtr = NULL;
		err = PBXGetVolInfo(&xpb, FALSE);	// hier spaeter mal asynchron
		if	(err)
			return(cnverr(err));

		wbu.wbytes = xpb.ioVFreeBytes;
		data[0] = wbu.bytes/xpb.ioVAlBlkSiz;	// # freie Bloecke

		wbu.wbytes = xpb.ioVTotalBytes;
		data[1] = wbu.bytes/xpb.ioVAlBlkSiz;	// # alle Bloecke
		data[2] = xpb.ioVAlBlkSiz;				// Bytes pro Sektor
		}
	else	{
		pb.ioVolIndex = 0;       /* ioRefNum ist gueltig */
		pb.ioVRefNum = drv_fsspec[drv].vRefNum;
		pb.ioNamePtr = NULL;
		err = PBHGetVInfoSync ((HParmBlkPtr) &pb);	// hier spaeter mal aynchron
		if	(err)
			return(cnverr(err));
		data[0] = pb.ioVFrBlk;
		data[1] = pb.ioVNmAlBlks;
		data[2] = pb.ioVAlBlkSiz;
		}

	data[3] = 1;							// Sektoren pro Cluster
	return(E_OK);
}


/*************************************************************
*
* Disklabel.
* Zurueckgeliefert wird der Macintosh-Name.
* Das Aendern des Labels ist z.Zt. nicht moeglich.
*
* Bei allen Operationen, die Dateinamen zurueckliefern, ist
* darauf zu achten, dass die Angabe der Puffergroesse immer
* INKLUSIVE End-of-String ist.
*
*************************************************************/

static LONG xfs_wlabel(WORD drv, LONG dirID, char *name)
{
	return(EINVFN);
}

static LONG xfs_rlabel(WORD drv, LONG dirID, char *name, WORD bufsiz)
{
	HVolumeParam pb;
	unsigned char buf[256];
	OSErr err;

	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	pb.ioVolIndex = 0;       /* ioRefNum ist gueltig */
	pb.ioVRefNum = drv_fsspec[drv].vRefNum;
	pb.ioNamePtr = buf;
	err = PBHGetVInfoSync ((HParmBlkPtr) &pb);	// hier spaeter mal asychron
	if	(err)
		return(cnverr(err));
	buf[buf[0] + 1] = EOS;
	if	(buf[0]+1 > bufsiz)
		return(ERANGE);
	MacFnameToAtariFname(buf+1, (unsigned char *) name);		// 9.6.96
	return(E_OK);
}


/*************************************************************
*
* Wandelt einen DOS-Pfad in das Mac-Aequivalent um. Diese
* Funktion wird verwendet, um dem Finder zu ermoeglichen,
* Aliase zu verwenden, die von MagicMac erstellt wurden.
*
* Der Mac-Name wird ganz normal als NUL-terminierter String
* erstellt, nicht als Pascal-String.
*
*************************************************************/

static OSErr PathNameFromDirID( long dirid, short vrefnum,
	char *fullpathname)
{
	DirInfo block;
	Str255 dirname;
	char dirnamec[255];
	OSErr err;

	fullpathname[0] = EOS;
	block.ioDrParID = dirid;
	block.ioNamePtr = dirname;
	do	{
		block.ioVRefNum = vrefnum;
		block.ioFDirIndex = -1;
		block.ioDrDirID = block.ioDrParID;
		err = PBGetCatInfoSync ((CInfoPBPtr) &block);
		if	(err)
			return(err);
		vmemcpy(dirnamec, dirname+1, dirname[0]);
		dirnamec[dirname[0]] = EOS;
		strcat(dirnamec, ":");
		memmove(fullpathname + dirname[0] + 1,
				fullpathname, strlen(fullpathname)+1);
		vmemcpy(fullpathname, dirnamec, dirname[0]+1);
		}
	while	(block.ioDrDirID != 2);
	return(0);
}


static LONG dospath2macpath( WORD drv, LONG reldir,
		char *dospath, char *macname)
{
	LONG doserr;
	OSErr err;
	char *restpfad;
	LONG symlink_dir;
	char *symlink;

	if	(dospath[0] && (dospath[1] == ':'))
		dospath += 2;
	if	(*dospath == '\\')			// absoluter Pfad
		{
		reldir = drv_dirID[drv];
		dospath++;
		}
	doserr = xfs_path2DD(0, drv, reldir, dospath,
			&restpfad, &symlink_dir, &symlink, &drv );	// !AK: 31.1.97
	if	(doserr < E_OK)
		return(doserr);

	err = PathNameFromDirID( doserr, drv_fsspec[drv].vRefNum, macname);
	if	(!err && *restpfad)
		strcat(macname, restpfad);
	return(cnverr(err));
}


/*************************************************************
*
* Fuer Fsymlink
*
* Unter dem Namen <name> wird im Ordner <dirID> ein
* Alias erstellt, der die Datei <to> repraesentiert.
*
*************************************************************/

static LONG xfs_symlink(WORD drv, LONG dirID, char *name, char *to)
{
	int symlink_ok;
	int dst_drv;
	int is_macpath;
	char fullpath[256];
	AliasHandle newalias;
	OSErr err;
	short refnum;
	FSSpec fs;
	CInfoPBRec pb;
	OSType creator, type;
	unsigned char dosname[20];
	Str255 resname;
	unsigned char macname[65];
	char *onlyname;
	FInfo	fi;
	short	saveRefNum;	// TT 31.3.97 neu

	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)    /* ungueltig */
		return(EDRIVE);
	if	(fname_is_invalid(name))
		return(EACCDN);

	/* pruefen, ob der Symlink auf ein Mac-Laufwerk zeigt */
	/* -------------------------------------------------- */

	symlink_ok = FALSE;		/* wir sind erstmal pessimistisch */
	dst_drv = toupper(*to)-'A';
	is_macpath = TRUE;
	if	((dst_drv >= 0) && (dst_drv < NDRVS) && (to[1] == ':'))
		{	// Laufwerk angegeben
		if	(!drv_fsspec[dst_drv].vRefNum)    /* ungueltig */
			is_macpath = FALSE;
		}

	onlyname = strrchr(to, '\\');
	if	(onlyname)
		{
		onlyname++;
		}
	else	{
		if	(to[0] && to[1] == ':')
			onlyname = to+2;
		else	onlyname = to;
		}

	if	(is_macpath)
		{
		symlink_ok = (! dospath2macpath( dst_drv, dirID,
				to, fullpath));
		}

	/* Wenn das Ziellaufwerk kein Mac-Volume ist oder der Pfad irgendwie	*/
	/* sonst nicht in Ordnung ist, setzen wir einen Dummy-Namen als		*/
	/* Alias fuer den Finder ein.								*/
	/* -----------------------------------------------------------------	*/

	if	(!symlink_ok)
		vstrcpy(fullpath, "dummy:dummy");

	err = NewAliasMinimalFromFullPath(strlen(fullpath),
							fullpath,
							NULL,
							NULL,
							&newalias);
	if	(err)
		return(cnverr(err));

	/* Der Alias braucht nicht umkopiert zu werden, wir vergroessern	*/
	/* einfach den Speicherblock, damit wir genug Platz fuer die	*/
	/* Zeichenkette <to> haben.							*/
	/* Wir setzen unsere Kennung und kopieren den DOS-Pfad 1:1	*/
	/* hinter den Alias.								*/
	/* ------------------------------------------------------------	*/

	SetHandleSize((Handle) newalias, (*newalias)->aliasSize + strlen(to)+1);
	(*newalias)->userType = 'MgMc';
	vmemcpy(((char *)(*newalias))+(*newalias)->aliasSize,
			to, strlen(to)+1);

	/* FFSpec erstellen */
	/* --------------- */

	if	(!drv_longnames[drv])
		{	// keine langen Namen: nach Gross-Schrift und 8+3
		nameto_8_3 ((unsigned char *) name, dosname, FALSE, FALSE);
		name = (char *) dosname;
		}
	cfss(drv, dirID, (unsigned char *) name, &fs, TRUE);

	/* Testen, ob die Datei schon existiert. Nach MagiC-Konvention */
	/* darf Fsymlink() niemals eine existierende Datei beeinflussen */
	/* ---------------------------------------------------------- */

	err = FSpGetFInfo (&fs, &fi);
	if	(err != fnfErr)		// file not found ??
		{
		if	(!err)			// Datei existiert => EACCDN
			err = permErr;
		goto ende;			// Aufruf abbrechen
		}

	/* Datei erstellen */
	/* -------------- */

	if	(!(*onlyname))		// "to" ist Verzeichnis
		{
		type = 'fdrp';			// !AK 6.2.99
		creator = 'MACS';
		}
	else	GetTypeAndCreator (name, &type, &creator);		// Datei
	FSpCreateResFile(&fs, creator, type, smSystemScript);

	/* Resource 'alis' erstellen */
	/* ---------------------- */

	saveRefNum = CurResFile ();	// TT 31.3.97 neu
	refnum = FSpOpenResFile(&fs, fsWrPerm);
	if	(refnum == -1)
		{
		err = permErr;
		goto ende;
		}
//	UseResFile(refnum);
	vstrcpy((char *) (resname+1), onlyname);
	strcat((char *) (resname+1), " Alias");
	sp((char *) resname);
	AddResource((Handle) newalias, 'alis', 0, resname);
	CloseResFile(refnum);
//	FlushVol(nil, drv_fsspec[drv].vRefNum);

	/* Finder-Flags fuer Alias setzen (umstaendlich!!!) */

	AtariFnameToMacFname((unsigned char *) name, macname+1);
	sp((char *) macname);
	pb.hFileInfo.ioVRefNum = drv_fsspec[drv].vRefNum;
	pb.hFileInfo.ioNamePtr = macname;
	pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
	pb.hFileInfo.ioDirID = dirID;
	if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
	err = PBGetCatInfoSync (&pb);
	if	(err)
		goto ende;
	pb.hFileInfo.ioFlFndrInfo.fdFlags |= kIsAlias;	// symlink
	pb.hFileInfo.ioDirID = dirID;		// Boese Falle !
	err = PBSetCatInfoSync (&pb);

ende:
	DisposeHandle((Handle) newalias);
	UseResFile (saveRefNum);	// TT 31.3.97 neu
	return(cnverr(err));
}


/*************************************************************
*
* Fuer Freadlink
*
*************************************************************/

static LONG xfs_readlink(WORD drv, LONG dirID, char *name,
				char *buf, WORD bufsiz)
{
	FSSpec fs;


	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)    /* ungueltig */
		return(EDRIVE);

	/* FSSpec erstellen und Alias auslesen	*/
	/* ---------------------------------	*/

	cfss(drv, dirID, (unsigned char *) name, &fs, TRUE);

	return(resolve_symlink( &fs, bufsiz, buf ));
}


/*************************************************************
*
* Fuer Dcntl
*
*************************************************************/

static LONG getCatInfo (short drv, CInfoPBRec *pb, Boolean resolveAlias)
// !!! Andreas, Aliase duerften hier gar nicht mehr vorkommen, oder?
// Ich verstehe das so: Der XFS-Kernel benutzt xfs_path2DD, um die
// Zieldatei, die bei Dcntl uebergeben wird, zu ermitteln. Dabei werden
// dann evtl. vorkommende Aliase schon aufgeloest.
// Warum ist dann trotzdem ueberall hier die Alias-Extrabehandlung zu finden?
// Z.B. duerfte xfs_fopen ebenso wie Dcntl nur die Zieldatei bekommen, oder?
{
	FSSpec fs;
	OSErr  err;
	LONG   doserr;

	err = PBGetCatInfoSync (pb);
	if	(err)
		return cnverr(err);

	/* Aliase dereferenzieren	*/
	/* ----------------------	*/
	doserr = E_OK;
	if	(pb->hFileInfo.ioFlFndrInfo.fdFlags & kIsAlias)
		{
		pb->hFileInfo.ioNamePtr[pb->hFileInfo.ioNamePtr[0]+1] = 0;
		cfss(drv, pb->hFileInfo.ioFlParID, pb->hFileInfo.ioNamePtr+1, &fs, TRUE);
		doserr = resolve_symlink( &fs, 0, NULL );
		if	(!doserr)		/* Der Mac hat dereferenziert! */
			{
			pb->hFileInfo.ioVRefNum = fs.vRefNum;
			pstrcpy (pb->hFileInfo.ioNamePtr, fs.name);
			pb->hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
			pb->hFileInfo.ioDirID = fs.parID;
			if (pb->hFileInfo.ioNamePtr[0] == 0) pb->hFileInfo.ioFDirIndex = -1;
			err = PBGetCatInfoSync(pb);
			if	(err)
				return cnverr(err);
			}
		}
	return doserr;
}

static LONG xfs_dcntl(WORD drv, LONG dirID, char *name, WORD cmd, LONG arg)
{
	CInfoPBRec pb;
	OSErr err;
	LONG doserr;
	unsigned char fname[64];

	if	(drv_changed[drv])
		return(E_CHNG);
	if	(!drv_fsspec[drv].vRefNum)
		return(EDRIVE);

	if	(drv_longnames[drv])
		{
		if	((name[0] == '.') && (!name[1]))
			fname[1] = EOS;		// "." wie leerer Name
		else	AtariFnameToMacFname((unsigned char *) name, fname+1);
		}
	else	{
		nameto_8_3 ((unsigned char *) name, fname+1, FALSE, FALSE);
		AtariFnameToMacFname(fname+1, fname+1);
		}

	sp((char *) fname);
	pb.hFileInfo.ioVRefNum = drv_fsspec[drv].vRefNum;
	pb.hFileInfo.ioNamePtr = (unsigned char*)fname;
	pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
	pb.hFileInfo.ioDirID = dirID;
	if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;

	switch(cmd)
	{
	  case FUTIME:
		if (arg == 0)
		    return EINVFN;
		doserr = getCatInfo (drv, &pb, true);
		if	(doserr)
			return doserr;
		date_dos2mac (((mutimbuf*)arg)->modtime, ((mutimbuf*)arg)->moddate, &pb.hFileInfo.ioFlMdDat);
		pb.hFileInfo.ioDirID = pb.hFileInfo.ioFlParID;
		if ((err = PBSetCatInfoSync(&pb)) != noErr)
		    return cnverr(err);
	  	return 0;

	  case FSTAT:
		if (arg == 0)
		    return EINVFN;
		doserr = getCatInfo (drv, &pb, true);
		if	(doserr)
			return doserr;
		cinfo_to_xattr( &pb, (XATTR *) arg, drv);
		return(E_OK);

	  case FMACGETTYCR:
		if (arg == 0)
		    return EINVFN;
		doserr = getCatInfo (drv, &pb, true);
		if	(doserr)
			return doserr;
		*(FInfo *)arg = pb.hFileInfo.ioFlFndrInfo;
		return(E_OK);

	  case FMACSETTYCR:
		if (arg == 0)
		    return EINVFN;
		doserr = getCatInfo (drv, &pb, true);
		if	(doserr)
			return doserr;
		pb.hFileInfo.ioFlFndrInfo = *(FInfo *)arg;
		pb.hFileInfo.ioDirID = pb.hFileInfo.ioFlParID;
		if ((err = PBHSetFInfoSync((HParmBlkPtr)&pb)) != noErr)
		    return cnverr(err);
		return(E_OK);

	  case FMACMAGICEX:
		{
		MMEXRec *mmex = (MMEXRec*)arg;
		switch (mmex->funcNo)
			{
			case MMEX_INFO:
      			mmex->longVal = 1;
      			mmex->destPtr = MM_VersionPtr;
				return 0;

			case MMEX_GETFSSPEC:
				doserr = getCatInfo (drv, &pb, true);
				if	(doserr)
					return doserr;
				mmex->longVal = FSMakeFSSpec (pb.hFileInfo.ioVRefNum, pb.hFileInfo.ioFlParID,
								pb.hFileInfo.ioNamePtr, (FSSpec*)mmex->destPtr);
				return cnverr (mmex->longVal);

			case MMEX_GETRSRCLEN:
				// Mac-Rsrc-Laenge liefern
				doserr = getCatInfo (drv, &pb, true);
				if	(doserr)
					return doserr;
				if (pb.hFileInfo.ioFlAttrib & ioDirMask)
					return EACCDN;
				mmex->longVal = pb.hFileInfo.ioFlRLgLen;
				return 0;

			case FMACGETTYCR:
				doserr = getCatInfo (drv, &pb, true);
				if	(doserr)
					return doserr;
				*(CInfoPBRec*)arg = pb;
				return(E_OK);

			case FMACSETTYCR:
				doserr = getCatInfo (drv, &pb, true);
				if	(doserr)
					return doserr;
				((HFileInfo*)arg)->ioVRefNum = pb.hFileInfo.ioVRefNum;
				((HFileInfo*)arg)->ioDirID = pb.hFileInfo.ioFlParID;
				((HFileInfo*)arg)->ioNamePtr = pb.hFileInfo.ioNamePtr;
				err = PBSetCatInfoSync ((CInfoPBRec*)arg);
				return cnverr(err);
			}
		}
	}
	return(EINVFN);
}



/*************************************************************/
/******************* Dateitreiber ****************************/
/*************************************************************/

static OSErr f_2_cinfo( MAC_FD *f, CInfoPBRec *pb, char *fname)
{
	FCBPBRec fpb;
	OSErr err;

	fpb.ioFCBIndx = 0;
	fpb.ioVRefNum = 0;
	fpb.ioNamePtr = (unsigned char*)fname;
     	fpb.ioRefNum = f->refnum;
	err = PBGetFCBInfoSync (&fpb);  /* refnum => parID und Name */

	if	(err)
		return(err);

	pb->hFileInfo.ioVRefNum = fpb.ioFCBVRefNum;
	pb->hFileInfo.ioNamePtr = (unsigned char*)fname;
	pb->hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
	pb->hFileInfo.ioDirID = fpb.ioFCBParID;
	if (pb->hFileInfo.ioNamePtr[0] == 0) pb->hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
	err = PBGetCatInfoSync (pb);
	return(err);
}


static LONG dev_close( MAC_FD *f )
{
	FCBPBRec fpb;
	OSErr err;
	char fname[64];
	CInfoPBRec pb;
	IOParam ipb;


	if	(f->fd.fd_refcnt <= 0)
		return(EINTRN);

	// FCB der Datei ermitteln
	fpb.ioFCBIndx = 0;
	fpb.ioVRefNum = 0;
	fpb.ioNamePtr = (unsigned char*)fname;
	fpb.ioRefNum = f->refnum;
	err = PBGetFCBInfoSync (&fpb);  /* refnum => parID und Name */
	if	(err)
		{
		FSClose(f->refnum);
		return(cnverr(err));
		}


	f->fd.fd_refcnt--;
	if	(!f->fd.fd_refcnt)
		{

	/* Datum und Uhrzeit koennen erst nach Schliessen gesetzt werden */
	/* ------------------------------------------------------------- */

		if	(f->mod_time_dirty)
			{
			err = FSClose(f->refnum);
			if	(err)
				return(cnverr(err));

			pb.hFileInfo.ioVRefNum = fpb.ioFCBVRefNum;	// !TT korrig. 07.04.96
			pb.hFileInfo.ioNamePtr = (unsigned char*)fname;
			pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
			pb.hFileInfo.ioDirID = fpb.ioFCBParID;
			if (pb.hFileInfo.ioNamePtr[0] == 0) pb.hFileInfo.ioFDirIndex = -1;	// TT v1.2.7
			err = PBGetCatInfoSync (&pb);

	    		if	(err)
				return(cnverr(err));

			// !TT Archiv-Bit: falls Datei gerade neu angelegt, dann Backup-Datum auf Null setzen
			if (pb.hFileInfo.ioFlCrDat == pb.hFileInfo.ioFlMdDat)
				{
				pb.hFileInfo.ioFlBkDat = 0;	// -> Archiv-Bit loeschen
				}

			pb.hFileInfo.ioFDirIndex = 0;      /* Namen suchen */
			pb.hFileInfo.ioDirID = fpb.ioFCBParID;
			date_dos2mac (f->mod_time[0], f->mod_time[1], &pb.hFileInfo.ioFlMdDat);
			pb.hFileInfo.ioFlCrDat = pb.hFileInfo.ioFlMdDat;	// !TT neu 30.5.95

			// !TT Archiv-Bit: sicherstellen, dass Backup-Datum verschieden von Modif.-Datum ist.
			if (pb.hFileInfo.ioFlBkDat == pb.hFileInfo.ioFlMdDat)
				{
				pb.hFileInfo.ioFlBkDat = 0;
				}

			err = PBSetCatInfoSync (&pb);    /* synchron */
			}
		else	err = FSClose(f->refnum);
		}

	else	{
		ipb.ioRefNum = f->refnum;
		err = PBFlushFileSync ((ParmBlkPtr) &ipb);
		}

	if	(!err && FlushWhenClosing)
		FlushVol (nil, fpb.ioVRefNum);

	return(cnverr(err));
}

/*
*
* pread() und pwrite() fuer "Hintergrund-DMA".
*
* Der Atari-Teil des XFS legt den ParamBlockRec (50 Bytes) auf dem Stapel
* an und initialisiert <ioCompletion>, <ioBuffer> und <ioReqCount>.
* Die Completion-Routine befindet sich
* auf der "Atari-Seite" in "macxfs.s", wird jedoch im Mac-Modus aufgerufen;
* diesen Umstand habe ich beruecksichtigt.
* Die Completion-Routine erhaelt in a0 einen Zeiger auf den ParamBlockRec und
* in d0 (== ParamBlockrec.ioResult) den Fehlercode. Die Routine darf d0-d2 und
* a0-a1 veraendern (PureC-Konvention) und ist "void". a5 ist undefiniert.
* Mit dem Trick:
*
*	LONG geta0 ( void )
*		= 0x2008;			// MOVE.L	A0,D0
*
*	static pascal void dev_p_complete( void )
*	{
*		ParamBlockRec *pb = (ParamBlockRec *) geta0();
*	}
*
* koennte man die Routine auch in C schreiben. Den ParamBlockRec kann man
* beliebig fuer eigene Zwecke erweitern (z.B. a5 ablegen).
*
* Rueckgabe von dev_pread() und dev_pwrite():
*
* >=0		Transfer laeuft und ist beendet, wenn ioComplete den
*		Fehlercode enthaelt.
* <0		Fehler
*
*/

static LONG dev_pwrite( MAC_FD *f, ParamBlockRec *pb )		// AK 27.3.98
{
	OSErr err;


	pb->ioParam.ioRefNum = f->refnum;		// Datei-Handle
	pb->ioParam.ioPosMode = 0;				// ???

	pb->ioParam.ioResult = 1;					// warte, bis <= 0
	err = PBWriteAsync (pb);				// asynchron!
	if	(err)
		return(cnverr(err));
	return(pb->ioParam.ioActCount);
}


static LONG dev_pread( MAC_FD *f, ParamBlockRec *pb )		// AK 27.3.98
{
	OSErr err;


	pb->ioParam.ioRefNum = f->refnum;		// Datei-Handle
	pb->ioParam.ioPosMode = 0;				// ???

	pb->ioParam.ioResult = 1;					// warte, bis <= 0
	err = PBReadAsync (pb);				// asynchron!
	if	(err == eofErr)
		err = 0;				/* nur Teil eingelesen, kein Fehler! */
	if	(err)
		return(cnverr(err));
	return(pb->ioParam.ioActCount);
}


static LONG dev_read( MAC_FD *f, LONG count, char *buf )
{
	OSErr err;

	err = FSRead(f->refnum, &count, buf);
	if	(err == eofErr)
		err = 0;				/* nur Teil eingelesen, kein Fehler! */
	else
	if	(err)
		return(cnverr(err));
	return(count);
}


static LONG dev_write( MAC_FD *f, LONG count, char *buf )
{
	OSErr err;

	err = FSWrite(f->refnum, &count, buf);
	if	(err)
		return(cnverr(err));
	return(count);
}


static LONG dev_stat( MAC_FD *f, void *unsel, WORD rwflag, LONG apcode )
{
	OSErr err;
	long pos;
	long laenge;


	if	(rwflag)
		return(1L);         /* Schreiben immer bereit */
	err = GetEOF(f->refnum, &laenge);
	if	(err)
		return(cnverr(err));
	err = GetFPos(f->refnum, &pos);
	if	(err)
		return(cnverr(err));
	if	(pos < laenge)
		return(1L);
	return(0L);
}


static LONG dev_seek( MAC_FD *f, LONG pos, WORD mode )
{
	OSErr err;
	short macmode;

	switch(mode)
		{
		case 0:   macmode = 1;break;
		case 1:   macmode = 3;break;
		case 2:   macmode = 2;break;
		default:  return(EINVFN);
		}
	err = SetFPos(f->refnum, macmode, pos);
	if	(err)
		return(cnverr(err));
	err = GetFPos(f->refnum, &pos);
	if	(err)
		return(cnverr(err));
	return(pos);
}


static LONG dev_datime( MAC_FD *f, UWORD d[2], WORD rwflag )
{
	OSErr err;
	char fname[64];
	CInfoPBRec pb;


	if	(rwflag)			/* schreiben */
		{
		f->mod_time[0] = d[0];
		f->mod_time[1] = d[1];
		f->mod_time_dirty = TRUE;	/* nur puffern */
		err = E_OK;				/* natuerlich kein Fehler */
		}
	else	{
		if	(f->mod_time_dirty)	/* war schon geaendert */
			{
			d[0] = f->mod_time[0];
			d[1] = f->mod_time[1];
			err = E_OK;				/* natuerlich kein Fehler */
			}
		else	{
			err = f_2_cinfo( f, &pb, fname);
     			if	(err)
          			return(cnverr(err));

	          	/* Datum ist ioFlMdDat bzw. ioDrMdDat */
	          	date_mac2dos(pb.hFileInfo.ioFlMdDat, &(d[0]), &(d[1]));
			}
		}
	return(cnverr(err));
}

static OSErr getFSSpecByFileRefNum (short fRefNum, FSSpec *spec, FCBPBRec *pb)
// !TT 2.5.96 neu
// Ermittelt Dateiname etc. anhand eines offenen File-Handles
{
	OSErr err;
	pb->ioFCBIndx = 0;
	pb->ioRefNum = fRefNum;
	pb->ioNamePtr = spec->name;
	err = PBGetFCBInfoSync ((FCBPBPtr)pb);
	spec->parID = pb->ioFCBParID;
	spec->vRefNum = pb->ioFCBVRefNum;
	return err;
}


static LONG dev_ioctl( MAC_FD *f, WORD cmd, void *buf )
{
	OSErr err;
	char fname[64];
	CInfoPBRec pb;


	switch(cmd)
	 {
	  case FSTAT:
		if (buf == 0)
		    return EINVFN;
		err = f_2_cinfo( f, &pb, fname);
		if	(err)
			return(cnverr(err));
		cinfo_to_xattr( &pb, (XATTR *) buf, f->fd.fd_dmd->d_drive);
		return(E_OK);
	  	break;
	  case FTRUNCATE:
	  	err = SetEOF(f->refnum, *((LONG *) buf));
		return(cnverr(err));
	  	break;

	// !TT 2.5.96 3 Funktionen neu:
	  case FMACOPENRES:
      	{
      		HParamBlockRec pb;
      		FSSpec	spec;
      		short	perm;
      		FCBPBRec	fcb;
      		
			// Get filename & dirID
			err = getFSSpecByFileRefNum (f->refnum, &spec, &fcb);
			if (err) return cnverr (err);
			
			// get the file's access permission
			switch (fcb.ioFCBFlags & 0x1100) {
			case 0x0100:
				perm = fsRdWrPerm;
				break;
			case 0x0000:
				perm = fsRdPerm;
				break;
			case 0x1100:
				perm = fsRdWrShPerm;
				break;
			case 0x1000:
				perm = fsRdPerm;
				break;
			}

			/* close the data fork */
			pb.ioParam.ioRefNum = f->refnum;
			if ((err = PBCloseSync((ParmBlkPtr)&pb)) != noErr)
			    return cnverr(err);

			/* now open the data fork */
			pb.ioParam.ioVRefNum = spec.vRefNum;
			pb.fileParam.ioDirID = spec.parID;
			pb.ioParam.ioNamePtr = spec.name;
			pb.ioParam.ioPermssn = perm;
			pb.ioParam.ioMisc = 0;
			if ((err = PBHOpenRFSync(&pb)) != noErr)
			    return cnverr(err);
			f->refnum = pb.ioParam.ioRefNum;
			if (f->fd.fd_mode & O_TRUNC) {
			    pb.ioParam.ioMisc = 0;
			    if ((err = PBSetEOFSync((ParmBlkPtr)&pb)) != noErr)
			        return cnverr(err);
			}
			return 0;
		}

	  case FMACGETTYCR:
		{
      		FSSpec	spec;
      		HFileParam pbf;
      		FCBPBRec	fcb;

			if (buf == 0)
			    return EINVFN;

			// Get filename & dirID
			err = getFSSpecByFileRefNum (f->refnum, &spec, &fcb);
			if (err) return cnverr (err);

			pbf.ioVRefNum = spec.vRefNum;
			pbf.ioDirID = spec.parID;
			pbf.ioNamePtr = spec.name;
			pbf.ioFDirIndex = 0;
			if ((err = PBHGetFInfoSync((HParmBlkPtr)&pbf)) != noErr)
			    return cnverr(err);
			*(FInfo *)buf = pbf.ioFlFndrInfo;
			return 0;
		}

	  case FMACSETTYCR:
		{
      		FSSpec	spec;
      		HFileParam pbf;
      		FCBPBRec	fcb;

			if (buf == 0)
			    return EINVFN;

			// Get filename & dirID
			err = getFSSpecByFileRefNum (f->refnum, &spec, &fcb);
			if (err) return cnverr (err);

			pbf.ioVRefNum = spec.vRefNum;
			pbf.ioDirID = spec.parID;
			pbf.ioNamePtr = spec.name;
			pbf.ioFDirIndex = 0;
			if ((err = PBHGetFInfoSync((HParmBlkPtr)&pbf)) != noErr)
			    return cnverr(err);

			pbf.ioFlFndrInfo = *(FInfo *)buf;
			pbf.ioDirID = spec.parID;
			if ((err = PBHSetFInfoSync((HParmBlkPtr)&pbf)) != noErr)
			    return cnverr(err);
			return 0;
		}

	  case FMACMAGICEX:
	  	{
	  	MMEXRec *mmex = (MMEXRec*)buf;
		switch (mmex->funcNo)
			{
      		case MMEX_INFO:
      			mmex->longVal = 1;
      			mmex->destPtr = MM_VersionPtr;
      			return 0;

      		case MMEX_GETFREFNUM:
      			// Mac-Datei-Handle liefern
      			mmex->longVal = (long)f->refnum;
      			return 0;
      		}
		}
	}
	return(EINVFN);
}

static LONG dev_getc( MAC_FD *f, WORD mode )
{
	unsigned char c;
	LONG ret;

	ret = dev_read(f, 1L, (void *) &c);
	if	(ret < 0L)
		return(ret);			// Fehler
	if	(!ret)
		return(0x0000ff1a);		// EOF
	return(c & 0x000000ff);
}


static LONG dev_getline( MAC_FD *f, char *buf, WORD mode, LONG size )
{
	unsigned char c;
	LONG gelesen,ret;

	for	(gelesen = 0L; gelesen < size;)
		{
		ret = dev_read(f, 1L, (void *) &c);
		if	(ret < 0L)
			return(ret);			// Fehler
		if	(ret == 0L)
			break;			// EOF
		if	(c == 0x0d)
			continue;
		if	(c == 0x0a)
			break;
		gelesen++;
		*buf++ = c;
		}
	return(gelesen);
}


static LONG dev_putc( MAC_FD *f, WORD mode, LONG val )
{
	unsigned char c;

	c = (unsigned char) val;
	return(dev_write(f, 1L, (void *) &c));
}




/*************************************************************
*
* initialisiert die Strukturen fuer das XFS
*
*************************************************************/

OSErr xfs_init( void )
{
	register int i;
	long	response;


	/* Feststellen, ob unser MacOS Volumes > 4G unterstuetzt */

	has_2TBVols = ((Gestalt(gestaltFSAttr, &response) == noErr) &&
				(response & (1L << gestaltFSSupports2TBVols)));

#if xfs_can_async
	ataridos.version         = 0;			// !AK 8.3.98
	ataridos.flags           = 0;			// !AK 8.3.98
#endif
	ataridos.xfs_sync        = xfs_sync;
	ataridos.xfs_pterm       = xfs_pterm;
	ataridos.xfs_drv_open    = xfs_drv_open;
	ataridos.xfs_drv_close   = xfs_drv_close;
	ataridos.xfs_path2DD     = xfs_path2DD;
	ataridos.xfs_sfirst      = xfs_sfirst;
	ataridos.xfs_snext       = xfs_snext;
	ataridos.xfs_fopen       = xfs_fopen;
	ataridos.xfs_fdelete     = xfs_fdelete;
	ataridos.xfs_link        = xfs_link;
	ataridos.xfs_xattr       = xfs_xattr;
	ataridos.xfs_attrib      = xfs_attrib;
	ataridos.xfs_fchown      = xfs_fchown;
	ataridos.xfs_fchmod      = xfs_fchmod;
	ataridos.xfs_dcreate     = xfs_dcreate;
	ataridos.xfs_ddelete     = xfs_ddelete;
	ataridos.xfs_DD2name     = xfs_DD2name;
	ataridos.xfs_dopendir    = xfs_dopendir;
	ataridos.xfs_dreaddir    = xfs_dreaddir;
	ataridos.xfs_drewinddir  = xfs_drewinddir;
	ataridos.xfs_dclosedir   = xfs_dclosedir;
	ataridos.xfs_dpathconf   = xfs_dpathconf;
	ataridos.xfs_dfree       = xfs_dfree;
	ataridos.xfs_wlabel      = xfs_wlabel;
	ataridos.xfs_rlabel      = xfs_rlabel;
	ataridos.xfs_symlink     = xfs_symlink;
	ataridos.xfs_readlink    = xfs_readlink;
	ataridos.xfs_dcntl       = xfs_dcntl;

#if xfs_can_async
	macdev.version           = 0;					// !AK 8.3.98
#endif
	macdev.dev_close         = dev_close;
	macdev.dev_read          = dev_read;
	macdev.dev_write         = dev_write;
	macdev.dev_stat          = dev_stat;
	macdev.dev_seek          = dev_seek;
	macdev.dev_datime        = dev_datime;
	macdev.dev_ioctl         = dev_ioctl;
	macdev.dev_getc          = dev_getc;
	macdev.dev_getline       = dev_getline;
	macdev.dev_putc          = dev_putc;
	
	macdev.dev_pread         = dev_pread;		// AK 15.2.98
	macdev.dev_pwrite        = dev_pwrite;		// AK 15.2.98

	for  (i = 0; i < NDRVS; i++) {
		xfs_alias[i] = nil;
		drv_fsspec[i].vRefNum = 0;    // ungueltig
//		drv_must_eject[i] = 0;
		drv_changed[i] = 0;
		drv_longnames[i] = false;
	}
	return 0;
}

OSErr xfs_init_after_prefs (void)		// !AK 8.3.98
{
	macdev.flags = UseAsynchronousDiskIO? 1 : 0;	// !AK 8.3.98
	return 0;
}


/*************************************************************
*
* Abbildung der Mac-Verzeichnisse auf XFS-Laufwerke
*
*************************************************************/

static void setDrivebits (long newbits)
{
#ifdef CALAMUS
	newbits |= (1L << ('m'-'a'));	// virtuelles Laufwerk M: immer praesent
#endif
	if (atari32K_logical) {
		*(long*)(&atari32K_logical[_drvbits]) &= -1L-xfs_drvbits;	// alte loeschen
		*(long*)(&atari32K_logical[_drvbits]) |= newbits;			// neue setzen
	}
	xfs_drvbits = newbits;
}

static short Num0DrvOfDrvr (short dRefNum, short drvNum)
{
	short n = 0;
	DrvQElPtr qep = (DrvQElPtr)(GetDrvQHdr()->qHead);
	while (qep) {
		if (qep->dQRefNum == dRefNum) {
			if (qep->dQDrive == drvNum) return n;
			++n;
		}
		qep = (DrvQElPtr)qep->qLink;
	}
	return -1;
}

/*
OSErr VolumeToDrvRef (AliasHandle volumeAlias, MacDrvRef *drvRef)
{
	OSErr err;
	FSSpec spec;
	gAlias = volumeAlias;
	gOnlyMountedVols = false;
	gSpec = &spec;
	drvRef->dRefNum = 0;
	resAlias ();
	err = gErr;
	if (!err) {
		if (spec.parID == 1 || spec.parID == 2 && spec.name[0] == 0) {
			HVolumeParam pb;
			Str31 name;
			pb.ioVolIndex = 0;
			pb.ioNamePtr = name;
			pb.ioVRefNum = spec.vRefNum;
			err = PBHGetVInfoSync ((HParamBlockRec*)&pb);
			if (!err) {
				drvRef->dRefNum = pb.ioVDRefNum;
				drvRef->drvNum0 = Num0DrvOfDrvr (pb.ioVDRefNum, pb.ioVDrvInfo);
			}
		} else {
			err = 1;	// not the root dir
		}
	}
	return err;
}
*/

OSErr VolumeToDrvRef (FSSpec *spec, MacDrvRef *drvRef)
{
	OSErr err;
	drvRef->dRefNum = 0;
	if (spec->parID == 1 || spec->parID == 2 && spec->name[0] == 0) {
		HVolumeParam pb;
		Str31 name;
		pb.ioVolIndex = 0;
		pb.ioNamePtr = name;
		pb.ioVRefNum = spec->vRefNum;
		err = PBHGetVInfoSync ((HParamBlockRec*)&pb);
		if (!err) {
			drvRef->dRefNum = pb.ioVDRefNum;
			drvRef->drvNum0 = Num0DrvOfDrvr (pb.ioVDRefNum, pb.ioVDrvInfo);
		}
	} else {
		err = 1;	// not the root dir
	}
	return err;
}


void SetXFSDrive (short drv, MacXFSDrvType drvType, AliasHandle alias, MacDrvRef *drvrRef, Boolean longnames, Boolean reverseDirOrder)
// !TT 27.4.96: reverseDirOrder neu
{
	long newbits = xfs_drvbits;
	if (drvType == NoMacXFS) {
		if (drv>=2) newbits &= ~(1L << drv);
	} else {
		if (drv>=2) newbits |= 1L << drv;
	}
	drv_changed[drv] = true;
	drv_drvrRef[drv].dRefNum = 0;
	xfs_alias[drv] = alias;
	drv_type[drv] = drvType;
	if (drvType == MacDir) {
		drv_valid[drv] = true;
	} else {
		drv_valid[drv] = false;
		drv_fsspec[drv].vRefNum = 0;
	}
	if (drvType == MacDrive && drvrRef) {
		drv_drvrRef[drv] = *drvrRef;
	}
	drv_longnames[drv] = longnames;
	drv_rvsDirOrder[drv] = reverseDirOrder;
	if (drv>=2) setDrivebits (newbits);
}


Boolean GetXFSRootDir (short drv, short *vRefNum, long *dirID)
// Liefert FSSpec des Root-Verzeichnisses eines MagiC-Laufwerks.
// Dazu muss das Laufwerk allerdings bereits in MagiC geoeffnet/gemountet sein!
{
	*vRefNum = drv_fsspec[drv].vRefNum;
	*dirID = drv_dirID[drv];
	return *vRefNum != 0;
}

void XFSVolUnmounted (ParmBlkPtr pb0)
// Hook in UnmountVol()
// Registriert, wenn ein von XFS benutztes Vol verschwindet, waehrend MM im Vordergrund laeuft
{
	HVolumeParam pb;
	short err;
	
	// Volume ermitteln
	pb.ioNamePtr = pb0->volumeParam.ioNamePtr;
	pb.ioVRefNum = pb0->volumeParam.ioVRefNum;
	pb.ioVolIndex = (pb.ioNamePtr)? -1:0;
	err = PBHGetVInfoSync ((HParamBlockRec*)&pb);
	if (!err && pb.ioVDrvInfo > 2) {	// nicht die Floppy-LWs vom Mac beruecksichtigen
		short drv;
		for (drv = 0; drv < NDRVS; ++drv) {
			if (drv_fsspec[drv].vRefNum == pb.ioVRefNum) {
				drv_changed[drv] = true;
				drv_fsspec[drv].vRefNum = 0;    // ungueltig
				if (drv_type[drv] == MacDrive) drv_valid[drv] = false;
			}
		}
	}
}


static void checkForNewDrive (short drv)
// Aufgabe: prueft, ob ein neues Mac-Volume gemountet wurde.
{
#ifdef CALAMUS
	if	(drv == 'M'-'A')					// Mac-Wurzelverzeichnis
		{
		drv_type[drv] = MacRoot;
		drv_valid[drv] = true;
		drv_dirID[drv] = 0;
		drv_fsspec[drv].vRefNum = -32768;		// ungueltig
		drv_fsspec[drv].parID = 0;
		drv_fsspec[drv].name[0] = EOS;
		xfs_alias[drv] = NULL;
		}
#endif
	if (drv_type[drv] == MacDrive && !drv_valid[drv] && drv_fsspec[drv].vRefNum == 0) {
		HVolumeParam pb;
		short idx = 1, driverRef, err;
		Str31 name;
		do {	// Schleife ueber alle gemounteten Volumes
			pb.ioVolIndex = idx;
			pb.ioNamePtr = name;
			err = PBHGetVInfoSync ((HParamBlockRec*)&pb);
			driverRef = pb.ioVDRefNum;
			if (!err && drv_drvrRef[drv].dRefNum == driverRef &&
				drv_drvrRef[drv].drvNum0 == Num0DrvOfDrvr (driverRef, pb.ioVDrvInfo)
			) {
				FSSpec spec;
				Boolean b;
				spec.vRefNum = pb.ioVRefNum;
				spec.parID = fsRtParID;
				pstrcpy (spec.name, name);
				UpdateAlias (&ThisPath, &spec, xfs_alias[drv], &b);
				drv_valid[drv] = true;
			}
			++idx;
		} while (!err);
	}
}

/*************************************************************
*
* Routinen fuer Diskwechsel (Auswurf durch Dcntl-Aufrufe)
*
*************************************************************/

ulong DriveToDeviceCode (short drv)
{
	short vol;

	if (drv <= 1) {
		// Floppy A: & B:
		return 0x00010000 | (long)(drv+1);	// liefert 1 bzw. 2
	}
	vol  = drv_fsspec[drv].vRefNum;
	if (vol == 0) {
		// evtl. AHDI-Drive?
		if (false) {	// !!! erstmal nicht unterstuetzt.
			return 0x00020000 | drv;
		} else  {
			return 0;
		}
	} else {
		// Es ist ein Mac-Volume - Drive-Nr. ermitteln
		HVolumeParam pb;
		short err, drvNum, driver;
		Str255 name;

		pb.ioVolIndex = 0;
		pb.ioVRefNum = vol;
		pb.ioNamePtr = name;
		err = PBHGetVInfoSync ((HParamBlockRec*)&pb);
		if (err) {
			return 0;
		} else {
			drvNum = pb.ioVDrvInfo;
			driver = pb.ioVDRefNum;
			if ((driver >= -39) && (driver <= -33)) {	// ein SCSI-Device?
				drvNum = driver;
			}
			return 0x00010000 | (ulong)(ushort)drvNum;
		}
	}
}

long EjectDevice (short opcode, long device)
{
	long ret;

	switch (opcode) 
		{
	case 0:
		if	(device == 0)	// Null bedeutet, dass kein Medium da ist!
			return(EDRIVE);
		if	((device >> 16)  == 1)
			{		// Mac-Medium auswerfen
#ifndef NO_FLOPPY_SUPPORT
			if	(!FloppyUnmountAndEject (device & 0xFFFF))
				{
				// Auswurf nicht moeglich, da vermutlich noch Dateien von
				// Mac-Seite her auf dem Volume offen sind.
				return(EACCDN);
				}
			else	return(E_OK);
#else
			return(EDRIVE);
#endif
			}
		else	{		// AHDI-Medium auswerfen
			return(EDRIVE);	// invalid drive (not supported yet!!!)
			}
	default:
		return(EINVFN);
	}
	return ret;
}

/*
* Version von Thomas, 23.3.98
*/

Boolean	GetPathFromFSSpec (FSSpec *spec, char* path, short pathSize)
{
	// Um herauszufinden, ob sich ein Mac-Ordner auf einem der MagiC-Laufwerke
	// befindet, wird einfach geprueft, ob dessen DirID oder eine seiner Parent-Dirs
	// als Root-Dir der MagiC-Laufwerke benutzt wird.
	OSErr	err;
	short	drv;
	long	theDir, theDir2;
	Boolean	isDir, ok = false;
	Boolean	tmpMount[NDRVS], was_changed[NDRVS];

	for (drv = 0; drv < NDRVS; ++drv) {
		tmpMount[drv] = (drv_fsspec[drv].vRefNum == 0);
		if (tmpMount[drv] || drv_changed[drv]) {
			drv_open (drv, true, false);
		}
		was_changed[drv] = drv_changed[drv];
		drv_changed[drv] = false;
	}
	
	err = FSpGetDirectoryID (spec, &theDir, &isDir);
	theDir2 = theDir;
	while (!err && !ok) {
		for (drv = 0; drv < NDRVS; ++drv) {
			if (drv_fsspec[drv].vRefNum == spec->vRefNum && drv_dirID[drv] == theDir) {
				// ein passendes Drive gefunden - nun den Pfad zusammensetzen
				short l;
				theDir = theDir2;
				// Laufwerk in Pfad einsetzen
				vstrcpy (path, "A:");
				path[0] += drv;
				l = strlen (path);
				// Pfad einsetzen
				if (xfs_DD2name (drv, theDir, &path[l], pathSize-l) == E_OK) {
					l = strlen (path);
					if ((l+1) < pathSize) {
						path[l++] = '\\';
						if (!isDir) {
							// Dateinamen anfuegen
							short nameLen = spec->name[0];
							if (nameLen + l < pathSize) {
								strncpy (&path[l], (char*)&spec->name[1], nameLen);
								path[l+nameLen] = 0;	// !TT 21.3.98
								MacFnameToAtariFname ((StringPtr)path+l, (StringPtr)path+l);
								ok = true;
							}
						}
					}
				}
			}
		}
		if (!ok) {
			err = GetParentID (spec->vRefNum, theDir, nil, &theDir);	// weiter mit Parent-Dir
		}
	}

	for (drv = 0; drv < NDRVS; ++drv) {
		if (tmpMount[drv]) {
			xfs_drv_close (drv, 0);
		}
		drv_changed[drv] = was_changed[drv];
	}
	
	return ok;
}

#if 0
Boolean	GetPathFromFSSpec (FSSpec *spec, char* path, short pathSize)
{
	// Um herauszufinden, ob sich ein Mac-Ordner auf einem der MagiC-Laufwerke
	// befindet, wird einfach geprueft, ob dessen DirID oder eine seiner Parent-Dirs
	// als Root-Dir der MagiC-Laufwerke benutzt wird.
	OSErr	err;
	short	drv;
	long	theDir, theDir2;
	Boolean	isDir, ok = false;
	Boolean	tmpMount[NDRVS], was_changed[NDRVS];

	for (drv = 0; drv < NDRVS; ++drv) {
		tmpMount[drv] = (drv_fsspec[drv].vRefNum == 0);
		if (tmpMount[drv] || drv_changed[drv]) {
			drv_open (drv, true, false);
		}
		was_changed[drv] = drv_changed[drv];
		drv_changed[drv] = false;
	}
	
	err = FSpGetDirectoryID (spec, &theDir, &isDir);
	theDir2 = theDir;
	while (!err && !ok) {
		for (drv = 0; drv < NDRVS; ++drv) {
			if (drv_fsspec[drv].vRefNum == spec->vRefNum && drv_dirID[drv] == theDir) {
				// ein passendes Drive gefunden - nun den Pfad zusammensetzen
				short l;
				theDir = theDir2;
				// Laufwerk in Pfad einsetzen
				vstrcpy (path, "A:");
				path[0] += drv;
				l = strlen (path);
				// Pfad einsetzen
				if (xfs_DD2name (drv, theDir, &path[l], pathSize-l) == E_OK) {
					l = strlen (path);
					if ((l+1) < pathSize) {
						path[l++] = '\\';
						if (!isDir) {
							// Dateinamen anfuegen
							if (spec->name[0] + l < pathSize) {
								strncpy (&path[l], (char*)&spec->name[1], spec->name[0]);
								path[strlen(path)] = 0;
								MacFnameToAtariFname ((StringPtr)path+l, (StringPtr)path+l);
								ok = true;
							}
						}
					}
				}
			}
		}
		if (!ok) {
			err = GetParentID (spec->vRefNum, theDir, nil, &theDir);	// weiter mit Parent-Dir
		}
	}

	for (drv = 0; drv < NDRVS; ++drv) {
		if (tmpMount[drv]) {
			xfs_drv_close (drv, 0);
		}
		drv_changed[drv] = was_changed[drv];
	}
	
	return ok;
}
#endif
