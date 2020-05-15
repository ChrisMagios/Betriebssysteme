#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Parameter missing. Usage: lttng.sh <program>"
    exit 1
fi

( kill -SIGSTOP $BASHPID; exec $@ ) &
PID=$!
lttng create --output trace
lttng enable-event --kernel --syscall openat,write,close
lttng track --kernel --pid=$PID
lttng start
kill -CONT $PID
while ps -p $PID > /dev/null; do sleep 1; done; 
lttng destroy
