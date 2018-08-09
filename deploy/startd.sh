export "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./."
ln -s libghttp.so libghttp.so.1
#export LD_LIBRARY_PATH
mv DataExportServiced DataExportService
./DataExportService /root/UserApp/vioncfg/DataExportService/config.ini &
