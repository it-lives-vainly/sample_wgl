// -*- mode: c++; coding: shift_jis-dos; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#include "stdafx.h"
#include "common.h"
#include "gl_context.h"
#include <GL/gl.h>
#include <GL/wglext.h>
#include <GL/glext.h>
#include "gl_proc_list.h"
#include "wgl_proc_list.h"
#include <iostream>
#include <string>

using namespace std;

class GLContext::Impl
{
  public:
    Impl(){}

  public:
    HDC hdc;
    HGLRC gl_context;
	std::string vendor_str;
	std::string gpu_str;
	std::string ver_str;
    int ver_major;
    int ver_minor;

};

void PrintPixelFormat(const PIXELFORMATDESCRIPTOR& pix_format) 
{
    std::string str = StrFormat("%d, %d\n", pix_format.nSize, pix_format.nVersion);
    ::OutputDebugStringA(str.c_str());
#if 0
    typedef struct tagPIXELFORMATDESCRIPTOR {
  WORD  nSize;
  WORD  nVersion;
  DWORD dwFlags;
  BYTE  iPixelType;
  BYTE  cColorBits;
  BYTE  cRedBits;
  BYTE  cRedShift;
  BYTE  cGreenBits;
  BYTE  cGreenShift;
  BYTE  cBlueBits;
  BYTE  cBlueShift;
  BYTE  cAlphaBits;
  BYTE  cAlphaShift;
  BYTE  cAccumBits;
  BYTE  cAccumRedBits;
  BYTE  cAccumGreenBits;
  BYTE  cAccumBlueBits;
  BYTE  cAccumAlphaBits;
  BYTE  cDepthBits;
  BYTE  cStencilBits;
  BYTE  cAuxBuffers;
  BYTE  iLayerType;
  BYTE  bReserved;
  DWORD dwLayerMask;
  DWORD dwVisibleMask;
  DWORD dwDamageMask;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR;
#endif
}

/// コンストラクタ
GLContext::GLContext()
    : impl_(new Impl())
{
}

///デストラクタ
GLContext::~GLContext()
{
    SAFE_DELETE(impl_);
}

/// 初期化処理
bool GLContext::Init(void* handle)
{
    impl_->hdc = GetDC((HWND)handle);
    if (!impl_->hdc) {
        DBG_ASSERT(impl_->hdc, "hDC が取得できなかった");
        return false;
    }

   // 現在対応しているフォーマットの数を参照する
   int format_count= DescribePixelFormat(impl_->hdc, 0, 0, NULL);

   // 列挙する
   for (int fi= 1; fi<= format_count; fi++) {
       PIXELFORMATDESCRIPTOR pix_format;
       DescribePixelFormat(impl_->hdc, fi, sizeof(PIXELFORMATDESCRIPTOR), &pix_format);

       //PrintPixelFormat(pix_format);
   }

   // ピクセルフォーマットの選択
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // nSize
        1,                              // nVersion
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL, // dwFlags
		PFD_TYPE_RGBA,                  // iPixelType
        24,                             // cColorBits
		0,                              // cRedBits
        0,                              // cRedShift
        0,                              // cGreenBits
        0,                              // cGreenShift
        0,                              // cBlueBits
        0,                              // cBlueShift
        0,                              // cAlphaBits
        0,                              // cAlphaShift
        0,                              // cAccumBits
        0,                              // cAccumRedBits
        0,                              // cAccumGreenBits
        0,                              // cAccumBlueBits
        0,                              // cAccumAlphaBits
        32,                             // cDepthBits
		0,                              // cStencilBits
        0,                              // cAuxBuffers
        PFD_MAIN_PLANE,                 // iLayerType
        0,                              // bReserved
        0,                              // dwLayerMask
        0,                              // dwVisibleMask
        0                               // dwDamageMask;
	};

	int pxfm = ChoosePixelFormat(impl_->hdc, &pfd);
	if (pxfm == 0) {
        DBG_ASSERT(pxfm == 0, "ChoosePixelFormat に失敗");
        return false;
    }

	if (!SetPixelFormat(impl_->hdc, pxfm, &pfd)) {
        DBG_ASSERT(false, "SetPixelFormat に失敗");
		return false;
    }

    HGLRC base_gl_context = wglCreateContext(impl_->hdc);
    if (base_gl_context == NULL) {
        DBG_ASSERT(false, "base_gl_context の初期化に失敗");
        return false;
    }
    wglMakeCurrent(impl_->hdc, base_gl_context);
    {
        BindGLProcAddress();
        BindWGLProcAddress();
        if (IsSupportedAPI(wglCreateContextAttribsARB)) {
            // 使用する OpenGL のバージョンとプロファイルの指定
            static const int attr[]= {
                WGL_CONTEXT_MAJOR_VERSION_ARB,   4,
                WGL_CONTEXT_MINOR_VERSION_ARB,   3,
                WGL_CONTEXT_FLAGS_ARB,           0,
                WGL_CONTEXT_PROFILE_MASK_ARB,    WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0,
            };

            // 新しい HGLRC の作成
            HGLRC gl_context = wglCreateContextAttribsARB(impl_->hdc, NULL, attr);
            impl_->gl_context = gl_context;

			wglMakeCurrent(impl_->hdc, impl_->gl_context);
    
            // 古い HGLRC の削除と置き換え
            wglDeleteContext(base_gl_context);
        } else {
            impl_->gl_context = base_gl_context;
        }
    }
    CheckVersion();
    wglMakeCurrent(0, 0);

    return true;
}

#if 0
static GLuint _strCLen (const GLubyte* s, GLubyte c)
{
  GLuint i=0;
  if (s == NULL) return 0;
  while (s[i] != '\0' && s[i] != c) i++;
  return (s[i] == '\0' || s[i] == c) ? i : 0;
}
#endif


/// バージョン確認
bool GLContext::CheckVersion()
{
	impl_->vendor_str = (char*)glGetString(GL_VENDOR);
	impl_->gpu_str = (char*)glGetString(GL_RENDERER);
	impl_->ver_str = (char*)glGetString(GL_VERSION);

    std::string::size_type dot = impl_->ver_str.find_first_of('.');
    if (dot == std::string::npos) {
        return false;
    }
    impl_->ver_major = impl_->ver_str[dot-1] - '0';
    impl_->ver_minor = impl_->ver_str[dot+1] - '0';

	
	DBG_LOG(0, StrFormat("Vendor : %s\n", impl_->vendor_str.c_str()).c_str());
	DBG_LOG(0, StrFormat("GPU : %s\n", impl_->gpu_str.c_str()).c_str());
	DBG_LOG(0, StrFormat("OpenGL ver. %s\n", impl_->ver_str.c_str()).c_str());
    //DBG_LOG(0, "【拡張機能一覧】\n");
	//DBG_LOG(0, StrFormat("%s\n", glGetString(GL_EXTENSIONS)).c_str());
    return true;
}

/// コンテキストをバインドする
void GLContext::Begin()
{
    wglMakeCurrent(impl_->hdc, impl_->gl_context);
}

/// コンテキストを案バインドする
void GLContext::End()
{
    SwapBuffers(impl_->hdc);
    wglMakeCurrent(0, 0);
}

/// (この環境で)サポートされているか確認する
bool GLContext::IsSupportedAPI(void* proc)
{
    return (proc != NULL);
}


//===
// EOF
//===
