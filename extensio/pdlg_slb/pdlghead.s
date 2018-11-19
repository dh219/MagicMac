/*
*
* Header f�r eine "shared library"
* Wird statt des Start-Codes von PureC verwendet
*
* Es sollte _dringend_ sichergestellt werden, da� Bit 3
* der Flags im Programmheader gesetzt ist, damit sich die
* Bibliothek nicht den gesamten freien Speicher reserviert.
*
* Andreas Kromke
* 22.10.97
*
*/

	XREF	slb_init
	XREF slb_exit
	XREF slb_open
	XREF slb_close

	TEXT

DC.L		$70004afc			; magischer Wert
DC.L		name				; Zeiger auf Namen der Bibliothek
DC.L		2				; Versionsnummer
DC.L		0				; Flags, z.Zt. 0L
DC.L		slb_init			; wird nach dem Laden aufgerufen
DC.L		slb_exit			; wird vor dem Entfernen aufgerufen
DC.L		slb_open			; wird beim �ffnen aufgerufen
DC.L		slb_close			; wird beim Schlie�en aufgerufen
DC.L		0				; Zeiger auf Prozedurnamen (optional)
DC.L		0,0,0,0,0,0,0,0	; unbenutzt, immer NULL
DC.L		0				; Anzahl der Funktionen (keine!)

name:		DC.B	'PDLG.SLB',0

	even
	dc.w $4afc

	END
