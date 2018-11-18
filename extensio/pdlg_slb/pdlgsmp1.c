/*
	Tabulatorweite: 3
	Kommentare ab: Spalte 60											*Spalte 60*
*/

/*----------------------------------------------------------------------------------------*/ 
/* Globale Includes																								*/
/*----------------------------------------------------------------------------------------*/ 
#include <portab.h>
#include <tos.h>
#include <vdi.h>
#include <mt_aes.h>

#include <string.h>
#include <stdio.h>

#include "pdsmprsc.h"

/*----------------------------------------------------------------------------------------*/ 
/* Prototypen																										*/
/*----------------------------------------------------------------------------------------*/ 
static WORD	is_macprn( WORD handle, WORD id );
void	print_sample( PRN_SETTINGS *settings );

PRN_SETTINGS	*read_psettings( PRN_DIALOG *prn_dialog );
WORD	save_psettings( PRN_SETTINGS *settings );

WORD	open_print_dialog( PRN_SETTINGS *settings, BYTE *document_name, WORD kind );
WORD	close_print_dialog( void );

void	menu_selected( WORD title, WORD entry );
void	handle_keybd( WORD keycode, WORD kstate );
void	handle_message( WORD msg[8] );
void	event_loop( void );

void	init_rsrc( void );
WORD	wlfp_available( void );

/*----------------------------------------------------------------------------------------*/ 
/* Globale Variablen																								*/
/*----------------------------------------------------------------------------------------*/ 

WORD	app_id;
WORD	aes_handle;
WORD	pwchar;
WORD	phchar;
WORD	pwbox;
WORD	phbox;

RSHDR		*rsh;
BYTE		**fstring_addr;
OBJECT	**tree_addr;
WORD		tree_count;
OBJECT	*menu_tree;

WORD	quit;

/*----------------------------------------------------------------------------------------*/ 
/* Informationen �ber den Druckdialog																		*/
/* In einer ausgewachsenen Applikation sollten diese Variablen in einer Struktur 			*/
/*	gekapselt werden, damit es nicht zu un�bersichtlich wird											*/
/*----------------------------------------------------------------------------------------*/ 
PRN_SETTINGS	*gprn_settings;
PRN_DIALOG		*gprn_dialog;
WORD				gprn_whdl;
WORD				gprn_x;
WORD				gprn_y;
WORD				gprn_is_print_dialog;

/*----------------------------------------------------------------------------------------*/ 
/* Abtesten, ob der Treiber MACPRN.SYS ist																*/
/* Funktionsresultat:	1: ist MACPRN.SYS																	*/
/*	handle:					Handle des Druckers																*/
/*	id:						Treibernummer																		*/
/*																														*/
/*	Bemerkung:																										*/
/*	Der alte MACPRN liefert die Orientierung nicht korrekt zur�ck, obwohl der Treiber die	*/
/*	Seite drehen kann.																							*/
/*----------------------------------------------------------------------------------------*/ 
static WORD	is_macprn( WORD handle, WORD id )
{
	VDIPB	pb;
	WORD	contrl[16];
	WORD	intin[1];
	WORD	ptsin[1];
	WORD	intout[64];
	WORD	ptsout[64];

	contrl[0] = 248;														/* Funktionsnummer */
	contrl[1] = 0;
	contrl[3] = 1;															/* ID wird �bergeben */
	contrl[5] = 0;
	contrl[6] = handle;

	intin[0] = id;

	pb.control = contrl;
	pb.intin = intin;
	pb.ptsin = ptsin;
   pb.intout = intout;
	pb.ptsout = ptsout;

   vdi( &pb );

	if ( contrl[4] && intout[0] )										/* Treiber vorhanden? */
	{
		BYTE	macprn[6] = { 'M','A','C','P','R','N' };
		WORD	i;
		WORD	len;

		len = contrl[4];
		if ( len > 6 )
			len = 6;															/* nur die ersten 6 Buchstaben abtesten */
		
		for ( i = 0; i < len; i++ )
		{
        if ( intout[i] != macprn[i] )
        {
 	       if ( intout[i] != ( macprn[i] + ( 'a' - 'A' )))
					return( 0 );											/* ist nicht MACPRN */
			}
		}
		return( 1 );
   }
	return( 0 );
}

/*----------------------------------------------------------------------------------------*/ 
/* Rumpffunktion f�r Druckausgabe																			*/
/* Funktionsresultat:	-																						*/
/*	settings:				Druckereinstellung																*/
/*----------------------------------------------------------------------------------------*/ 
void	print_sample( PRN_SETTINGS *settings )
{
#if 0
	WORD	prn_work_out[57];
	WORD	prn_handle;

	prn_handle = v_opnprn( aes_handle, settings, prn_work_out );

	if ( prn_handle )														/* konnte der Druckertreiber ge�ffnet werden? */
	{
		WORD	page_inc;
		WORD	no_copies;
		WORD	do_landscape;
		WORD	page;

#if 0
		/* 
			Der Metafile-Treiber ben�tigt die folgenden drei
			Aufrufe, damit Programme den Metafile korrekt skalieren
			und anzeigen k�nnen. Der Metafile-Treiber unterscheidet
			sich auch insofern von allen anderen Treibern, als da�
			er keine vrt/vro_cpyfm()-Aufrufe erlaubt.
		*/

		if ( settings->driver_id == 31 )								/* Metafile? */
		{
			v_meta_extents( prn_handle, x_min, y_min, x_max, y_max );	/* umgebendes Rechteck */
			vm_pagesize( prn_handle, pgwidth, pgheight );		/* Seitenausma�e */
			vm_coords( prn_handle, llx, lly, urx, ury );			/* Koordinatensystem */
		}
#endif

		if ( settings->first_page > settings->last_page )		/* r�ckw�rts drucken? */
			page_inc = -1;
		else																	/* aufsteigende Seitenreihenfolge */
			page_inc = 1;

		if ( v_copies( prn_handle, -1 ) <= 1 )						/* kann der Treiber keine Kopien erzeugen? */
			no_copies = settings->no_copies;
		else																	/* Treiber fertigt selber Kopien an */
			no_copies = 1;

		do_landscape = 0;													/* Treiber sorgt f�r Drehung */
		if ( settings->orientation == PG_LANDSCAPE )				/* Querformat eingestellt? */
		{
			if ( v_orient( prn_handle, -1 ) != 1 )					/* kein Querformat eingestellt? */
			{
				if ( is_macprn( prn_handle, settings->driver_id ) == 0 )
					do_landscape = 1;										/* selber drehen */
			}
		}

		for ( page = settings->first_page; page <= settings->last_page; page += page_inc )
		{
			if (((( page & 1 ) == 0 ) && ( settings->page_flags & PG_EVEN_PAGES )) ||	/* gerade Seitennummern erlaubt? */
				 (( page & 1 ) && ( settings->page_flags & PG_ODD_PAGES )))					/* ungerade Seitennummern erlaubt? */
			{
				WORD	copy;
				
				for ( copy = 0; copy < no_copies; copy++ )		/* Schleife f�r Treiber, die keine Kopien erstellen k�nnen */
				{
					if ( do_landscape )									/* kann der Treiber kein Querformat ausgeben? */
					{
						/* hier w�re Ausgabe mit gedrehtem Koordinatensystem angesagt */
					}
					else														/* Treiber sorgt f�r die Querausgabe */
					{
						/* normal ausgeben */
					}
					
					v_updwk( prn_handle );								/* Seite aufbauen */
					v_clrwk( prn_handle );								/* Seitenvorschub */
				}
			}
		}
	
		v_clswk( prn_handle );											/* Treiber wieder schlie�en */
	}		
#else
	(void) settings;
	form_alert( 1, fstring_addr[PRINT_ALERT] );
#endif
}

/*----------------------------------------------------------------------------------------*/ 
/* Gespeicherte Druckereinstellung zur�ckliefern														*/
/* Funktionsresultat:	Zeiger auf Druckereinstellung oder 0L										*/
/*	prn_dialog:				Zeiger auf Verwaltungsstruktur (wenn dauerhaft ge�ffnet) oder 0L	*/
/*----------------------------------------------------------------------------------------*/ 
PRN_SETTINGS	*read_psettings( PRN_DIALOG *prn_dialog )
{
	PRN_DIALOG		*p;
	PRN_SETTINGS	*settings;

	settings = 0L;

	if ( prn_dialog == 0L )												/* noch nicht offen? */
	{
		p = pdlg_create( 0 );											/* kurzzeitig �ffnen */
		if ( p == 0L ) 
			return( 0L );
	
		prn_dialog = p;
	}
	else
		p = 0L;

#if 0	
	
	Wenn das Programm die Einstellungen in einer Datei gespeichert h�tte,
	sollte der folgende Code benutzt werden:
	
	settings = read_settings_from_file();							/* Einstellungen aus programmeigener Datei holen */
	
	if ( settings )
	{
		if ( pdlg_validate_settings( prn_dialog, settings ) == 0 )	/* schwerwiegender Fehler? */
		{
			Mfree( settings );
			settings = 0L;
		}		
	}
#endif

	if ( settings == 0L )
	{
		settings = 	Malloc( pdlg_get_setsize());					/* Speicherbereich anfordern */
		
		if ( settings )
			pdlg_dflt_settings( prn_dialog, settings );			/* und initialisieren */
	}
	
	if ( p )																	/* nur kurzzeitig ge�ffnet? */
		pdlg_delete( p );

	return( settings );
}

/*----------------------------------------------------------------------------------------*/ 
/* Druckereinstellung speichern																				*/
/* Funktionsresultat:	1: alles in Ordnung																*/
/*	settings:				Druckereinstellung																*/
/*----------------------------------------------------------------------------------------*/ 
WORD	save_psettings( PRN_SETTINGS *settings )
{
	if ( settings )
	{
		#if 0
	
		Wenn das Programm die Einstellungen in einer Datei speichern w�rde,
		sollte der folgende Code benutzt werden:
		
		write_settings_to_file( settings );							/* Druckereinstellung speichern */
		
		#endif
	
		Mfree( settings );												/* Speicher freigeben */
		return( 1 );
	}
	
	return( 0 );
}

/* Hoch/Querformat, Kopien und gerade/ungerade Seiten anbieten */
#define	PRINT_FLAGS	PDLG_ALWAYS_ORIENT + PDLG_ALWAYS_COPIES /*+ PDLG_ALWAYS_SCALE*/ + PDLG_EVENODD

/*----------------------------------------------------------------------------------------*/ 
/* Druckdialog �ffnen																							*/
/* Funktionsresultat:	Fensterhandle																		*/
/*	settings:				Druckereinstellung																*/
/*	document_name:			Dokumentenname																		*/
/*	kind:						PDLG_PREFS: Einstelldialog PDLG_PRINT: Druckdialog						*/
/*----------------------------------------------------------------------------------------*/ 
WORD	open_print_dialog( PRN_SETTINGS *settings, BYTE *document_name, WORD kind )
{
	extern PRN_DIALOG	*gprn_dialog;
	extern WORD gprn_whdl;
	extern WORD gprn_x;
	extern WORD gprn_y;
	
	if ( gprn_dialog )													/* Dialog bereits ge�ffnet? */
	{
		wind_set( gprn_whdl, WF_TOP, 0, 0, 0, 0 );				/* Fenster nach vorne bringen */
		return( gprn_whdl );
	}
	else
	{
		gprn_dialog = pdlg_create( PDLG_3D );						/* Speicher anfordern, Treiber scannen */
		if ( gprn_dialog )
		{
			gprn_whdl = pdlg_open( gprn_dialog, settings, document_name, PRINT_FLAGS + kind, gprn_x, gprn_y );
	
			if ( gprn_whdl )
				return( gprn_whdl );
			else																/* Fehler beim �ffnen des Fensters */
			{
				pdlg_delete( gprn_dialog );							/* Speicher freigeben */
				gprn_dialog = 0L;
			}
		}
	}
	return( 0 );
}

/*----------------------------------------------------------------------------------------*/ 
/* Druckdialog schlie�en																						*/
/* Funktionsresultat:	0: Fehler 1: alles in Ordnung													*/
/*----------------------------------------------------------------------------------------*/ 
WORD	close_print_dialog( void )
{
	extern PRN_DIALOG	*gprn_dialog;
	extern WORD gprn_x;
	extern WORD gprn_y;
	
	if ( gprn_dialog )													/* Dialog ge�ffnet? */
	{
		pdlg_close( gprn_dialog, &gprn_x, &gprn_y );				/* Fenster schlie�en, Position merken */
		pdlg_delete( gprn_dialog );									/* Speicher freigeben */
		gprn_dialog = 0L;
		return( 1 );
	}
	return( 0 );
}

/*----------------------------------------------------------------------------------------*/ 
/* Auf angeklickten Men�eintrag reagieren																	*/
/* Funktionsresultat:	-																						*/
/*	title:					Objektnummer des Men�titels													*/
/*	entry:					Objektnummer des Men�punktes													*/
/*----------------------------------------------------------------------------------------*/ 
void	menu_selected( WORD title, WORD entry )
{
	menu_tnormal( menu_tree, title, 0 );							/* Men�titel selektieren */
	
	switch( entry )
	{
		case	DLAYOUT:
		{
			form_alert( 1, fstring_addr[LAYOUT_ALERT] );
			break;
		}
		case	DPAPER:
		{
	
			menu_ienable( menu_tree, DPRINT, 0 );				/* "Drucken" ist nicht anw�hlbar */
			open_print_dialog( gprn_settings, fstring_addr[S_NONAME], PDLG_PREFS );	/* Einstelldialog �ffnen */
			gprn_is_print_dialog = 0;									/* Einstelldialog wird angezeigt */
			break;
		}
		case	DPRINT:
		{
			menu_ienable( menu_tree, DPAPER, 0 );					/* "Papierformat" ist nicht anw�hlbar */
			open_print_dialog( gprn_settings, fstring_addr[S_NONAME], PDLG_PRINT );	/* Druckdialog �ffnen */
			gprn_is_print_dialog = 1;									/* Druckdialog wird angezeigt */
			break;
		}
		case	DQUIT:
		{
			if ( gprn_dialog )											/* Dialog noch offen? */
				close_print_dialog();

	 		quit = 1;
	 		break;
		}
	}
	menu_tnormal( menu_tree, title, 1 );							/* Men�titel deselektieren */
}

/*----------------------------------------------------------------------------------------*/ 
/* Auf Tastendruck reagieren																					*/
/* Funktionsresultat:	-																						*/
/*	keycode:					ist events->key																	*/
/*	kstate:					ist events->kstate																*/
/*----------------------------------------------------------------------------------------*/ 
void	handle_keybd( WORD keycode, WORD kstate )
{
	if ( kstate == K_CTRL )
	{
		switch ( keycode & 0xff )
		{
			case 'P'-64:	menu_selected( MFILE, DPRINT );	break;
			case 'Q'-64:	menu_selected( MFILE, DQUIT );	break;
		}
	}
}

/*----------------------------------------------------------------------------------------*/ 
/* AES-Nachrichten bearbeiten																					*/
/* Funktionsresultat:	-																						*/
/*	msg:						Zeiger auf den Nachrichtenpuffer												*/
/*----------------------------------------------------------------------------------------*/ 
void	handle_message( WORD msg[8] )
{
	switch ( msg[0] )
	{
		case	MN_SELECTED:	menu_selected( msg[3], msg[4] ); break;
	}
}

void	event_loop( void )
{
	EVNT	events;
	
	quit = 0;
	
	while ( quit == 0 )
	{
		EVNT_multi( MU_KEYBD + MU_BUTTON + MU_MESAG, 2, 1, 1,	0L, 0L, 0L, &events );

		if ( events.mwhich & MU_KEYBD )
			handle_keybd( events.key, events.kstate );

		if ( events.mwhich & MU_MESAG )
			handle_message( events.msg );

		if ( gprn_dialog )
		{
			WORD	button;

			if ( pdlg_evnt( gprn_dialog, gprn_settings, &events, &button ) == 0 )	/* Dialog schlie�en? */
			{
				close_print_dialog();									/* Dialog schlie�en */

				if ( gprn_is_print_dialog )							/* Druckdialog? */
				{
					menu_ienable( menu_tree, DPAPER, 1 );			/* "Papierformat" ist wieder anw�hlbar */

					if ( button == PDLG_OK )							/* "Drucken" angew�hlt? */
						print_sample( gprn_settings );
				}
				else															/* Einstelldialog */
					menu_ienable( menu_tree, DPRINT, 1 );		/* "Drucken" ist wieder anw�hlbar */
			}
		}
	}
}

/*----------------------------------------------------------------------------------------*/ 
/* Resource und dazugeh�rige Strukturen initialisieren												*/
/*----------------------------------------------------------------------------------------*/ 
void	init_rsrc( void )
{
	rsh = *((RSHDR **)(&_GemParBlk.global[7]));					/* Adresse des Resource-Headers �ber global[7/8] holen */

	tree_addr = (OBJECT **)(((UBYTE *)rsh) + rsh->rsh_trindex);	/* Zeiger auf die Objektbaumtabelle holen */
	tree_count = rsh->rsh_ntree;										/* und Anzahl der Objektb�ume (von 1 ab gez�hlt) bestimmen */
	fstring_addr = (BYTE **)((UBYTE *)rsh + rsh->rsh_frstr);

	menu_tree = tree_addr[MENU];

	/* hier k�nne ggf. adaptrsc aufgrufen werden */
}

/*----------------------------------------------------------------------------------------*/ 
/* Testen, ob wdlg_xx()/lbox_xx()/fnts_xx()/pdlg_xx()-Funktionen vorhanden sind				*/
/* Funktionsresultat:	1: vorhanden, 0: nicht vorhanden												*/
/*----------------------------------------------------------------------------------------*/ 
WORD	wlfp_available( void )
{
	if ( appl_find( "?AGI" ) == 0 )									/* appl_getinfo() vorhanden? */
	{
		WORD	ag1;
		WORD	ag2;
		WORD	ag3;
		WORD	ag4;

		if ( appl_getinfo( 7, &ag1, &ag2, &ag3, &ag4 ))			/* Unterfunktion 7 aufrufen */
		{
			if (( ag1 & 0x17 ) == 0x17 )								/* wdlg_xx()/lbox_xx()/fnts_xx()/pdlg_xx() vorhanden? */
				return( 1 );
		}	
	}
	return( 0 );
}

/*----------------------------------------------------------------------------------------*/ 
/* Hauptprogramm																									*/
/*----------------------------------------------------------------------------------------*/ 
WORD	main( void )
{
	extern WORD	app_id;
	extern WORD	aes_handle;
	extern WORD	pwchar;
	extern WORD	phchar;
	extern WORD	pwbox;
	extern WORD	phbox;
	
	app_id = appl_init();

	if( app_id != -1 )													/* Anmeldung erfolgreich? */
	{
		aes_handle = graf_handle( &pwchar, &phchar, &pwbox, &phbox );
		graf_mouse( ARROW, 0L );									/* Mauszeiger anschalten */

		if( rsrc_load( "pdsmprsc.rsc" ) )
		{
			init_rsrc();												/* Resource anpassen */

			if ( wlfp_available())											/* Dialogroutinen vorhanden? */
			{
				gprn_settings = read_psettings( 0L );				/* Druckereinstellung einlesen/erzeugen */
				gprn_dialog = 0L;
				gprn_x = -1;												/* Fenster anf�nglich zentrieren */
				gprn_y = -1;

				menu_bar( menu_tree, 1 );								/* Men�leiste anzeigen */
				event_loop();
				menu_bar( menu_tree, 0 );								/* Men�leiste nicht mehr anzeigen */

				save_psettings( gprn_settings );						/* Druckereinstellung speichern */
			}
			else
				form_alert( 1, fstring_addr[AL_WDIALOG] );
			rsrc_free();
		}	
		appl_exit();
	}
	return( 0 );
}
