#!/bin/python

import  re
import  sys

mp_api = re.compile("^GLAPI\s+[a-zA-Z0-9_*]+\s+APIENTRY\s+(.*)\s+\(")
mp_ver = re.compile("^#ifndef\s+(GL_.*)")

def ProcList( filename ):
    f= open( filename, 'r' )
    for line in f:
        pat_ver = mp_ver.search( line )
        pat_api= mp_api.search( line )
        
        if pat_ver != None:
            ver_name = pat_ver.group(1)
            print "// " + ver_name
        if pat_api != None:
            func= pat_api.group(1)
            print "DEF_GL_PROC(PFN"+ func.upper() + "PROC, " + func + ")"
    f.close()
ProcList( sys.argv[1] )
