#!/bin/sh
#
# Script for generating a release archive (OS3/AROS only).
#

HOST="${1:-m68k-amigaos}"
FORMAT="${2:-lha}"

if [ "$HOST" = "m68k-amigaos" ]; then
  make -f makefile.os3 all
else
  CPU=`echo "${HOST}" | cut -d'-' -f1`
  make -f makefile.aros CPU=${CPU} all
fi;

LIBSMB2='libsmb2-git'
DESTDIR='tmp'

rm -rf ${DESTDIR}
mkdir -p ${DESTDIR}/smb2fs/L

if [ "$HOST" = "m68k-amigaos" ]; then
  cp -p Install-OS3 ${DESTDIR}/smb2fs/Install
  cp -p README-OS3 ${DESTDIR}/smb2fs/README
  cp -p bin/smb2-handler.000 ${DESTDIR}/smb2fs/L
  cp -p bin/smb2-handler.020 ${DESTDIR}/smb2fs/L
  cp -p bin/smb2-handler.060 ${DESTDIR}/smb2fs/L
else
  cp -p Install-AROS ${DESTDIR}/smb2fs/Install
  cp -p README-AROS ${DESTDIR}/smb2fs/README
  cp -p bin/smb2-handler.${CPU} ${DESTDIR}/smb2fs/L/smb2-handler
fi;
cp -p COPYING ${DESTDIR}/smb2fs
cp -p ${LIBSMB2}/LICENCE-LGPL-2.1.txt ${DESTDIR}/smb2fs/LICENCE-libsmb2
cp -p releasenotes ${DESTDIR}/smb2fs

cp -p icons-os3/def_drawer.info ${DESTDIR}/smb2fs.info
cp -p icons-os3/def_install.info ${DESTDIR}/smb2fs/Install.info
cp -p icons-os3/def_doc.info ${DESTDIR}/smb2fs/README.info
cp -p icons-os3/def_doc.info ${DESTDIR}/smb2fs/COPYING.info
cp -p icons-os3/def_doc.info ${DESTDIR}/smb2fs/LICENCE-libsmb2.info
cp -p icons-os3/def_doc.info ${DESTDIR}/smb2fs/releasenotes.info

case "${FORMAT}" in
  "7z")
    rm -f smb2fs.${HOST}.7z
    7za u smb2fs.${HOST}.7z ./${DESTDIR}/*
    echo "smb2fs.${HOST}.7z created"
    ;;
  "iso")
    rm -f smb2fs.${HOST}.iso
    PREVDIR=`pwd`
    cd ${DESTDIR} && mkisofs -R -o ../smb2fs.${HOST}.iso -V SMB2FS .
    cd ${PREVDIR}
    echo "smb2fs.${HOST}.iso created"
    ;;
  "lha")
    rm -f smb2fs.${HOST}.lha
    PREVDIR=`pwd`
    cd ${DESTDIR} && lha ao5 ../smb2fs.${HOST}.lha *
    cd ${PREVDIR}
    echo "smb2fs.${HOST}.lha created"
    ;;
esac

rm -rf ${DESTDIR}

