# this awk script helps create the vb6 declarations
function splittypenamedefault(s,tnd,   i,t,n,d,a)
{
	i = index(s,"=");
	if(i>0) {
		d = substr(s,i+1);
		s = substr(s,1,i-1);
	} else {
		d = "";
	}
	for(i=length(s);substr(s,i,1)~/[A-Za-z0-9_]/&&i>0;i--) { }
	if(i>0) {
		t = substr(s,1,i);
		n = substr(s,i+1);
		if(t~/\/\*.*\*\//) {
			split(t,a,/\/\*/);
			t = a[2];
			split(t,a,/\*\//);
			t = a[1];
		}
		if(substr(t,1,1)==" ") {
			t = substr(t,2);
		}
		if(substr(t,length(t),1)==" ") {
			t = substr(t,1,length(t)-1);
		}
	} else {
		t = s;
		n = "";
	}
	if(t=="...") {
		n = "VarArgs()";
	}
	if(n=="type") {
		n = n "_";
	}
	if(d=="FALSE"||d=="NULL") {
		d = "0";
	}
	if(d=="TRUE") {
		d = "1";
	}
	tnd[0] = t;
	tnd[1] = n;
	tnd[2] = d;
}
function vbpasstypesize(t,pts,   a)
{
	if(t=="void") {
		t = "";
	} else if(t=="char"||t=="unsigned char") {
		t = "ByVal,Byte,4";
	} else if(t=="char *"||t=="unsigned char *"||t=="const char *"||t=="const char*") {
		t = "ByVal,String,4";
	} else if(t=="WORD") {
		t = "ByVal,Integer,4";
	} else if(t=="int"||t=="unsigned"||t=="unsigned int"||t=="long"||t=="unsigned long") {
		t = "ByVal,Long,4";
	} else if(t=="void *"||t=="const void *"||t=="int *"||t=="unsigned int *"||t=="long *"||t=="unsigned long *") {
		t = "ByRef,Long,4";
	} else if(t=="float") {
		t = "ByVal,Single,4";
	} else if(t=="float *") {
		t = "ByRef,Single,4";
	} else if(t=="double") {
		t = "ByVal,Double,8";
	} else if(t=="double *") {
		t = "ByRef,Double,4";
	} else if(t=="wchar_t *") {
		t = "ByVal,Long,4";
	} else if(t=="BYTE") {
		t = "ByVal,Byte,4";
	} else if(t=="BOOL"||t=="DWORD") {
		t = "ByVal,Long,4";
	} else if(t=="BYTE *"||t=="DWORD *") {
		t = "ByRef,Long,4";
	} else if(t=="FREE_IMAGE_FORMAT"||t=="FREE_IMAGE_TYPE"||t=="FREE_IMAGE_COLOR_TYPE"||t=="FREE_IMAGE_QUANTIZE"||t=="FREE_IMAGE_DITHER"||t=="FREE_IMAGE_FILTER"||t=="FREE_IMAGE_COLOR_CHANNEL"||t=="FREE_IMAGE_MDMODEL"||t=="FREE_IMAGE_MDTYPE") {
		t = "ByVal," t ",4";
	} else if(t=="FIBITMAP *"||t=="FIMULTIBITMAP *"||t=="RGBQUAD *"||t=="BITMAPINFO *"||t=="BITMAPINFOHEADER *"||t=="FIICCPROFILE *"||t=="FreeImageIO *"||t=="fi_handle"||t=="FITAG *"||t=="FIMEMORY *"||t=="FIMETADATA *") {
		t = "ByVal,Long,4";
	} else if(t=="BYTE **"||t=="FITAG **") {
		t = "ByRef,Long,4";
	} else if(t=="FI_InitProc"||t=="FreeImage_OutputMessageFunction") {
		t = "ByVal,Long,4";
	} else if(t~/V:.*/) {
		t = "ByVal," substr(t,3);
	} else if(t~/R:.*/) {
		t = "ByRef," substr(t,3);
	} else if(t=="...") {
		t = "ParamArray,Variant,0";
	} else {
		t = "UNKNOWN," t ",0";
	}
	split(t,a,/,/);
	pts[0] = a[1];
	pts[1] = a[2];
	pts[2] = a[3];
}
{
	printf("Public Declare ");
	if($1=="void") {
		printf("Sub");
	} else {
		printf("Function");
	}
	s = 0;
	for(i=3; i<NF; i++) {
		splittypenamedefault($(i),tnd);
		vbpasstypesize(tnd[0],pts);
		s += pts[2];
	}
	printf(" %s Lib \"%s\" Alias \"_%s@%d\" (",$2,ENVIRON["DLL"],$2,s);
	for(i=3; i<NF; i++) {
		splittypenamedefault($(i),tnd);
		vbpasstypesize(tnd[0],pts);
		if( pts[1] != "" ) {
			if( tnd[2] != "" ) {
				printf("Optional %s %s As %s = %s",pts[0],tnd[1],pts[1],tnd[2]);
			} else {
				printf("%s %s As %s",pts[0],tnd[1],pts[1]);
			}
		}
		if( i != NF-1 ) {
			printf(", ");
		}
	}
	printf(")");
	if($1!="void") {
		vbpasstypesize($1,pts);
		if( pts[1] == "String" ) {
			pts[1] = "Long";
		}
		printf(" As %s",pts[1]);
	}
	printf("\n");
}
