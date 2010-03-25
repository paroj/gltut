#!/bin/sh

HDR=../../../Source/FreeImage.h
BAS=../modFreeImage.bas
DLL=FreeImage.dll

echo Attribute VB_Name = \"FreeImage\" > $BAS
echo Option Explicit >> $BAS

echo >> $BAS
gcc -E -P -dD $HDR | egrep '^#[ 	]*define[ 	]+[A-Z][0-9A-Z_]*[	 ]+([0-9]+|0x[0-9A-Fa-f]+|"[^"]*")' | awk '{sub(/0x/,"\\&H",$3);if($2!="TRUE"&&$2!="FALSE"&&$2!="NULL")printf("Const %s As %s = %s\n",$2,substr($3,1,1)=="\""?"String":"Long",$3);}' >> $BAS

echo >> $BAS
gcc -E -P $HDR | indent -kr | tr -s '\n' | awk '{if(e&&$0~"^}"){e=0;printf("End Enum\n");}if(e){printf("\t%s",$1);if($2=="="){sub(/,/,"",$3);printf(" = %s",$3);}printf("\n");}if($0~"^enum "){e=1;printf("Public Enum %s\n",$2);}}' >> $BAS

echo >> $BAS
gcc -E -P $HDR | indent -kr | tr -s '\n' | awk '{if(e&&$0~"^}"){e=0;if(n==""){n=$2;sub(/,|;/,"",n);}printf("Public Type %s\n%sEnd Type\n",n,s);}if(e){if(substr($2,1,1)=="*")$1=$1 " *";gsub(/;|\*/,"",$2);sub(/\[1\]/,"(0)",$2);if($1=="BYTE")$1="Byte";else if($1=="WORD")$1="Integer";else if($1=="double")$1="Double";else if($1!="BITMAPINFOHEADER"&&$1!="RGBQUAD") $1="Long";s=s "\t" $2 " As " $1 "\n";}if($0~"^struct "){e=1;n=$2;s="";}if($0~"^typedef struct [^ ]+ {"){e=1;n="";s=""}}' >> $BAS

echo >> $BAS
export DLL
grep ^DLL_API $HDR | sed 's/DLL_API //;s/ *DLL_CALLCONV /,/;s/ FI_DEFAULT(\([^)]*\))/=\1/g;s/(/,/g;s/)/,/g' | awk -F"," -f genbasfuncs.awk >> $BAS
