// -*- mode: c++; coding: utf-8-unix; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#ifndef __H_WGL_PROC_LIST__
#define __H_WGL_PROC_LIST__

#include <GL/gl.h>
#include <GL/wglext.h>

#define DEF_GL_PROC(type,name) extern type name;

#include "wgl_proc.inl"

#undef  DEF_GL_PROC

/// WGL 関連の ProcAddress を確定させる
void BindWGLProcAddress();


#endif // __H_WGL_PROC_LIST__
//===
// EOF
//===
