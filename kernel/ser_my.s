     XDEF      serno_test
     XDEF      serno_t2
     XDEF      serno_t3
     XDEF      serno_t4

	 XREF serno_isok
	 XREF dos_time
	 XREF ss_serno
     XREF prtstr

serno_test:
 rts



serno_t2:
 moveq    #0,d0                    ; OK
serno_t3:
serno_t4:
 rts

     END
