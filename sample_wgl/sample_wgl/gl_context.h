// -*- mode: c++; coding: shift_jis-dos; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#ifndef __H_GL_CONTEXT__
#define __H_GL_CONTEXT__

/// OpenGL のコンテキストWrapper
class GLContext
{
  public:
    /// コンストラクタ
    GLContext();

    ///デストラクタ
    virtual ~GLContext();

    /// 初期化処理
    bool Init(void* handle);

    /// コンテキストをバインドする
    void Begin();

    /// コンテキストを案バインドする
    void End();

    /// (この環境で)サポートされているか確認する
    bool IsSupportedAPI(void* proc);

  private:
    /// gl のバージョン確認
    bool CheckVersion();

  private:
    class Impl;
    Impl* impl_;

  private: // not imp.
    GLContext(const GLContext&);
    GLContext& operator= (const GLContext&);
};


#endif // __H_GL_CONTEXT__
//===
// EOF
//===
