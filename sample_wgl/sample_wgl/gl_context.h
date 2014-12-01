// -*- mode: c++; coding: shift_jis-dos; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#ifndef __H_GL_CONTEXT__
#define __H_GL_CONTEXT__

/// OpenGL �̃R���e�L�X�gWrapper
class GLContext
{
  public:
    /// �R���X�g���N�^
    GLContext();

    ///�f�X�g���N�^
    virtual ~GLContext();

    /// ����������
    bool Init(void* handle);

    /// �R���e�L�X�g���o�C���h����
    void Begin();

    /// �R���e�L�X�g���ăo�C���h����
    void End();

    /// (���̊���)�T�|�[�g����Ă��邩�m�F����
    bool IsSupportedAPI(void* proc);

  private:
    /// gl �̃o�[�W�����m�F
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
