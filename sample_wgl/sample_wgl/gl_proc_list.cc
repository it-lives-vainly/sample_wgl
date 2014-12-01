// -*- mode: c++; coding: shift_jis-dos; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#include "stdafx.h"
#include "common.h"
#include "gl_proc_list.h"

// GLProc のための関数ポインタ実態
#define DEF_GL_PROC(type,name) type name;

#include "gl_proc_4_5.inl"
#include "gl_proc_4_3.inl"
#include "gl_proc_4_4.inl"
#include "gl_proc_4_2.inl"
#include "gl_proc_4_1.inl"
#include "gl_proc_4_0.inl"
#include "gl_proc_3_3.inl"
#include "gl_proc_3_2.inl"
#include "gl_proc_3_1.inl"
#include "gl_proc_2_1.inl" 
#include "gl_proc_3_0.inl" 
#include "gl_proc_2_0.inl" 
#include "gl_proc_1_5.inl" 
#include "gl_proc_1_4.inl" 
#include "gl_proc_1_3.inl" 
#include "gl_proc_1_2.inl" 

#undef  DEF_GL_PROC

/// GL 関連の ProcAddress を確定させる
void BindGLProcAddress()
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

    static GLProc gl_1_2_list[] = {
#include "gl_proc_1_2.inl" 
    { NULL, NULL },
    };
    static GLProc gl_1_3_list[] = {
#include "gl_proc_1_3.inl" 
    { NULL, NULL },
    };
    static GLProc gl_1_4_list[] = {
#include "gl_proc_1_4.inl" 
    { NULL, NULL },
    };
    static GLProc gl_1_5_list[] = {
#include "gl_proc_1_5.inl" 
    { NULL, NULL },
    };
    static GLProc gl_2_0_list[] = {
#include "gl_proc_2_0.inl" 
    { NULL, NULL },
    };
    static GLProc gl_2_1_list[] = {
#include "gl_proc_2_1.inl" 
    { NULL, NULL },
    };
    static GLProc gl_3_0_list[] = {
#include "gl_proc_3_0.inl" 
    { NULL, NULL },
    };
    static GLProc gl_3_1_list[] = {
#include "gl_proc_3_1.inl" 
    { NULL, NULL },
    };
    static GLProc gl_3_2_list[] = {
#include "gl_proc_3_2.inl"
    { NULL, NULL },
    };
    static GLProc gl_3_3_list[] = {
#include "gl_proc_3_3.inl"
    { NULL, NULL },
    };
    static GLProc gl_4_0_list[] = {
#include "gl_proc_4_0.inl"
    { NULL, NULL },
    };
    static GLProc gl_4_1_list[] = {
#include "gl_proc_4_1.inl"
    { NULL, NULL },
    };
    static GLProc gl_4_2_list[] = {
#include "gl_proc_4_2.inl"
    { NULL, NULL },
    };
    static GLProc gl_4_3_list[] = {
#include "gl_proc_4_3.inl"
    { NULL, NULL },
    };
    static GLProc gl_4_4_list[] = {
#include "gl_proc_4_4.inl"
    { NULL, NULL },
    };
    static GLProc gl_4_5_list[] = {
#include "gl_proc_4_5.inl"
    { NULL, NULL },
    };


    static GLProcTable api_table[] = {
        { "GL_1_2", gl_1_2_list},
        { "GL_1_3", gl_1_3_list},
        { "GL_1_4", gl_1_4_list},
        { "GL_1_5", gl_1_5_list},
        { "GL_2_0", gl_2_0_list},
        { "GL_2_1", gl_2_1_list},
        { "GL_3_0", gl_3_0_list},
        { "GL_3_1", gl_3_1_list},
        { "GL_3_2", gl_3_2_list},
        { "GL_3_3", gl_3_3_list},
        { "GL_4_0", gl_4_0_list},
        { "GL_4_1", gl_4_1_list},
        { "GL_4_2", gl_4_2_list},
        { "GL_4_3", gl_4_3_list},
        { "GL_4_4", gl_4_4_list},
        { "GL_4_5", gl_4_5_list},
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
