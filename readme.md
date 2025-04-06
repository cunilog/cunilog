
# Cunilog

## Introduction

Cunilog is a simple and easy-to-use platform-independent module/unit written
in C to log events in high-performance applications.

It serves as a drop-in module where you just add the two files (combined source code and combined header files) 
to your own project and build everything together. It can also be built as statically or dynamically linked libraries.

## Disclaimer and Status

While most of the single source code files/units in this module have been in use
and tested over many years in production environments, some of the files/units
are relatively new and still not fully tested.

Until this task is finished, use at your own risk!

While the module is being tested, interfaces might also still change as long as ideal versions haven't been worked out yet.

## Characteristics

Although at the moment many of its features either haven't been completed or
aren't available at all yet, the module is meant to have the following
characteristics:

- A simple drop-in module. Just build its source code together with
	the rest of your project/application or add the library for static linking.
- Execution speed was a major factor in developing this module. It is very fast
	and outperforms other logging facilities.
- Small footprint. The goal is to keep it below 50 KiB of binary code and below
	20 KiB when rarely used features are removed.
- Single and multi-threaded.
- Available as drop-in module, or as static or dynamic library.
- Platform independent, without build automation system. No cmake or autotools
	are needed to build the module. Simply build it alongside your application.
- UTF-8 by default but some UTF-16 functions are available on Windows.
- Preprocessor definitions to include or remove rarely used features.
- Bindings for other programming languages. Right now only C is supported, though, as the interfaces haven't been finalised yet.
- Command-line utility to capture the output of executables and scripts.
	This is planned but doesn't exist yet.
- Logging of binary data as hex dumps.
- Optional severity levels like warning, info, debug, error, etc.
- Severity levels in different formats.
- Optional colour support for severity levels via ANSI escape sequences.

## History

Cunilog is a complete redesign and rewrite of an earlier Windows-only solution.
The main goals in mind were execution speed, small footprint, and usability
without sacrificing as much of its predecessor's flexibility and powerful
features as possible.

Since the incentive to develop Cunilog rose from the necessity to replace a
Windows-only solution, the implementation for this platform will most likely
be the most feature-complete for the forseeable future. However, the rewrite
was also driven by the fact that it would have been next to impossible to port
Cunilog's predecessor to POSIX platforms.

## Purpose

Cunilog writes event text to the console and/or logfiles. It compresses and/or
deletes less recent files. Essentially, its main purpose is to write out something
like this:

	2024-08-02 23:36:00.076+01:00 
	2024-08-02 23:36:00.076+01:00 ----------
	2024-08-02 23:36:00.076+01:00 Hello from a 64 bit MSVC build!
	2024-08-02 23:36:00.076+01:00 A simple line to go in the logfile.

What it does in detail is highly configurable, and the way it does this is quick,
very quick. The software's origins are in automation with realtime constraints.

## What it is not

- It is not a replacement for existing logging facilities like syslog or logrotate
	on Linux systems or Windows event logging. However, it can mimic logrotate's dot-number file naming scheme.

- It is even further away from software like Apache Kafka and Pulsar. These serve
	totally different purposes.

## Status

It builds and works on Windows with MSVC. It's not fully tested yet.

Preparation work has been made for Linux and MacOS but it will currently not build.

Once it builds and works on Linux it will most likely also build for and work on
Android.

## How to build Cunilog

To find out how to build Cunilog, see [Building Cunilog](building.md).

## Cunilog Basics

Some basics are explained in [Cunilog Basics](basics.md).

## Using Cunilog

To use Cunilog in your own projects, see [Using Cunilog](using.md).

