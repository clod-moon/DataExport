#!/bin/bash
chmod +x data_exportd
ulimit -s 1024
LD_LIBRARY_PATH=./ ./data_exportd &
