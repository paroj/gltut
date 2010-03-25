#!/bin/sh

DIRLIST=". Source Source/Metadata Source/FreeImageToolkit Source/LibJPEG Source/LibMNG Source/LibPNG Source/LibTIFF Source/ZLib Source/LibOpenJPEG Source/OpenEXR Source/OpenEXR/Half Source/OpenEXR/Iex Source/OpenEXR/IlmImf Source/OpenEXR/IlmThread Source/OpenEXR/Imath Source/LibRawLite Source/LibRawLite/dcraw Source/LibRawLite/internal Source/LibRawLite/libraw Source/LibRawLite/src Wrapper/FreeImagePlus"


echo "VER_MAJOR = 3" > fipMakefile.srcs
echo "VER_MINOR = 13.1" >> fipMakefile.srcs

echo -n "SRCS = " >> fipMakefile.srcs
for DIR in $DIRLIST; do
	VCPRJS=`echo $DIR/*.2003.vcproj`
	if [ "$VCPRJS" != "$DIR/*.2003.vcproj" ]; then
		egrep 'RelativePath=.*\.(c|cpp)' $DIR/*.2003.vcproj | cut -d'"' -f2 | tr '\\' '/' | awk '{print "'$DIR'/"$0}' | tr '\r\n' '  ' | tr -s ' ' >> fipMakefile.srcs
	fi
done
echo >> fipMakefile.srcs

echo -n "INCLUDE =" >> fipMakefile.srcs
for DIR in $DIRLIST; do
	echo -n " -I$DIR" >> fipMakefile.srcs
done
echo >> fipMakefile.srcs

