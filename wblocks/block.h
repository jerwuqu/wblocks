#pragma once

#include "wblocks.h"

#include <stdint.h>
#include <luajit.h>
#include <lualib.h>
#include <lauxlib.h>

struct wtext
{
    wchar_t* wstr;
    int wlen;
};

struct ltimer
{
    uint64_t time;
    int luaRef;
    struct ltimer* prev;
    struct ltimer* next;
};

// Only to be accessed from script thread after creation
struct block_BlockThreadData
{
    int blockId;
    char* scriptPath;
    lua_State* L;
    struct ltimer timerRoot;
};

// _NOT_ to be accessed from script thread
struct block_Block
{
    int blockId;
    char blockIsScripted;
    DWORD scriptThreadId;
    int bar_xpos, bar_width;

    struct wtext text;
    COLORREF color;
};

enum block_ModifyEventType
{
    BLOCK_MEVENT_NONE,
    BLOCK_MEVENT_SETTEXT,
    BLOCK_MEVENT_SETCOLOR,
    BLOCK_MEVENT_MOUSE_DOWN
};

struct block_ModifyEvent
{
    int blockId;
    enum block_ModifyEventType type;

    union
    {
        wchar_t* wstr;
    };

    union
    {
        int wstrlen; // length in characters, not bytes
        COLORREF color;
    };
};

enum block_InteractEventType
{
    BLOCK_IEVENT_NONE,
    BLOCK_IEVENT_MOUSE_DOWN
};

struct block_InteractEvent
{
    enum block_InteractEventType type;
};

struct block_Block* block_addScriptBlock(char* scriptPath);
struct block_Block* block_addStaticBlock(char* str, int len);
void block_barEventHandler(struct block_ModifyEvent* event);
int block_getBlockCount();
struct block_Block** block_getBlocks();
