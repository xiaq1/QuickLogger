#########################################################################
# File Name: changelevel.sh
# Author: Qichao
# mail: 87312668@qq.com
# Created Time: Mon 14 Nov 2016 04:11:26 AM EST
#########################################################################
#!/bin/bash

## change log level during running time based on gdb ##

## usages: changelevle $program_name $level

usage()
{
	echo "Usage of changelevel.sh:"
	echo "changelevle $program_name $level"
	echo "$program_name: name of the program which call Logger API"
	echo "$level: detailed levels of Logger, refer below availble values"
	echo "\t\t 0	-----------	NO Log output"
	echo "\t\t 1	-----------	NO Log output"
	echo "\t\t 2	-----------	NO Log output"
	echo "\t\t 3	-----------	NO Log output"
	echo "\t\t 5	-----------	NO Log output"
	echo "\t\t 6	-----------	NO Log output"
	echo "\t\t 7	-----------	NO Log output"
}


### input: paramter counter ###
parm_check()
{
	if [ $# -lt 2 ]
	then	
		echo "Parameter errors!"
		usage;
	fi
}

program_check()
{
	echo "empty, to be filled later"
}

get_original_level()
{
	local prgoram=$1;
	
	gdb -q --batch --ex "print f_defaultLevel" attach `pidof $program`
}

numLevel_to_debugLevel()
{
	echo "empty, to be filled later"
}

update_log_level()
{
	gdb -q --batch --ex "set f_defaultLevel= "
}

main()
{
	prog_name=$1
	loglevel=$2;
	pid=`pidof $prog_name`
	ex_cmd=`echo "set f_defaultLevel=$loglevel"`

	echo "GDB execution cmd: $ex_cmd";

	gdb -q --batch --ex "$ex_cmd" attach $pid 2>&1 >> /dev/null
}

# How to get all extra parameter of a bash script ? #
echo "First parameter is $1, second parameter is $2"
main $1 $2;
echo "Change log level to be $1 done!"
