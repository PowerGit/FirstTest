#!/bin/bash
#Process=`ps aux | grep VgGateServer | grep -v grep`
Process=`ps aux | grep Vg.*Server | grep -v grep`
if [ ! -n "$Process" ]; then
	echo "没有进程"
else
        PID=`echo $Process | cut -d' ' -f2`
	echo "stop PID:" $PID
	kill -3 $PID
fi
