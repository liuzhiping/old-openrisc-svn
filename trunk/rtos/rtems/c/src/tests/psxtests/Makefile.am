##
## $Id: Makefile.am,v 1.2 2001-09-27 12:02:23 chris Exp $
##

AUTOMAKE_OPTIONS = foreign 1.4
ACLOCAL_AMFLAGS = -I $(RTEMS_TOPdir)/aclocal

SHARED_DIRS =

POSIX_DIRS = include psxhdrs psx01 psx02 psx03 psx04 psx05 psx06 psx07 psx08 \
    psx09 psx10 psx11 psx12 psxtime psxtimer psxcancel psxmsgq01 psxsem01

POSIX_FILES_DIRS = psxfile01 psxreaddir psxstat psxmount psx13

UNUSED_DIRS =

SUBDIRS = $(SHARED_DIRS) $(POSIX_DIRS) $(POSIX_FILES_DIRS) $(UNUSED_DIRS)

EXTRA_DIST = psxtests.am

include $(top_srcdir)/../../../../automake/subdirs.am
include $(top_srcdir)/../../../../automake/local.am
