#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER my_trace

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./tp.h"

#if !defined(_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _TP_H

#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(
    /* Tracepoint provider name */
    my_trace,

    /* Tracepoint name */
    counter,

    /* Input arguments */
    TP_ARGS(
	    int, value
    ),

    /* Output event fields */
    TP_FIELDS(
        ctf_integer(int, value, value)
    )
)

#endif /* _TP_H */

#include <lttng/tracepoint-event.h>
