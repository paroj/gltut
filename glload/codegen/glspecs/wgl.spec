# Copyright (c) 1991-2002 Silicon Graphics, Inc. All Rights Reserved.
# Copyright (c) 2006-2010 The Khronos Group, Inc.
#
# This document is licensed under the SGI Free Software B License Version
# 2.0. For details, see http://oss.sgi.com/projects/FreeB/ .
#
# $Revision: 10796 $ on $Date: 2010-03-19 17:31:10 -0700 (Fri, 19 Mar 2010) $

required-props:
param:		retval retained
dlflags:	notlistable handcode nop
wglflags:	client-handcode server-handcode non-dispatch
vectorequiv:	*
category:	wgl

CreateContext( hDc )
	return		HGLRC
	param		hDc		HDC in value
	category	wgl
	dlflags		notlistable handcode
	wglflags	non-dispatch

DeleteContext( oldContext )
	return		BOOL
	param		oldContext	HGLRC in value
	category	wgl
	dlflags		notlistable handcode
	wglflags	non-dispatch

GetCurrentContext( )
	return		HGLRC
	category	wgl
	dlflags		notlistable handcode
	wglflags	non-dispatch

MakeCurrent( hDc, newContext )
	return		BOOL
	param		hDc		HDC in value
	param		newContext	HGLRC in value
	category	wgl
	dlflags		notlistable
	wglflags	non-dispatch

CopyContext( hglrcSrc, hglrcDst, mask )
	return		BOOL
	param		hglrcSrc	HGLRC in value
	param		hglrcDst	HGLRC in value
	param		mask		UINT in value
	category	wgl
	dlflags		notlistable
	wglflags	non-dispatch

ChoosePixelFormat( hDc, pPfd )
	return		int
	param		hDc		HDC in value
	param		pPfd		PIXELFORMATDESCRIPTOR in reference
	category	wgl
	dlflags		notlistable
	wglflags	non-dispatch

DescribePixelFormat( hdc, ipfd, cjpfd, ppfd )
	return		int
	param		hdc		HDC in value
	param		ipfd		int in value
	param		cjpfd		UINT in value
	param		ppfd		PIXELFORMATDESCRIPTOR in reference

GetCurrentDC( )
	return		HDC
	category	wgl

GetDefaultProcAddress( lpszProc)
	return		PROC
	param		lpszProc	LPCSTR in value
	category	wgl

GetProcAddress( lpszProc)
	return		PROC
	param		lpszProc	LPCSTR in value
	category	wgl

GetPixelFormat( hdc )
	return		int
	param		hdc		HDC in value
	category	wgl

SetPixelFormat( hdc, ipfd, ppfd )
	return		BOOL
	param		hdc		HDC in value
	param		ipfd		int in value
	param		ppfd		PIXELFORMATDESCRIPTOR in reference
	category	wgl

SwapBuffers( hdc )
	return		BOOL
	param		hdc		HDC in value
	category	wgl

ShareLists( hrcSrvShare, hrcSrvSource)
	return		BOOL
	param		hrcSrvShare	HGLRC in value
	param		hrcSrvSource	HGLRC in value
	category	wgl

CreateLayerContext( hDc, level )
	return		HGLRC
	param		hDc		HDC in value
	param		level		int in value
	category	wgl

DescribeLayerPlane( hDc, pixelFormat, layerPlane, nBytes, plpd )
	return		BOOL
	param		hDc		HDC in value
	param		pixelFormat	int in value
	param		layerPlane	int in value
	param		nBytes		UINT in value
	param		plpd		LAYERPLANEDESCRIPTOR in reference
	category	wgl

SetLayerPaletteEntries( hdc, iLayerPlane, iStart, cEntries, pcr )
	return		int
	param		hdc		HDC in value
	param		iLayerPlane	int in value
	param		iStart		int in value
	param		cEntries	int in value
	param		pcr		COLORREF in reference
	category	wgl

GetLayerPaletteEntries( hdc, iLayerPlane, iStart, cEntries, pcr )
	return		int
	param		hdc		HDC in value
	param		iLayerPlane	int in value
	param		iStart		int in value
	param		cEntries	int in value
	param		pcr		COLORREF in reference
	category	wgl

RealizeLayerPalette( hdc, iLayerPlane, bRealize )
	return		BOOL
	param		hdc		HDC in value
	param		iLayerPlane	int in value
	param		bRealize	BOOL in value
	category	wgl

SwapLayerBuffers( hdc, fuFlags )
	return		BOOL
	param		hdc		HDC in value
	param		fuFlags		UINT in value
	category	wgl

UseFontBitmapsA( hDC, first, count, listBase )
	return		BOOL
	param		hDC		HDC in value
	param		first		DWORD in value
	param		count		DWORD in value
	param		listBase	DWORD in value
	category	wgl
	dlflags		notlistable

UseFontBitmapsW( hDC, first, count, listBase )
	return		BOOL
	param		hDC		HDC in value
	param		first		DWORD in value
	param		count		DWORD in value
	param		listBase	DWORD in value
	category	wgl
	dlflags		notlistable

