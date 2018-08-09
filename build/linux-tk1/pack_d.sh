#! /bin/bash
#放在build目录，打包TK1的debug版本
v=$1
dirname=DataExportService
tarname=${dirname}_-LINUX-TK1_$v.tar.gz

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

chmod +x ../bin_d/linux-tk1/*.sh 
cp -r ../../bin_d/linux-tk1/* ~/$dirname/
cp -r ../../lib_d/linux-tk1/* ~/$dirname/
cp -r ../../deploy/*       ~/$dirname/
mv ~/$dirname/startd.sh ~/$dirname/start.sh
mv  version.log  ~/$dirname/
echo "time:$now, version:$v" |tee ~/$dirname/last_build.log

cd ~
find $dirname -name ".svn" -exec rm -rf {} \;
tar zcvf ~/$tarname $dirname
echo "package is: ~/$tarname"
