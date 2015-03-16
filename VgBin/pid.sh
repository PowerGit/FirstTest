#!/bin/bash
Process=`ps aux | grep Vg.*Server | grep -v grep`
if [ ! -n "$Process" ]; then
	echo "没有进程"
else
	echo $Process
fi
