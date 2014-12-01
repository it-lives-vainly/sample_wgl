// -*- mode: c++; coding: shift_jis-dos; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#include "stdafx.h"
#include "common.h"
#include "wgl_proc_list.h"

// WGLProc のための関数ポインタ実態
#define DEF_GL_PROC(type,name) type name;
#include "wgl_proc.inl"
#undef  DEF_GL_PROC

/// WGL 関連の ProcAddress を確定させる
void BindWGLProcAddress()
{
    struct GLProc {
        const char* proc;
        void** addr;
    };
    struct GLProcTable {
        const char* ver_name;
        GLProc* api_list;
    };

#define DEF_GL_PROC(type,name) { #name, (void**)&name },

    static GLProc wgl_list[] = {
#include "wgl_proc.inl"
		{ NULL, NULL },
    };

    static GLProcTable api_table[] = {
        { "WGL", wgl_list},
    };
#undef  DEF_GL_PROC

    for (int i = 0; i < ARRAY_SIZE(api_table); i++) {
        DBG_LOG(0, StrFormat("%s\n", api_table[i].ver_name).c_str());
        const GLProc* list = api_table[i].api_list;
        for (; list->proc; list++) {
            *list->addr = wglGetProcAddress(list->proc);

            if (!*list->addr) {
                int errcode= GetLastError();
                DBG_LOG(0, StrFormat("[%s] '%s' not found %d/%x\n", api_table[i].ver_name, list->proc, errcode, errcode).c_str());
            }
        }
    }
}


//===
// EOF
//===
