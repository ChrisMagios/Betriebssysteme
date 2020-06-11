#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Parameter missing. Usage: lttng.sh <program>"
    exit 1
fi

( kill -SIGSTOP $BASHPID; exec $@ ) &
PID=$!
lttng create --output trace
lttng enable-event --kernel sched_switch,sched_wakeup,sched_process_exit,sched_process_wait,sched_process_fork,sched_process_exec,sched_stat_sleep
lttng start
kill -CONT $PID
while ps -p $PID > /dev/null; do sleep 1; done;
lttng destroy
