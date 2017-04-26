#########################################################################
# File Name: replace_printf.sh
# Author: xxxxx
# mail: xxxxx.xxx@leadstor.com
# Created Time: Fri 14 Apr 2017 10:24:52 PM EDT
#########################################################################
#!/bin/bash

## step 1: find all .c file which may need to be replaced

headtext="#include <loggerFacade.h>"

for i in `find ./ -name "*.c"`
do 
	egrep -e " printf\(| fprintf\(" $i | egrep -ie "stderr|error|fatal|fail"
	if [[ $? -eq 0 ]]
	then
		echo "Now replace file: $i"
		## step 2: for each C file:
		# 2.1 add include <>
		# 2.1.1 find last line of "#include"
		last_line=`grep -ne "#include" $i | tail -n 1 | awk -F: '{print $1}'`
		#let last_line=$last_line+1
		#expr last_line=$last_line+1
		#((last_line=last_line+1))
		#2.1.2 add "include log" to the line
		#sed -i '${last_line}a\ ${headtext}' $i
		sed -i ${last_line}a\ "${headtext}" $i

		#2.2 replace printf*error|fatal with LOGLIB_ERROR

		## 2.2.0 get all lines which need replace
		replace_lines=`egrep -ne " fprintf\(stderr" $i |  awk -F: '{print $1}'`
		for line in $replace_lines
		do
			echo $line
			sed -i ${line}s/fprintf\(error,/LOGLIB_ERROR\(/g $i
		done

		## 2.2.1 get all lines which need replace
		replace_lines=`egrep -ne " printf\(" $i | egrep -ie "error|fail" | awk -F: '{print $1}'`
		for line in $replace_lines
		do
			echo $line
			#sed -i "${line}s/printf/LOGLIB_ERROR" $i
			sed -i ${line}s/printf/LOGLIB_ERROR/g $i
			#sed  '${line}s/printf/LOGLIB_ERROR/w' $i
		done

		replace_lines=`egrep -ne " printf\(" $i | egrep -ie "fatal" | awk -F: '{print $1}'`
		for line in $replace_lines
		do
			echo $line
			sed -i ${line}s/printf/LOGLIB_FATAL/g $i
		done
		
	fi
 done
