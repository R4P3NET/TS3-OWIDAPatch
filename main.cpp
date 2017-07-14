/* Disable Unreferenced parameter warning
-----------------------------------------*/
#ifdef _WIN32

	#pragma warning (disable : 4100) 

#endif	
/*---------------------------------------*/

/* Include
-----------------------------------------*/
#ifdef _WIN32
	#include <Windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "public_errors.h"
#include "public_errors_rare.h"
#include "public_definitions.h"
#include "public_rare_definitions.h"
#include "ts3_functions.h"
#include "plugin.h"
/*---------------------------------------*/



/* Static Allocations
-----------------------------------------*/
static struct TS3Functions ts3Functions;
static char* pluginID = NULL;
static char* wcharBuff = NULL;
/*---------------------------------------*/


/* BUFSIZE Definitions
-----------------------------------------*/
#define PLUGIN_API_VERSION 22
#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

/*---------------------------------------*/


/* WIN32 Stuff
-----------------------------------------*/

#ifdef _WIN32
	
	#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
	#define snprintf sprintf_s

	static int wcharToUtf8(const wchar_t* str, char** result) 
	{
		int outlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, 0, 0);
		*result = (char*)malloc(outlen);
		if(WideCharToMultiByte(CP_UTF8, 0, str, -1, *result, outlen, 0, 0) == 0) 
		{
			*result = NULL;
			return -1;
		}
		return 0;
	}

#else
	#define _strcpy(dest, destSize, src) { strncpy(dest, src, destSize-1); (dest)[destSize-1] = '\0'; }
#endif
/*---------------------------------------*/


/* Menu ID Definitions
------------------------------------------*/
enum {
	R4P3_CRASH_CLIENT = 1,
	R4P3_CRASH_CHANNEL,
};
/*----------------------------------------*/


/* Plugin ID
-----------------------------------------*/
void ts3plugin_registerPluginID(const char* id) 
{
	const size_t sz = strlen(id) + 1;
	pluginID = (char*)malloc(sz * sizeof(char));
	_strcpy(pluginID, sz, id);
}
/*---------------------------------------*/



/* Name
-----------------------------------------*/
const char* ts3plugin_name() 
{
	return "R4P3 OWIDA Exploit Patch";
}
/*---------------------------------------*/



/* Version
-----------------------------------------*/
const char* ts3plugin_version() 
{
	return "1.0";
}
/*---------------------------------------*/



/* API Version
-----------------------------------------*/
int ts3plugin_apiVersion() 
{
	return PLUGIN_API_VERSION;
}
/*---------------------------------------*/



/* Author
-----------------------------------------*/
const char* ts3plugin_author() 
{
	return "R4P3.NET";
}
/*---------------------------------------*/



/* Description
-----------------------------------------*/
const char* ts3plugin_description() 
{
	return "This plugin provides a hotfix addressing an issue affecting TeamSpeak Client versions 3.1.4.2 and below";
}
/*---------------------------------------*/



/* Plugin Command Keyword
-----------------------------------------*/
const char* ts3plugin_commandKeyword() 
{
	return "";
}
/*---------------------------------------*/



/* Plugin Init
-----------------------------------------*/
int ts3plugin_init() 
{
	wcharBuff = NULL;
	return 0;
}
/*---------------------------------------*/



/* Callbacks
-----------------------------------------*/
void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) 
{
	ts3Functions = funcs;
}
/*---------------------------------------*/

//-----------------------------------------------------------
//--- MAIN!
//-----------------------------------------------------------
int ts3plugin_onTextMessageEvent(uint64 serverConnectionHandlerID, anyID targetMode, anyID toID, anyID fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message, int ffIgnored) 
{
	/* 0 = handle normally, 1 = client will ignore the text message */
	if(targetMode == 1)
	{
		if(strlen(fromName) > 0)
		{
			return 0;
		}
		else
		{
			ts3Functions.printMessageToCurrentTab("[b][R4P3.NET][/b]:[color=red][b]Received OWIDA Exploit attempt! Successfully protected by [url=https://r4p3.net]R4P3.NET![/url][/b][/color]");
			return 1;
		}
	}
	return 0;
}


/* Plugin AutoLoad
-----------------------------------------*/
int ts3plugin_requestAutoload() 
{
	return 0;
}
/*---------------------------------------*/



/* Plugin Exit
-----------------------------------------*/
void ts3plugin_shutdown() 
{
	/* Free pluginID */
	if(pluginID) 
	{
		free(pluginID);
		pluginID = NULL;
	}
	/* Free wcharBuff */
	if(wcharBuff) 
	{
		free(wcharBuff);
		wcharBuff = NULL;
	}
}
/*---------------------------------------*/


/* Free Memory
-----------------------------------------*/
void ts3plugin_freeMemory(void* data) {
	free(data);
}
/*---------------------------------------*/
