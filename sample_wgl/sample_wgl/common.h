// -*- mode: c++; coding: shift_jis-dos; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#ifndef __H_COMMON__
#define __H_COMMON__

#include <string>

/// std::string ‚É‘Î‚·‚é format
std::string StrFormatVA( const char* i_format, va_list i_va );

/// std::string ‚É‘Î‚·‚é format
std::string StrFormat( const char* i_format, ... );

#define ARRAY_SIZE( ptr )         (sizeof(ptr)/sizeof(ptr[0]))
#define DBG_ASSERT(i_exp, ...) if( !(i_exp) ){ ::OutputDebugStringA( __VA_ARGS__ ); abort();}
#define DBG_LOG(id, ...)       if (true) {::OutputDebugStringA( __VA_ARGS__ ); }
#define DBG_TRACE(id, ...)       if (true) {::OutputDebugStringA( __VA_ARGS__ ); }


#define SAFE_DELETE(ptr) if (ptr) { delete ptr; }

#endif // __H_COMMON__
//===
// EOF
//===
