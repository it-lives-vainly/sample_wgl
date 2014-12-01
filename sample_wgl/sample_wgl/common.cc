// -*- mode: c++; coding: shift_jis-dos; tab-width: 4; -*-
/**
 * @file
 * @brief
 * 
 * $Id$ 
 */
#include "stdafx.h"
#include "common.h"

/// std::string ‚É‘Î‚·‚é format
std::string StrFormatVA( const char* i_format, va_list i_va )
{
    char a_buf[ 65536 ];
    vsnprintf( a_buf, sizeof( a_buf ), i_format, i_va );
    a_buf[ sizeof( a_buf ) - 1 ] = '\0';
    va_end( i_va );
    return std::string( a_buf );
}

/// std::string ‚É‘Î‚·‚é format
std::string StrFormat( const char* i_format, ... )
{
    va_list a_va;
    va_start( a_va, i_format );
    std::string a_str = StrFormatVA( i_format, a_va );
    va_end( a_va );
    return a_str;
}



//===
// EOF
//===
