/*
 * ../syscall/gen-syscall *
 * DO NOT EDIT - this file is automatically generated!
 */

/*                                                                      
 * This file belongs to FreeMiNT. It's not in the original MiNT 1.12    
 * distribution. See the file CHANGES for a detailed log of changes.    
 *                                                                      
 *                                                                      
 * Copyright 2000-2005 Frank Naumann <fnaumann@freemint.de>             
 * All rights reserved.                                                 
 *                                                                      
 * Please send suggestions, patches or bug reports to me or             
 * the MiNT mailing list.                                               
 *                                                                      
 *                                                                      
 * This file is free software; you can redistribute it and/or modify    
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 2, or (at your option)  
 * any later version.                                                   
 *                                                                      
 * This file is distributed in the hope that it will be useful,         
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        
 * GNU General Public License for more details.                         
 *                                                                      
 * You should have received a copy of the GNU General Public License    
 * along with this program; if not, write to the Free Software          
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            
 *                                                                      
 */                                                                     

#ifndef _MINT_SYSBIND_H
#define _MINT_SYSBIND_H

#ifndef _FEATURES_H
# include <features.h>
#endif

#ifndef _MINT_OSTRUCT_H
# include <mint/ostruct.h>
#endif

#ifndef _MINT_TRAP1_H
# include <mint/trap1.h>
#endif
#ifndef _MINT_TRAP13_H
# include <mint/trap13.h>
#endif
#ifndef _MINT_TRAP14_H
# include <mint/trap14.h>
#endif

__BEGIN_DECLS

/* GEMDOS */

#define Pterm0() (void)trap_1_w(0x0)
#define Cconin() (long)trap_1_w(0x1)
#define Cconout(a) (void)trap_1_ww(0x2,(short)(a))
#define Cauxin() (short)trap_1_w(0x3)
#define Cauxout(a) (void)trap_1_ww(0x4,(short)(a))
#define Cprnout(a) (short)trap_1_ww(0x5,(short)(a))
#define Crawio(a) (long)trap_1_ww(0x6,(short)(a))
#define Crawcin() (long)trap_1_w(0x7)
#define Cnecin() (long)trap_1_w(0x8)
#define Cconws(a) (short)trap_1_wl(0x9,(long)(a))
#define Cconrs(a) (long)trap_1_wl(0xa,(long)(a))
#define Cconis() (short)trap_1_w(0xb)
#define Dsetdrv(a) (long)trap_1_ww(0xe,(short)(a))
#define Cconos() (short)trap_1_w(0x10)
#define Cprnos() (short)trap_1_w(0x11)
#define Cauxis() (short)trap_1_w(0x12)
#define Cauxos() (short)trap_1_w(0x13)
#define Maddalt(a,b) (long)trap_1_wll(0x14,(long)(a),(long)(b))
#define Srealloc(a) (long)trap_1_wl(0x15,(long)(a))
#define Slbopen(a,b,c,d,e) (long)trap_1_wlllll(0x16,(long)(a),(long)(b),(long)(c),(long)(d),(long)(e))
#define Slbclose(a) (long)trap_1_wl(0x17,(long)(a))
#define Dgetdrv() (short)trap_1_w(0x19)
#define Fsetdta(a) (void)trap_1_wl(0x1a,(long)(a))
#define Super(a) (long)trap_1_wl(0x20,(long)(a))
#define Tgetdate() (short)trap_1_w(0x2a)
#define Tsetdate(a) (long)trap_1_ww(0x2b,(short)(a))
#define Tgettime() (short)trap_1_w(0x2c)
#define Tsettime(a) (long)trap_1_ww(0x2d,(short)(a))
#define Fgetdta() (_DTA *)trap_1_w(0x2f)
#define Sversion() (short)trap_1_w(0x30)
#define Ptermres(a,b) (void)trap_1_wlw(0x31,(long)(a),(short)(b))
#define Sconfig(a,b) (long)trap_1_wwl(0x33,(short)(a),(long)(b))
#define Dfree(a,b) (long)trap_1_wlw(0x36,(long)(a),(short)(b))
#define Dcreate(a) (short)trap_1_wl(0x39,(long)(a))
#define Ddelete(a) (long)trap_1_wl(0x3a,(long)(a))
#define Dsetpath(a) (long)trap_1_wl(0x3b,(long)(a))
#define Fcreate(a,b) (long)trap_1_wlw(0x3c,(long)(a),(short)(b))
#define Fopen(a,b) (long)trap_1_wlw(0x3d,(long)(a),(short)(b))
#define Fclose(a) (long)trap_1_ww(0x3e,(short)(a))
#define Fread(a,b,c) (long)trap_1_wwll(0x3f,(short)(a),(long)(b),(long)(c))
#define Fwrite(a,b,c) (long)trap_1_wwll(0x40,(short)(a),(long)(b),(long)(c))
#define Fdelete(a) (long)trap_1_wl(0x41,(long)(a))
#define Fseek(a,b,c) (long)trap_1_wlww(0x42,(long)(a),(short)(b),(short)(c))
#define Fattrib(a,b,c) (short)trap_1_wlww(0x43,(long)(a),(short)(b),(short)(c))
#define Mxalloc(a,b) (long)trap_1_wlw(0x44,(long)(a),(short)(b))
#define Fdup(a) (long)trap_1_ww(0x45,(short)(a))
#define Fforce(a,b) (long)trap_1_www(0x46,(short)(a),(short)(b))
#define Dgetpath(a,b) (long)trap_1_wlw(0x47,(long)(a),(short)(b))
#define Malloc(a) (long)trap_1_wl(0x48,(long)(a))
#define Mfree(a) (long)trap_1_wl(0x49,(long)(a))
#define Mshrink(b,c) (long)trap_1_wwll(0x4a,(short)0,(long)(b),(long)(c))
#define Pexec(a,b,c,d) (long)trap_1_wwlll(0x4b,(short)(a),(long)(b),(long)(c),(long)(d))
#define Pterm(a) (void)trap_1_ww(0x4c,(short)(a))
#define Fsfirst(a,b) (long)trap_1_wlw(0x4e,(long)(a),(short)(b))
#define Fsnext() (long)trap_1_w(0x4f)
#define Frename(a,b,c) (short)trap_1_wwll(0x56,(short)(a),(long)(b),(long)(c))
#define Fdatime(a,b,c) (long)trap_1_wlww(0x57,(long)(a),(short)(b),(short)(c))
#define Flock(a,b,c,d) (long)trap_1_wwwll(0x5c,(short)(a),(short)(b),(long)(c),(long)(d))
#define Syield() (short)trap_1_w(0xff)
#define Fpipe(a) (short)trap_1_wl(0x100,(long)(a))
#define Ffchown(a,b,c) (short)trap_1_wwww(0x101,(short)(a),(short)(b),(short)(c))
#define Ffchmod(a,b) (short)trap_1_www(0x102,(short)(a),(short)(b))
#define Fsync(a) (short)trap_1_ww(0x103,(short)(a))
#define Fcntl(a,b,c) (long)trap_1_wwlw(0x104,(short)(a),(long)(b),(short)(c))
#define Finstat(a) (long)trap_1_ww(0x105,(short)(a))
#define Foutstat(a) (long)trap_1_ww(0x106,(short)(a))
#define Fgetchar(a,b) (long)trap_1_www(0x107,(short)(a),(short)(b))
#define Fputchar(a,b,c) (long)trap_1_wwlw(0x108,(short)(a),(long)(b),(short)(c))
#define Pwait() (long)trap_1_w(0x109)
#define Pnice(a) (short)trap_1_ww(0x10a,(short)(a))
#define Pgetpid() (short)trap_1_w(0x10b)
#define Pgetppid() (short)trap_1_w(0x10c)
#define Pgetpgrp() (short)trap_1_w(0x10d)
#define Psetpgrp(a,b) (short)trap_1_www(0x10e,(short)(a),(short)(b))
#define Pgetuid() (short)trap_1_w(0x10f)
#define Psetuid(a) (short)trap_1_ww(0x110,(short)(a))
#define Pkill(a,b) (short)trap_1_www(0x111,(short)(a),(short)(b))
#define Psignal(a,b) (long)trap_1_wwl(0x112,(short)(a),(long)(b))
#define Pvfork() (long)trap_1_w(0x113)
#define Pgetgid() (short)trap_1_w(0x114)
#define Psetgid(a) (short)trap_1_ww(0x115,(short)(a))
#define Psigblock(a) (long)trap_1_wl(0x116,(long)(a))
#define Psigsetmask(a) (long)trap_1_wl(0x117,(long)(a))
#define Pusrval(a) (long)trap_1_wl(0x118,(long)(a))
#define Pdomain(a) (short)trap_1_ww(0x119,(short)(a))
#define Psigreturn() (void)trap_1_w(0x11a)
#define Pfork() (long)trap_1_w(0x11b)
#define Pwait3(a,b) (long)trap_1_wwl(0x11c,(short)(a),(long)(b))
#define Fselect(a,b,c,d) (short)trap_1_wwlll(0x11d,(short)(a),(long)(b),(long)(c),(long)(d))
#define Prusage(a) (short)trap_1_wl(0x11e,(long)(a))
#define Psetlimit(a,b) (long)trap_1_wwl(0x11f,(short)(a),(long)(b))
#define Talarm(a) (long)trap_1_wl(0x120,(long)(a))
#define Pause() (long)trap_1_w(0x121)
#define Sysconf(a) (long)trap_1_ww(0x122,(short)(a))
#define Psigpending() (long)trap_1_w(0x123)
#define Dpathconf(a,b) (long)trap_1_wlw(0x124,(long)(a),(short)(b))
#define Pmsg(a,b,c) (long)trap_1_wwll(0x125,(short)(a),(long)(b),(long)(c))
#define Fmidipipe(a,b,c) (long)trap_1_wwww(0x126,(short)(a),(short)(b),(short)(c))
#define Prenice(a,b) (short)trap_1_www(0x127,(short)(a),(short)(b))
#define Dopendir(a,b) (long)trap_1_wlw(0x128,(long)(a),(short)(b))
#define Dreaddir(a,b,c) (long)trap_1_wwll(0x129,(short)(a),(long)(b),(long)(c))
#define Drewinddir(a) (long)trap_1_wl(0x12a,(long)(a))
#define Dclosedir(a) (long)trap_1_wl(0x12b,(long)(a))
#define Fxattr(a,b,c) (long)trap_1_wwll(0x12c,(short)(a),(long)(b),(long)(c))
#define Flink(a,b) (long)trap_1_wll(0x12d,(long)(a),(long)(b))
#define Fsymlink(a,b) (long)trap_1_wll(0x12e,(long)(a),(long)(b))
#define Freadlink(a,b,c) (long)trap_1_wwll(0x12f,(short)(a),(long)(b),(long)(c))
#define Dcntl(a,b,c) (long)trap_1_wwll(0x130,(short)(a),(long)(b),(long)(c))
#define Fchown(a,b,c) (long)trap_1_wlww(0x131,(long)(a),(short)(b),(short)(c))
#define Fchmod(a,b) (long)trap_1_wlw(0x132,(long)(a),(short)(b))
#define Pumask(a) (unsigned short)trap_1_ww(0x133,(short)(a))
#define Psemaphore(a,b,c) (long)trap_1_wwll(0x134,(short)(a),(long)(b),(long)(c))
#define Dlock(a,b) (short)trap_1_www(0x135,(short)(a),(short)(b))
#define Psigpause(a) (long)trap_1_wl(0x136,(long)(a))
#define Psigaction(a,b,c) (long)trap_1_wwll(0x137,(short)(a),(long)(b),(long)(c))
#define Pgeteuid() (short)trap_1_w(0x138)
#define Pgetegid() (short)trap_1_w(0x139)
#define Pwaitpid(a,b,c) (long)trap_1_wwwl(0x13a,(short)(a),(short)(b),(long)(c))
#define Dgetcwd(a,b,c) (long)trap_1_wlww(0x13b,(long)(a),(short)(b),(short)(c))
#define Salert(a) (long)trap_1_wl(0x13c,(long)(a))
#define Tmalarm(a) (unsigned long)trap_1_wl(0x13d,(long)(a))
#define Psigintr(a,b) (long)trap_1_www(0x13e,(short)(a),(short)(b))
#define Suptime(a,b) (long)trap_1_wll(0x13f,(long)(a),(long)(b))
#define Ptrace(a,b,c,d) (long)trap_1_wwwll(0x140,(short)(a),(short)(b),(long)(c),(long)(d))
#define Mvalidate(a,b,c,d) (long)trap_1_wwlll(0x141,(short)(a),(long)(b),(long)(c),(long)(d))
#define Dxreaddir(a,b,c,d,e) (long)trap_1_wwllll(0x142,(short)(a),(long)(b),(long)(c),(long)(d),(long)(e))
#define Pseteuid(a) (long)trap_1_ww(0x143,(short)(a))
#define Psetegid(a) (long)trap_1_ww(0x144,(short)(a))
#define Pgetauid() (long)trap_1_w(0x145)
#define Psetauid(a) (long)trap_1_ww(0x146,(short)(a))
#define Pgetgroups(a,b) (long)trap_1_wwl(0x147,(short)(a),(long)(b))
#define Psetgroups(a,b) (long)trap_1_wwl(0x148,(short)(a),(long)(b))
#define Tsetitimer(a,b,c,d,e) (long)trap_1_wwllll(0x149,(short)(a),(long)(b),(long)(c),(long)(d),(long)(e))
#define Dchroot(a) (long)trap_1_wl(0x14a,(long)(a))
#define Fstat64(a,b,c) (long)trap_1_wwll(0x14b,(short)(a),(long)(b),(long)(c))
#define Fseek64(a,b,c,d,e) (long)trap_1_wllwwl(0x14c,(long)(a),(long)(b),(short)(c),(short)(d),(long)(e))
#define Dsetkey(a,b,c,d) (long)trap_1_wlllw(0x14d,(long)(a),(long)(b),(long)(c),(short)(d))
#define Psetreuid(a,b) (long)trap_1_www(0x14e,(short)(a),(short)(b))
#define Psetregid(a,b) (long)trap_1_www(0x14f,(short)(a),(short)(b))
#define Sync() (long)trap_1_w(0x150)
#define Shutdown(a) (long)trap_1_wl(0x151,(long)(a))
#define Dreadlabel(a,b,c) (long)trap_1_wllw(0x152,(long)(a),(long)(b),(short)(c))
#define Dwritelabel(a,b) (long)trap_1_wll(0x153,(long)(a),(long)(b))
#define Ssystem(a,b,c) (long)trap_1_wwll(0x154,(short)(a),(long)(b),(long)(c))
#define Tgettimeofday(a,b) (long)trap_1_wll(0x155,(long)(a),(long)(b))
#define Tsettimeofday(a,b) (long)trap_1_wll(0x156,(long)(a),(long)(b))
#define Tadjtime(a,b) (long)trap_1_wll(0x157,(long)(a),(long)(b))
#define Pgetpriority(a,b) (long)trap_1_www(0x158,(short)(a),(short)(b))
#define Psetpriority(a,b,c) (long)trap_1_wwww(0x159,(short)(a),(short)(b),(short)(c))
#define Fpoll(a,b,c) (long)trap_1_wlll(0x15a,(long)(a),(long)(b),(long)(c))
#define Fwritev(a,b,c) (long)trap_1_wwll(0x15b,(short)(a),(long)(b),(long)(c))
#define Freadv(a,b,c) (long)trap_1_wwll(0x15c,(short)(a),(long)(b),(long)(c))
#define Ffstat64(a,b) (long)trap_1_wwl(0x15d,(short)(a),(long)(b))
#define Psysctl(a,b,c,d,e,f) (long)trap_1_wllllll(0x15e,(long)(a),(long)(b),(long)(c),(long)(d),(long)(e),(long)(f))
#define Semulation(a,b,c,d,e,f,g,h,i) (long)trap_1_wwwlllllll(0x15f,(short)(a),(short)(b),(long)(c),(long)(d),(long)(e),(long)(f),(long)(g),(long)(h),(long)(i))
#define Fsocket(a,b,c) (long)trap_1_wlll(0x160,(long)(a),(long)(b),(long)(c))
#define Fsocketpair(a,b,c,d) (long)trap_1_wllll(0x161,(long)(a),(long)(b),(long)(c),(long)(d))
#define Faccept(a,b,c) (long)trap_1_wwll(0x162,(short)(a),(long)(b),(long)(c))
#define Fconnect(a,b,c) (long)trap_1_wwll(0x163,(short)(a),(long)(b),(long)(c))
#define Fbind(a,b,c) (long)trap_1_wwll(0x164,(short)(a),(long)(b),(long)(c))
#define Flisten(a,b) (long)trap_1_wwl(0x165,(short)(a),(long)(b))
#define Frecvmsg(a,b,c) (long)trap_1_wwll(0x166,(short)(a),(long)(b),(long)(c))
#define Fsendmsg(a,b,c) (long)trap_1_wwll(0x167,(short)(a),(long)(b),(long)(c))
#define Frecvfrom(a,b,c,d,e,f) (long)trap_1_wwlllll(0x168,(short)(a),(long)(b),(long)(c),(long)(d),(long)(e),(long)(f))
#define Fsendto(a,b,c,d,e,f) (long)trap_1_wwlllll(0x169,(short)(a),(long)(b),(long)(c),(long)(d),(long)(e),(long)(f))
#define Fsetsockopt(a,b,c,d,e) (long)trap_1_wwllll(0x16a,(short)(a),(long)(b),(long)(c),(long)(d),(long)(e))
#define Fgetsockopt(a,b,c,d,e) (long)trap_1_wwllll(0x16b,(short)(a),(long)(b),(long)(c),(long)(d),(long)(e))
#define Fgetpeername(a,b,c) (long)trap_1_wwll(0x16c,(short)(a),(long)(b),(long)(c))
#define Fgetsockname(a,b,c) (long)trap_1_wwll(0x16d,(short)(a),(long)(b),(long)(c))
#define Fshutdown(a,b) (long)trap_1_wwl(0x16e,(short)(a),(long)(b))
#define Pshmget(a,b,c) (long)trap_1_wlll(0x170,(long)(a),(long)(b),(long)(c))
#define Pshmctl(a,b,c) (long)trap_1_wlll(0x171,(long)(a),(long)(b),(long)(c))
#define Pshmat(a,b,c) (long)trap_1_wlll(0x172,(long)(a),(long)(b),(long)(c))
#define Pshmdt(a) (long)trap_1_wl(0x173,(long)(a))
#define Psemget(a,b,c) (long)trap_1_wlll(0x174,(long)(a),(long)(b),(long)(c))
#define Psemctl(a,b,c,d) (long)trap_1_wllll(0x175,(long)(a),(long)(b),(long)(c),(long)(d))
#define Psemop(a,b,c) (long)trap_1_wlll(0x176,(long)(a),(long)(b),(long)(c))
#define Psemconfig(a) (long)trap_1_wl(0x177,(long)(a))
#define Pmsgget(a,b) (long)trap_1_wll(0x178,(long)(a),(long)(b))
#define Pmsgctl(a,b,c) (long)trap_1_wlll(0x179,(long)(a),(long)(b),(long)(c))
#define Pmsgsnd(a,b,c,d) (long)trap_1_wllll(0x17a,(long)(a),(long)(b),(long)(c),(long)(d))
#define Pmsgrcv(a,b,c,d,e) (long)trap_1_wlllll(0x17b,(long)(a),(long)(b),(long)(c),(long)(d),(long)(e))
#define Maccess(a,b,c) (long)trap_1_wllw(0x17d,(long)(a),(long)(b),(short)(c))
#define Fchown16(a,b,c,d) (long)trap_1_wlwww(0x180,(long)(a),(short)(b),(short)(c),(short)(d))
#define Fchdir(a) (long)trap_1_ww(0x181,(short)(a))
#define Ffdopendir(a) (long)trap_1_ww(0x182,(short)(a))
#define Fdirfd(a) (long)trap_1_wl(0x183,(long)(a))

/* BIOS */

#define Getmpb(a) (void)trap_13_wl(0x0,(long)(a))
#define Bconstat(a) (short)trap_13_ww(0x1,(short)(a))
#define Bconin(a) (long)trap_13_ww(0x2,(short)(a))
#define Bconout(a,b) (long)trap_13_www(0x3,(short)(a),(short)(b))
#define Rwabs(a,b,c,d,e,f) (long)trap_13_wwlwwwl(0x4,(short)(a),(long)(b),(short)(c),(short)(d),(short)(e),(long)(f))
#define Setexc(a,b) (void *)trap_13_wwl(0x5,(short)(a),(long)(b))
#define Tickcal() (long)trap_13_w(0x6)
#define Getbpb(a) (void *)trap_13_ww(0x7,(short)(a))
#define Bcostat(a) (short)trap_13_ww(0x8,(short)(a))
#define Mediach(a) (short)trap_13_ww(0x9,(short)(a))
#define Drvmap() (long)trap_13_w(0xa)
#define Kbshift(a) (long)trap_13_ww(0xb,(short)(a))

/* XBIOS */

#define Initmouse(a,b,c) (void)trap_14_wwll(0x0,(short)(a),(long)(b),(long)(c))
#define Ssbrk(a) (void *)trap_14_ww(0x1,(short)(a))
#define Physbase() (void *)trap_14_w(0x2)
#define Logbase() (void *)trap_14_w(0x3)
#define Getrez() (short)trap_14_w(0x4)
#define VsetScreen(a,b,c,d) (void)trap_14_wllww(0x5,(long)(a),(long)(b),(short)(c),(short)(d))
#define Setpalette(a) (void)trap_14_wl(0x6,(long)(a))
#define Setcolor(a,b) (short)trap_14_www(0x7,(short)(a),(short)(b))
#define Floprd(a,b,c,d,e,f,g) (short)trap_14_wllwwwww(0x8,(long)(a),(long)(b),(short)(c),(short)(d),(short)(e),(short)(f),(short)(g))
#define Flopwr(a,b,c,d,e,f,g) (short)trap_14_wllwwwww(0x9,(long)(a),(long)(b),(short)(c),(short)(d),(short)(e),(short)(f),(short)(g))
#define Flopfmt(a,b,c,d,e,f,g,h,i) (short)trap_14_wllwwwwwlw(0xa,(long)(a),(long)(b),(short)(c),(short)(d),(short)(e),(short)(f),(short)(g),(long)(h),(short)(i))
#define Dbmsg(a,b,c) (void)trap_14_wwwl(0xb,(short)(a),(short)(b),(long)(c))
#define Midiws(a,b) (void)trap_14_wwl(0xc,(short)(a),(long)(b))
#define Mfpint(a,b) (void)trap_14_wwl(0xd,(short)(a),(long)(b))
#define Iorec(a) (void *)trap_14_ww(0xe,(short)(a))
#define Rsconf(a,b,c,d,e,f) (long)trap_14_wwwwwww(0xf,(short)(a),(short)(b),(short)(c),(short)(d),(short)(e),(short)(f))
#define Keytbl(a,b,c) (void *)trap_14_wlll(0x10,(long)(a),(long)(b),(long)(c))
#define Random() (long)trap_14_w(0x11)
#define Protobt(a,b,c,d) (void)trap_14_wllww(0x12,(long)(a),(long)(b),(short)(c),(short)(d))
#define Flopver(a,b,c,d,e,f,g) (short)trap_14_wllwwwww(0x13,(long)(a),(long)(b),(short)(c),(short)(d),(short)(e),(short)(f),(short)(g))
#define Scrdmp() (void)trap_14_w(0x14)
#define Cursconf(a,b) (short)trap_14_www(0x15,(short)(a),(short)(b))
#define Settime(a) (void)trap_14_wl(0x16,(long)(a))
#define Gettime() (long)trap_14_w(0x17)
#define Bioskeys() (void)trap_14_w(0x18)
#define Ikbdws(a,b) (void)trap_14_wwl(0x19,(short)(a),(long)(b))
#define Jdisint(a) (void)trap_14_ww(0x1a,(short)(a))
#define Jenabint(a) (void)trap_14_ww(0x1b,(short)(a))
#define Giaccess(a,b) (short)trap_14_www(0x1c,(short)(a),(short)(b))
#define Offgibit(a) (void)trap_14_ww(0x1d,(short)(a))
#define Ongibit(a) (void)trap_14_ww(0x1e,(short)(a))
#define Xbtimer(a,b,c,d) (void)trap_14_wwwwl(0x1f,(short)(a),(short)(b),(short)(c),(long)(d))
#define Dosound(a) (void *)trap_14_wl(0x20,(long)(a))
#define Setprt(a) (short)trap_14_ww(0x21,(short)(a))
#define Kbdvbase() (_KBDVECS *)trap_14_w(0x22)
#define Kbrate(a,b) (short)trap_14_www(0x23,(short)(a),(short)(b))
#define Prtblk(a) (void)trap_14_wl(0x24,(long)(a))
#define Vsync() (void)trap_14_w(0x25)
#define Supexec(a) (long)trap_14_wl(0x26,(long)(a))
#define Puntaes() (void)trap_14_w(0x27)
#define Floprate(a,b) (short)trap_14_www(0x29,(short)(a),(short)(b))
#define DMAread(a,b,c,d) (long)trap_14_wlwlw(0x2a,(long)(a),(short)(b),(long)(c),(short)(d))
#define DMAwrite(a,b,c,d) (long)trap_14_wlwlw(0x2b,(long)(a),(short)(b),(long)(c),(short)(d))
#define Bconmap(a) (long)trap_14_ww(0x2c,(short)(a))
#define NVMaccess(a,b,c,d) (short)trap_14_wwwwl(0x2e,(short)(a),(short)(b),(short)(c),(long)(d))
#define Waketime(a,b) (void)trap_14_www(0x2f,(short)(a),(short)(b))
#define Metainit(a) (void)trap_14_wl(0x30,(long)(a))
#define Metaopen(a,b) (long)trap_14_wwl(0x31,(short)(a),(long)(b))
#define Metaclose(a) (void)trap_14_ww(0x32,(short)(a))
#define Metaread(a,b,c,d) (long)trap_14_wwllw(0x33,(short)(a),(long)(b),(long)(c),(short)(d))
#define Metawrite(a,b,c,d) (long)trap_14_wwllw(0x34,(short)(a),(long)(b),(long)(c),(short)(d))
#define Metaseek(a,b) (long)trap_14_wwl(0x35,(short)(a),(long)(b))
#define Metastatus(a,b) (long)trap_14_wwl(0x36,(short)(a),(long)(b))
#define Metaioctl(a,b,c,d) (long)trap_14_wwlwl(0x37,(short)(a),(long)(b),(short)(c),(long)(d))
#define Metastartaudio(a,b,c) (long)trap_14_wwwl(0x3b,(short)(a),(short)(b),(long)(c))
#define Metastopaudio(a) (long)trap_14_ww(0x3c,(short)(a))
#define Metasetsongtime(a,b,c,d) (long)trap_14_wwwll(0x3d,(short)(a),(short)(b),(long)(c),(long)(d))
#define Metagettoc(a,b,c) (long)trap_14_wwwl(0x3e,(short)(a),(short)(b),(long)(c))
#define Metadiscinfo(a,b) (long)trap_14_wwl(0x3f,(short)(a),(long)(b))
#define Blitmode(a) (short)trap_14_ww(0x40,(short)(a))
#define EsetShift(a) (short)trap_14_ww(0x50,(short)(a))
#define EgetShift() (short)trap_14_w(0x51)
#define EsetBank(a) (short)trap_14_ww(0x52,(short)(a))
#define EsetColor(a,b) (short)trap_14_www(0x53,(short)(a),(short)(b))
#define EsetPalette(a,b,c) (void)trap_14_wwwl(0x54,(short)(a),(short)(b),(long)(c))
#define EgetPalette(a,b,c) (void)trap_14_wwwl(0x55,(short)(a),(short)(b),(long)(c))
#define EsetGray(a) (short)trap_14_ww(0x56,(short)(a))
#define EsetSmear(a) (short)trap_14_ww(0x57,(short)(a))
#define VsetMode(a) (short)trap_14_ww(0x58,(short)(a))
#define VgetMonitor() (short)trap_14_w(0x59)
#define VsetSync(a) (void)trap_14_ww(0x5a,(short)(a))
#define VgetSize(a) (long)trap_14_ww(0x5b,(short)(a))
#define VsetRGB(a,b,c) (void)trap_14_wwwl(0x5d,(short)(a),(short)(b),(long)(c))
#define VgetRGB(a,b,c) (void)trap_14_wwwl(0x5e,(short)(a),(short)(b),(long)(c))
#define Validmode(a) (short)trap_14_ww(0x5f,(short)(a))
#define Dsp_DoBlock(a,b,c,d) (void)trap_14_wllll(0x60,(long)(a),(long)(b),(long)(c),(long)(d))
#define Dsp_BlkHandShake(a,b,c,d) (void)trap_14_wllll(0x61,(long)(a),(long)(b),(long)(c),(long)(d))
#define Dsp_BlkUnpacked(a,b,c,d) (void)trap_14_wllll(0x62,(long)(a),(long)(b),(long)(c),(long)(d))
#define Dsp_InStream(a,b,c,d) (void)trap_14_wllll(0x63,(long)(a),(long)(b),(long)(c),(long)(d))
#define Dsp_OutStream(a,b,c,d) (void)trap_14_wllll(0x64,(long)(a),(long)(b),(long)(c),(long)(d))
#define Dsp_IOStream(a,b,c,d,e,f) (void)trap_14_wllllll(0x65,(long)(a),(long)(b),(long)(c),(long)(d),(long)(e),(long)(f))
#define Dsp_RemoveInterrupts(a) (void)trap_14_ww(0x66,(short)(a))
#define Dsp_GetWordSize() (short)trap_14_w(0x67)
#define Dsp_Lock() (short)trap_14_w(0x68)
#define Dsp_Unlock() (void)trap_14_w(0x69)
#define Dsp_Available(a,b) (void)trap_14_wll(0x6a,(long)(a),(long)(b))
#define Dsp_Reserve(a,b) (short)trap_14_wll(0x6b,(long)(a),(long)(b))
#define Dsp_LoadProg(a,b,c) (short)trap_14_wlwl(0x6c,(long)(a),(short)(b),(long)(c))
#define Dsp_ExecProg(a,b,c) (void)trap_14_wllw(0x6d,(long)(a),(long)(b),(short)(c))
#define Dsp_ExecBoot(a,b,c) (void)trap_14_wllw(0x6e,(long)(a),(long)(b),(short)(c))
#define Dsp_LodToBinary(a,b) (long)trap_14_wll(0x6f,(long)(a),(long)(b))
#define Dsp_TriggerHC(a) (void)trap_14_ww(0x70,(short)(a))
#define Dsp_RequestUniqueAbility() (short)trap_14_w(0x71)
#define Dsp_GetProgAbility() (short)trap_14_w(0x72)
#define Dsp_FlushSubroutines() (void)trap_14_w(0x73)
#define Dsp_LoadSubroutine(a,b,c) (short)trap_14_wllw(0x74,(long)(a),(long)(b),(short)(c))
#define Dsp_InqSubrAbility(a) (short)trap_14_ww(0x75,(short)(a))
#define Dsp_RunSubroutine(a) (short)trap_14_ww(0x76,(short)(a))
#define Dsp_Hf0(a) (short)trap_14_ww(0x77,(short)(a))
#define Dsp_Hf1(a) (short)trap_14_ww(0x78,(short)(a))
#define Dsp_Hf2() (short)trap_14_w(0x79)
#define Dsp_Hf3() (short)trap_14_w(0x7a)
#define Dsp_BlkWords(a,b,c,d) (void)trap_14_wllll(0x7b,(long)(a),(long)(b),(long)(c),(long)(d))
#define Dsp_BlkBytes(a,b,c,d) (void)trap_14_wllll(0x7c,(long)(a),(long)(b),(long)(c),(long)(d))
#define Dsp_HStat() (short)trap_14_w(0x7d)
#define Dsp_SetVectors(a,b) (void)trap_14_wll(0x7e,(long)(a),(long)(b))
#define Dsp_MultBlocks(a,b,c,d) (void)trap_14_wllll(0x7f,(long)(a),(long)(b),(long)(c),(long)(d))
#define Locksnd() (long)trap_14_w(0x80)
#define Unlocksnd() (long)trap_14_w(0x81)
#define NSoundcmd(a,b,c) (long)trap_14_wwwl(0x82,(short)(a),(short)(b),(long)(c))
#define Setbuffer(a,b,c) (long)trap_14_wwll(0x83,(short)(a),(long)(b),(long)(c))
#define Setmode(a) (long)trap_14_ww(0x84,(short)(a))
#define Settracks(a,b) (long)trap_14_www(0x85,(short)(a),(short)(b))
#define Setmontracks(a) (long)trap_14_ww(0x86,(short)(a))
#define Setinterrupt(a,b) (long)trap_14_www(0x87,(short)(a),(short)(b))
#define Buffoper(a) (long)trap_14_ww(0x88,(short)(a))
#define Dsptristate(a,b) (long)trap_14_www(0x89,(short)(a),(short)(b))
#define Gpio(a,b) (long)trap_14_www(0x8a,(short)(a),(short)(b))
#define Devconnect(a,b,c,d,e) (long)trap_14_wwwwww(0x8b,(short)(a),(short)(b),(short)(c),(short)(d),(short)(e))
#define Sndstatus(a) (long)trap_14_ww(0x8c,(short)(a))
#define Buffptr(a) (long)trap_14_wl(0x8d,(long)(a))
#define VsetMask(a,b,c) (void)trap_14_wllw(0x96,(long)(a),(long)(b),(short)(c))
#define CacheCtrl(a,b) (long)trap_14_www(0xa0,(short)(a),(short)(b))
#define WdgCtrl(a) (long)trap_14_ww(0xa1,(short)(a))
#define ExtRsConf(a,b,c) (long)trap_14_wwwl(0xa2,(short)(a),(short)(b),(long)(c))
#define WavePlay(a,b,c,d) (long)trap_14_wwlll(0xa5,(short)(a),(long)(b),(long)(c),(long)(d))

__END_DECLS

#endif /* _MINT_SYSBIND_H */
