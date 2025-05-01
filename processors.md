
# Processors and Rotators

## Processors

When an event goes to a target it is passed through an array of processors, literally in a loop.
The C type definition for a Cunilog processor structure is __CUNILOG_PROCESSOR__. Each target
holds a pointer
to an array of processors. If a target is initialised without a processors array, the default
is assigned.

Each processor is assigned a certain task. Cunilog provides a default set of tasks for processors
to carry out. A custom task is also available for which a callback function can be invoked.
Each processor is assigned precisely one task, which is the member __task__ of data
type __enum cunilogprocesstask__.

| member __task__ | |
| :------------------- | --- |
| cunilogProcessNoOperation | Does nothing, obviously |
| cunilogProcessEchoToConsole | Console/terminal output |
| cunilogProcessUpdateLogFileName | If the logfile's name requires changing, this processor takes on this task |
| cunilogProcessWriteToLogFile | Writes the event to the logfile |
| cunilogProcessFlushLogFile | Flushes the logfile to disk |
| cunilogProcessRotateLogfiles | Provides a rotator. See Rotators. |
| cunilogProcessCustomProcessor | A user-provided callback function is called to carry out this processor's task. |
| cunilogProcessTargetRedirector | Redirects events to another target |
| cunilogProcessTargetFork | Sends a copy of events to another target |

Processors are not necessarily all called for every event. A processor's member __freq__ of type __enum cunilogprocessfrequency__ specifies when and how often it is processed.

## Rotators

Rotators are s special type of processor. Rotators are s special type of processor. While other
processors do something with an event, the job of a rotator is to do something with the logfile
or an entire set of logfiles.
A rotator processor's __task__ member is set to __cunilogProcessRotateLogfiles__ and
its __pData__ member points to a __CUNILOG_ROTATION_DATA__ structure.
