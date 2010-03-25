// ==========================================================
// Tag manipulation functions
//
// Design and implementation by
// - Hervé Drolon <drolon@infonie.fr>
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
// ==========================================================

#ifdef _MSC_VER 
#pragma warning (disable : 4786) // identifier was truncated to 'number' characters
#endif

#include "FreeImage.h"
#include "Utilities.h"
#include "FreeImageTag.h"

// --------------------------------------------------------------------------
// FITAG header definition
// --------------------------------------------------------------------------

FI_STRUCT (FITAGHEADER) { 
	char *key;			// tag field name
	char *description;	// tag description
	WORD id;			// tag ID
	WORD type;			// tag data type (see FREE_IMAGE_MDTYPE)
	DWORD count;		// number of components (in 'tag data types' units)
	DWORD length;		// value length in bytes
	void *value;		// tag value
};

// --------------------------------------------------------------------------
// FITAG creation / destruction
// --------------------------------------------------------------------------

FITAG * DLL_CALLCONV 
FreeImage_CreateTag() {
	FITAG *tag = (FITAG *)malloc(sizeof(FITAG));

	if (tag != NULL) {
		unsigned tag_size = sizeof(FITAGHEADER); 
		tag->data = (BYTE *)malloc(tag_size * sizeof(BYTE));
		if (tag->data != NULL) {
			memset(tag->data, 0, tag_size);
			return tag;
		}
		free(tag);
	}

	return NULL;
}

void DLL_CALLCONV 
FreeImage_DeleteTag(FITAG *tag) {
	if (NULL != tag) {	
		if (NULL != tag->data) {
			FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;
			// delete tag members
			free(tag_header->key); 
			free(tag_header->description); 
			free(tag_header->value);
			// delete the tag
			free(tag->data);
		}
		// and the wrapper
		free(tag);
	}
}

FITAG * DLL_CALLCONV 
FreeImage_CloneTag(FITAG *tag) {
	if(!tag) return NULL;

	// allocate a new tag
	FITAG *clone = FreeImage_CreateTag();
	if(!clone) return NULL;

	// copy the tag
	FITAGHEADER *src_tag = (FITAGHEADER *)tag->data;
	FITAGHEADER *dst_tag = (FITAGHEADER *)clone->data;

	// tag ID
	dst_tag->id = src_tag->id;
	// tag key
	if(src_tag->key) {
		dst_tag->key = (char*)malloc((strlen(src_tag->key) + 1) * sizeof(char));
		strcpy(dst_tag->key, src_tag->key);
	}
	// tag description
	if(src_tag->description) {
		dst_tag->description = (char*)malloc((strlen(src_tag->description) + 1) * sizeof(char));
		strcpy(dst_tag->description, src_tag->description);
	}
	// tag data type
	dst_tag->type = src_tag->type;
	// tag count
	dst_tag->count = src_tag->count;
	// tag length
	dst_tag->length = src_tag->length;
	// tag value
	switch(dst_tag->type) {
		case FIDT_ASCII:
			dst_tag->value = (char*)malloc((strlen((char*)src_tag->value) + 1) * sizeof(char));
			strcpy((char*)dst_tag->value, (char*)src_tag->value);
			break;
		default:
			dst_tag->value = (BYTE*)malloc(src_tag->length * sizeof(BYTE));
			memcpy(dst_tag->value, src_tag->value, src_tag->length);
			break;
	}

	return clone;
}

// --------------------------------------------------------------------------
// FITAG getters / setters
// --------------------------------------------------------------------------

const char * DLL_CALLCONV 
FreeImage_GetTagKey(FITAG *tag) {
	return tag ? ((FITAGHEADER *)tag->data)->key : 0;
}

const char * DLL_CALLCONV 
FreeImage_GetTagDescription(FITAG *tag) {
	return tag ? ((FITAGHEADER *)tag->data)->description : 0;
}

WORD DLL_CALLCONV 
FreeImage_GetTagID(FITAG *tag) {
	return tag ? ((FITAGHEADER *)tag->data)->id : 0;
}

FREE_IMAGE_MDTYPE DLL_CALLCONV 
FreeImage_GetTagType(FITAG *tag) {
	return tag ? (FREE_IMAGE_MDTYPE)(((FITAGHEADER *)tag->data)->type) : FIDT_NOTYPE;
}

DWORD DLL_CALLCONV 
FreeImage_GetTagCount(FITAG *tag) {
	return tag ? ((FITAGHEADER *)tag->data)->count : 0;
}

DWORD DLL_CALLCONV 
FreeImage_GetTagLength(FITAG *tag) {
	return tag ? ((FITAGHEADER *)tag->data)->length : 0;
}

const void *DLL_CALLCONV 
FreeImage_GetTagValue(FITAG *tag) {
	return tag ? ((FITAGHEADER *)tag->data)->value : 0;
}

BOOL DLL_CALLCONV 
FreeImage_SetTagKey(FITAG *tag, const char *key) {
	if(tag && key) {
		FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;
		if(tag_header->key) free(tag_header->key);
		tag_header->key = (char*)malloc(strlen(key) + 1);
		strcpy(tag_header->key, key);
		return TRUE;
	}
	return FALSE;
}

BOOL DLL_CALLCONV 
FreeImage_SetTagDescription(FITAG *tag, const char *description) {
	if(tag && description) {
		FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;
		if(tag_header->description) free(tag_header->description);
		tag_header->description = (char*)malloc(strlen(description) + 1);
		strcpy(tag_header->description, description);
		return TRUE;
	}
	return FALSE;
}

BOOL DLL_CALLCONV 
FreeImage_SetTagID(FITAG *tag, WORD id) {
	if(tag) {
		FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;
		tag_header->id = id;
		return TRUE;
	}
	return FALSE;
}

BOOL DLL_CALLCONV 
FreeImage_SetTagType(FITAG *tag, FREE_IMAGE_MDTYPE type) {
	if(tag) {
		FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;
		tag_header->type = (WORD)type;
		return TRUE;
	}
	return FALSE;
}

BOOL DLL_CALLCONV 
FreeImage_SetTagCount(FITAG *tag, DWORD count) {
	if(tag) {
		FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;
		tag_header->count = count;
		return TRUE;
	}
	return FALSE;
}

BOOL DLL_CALLCONV 
FreeImage_SetTagLength(FITAG *tag, DWORD length) {
	if(tag) {
		FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;
		tag_header->length = length;
		return TRUE;
	}
	return FALSE;
}

BOOL DLL_CALLCONV 
FreeImage_SetTagValue(FITAG *tag, const void *value) {
	if(tag) {
		FITAGHEADER *tag_header = (FITAGHEADER *)tag->data;
		// first, check the tag
		if(tag_header->count * FreeImage_TagDataWidth(tag_header->type) != tag_header->length) {
			// invalid data count ?
			return FALSE;
		}

		if(tag_header->value) free(tag_header->value);

		switch(tag_header->type) {
			case FIDT_ASCII:
			{
				tag_header->value = (char*)malloc((tag_header->length + 1) * sizeof(char));
				char *src_data = (char*)value;
				char *dst_data = (char*)tag_header->value;
				for(DWORD i = 0; i < tag_header->length; i++) {
					dst_data[i] = src_data[i];
				}
				dst_data[tag_header->length] = '\0';
			}
			break;

			default:
				tag_header->value = malloc(tag_header->length * sizeof(BYTE));
				memcpy(tag_header->value, value, tag_header->length);
				break;
		}
		return TRUE;
	}
	return FALSE;
}


// --------------------------------------------------------------------------
// FITAG internal helper functions
// --------------------------------------------------------------------------

int 
FreeImage_TagDataWidth(WORD type) {
	static int format_bytes[] = { 0, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 4, 8, 4, 4 };

	return (type < 15) ? format_bytes[type] : 0;
}



