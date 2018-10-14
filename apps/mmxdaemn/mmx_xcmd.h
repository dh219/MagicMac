/*********************************************************************
*
* Diese Daten enth�lt die Schnittstelle, um von einem Atari-Programm
* aus unter MagicMacX PPC-native Funktionen aufzurufen.
*
*********************************************************************/

typedef INT32(XCMD_CMD)(struct strXCMD *pCmd);
typedef INT32(XCMD_EXEC)(UINT32 SymPtr, void *pParams);
typedef INT32(MMX_DAEMN)(UINT16 cmd, void *pParams);

struct MgMxCookieData
{
	UINT32	mgmx_magic;		/* ist "MgMx" */
	UINT32	mgmx_version;		/* Versionsnummer */
	UINT32	mgmx_len;			/* Strukturl�nge */
	XCMD_CMD	*mgmx_xcmd;		/* PPC-Bibliotheken laden und verwalten */
	XCMD_EXEC	*mgmx_xcmd_exec;	/* PPC-Aufruf aus PPC-Bibliothek */
	UINT32	mgmx_internal;
	MMX_DAEMN *mgmx_daemon;
};

/* Befehlsformat f�r XCmd-Kommandos: */
enum eXCMD