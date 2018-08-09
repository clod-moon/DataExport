#!/bin/bash
#放在build目录，打包TK1的debug版本
v=$1
dirname=dataExport
tarname=${dirname}_LINUX-ARM-TX1_$v.tar.gz

if [ "$v" == "" ];then
	echo "  Usage: $0 version"
	exit 1
fi

now=`date +"%F %T"`
echo "time:$now, version:$v" >> version.log

if [ -e ~/$dirname ]; then
 rm -rf ~/$dirname/*
else
 mkdir ~/$dirname
fi

chmod +x ../../bin/linux-tx1/*.sh 
cp -vr ../../bin/linux-tx1/* ~/$dirname/
echo "time:$now, version:$v" |tee ~/$dirname/last_build.log

cd ~
find $dirname -name ".svn" -exec rm -rf {} \;
tar zcvf ~/$tarname $dirname
echo "package is: ~/$tarname"
