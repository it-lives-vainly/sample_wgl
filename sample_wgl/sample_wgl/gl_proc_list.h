// -*- mode: c++; coding: utf-8-unix; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#ifndef __H_GL_PROC_LIST__
#define __H_GL_PROC_LIST__

#include <GL/gl.h>
#include <GL/glext.h>

#define DEF_GL_PROC(type,name) extern type name;

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
void BindGLProcAddress();


#endif // __H_GL_PROC_LIST__
//===
// EOF
//===
