#!/bin/bash
#放在build目录，打包TK1的debug版本
v=$1
dirname=dataExport
tarname=${dirname}-RELEASE_X86_64_$v.tar.gz

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

chmod +x ../bin/linux-X86_64/*.sh 
cp -r ../bin/linux-x86_64/* ~/$dirname/
cp -r ../lib/linux-x86_64/* ~/$dirname/
echo "time:$now, version:$v" |tee ~/$dirname/last_build.log

cd ~
find $dirname -name ".svn" -exec rm -rf {} \;
tar zcvf ~/$tarname $dirname
echo "package is: ~/$tarname"