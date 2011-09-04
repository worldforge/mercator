#! /bin/sh

echo aclocal...
(aclocal --version) < /dev/null > /dev/null 2>&1 || {
    echo aclocal not found
    exit 1
}

aclocal $ACLOCAL_FLAGS

echo autoheader...
(autoheader --version) < /dev/null > /dev/null 2>&1 || {
    echo autoheader not found
    exit 1
}    

autoheader

if [ "`echo $OSTYPE | grep darwin`" != "" ] ; then
LIBTOOLIZE="glibtoolize"
else
LIBTOOLIZE="libtoolize"
fi

($LIBTOOLIZE --version) < /dev/null > /dev/null 2>&1 || {
    echo $LIBTOOLIZE not found
    exit 1
}

$LIBTOOLIZE --automake --force --copy

echo automake...
(automake --version) < /dev/null > /dev/null 2>&1 || {
    echo automake not found
    exit 1
}

automake --add-missing --copy --gnu

echo autoconf...
(autoconf --version) < /dev/null > /dev/null 2>&1 || {
    echo autoconf not found
    exit 1
}

autoconf

if test "x$NOCONFIGURE" = "x" ; then
    CONFIGUREFLAGS="--enable-debug=yes $@"
    echo Running: configure $CONFIGUREFLAGS
    ./configure $CONFIGUREFLAGS
fi


exit 0
