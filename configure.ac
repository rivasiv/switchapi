#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([switchapi], [0.1], [])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_SILENT_RULES([yes])
AC_CONFIG_HEADERS([config.h])

AC_ARG_ENABLE([coverage],
    AS_HELP_STRING([--enable-coverage], [Enable gcov flags]))
AS_IF([test "x$enable_coverage" = "xyes"], [
    AC_DEFINE([COVERAGE], [], ["Link with gcov."])
    COVERAGE_FLAGS="--coverage"
])

# Checks for programs.
CFLAGS="-g -Wall -Wextra -Wno-unused-parameter"
AC_PROG_CC_STDC
AC_PROG_CXX
AC_PROG_RANLIB

AC_CONFIG_MACRO_DIR([m4])

# enforce -std=c++11
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

# Checks for header files.
AC_LANG_PUSH(C)

AC_CHECK_HEADERS([assert.h stdio.h string.h sys/stat.h sys/types.h unistd.h], \
[], [AC_MSG_ERROR([Missing header file])])

# Check for thrift support (Facebook's Thrift RPC library)
AC_PATH_PROG([THRIFT], [thrift], [])
AS_IF([test x"$THRIFT" = x],
[AC_MSG_ERROR([cannot find thrift])])

AC_CHECK_LIB([pcap], [pcap_create], [], [AC_MSG_ERROR([Missing libpcap])])
if test -n "$COVERAGE_FLAGS"; then
    AC_CHECK_LIB([gcov], [__gcov_init], [], [AC_MSG_ERROR([Missing gcov library])])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_UINT64_T

# Doxygen support.
#AC_CHECK_PROGS([DOXYGEN], [doxygen])
#if test -z "$DOXYGEN";
#   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
#fi
#AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])AM_COND_IF([HAVE_DOXYGEN],
#[AC_CONFIG_FILES([doc/Doxyfile])])

# Generate makefiles
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
