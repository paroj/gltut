unit FreeUtils;

// ==========================================================
//
// Delphi wrapper for FreeImage 3
//
// Design and implementation by
// - Anatoliy Pulyaevskiy (xvel84@rambler.ru)
//
// Contributors:
// - Enzo Costantini (enzocostantini@libero.it)
//
// This file is part of FreeImage 3
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at your own risk!
//
// ==========================================================

interface

uses
    SysUtils, Classes, FreeImage;

function FIU_GetFIFType(filename: string): FREE_IMAGE_FORMAT;

// returns FIF (plugin) description string
function FIU_GetFIFDescription(fif: FREE_IMAGE_FORMAT): string;

procedure FIU_GetAllDescriptions(var Descriptions: TStringList);

// returns file extentions for FIF (e.g. '*.tif;*.tiff)
function FIU_GetFIFExtList(fif: FREE_IMAGE_FORMAT): string;

// returns file extentions for all plugins
function FIU_GetFullExtList: string;

// returns "Description + | + ExtList" for specified FIF
function FIU_GetFIFFilter(fif: FREE_IMAGE_FORMAT): string;

// All supported formats + Full filter list for FIFs + All files
function FIU_GetAllFilters: string;

implementation

uses StrUtils;

function FIU_GetFIFType(filename: string): FREE_IMAGE_FORMAT;
begin
  Result:=FreeImage_GetFileType(PAnsiChar(filename),0);
end;

function FIU_GetFIFDescription(fif: FREE_IMAGE_FORMAT): string;
begin
  Result := FreeImage_GetFIFDescription(fif)
end;

procedure FIU_GetAllDescriptions(var Descriptions: TStringList);
var
  fif: FREE_IMAGE_FORMAT;
begin
  Descriptions.Clear;
  for fif := FIF_BMP to FIF_XPM do
    Descriptions.Add(FreeImage_GetFIFDescription(fif) + ' (' + FIu_GetFIFExtList(fif) + ')')
end;

function FIU_GetFIFExtList(fif: FREE_IMAGE_FORMAT): string;
var
  ExtList: string;
  I: Smallint;
  C: Char;
begin
  Result := '*.';
  ExtList := FreeImage_GetFIFExtensionList(fif);
  for I := 1 to Length(ExtList) do
  begin
    C := ExtList[i];
    if C <> ',' then
      Result := Result + C
    else
      Result := Result + ';*.';
  end
end;

function FIU_GetFullExtList: string;
var
  fif: FREE_IMAGE_FORMAT;
begin
  Result := FIU_GetFIFExtList(FIF_BMP);
  for fif := FIF_ICO to FIF_XPM do
    Result := Result + ';' + FIU_GetFIFExtList(fif)
end;

function FIU_GetFIFFilter(fif: FREE_IMAGE_FORMAT): string;
var
  Text, ExtList: string;
begin
  Result := '';
  if fif <> FIF_UNKNOWN then
  begin
    Text := Trim(FreeImage_GetFIFDescription(fif));
    ExtList := FIU_GetFIFExtList(fif);
    Result := Text + '(' + ExtList + ')' + '|' + ExtList
  end
end;

function FIU_GetAllFilters: string;
var
  fif: FREE_IMAGE_FORMAT;
begin
  Result := 'All supported formats|' + FIU_GetFullExtList;
  for fif := FIF_BMP to FIF_XPM do
  begin
    Result := Result + '|' + FIU_GetFIFFilter(fif)
  end;
end;

end.
