gcc -std=c99 example_main.c ../src/logger_stringUtil.c ../src/logger.c ../src/logger_ini.c ../src/logger_initTerm.c ../src/logger_levelManagement.c ../src/logger_messageAssemble.c ../src/output_plugins/logger_pluginFile.c ../src/output_plugins/logger_pluginStdout.c ../src/output_plugins/logger_pluginUdp.c -I ../inc -I ../src -I ../src/output_plugins -o logger_example
./logger_example ${PWD}/example_ini.ini