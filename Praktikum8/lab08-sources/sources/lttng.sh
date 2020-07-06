#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Parameter missing. Usage: lttng.sh <program>"
    exit 1
fi

lttng create --output trace-realtime
lttng enable-event --kernel sched_switch,sched_process_fork
lttng start
sudo chrt -r 50 $@
wait $!
lttng destroy
