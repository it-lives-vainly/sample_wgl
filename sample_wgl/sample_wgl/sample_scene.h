// -*- mode: c++; coding: shift_jis-dos; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#ifndef __H_GL_HELPER__
#define __H_GL_HELPER__

#include <windows.h>
#include "gl_context.h"

/// GL 関連の初期化処理
bool InitGL(void* handle);

/// OpenGL のテスト描画
void TestDraw(GLContext* gc);


#endif // __H_GL_HELPER__
//===
// EOF
//===
