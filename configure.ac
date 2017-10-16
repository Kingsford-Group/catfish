#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(catfish, 0.2.1, mingfu.shao@cs.cmu.edu)
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR([lib/graph/vertex_base.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_RANLIB

# Check home directories for BOOST and assign CXXFLAGS
AC_ARG_WITH(boost, AS_HELP_STRING([--with-boost], [home directory for boost]), BOOST_HOME=$withval, BOOST_HOME=)
AS_IF([test "x$BOOST_HOME" != "x"], [AC_SUBST([CXXFLAGS], ["-I$BOOST_HOME $CXXFLAGS"])], [])

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lgraph':
AC_CHECK_LIB([graph], [main])
# FIXME: Replace `main' with a function in `-lgtf':
AC_CHECK_LIB([gtf], [main])
# FIXME: Replace `main' with a function in `-lutil':
AC_CHECK_LIB([util], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([sqrt])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 lib/graph/Makefile
                 lib/gtf/Makefile
                 lib/util/Makefile
                 src/Makefile])
AC_OUTPUT
