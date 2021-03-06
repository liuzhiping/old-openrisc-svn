/*  bspclean.c
 *
 *  These routines return control to 167Bug after a normal exit from the
 *  application.
 *
 *  COPYRIGHT (c) 1989-1999.
 *  On-Line Applications Research Corporation (OAR).
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.OARcorp.com/rtems/license.html.
 *
 *  Modifications of respective RTEMS files:
 *  Copyright (c) 1998, National Research Council of Canada
 *
 *  $Id: bspclean.c,v 1.2 2001-09-27 12:00:20 chris Exp $
 */

#include <rtems.h>
#include <bsp.h>
#include <page_table.h>

/*
 *  bsp_return_to_monitor_trap
 *
 *  Switch the VBR back to ROM and make a .RETURN syscall to return control to
 *  167 Bug. If 167Bug ever returns, restart the application.
 *
 *  Input parameters: NONE
 *
 *  Output parameters: NONE
 *
 *  Return values: NONE
 */
static void bsp_return_to_monitor_trap( void )
{
  extern void start( void );

  register volatile void *start_addr;

  page_table_teardown();

  lcsr->intr_ena = 0;               /* disable interrupts */
  m68k_set_vbr(0xFFE00000);         /* restore 167Bug vectors */
  asm volatile( "trap   #15         /* trap to 167Bug */
                 .short 0x63" );    /* return to 167Bug (.RETURN) */
  
  /* restart program */
  start_addr = start;
  asm volatile( "jmp %0@" : "=a" (start_addr) : "0" (start_addr) );
}

/*
 *  bsp_cleanup
 *
 *  This code was copied from other MC680x0 MVME BSPs.
 *  Our guess is that someone was concerned about the CPU no longer being in
 *  supervisor mode when they got here. This function forces the CPU back to
 *  supervisor mode so the VBR may be changed. It places the address of the
 *  function that makes a 167Bug .RETURN syscall in the trap 13 entry in the
 *  exception vector, and then issues a trap 13 call. It is also possible that
 *  the code was copied from some other OS that does run tasks in user mode.
 *  In any case, it appears to be a bit of paranoia, and could lead to 
 *  problems if 167Bug is invoked before we get to switch the VBR back to
 *  167Bug because trap 13 is documented as being reserved for the internal
 *  use of the debugger.
 *
 *  Prototyped in rtems/c/src/lib/libbsp/m68k/mvme167/include/bsp.h
 *
 *  Input parameters: NONE
 *
 *  Output parameters: NONE
 *
 *  Return values: DOES NOT RETURN
 */
void bsp_cleanup( void )
{
   M68Kvec[ 45 ] = bsp_return_to_monitor_trap;
   asm volatile( "trap #13" );
}
