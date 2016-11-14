#!/usr/bin/python

import os, commands;

env = Environment()

env['CC'] = 'gcc'
env['LINKFLAGS'] = Split('-pipe -Wall')
#env['CCFLAGS'] = Split('-pipe -Wall -std=c99 -Wno-switch -Wno-unused -Wno-missing-braces -Wno-parentheses -Wno-uninitialized -fno-strict-aliasing -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -D_REENTRANT')
env['CCFLAGS'] = Split('-pipe -Wall -std=c99 -Wno-switch -Wno-unused -Wno-missing-braces -Wno-parentheses -Wno-uninitialized -fno-strict-aliasing -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -D_REENTRANT -DLOGGER_PRINT_LOGGER')
env['CPPPATH'] = []
env['CPPDEFINES'] = []
env['LIBPATH']=Split('#./')

#Import('env');

#local_ccflags=Split('-ggdb -O2 -std=c99')
local_ccflags=Split('-ggdb -g -std=c99')
#local_ccflags=Split('-O2')
local_cppdefines=[]
local_cpppath=Split('#./src/ #./src/output_plugins/ #./inc/')
local_clibs=Split('liblogger.a')
dynamic_clibs=Split('liblogger.so')
objlist=''

libs=Split('logger')

srclist=commands.getoutput('ls src/*.c src/output_plugins/*.c')
#objlist=commands.getoutput('ls src/*.o src/output_plugins/*.o')
#for i in os.system('ls *.c output_plugins/*.c'):
for i in srclist.split('\n'):
	src=i;
	objname=i[:-2]+".o"
	#print objname;
	env.StaticObject(target=objname, source=src, CCFLAGS=local_ccflags + env['CCFLAGS'], CPPPATH=env['CPPPATH'] + local_cpppath, CPPDEFINES=env['CPPDEFINES'] + local_cppdefines);
	objlist+=objname+" "
	#env.Install('src/', source = objname)
	#print objlist;

#for i in os.system
env.StaticLibrary(target=local_clibs, source=Split(objlist))
env.SharedLibrary(dynamic_clibs, source=Split(srclist), CCFLAGS=local_ccflags + env['CCFLAGS'], CPPPATH=env['CPPPATH'] + local_cpppath, CPPDEFINES=env['CPPDEFINES'] + local_cppdefines);
env.Install('src/', source = local_clibs)
env.Install('src/', source = dynamic_clibs)

examples_src=commands.getoutput('ls example/*.c test/*.c')
for i in examples_src.split('\n'):
	src=i;
	objname=i[:-2]+".o"
	#print objname;
	#gcc -C -o objname 
	StaticObject(target=objname, source=src, CCFLAGS=local_ccflags + env['CCFLAGS'], CPPPATH=env['CPPPATH'] + local_cpppath, CPPDEFINES=env['CPPDEFINES'] + local_cppdefines);
	#objlist+=objname+" "

printf_flag = Split('-Dprintf=LOG_INFO -Dfprintf=LOG_ERROR_WRAPPER')
examples_src=commands.getoutput('ls wrapper/*.c')
for i in examples_src.split('\n'):
	src=i;
	objname=i[:-2]+".o"
	#print objname;
	#gcc -C -o objname 
	#StaticObject(target=objname, source=src, CCFLAGS=local_ccflags + env['CCFLAGS'] + printf_flag, CPPPATH=env['CPPPATH'] + local_cpppath, CPPDEFINES=env['CPPDEFINES'] + local_cppdefines);
	StaticObject(target=objname, source=src, CCFLAGS=local_ccflags + env['CCFLAGS'] + printf_flag, CPPPATH=env['CPPPATH'] + local_cpppath, CPPDEFINES=env['CPPDEFINES'] + local_cppdefines);
	#objlist+=objname+" "

printf_flag = Split('-Dprintf=LOGLIB_INFO -Dfprintf=LOGLIB_ERROR_WRAPPER ')
examples_src=commands.getoutput('ls libtest/*.c')
for i in examples_src.split('\n'):
	src=i;
	objname=i[:-2]+".o"
	StaticObject(target=objname, source=src, CCFLAGS=local_ccflags + env['CCFLAGS'] + printf_flag, CPPPATH=env['CPPPATH'] + local_cpppath, CPPDEFINES=env['CPPDEFINES'] + local_cppdefines);

printf_flag = Split('-Dprintf=lsd_printf -Dfprintf=lsd_fprintf')
examples_src=commands.getoutput('ls clibtest/*.c')
for i in examples_src.split('\n'):
	src=i;
	objname=i[:-2]+".o"
	StaticObject(target=objname, source=src, CCFLAGS=local_ccflags + env['CCFLAGS'] + printf_flag, CPPPATH=env['CPPPATH'] + local_cpppath, CPPDEFINES=env['CPPDEFINES'] + local_cppdefines);

examples_program=Split('example/example_main')
#env.Program(target = examples_program, source = Split('example/example_main.o src/liblogger.a'))
env.Program(target = examples_program, source = Split('example/example_main.o src/liblogger.a'), LIBS = libs)
#env.Install('example/', source = examples_program)

test_program=Split('test/test_main')
#env.Program(target = test_program, source = Split('test/test_main.o test/test_logger_output.o src/liblogger.a'))
env.Program(target = test_program, source = Split('test/test_main.o test/test_logger_output.o src/liblogger.a'),  LIBS = libs)
#env.Install('test/', source = test_program)

pritnf_program=Split('wrapper/example_printf')
#env.Program(target = pritnf_program, source = Split('wrapper/example_printf.o src/liblogger.a'))
env.Program(target = pritnf_program, source = Split('wrapper/example_printf.o src/liblogger.a'), LIBS = libs)

pritnf_program=Split('libtest/libtest')
#env.Program(target = pritnf_program, source = Split('libtest/libtest.o libtest/main.o src/liblogger.a'))
env.Program(target = pritnf_program, source = Split('libtest/libtest.o libtest/main.o src/liblogger.a'),  LIBS = libs)

pritnf_program=Split('clibtest/libtest')
#env.Program(target = pritnf_program, source = Split('clibtest/libtest.o clibtest/main.o src/liblogger.a'))
env.Program(target = pritnf_program, source = Split('clibtest/libtest.o clibtest/main.o src/liblogger.a'),LIBS = libs)
