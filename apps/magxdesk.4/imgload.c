/*
	Tabulatorweite: 3
	Kommentare ab: Spalte 60											*Spalte 60*
*/

#include	<MGX_DOS.H>
#include	<STDDEF.H>
#include	<STRING.H>

#include "imgload.h"

typedef struct
{
	WORD	version;
	WORD	length;
	WORD	planes;
	WORD	pattern_length;
	WORD	pix_width;
	WORD	pix_height;
	WORD	w;
	WORD	h;
} IMGHDR;

static LONG open_img( char *name );
static WORD close_img( void );
static void unpack_line( UBYTE *des );
static void fill_img_buf( void );
static UBYTE *unpack_line1( UBYTE *img, UBYTE *des, WORD pat_len, WORD len );
static UBYTE *unpack_line2( UBYTE *img, UBYTE *des, WORD pat_len, WORD len );

static UBYTE *img_buf;			/* Zeiger auf IMG-Buffer */
static WORD unpacked_lines;		/* Anzahl der entpackten Zeilen */
static LONG buf_len;			/* Bufferl�nge */
static LONG buf_used;			/* Anzahl der benutzten Bytes */
static LONG buf_offset;			/* Abstand zum Bufferanfang */
static WORD fd;				/* GEMDOS-Handle des IMGs */
static void *external_buf;
static WORD pat_len;			/* L�nge eines Musters in Bytes */
static WORD line_len;			/* L�nge einer Zeile in Bytes */
static WORD img_pl;
static LONG d_len;				/* verbleibende Dateil�nge */

static IMGHDR	head;

/*--------------------------------------------------------------------------------*/ 
/* IMG laden und entpacken																						*/
/* Funktionsresultat:	Zeiger auf das entpackte IMG (liegt im Standardformat vor!)			*/
/*	name:						Dateiname																			*/
/*	w:							hier wird die Breite in Pixeln zur�ckgeliefert							*/
/*	h:							hier wird die H�he in Zeilen zur�ckgeliefert								*/
/*	line_width:				hier wird die Zeilenbreite in Bytes zur�ckgeliefert					*/
/*	planes:					hier wird die Anzahl der Ebenen zur�ckgeliefert							*/
/* palette:					Zeiger auf Zeiger auf Palettendaten (0: keine Palette vorhanden)	*/
/*	pal_entries:			Anzahl der Eintr�ge in der Palette 											*/
/*----------------------------------------------------------------------------------------*/ 
LONG load_IMG( BYTE *name, WORD *w, WORD *h,
			WORD *line_width, WORD *planes,
			WORD **palette, WORD *pal_entries,
			UBYTE **img )
{
	LONG retcode;
	UBYTE	*buf;
	UBYTE	*des;
	LONG	plane_len;


	*img = NULL;
	retcode = open_img( name );
	if	(retcode < 0)
		return(retcode);

	*w = head.w;														/* Breite in Pixeln */
	*h = head.h;														/* H�he in Zeilen */
	*line_width = (( head.w + 15 ) & 0xfff0) / 8;	/* Breite in Bytes (Vielfaches von 2) */
	*planes = head.planes;											/* Anzahl der Ebenen */
	*palette = 0L;														/* keine Palettendaten */
	*pal_entries = 0;													/* keine Eintr�ge */

	plane_len = (LONG) ( *line_width ) * head.h;		/* L�nge einer Ebene */

	if	( head.length > ( sizeof(IMGHDR) / 2 ))		/* m�glicherweise XIMG? */
		{
		BYTE	identify[6];

		Fseek( sizeof( IMGHDR ), fd, 0 );					/* Dateiheader �berspringen */
		Fread( fd, 6, identify );
		if	( *(LONG *) identify == 'XIMG' )						/* XIMG-Kennung vorhanden? */
			{
			LONG	pal_len;
			
			pal_len = (head.length * 2 ) - 6 - sizeof( IMGHDR );	/* L�nge der Palette in Bytes */
			
			if ( pal_len > ( 256 * 6 ))
				pal_len = 256 * 6;
			
			*palette = Malloc( pal_len );							/* Speicher f�r Palette anfordern */
			if ( *palette )
			{
				*pal_entries = (WORD) pal_len / 6;				/* Anzahl der Paletteneintr�ge */
				Fread( fd, pal_len, *palette );				/* Palettendaten einlesen */
			}
			}
		Fseek( head.length * 2, fd, 0 );					/* Dateiheader �berspringen */
		}

	des = Malloc( plane_len * head.planes );					/* Buffer f�r entpacktes Bild anfordern */
	buf = Malloc((LONG) (*line_width) * head.planes );		/* Buffer f�rs Entpacken einer Zeile */

	if	(( buf == 0L ) && ( des ))									/* konnte der Zeilenbuffer nicht angefordert werden? */
		{
		Mfree( des );
		des = 0L;
		}	
	
	if	( des )
		{
		WORD	y;
		UBYTE	*tmp;
		
		tmp = des;
		
		for	( y = 0; y < head.h; y++ )
			{
			WORD	plane;
			UBYTE	*src;
			UBYTE	*dst;
			
			unpack_line( buf );										/* komplette Zeile in den Buffer entpacken */
			
			src = buf;
			dst = tmp;				
			
			for ( plane = 0; plane < head.planes; plane++ )
			{
				memcpy( dst, src, line_len );						/* Ebene in den Bildbuffer kopieren */
				src += line_len;
				dst += plane_len;
			}
			
			tmp += *line_width;										/* n�chste Zeile */
			}
		}

	if ( buf )
		Mfree( buf );													/* Zeilenbuffer freigeben */

	close_img();

	*img = des;
	return( E_OK );
}

/*----------------------------------------------------------------------------------------*/ 
/* IMG-Datei �ffnen																								*/
/* Funktionsresultat:	1: alles in Ordung 0: Fehler													*/
/* name:						Dateiname																			*/
/*----------------------------------------------------------------------------------------*/ 
static LONG open_img( char *path )
{
	XATTR xa;
	LONG retcode;


	retcode = Fopen( path, FO_READ );
	if	(retcode < 0)
		return(retcode);
	fd = (WORD) retcode;
	retcode = Fcntl(fd, (long) &xa, FSTAT);
	if	(!retcode)
		d_len = xa.size;
	else	goto err;

	external_buf = Malloc( d_len );	/* Puffer anfordern */

	if	( !external_buf )
		{
		retcode = ENSMEM;
		err:
		Fclose(fd);
		return(retcode);
		}

	img_buf = external_buf;
	buf_len = d_len;
			
	Fread( fd, sizeof( IMGHDR ), &head );
	Fseek( head.length * 2, fd, 0 );		/* Dateiheader �berspringen */
	d_len -= head.length * 2;		/* verbleibende Dateil�nge korrigieren */
	fill_img_buf();				/* Buffer auff�llen */
	pat_len = head.pattern_length;	/* Bytes pro Muster */
	line_len = ( head.w + 7 ) / 8;	/* L�nge einer IMG-Zeile in Bytes */
	img_pl = head.planes;
	unpacked_lines = 0;				/* noch keine Zeile entpackt */

	return( E_OK );
}

/*----------------------------------------------------------------------------------------*/ 
/* IMG-Datei schlie�en																							*/
/* Funktionsresultat:	1																						*/
/*----------------------------------------------------------------------------------------*/ 
static WORD close_img( void )
{
	if ( external_buf )													/* Buffer �ber Malloc alloziert? */
		Mfree( external_buf );

	Fclose( fd );
	return( 1 );
}

/*----------------------------------------------------------------------------------------*/ 
/* IMG-Zeile auspacken																							*/
/* Funktionsresultat:	-																						*/
/*----------------------------------------------------------------------------------------*/ 
static void unpack_line( UBYTE *des )
{
	UBYTE	*img_line;
	LONG	read;
	
	if ( unpacked_lines < head.h )									/* sind noch gepackte Zeilen vorhanden? */
	{
		img_line = img_buf + buf_offset;
		read = (LONG) ( unpack_line1( img_line, des, pat_len, line_len * head.planes ) - img_line );
		buf_used -= read;													/* Anzahl der g�ltigen Bytes im Buffer */
		buf_offset += read;												/* Abstand zum Bufferstart */
		unpacked_lines++;													/* eine weitere Zeile ist entpackt worden */
	}
}

/*----------------------------------------------------------------------------------------*/ 
/* Buffer zum ersten Mal f�llen																				*/
/* Funktionsresultat:	-																						*/
/*----------------------------------------------------------------------------------------*/ 
static void fill_img_buf( void )
{
	LONG	read;

	read = buf_len;														/* Buffer komplett f�llen */
	if ( read > d_len )													/* mehr Bytes als die Datei lang ist? */
		read = d_len;	

	buf_offset = 0;														/* Bufferstart */	
	buf_used = Fread( fd, read, img_buf );	/* einlesen */
	d_len -= buf_used;													/* noch vorhandene Dateil�nge verkleinern */
}

/*----------------------------------------------------------------------------------------*/ 
/* Zeile eines IMGs entpacken																					*/
/* Funktionsresultat:	Zeiger auf die n�chste Zeile im IMG-Format								*/
/*	img:						Zeiger auf die IMG-Zeile														*/
/*	des:						Zeiger auf die Zielbitmap														*/
/*	pat_len:					L�nge eines IMG-Muster in Bytes												*/
/*	len:						L�nge einer entpackten Zeile in Bytes										*/
/*----------------------------------------------------------------------------------------*/ 
static UBYTE *unpack_line1( UBYTE *img, UBYTE *des, WORD pat_len, WORD len )
{
	if (( img[0] == 0 ) && ( img[1] == 0 ) && ( img[2] == 0xff ))	/* vertikale Wiederholung? */
	{
		if ( img[3] > 1 )													/* mehr als eine Zeile? */
		{
			unpack_line2( img + 4, des, pat_len, len );
			img[3] -= 1;													/* eine Wiederholung weniger */
			return( img );
		}
		else
			return( unpack_line2( img + 4, des, pat_len, len ));
	}
	else
		return( unpack_line2( img, des, pat_len, len ));
}

/*----------------------------------------------------------------------------------------*/ 
/* Zeile eines IMGs entpacken, vertikale Wiederholfaktoren d�rfen nicht vorkommen			*/
/* Funktionsresultat:	Zeiger auf die n�chste Zeile im IMG-Format								*/
/*	img:						Zeiger auf die IMG-Zeile														*/
/*	des:						Zeiger auf die Zielbitmap														*/
/*	pat_len:					L�nge eines IMG-Muster in Bytes												*/
/*	len:						L�nge einer entpackten Zeile in Bytes										*/
/*----------------------------------------------------------------------------------------*/ 
static UBYTE *unpack_line2( UBYTE *img, UBYTE *des, WORD pat_len, WORD len )
{
	WORD	i;
	UWORD	cnt;

	while ( len > 0 )														/* komplette Zeile abgearbeitet? */
	{
		UBYTE	tag;
		
		tag = *img++;
		
		if ( tag == 0 )													/* Pattern Run? */
		{
			cnt = *img++;													/* Anzahl der Wiederholungen */
			
			for ( i = 0; i < cnt; i++ )
			{
				WORD	j;
				for ( j = 0; j < pat_len; j++ )
					*des++ = img[j];
			}
																							
			img += pat_len;												/* Musterdaten �berspringen */
			cnt *= pat_len;												/* L�nge des Musters */
		}
		else if ( tag == 0x80 )											/* Bit String? */
		{
			cnt = *img++;													/* Anzahl der unkomprimierten Bytes */
		
			for ( i = 0; i < cnt; i++ )
				*des++ = *img++;
		}
		else if (( tag & 0x80 ) == 0 )								/* wei�er Solid Run? */
		{
			cnt = tag & 0x7f;												/* Anzahl der Wiederholungen */
			
			for ( i = 0; i < cnt; i++ )
				*des++ = 0;
		}
		else																	/* schwarzer Solid Run */
		{
			cnt = tag & 0x7f;												/* Anzahl der Wiederholungen */
			
			for ( i = 0; i < cnt; i++ )
				*des++ = 0xff;
		}	

		len -= cnt;															/* Anzahl der noch vorhandenen Bytes */
	}
	return( img );
}
