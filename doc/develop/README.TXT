�bersicht �ber die MagiC Dokumentation
======================================

Stand: 5.6.99

1. AES
------

DRAGDROP\			Routinen f�r das Drag&Drop-Konzept von MultiTOS
				(etwas �lter, daher ohne MT_AES)
EDSCROLL\			Ein vollst�ndiges Beispielprogramm f�r den 
				Gebrauch scrollender Eingabefelder
				(etwas �lter, ab MagiC 3)
FSLX\			vollst�ndige Dokumentation und ein 
				Beispielpgrogramm zum Gebrauch der erweiterten 
				Dateiauswahl-Funktionen, u.a. im Fenster.
				(neue Version, mit MT_AES).
MAGXLIB\			Eine etwas �ltere Bibliothek mit drei MagiC-
				spezifischen Funktionen, wird f�r die scrollbaren 
				Edit-Felder ben�tigt.
MOD_APP\			Dienstprogramm und Dokumentation zur Manipulation 
				der APPLICAT.INF f�r Installationsprogramme zur 
				automatischen Zuweisung von Dateitypen und Icons.
MT_AES\			vollst�ndige reentrante (!) AES-Bibliothek f�r 
				PureC. Wird f�r alle MT-Programme (multi 
				threaded) ben�tigt, die AES aufrufen.
				(wird stets aktualisiert)
WINFRAME.DEM\		Seit MagiC 6 kann ein eigener Fensterrahmen-
				Manager installiert werden. Hier ist ein 
				einfaches Beispiel, das f�r eigene W�nsche 
				erweitert werden kann. Es ersetzt das 
				mitgelieferte WINFRAME.SLB.
AES.TXT			ein alter Text, der verschiedene Informationen 
				�ber MagiC und AES enth�lt, welche nicht in die 
				anderen Dokumente passen.
COLMAPIC.C		Prozedur zur Anmeldung einer eigenen Icon-
				Farbpalette.
EDITOB.TXT		Vollst�ndige Dokumentation zum Edit-Objekt, das 
				ab Version 5.20 in einer SLB (EDITOBJC.SLB) 
				mitgeliefert wird und von MGEDIT und MGNOTICE 
				verwendet wird. Es handelt sich um ein einfaches, 
				mehrzeiliges Editfeld.
OBTYPES.TXT		aktuelle Beschreibung aller AES-Objekte inklusive 
				aller Statusbits usw. Leider nicht ganz 
				vollst�ndig, enth�lt aber alle MagiC-
				Besonderheiten.
SINGLE.TXT		Eine �ltere Beschreibung des "single mode"
THREADS.TXT		Eine vollst�ndige, aktuelle und ausf�hrliche 
				Beschreibung des Thread-Konzepts.
WDIALOG.TXT		Beschreibung der Fensterdialoge, der 
				Zeichensatzauswahl und der Druckdialoge (von 
				Sven & Wilfried Behne).
WINDFUN.TXT		Beschreibung der fensterorientierten 
				Zeichenfunktionen (objc_wdraw() usw.).

2. DEV_LPT1
-----------

Quelltext f�r einen Druckertreiber, der Hintergrundtransfer unterst�tzt,
als Beispiel f�r einen MagiC-Ger�tetreiber


3. DOS
------

MT_DOS\			MT-sicheres Binding f�r GEMDOS-Aufrufe, die in 
				der PCTOSLIB von PureC fehlen (mit Quelltext).

LONGFNAM.TXT		Richtlinien zum Unterst�tzen von langen Dateinamen
MGX_DOS.TXT		Beschreibung aller GEMDOS-Aufrufe
PCMXSTRT.O		PureC-Startcode f�r lange Dateinamen
PCMXSTRT.S		Quelltext dazu
PIPES.TXT			Beschreibung des Pipe-Konzepts
SHARELIB.TXT		Beschreibung des "shared library"-Konzepts
SIGNALE.TXT		Beschreibung des "signal"-Konzepts
VFATCONF.TXT 		Beschreibung des gleichnamigen Programms


4. FILESYS 
----------

MGX_DEVD.H		'C'-Header f�r MagiC-Ger�tetreiber
MGX_DEVD.INC		dito f�r Assembler
MGX_DFS.H			'C'-Header f�r MagiC-DFS-Dateisystemtreiber
MGX_DFS.INC		dito f�r Assembler
MGX_DFS.TXT		Beschreibung des DFS-Konzepts (einschl. DOS-
				Ger�tetreiber, z.B. in U:\dev)
MGX_HDD.TXT		Informationen f�r Hintergrund-Plattentransfer
MGX_UDFS.TXT		Beschreibung des Laufwerks U:
MGX_XFS.H			'C'-Header f�r MagiC-XFS-Dateisystemtreiber
MGX_XFS.INC		dito f�r Assembler
MGX_XFS.TXT		Beschreibung des XFS-Konzepts 
				(einschl. Ger�tetreiber, Kernelfunktionen)


5. HEADERS
----------

MGX_DOS.H			Ersatz f�r TOS.H.


6. MXDEV_DK
-----------

Dateien f�r die Entwicklung eines Ger�tetreibers.


7. MXXFS_DK\
------------

Dateien f�r die Entwicklung eines XFS-Treibers in 'C'. Hier ist ein 
Umsetzer von Assembler in 'C' eingebaut. Entstanden sind die Dateien 
bei Entwicklung des SPIN!-Treibers f�r MagiC.


8. SLB_DEMO\
------------

Beispielprogramm f�r das "shared library"-Konzept. Die SLB_xxxx-
Dateien geh�ren zur Bibliothek selbst, die SLC_xxxxx-Dateien zum 
Aufrufprogramm ("client").


9. Diverse
----------

CMD.DOC			Beschreibung von (M)CMD.TOS
FATALERR.TXT		Beschreibung aller "System angehalten"-Meldungen
PROBLEME.TXT		Probleme ab MagiC 5 (teilw. Inkompatibilit�ten)
README.TXT		diese Datei
SHUTDOWN.TXT 		Beschreibung des Shutdown-Mechanismus