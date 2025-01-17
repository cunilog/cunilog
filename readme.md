
# Cunilog

## Introduction

Cunilog is a simple and easy-to-use platform-independent module/unit written
in C to log events in high-performance applications.

## Disclaimer and Status

While most of the single source code files/units in this module have been in use
and tested over many years in production environments, some of the files/units
are relatively new and still not fully tested.

Until this task is completed, use at your own risk!

## Characteristics

Although at the moment most of its features either haven't been completed or
aren't available at all yet, the module is meant to have the following
characteristics:

- A simple drop-in module. No library is required. Just build it together with
	the rest of your project/application. This is how it works at the moment.
- Execution speed was a major factor in developing this module. It is very fast
	and outperforms other logging facilities.
- Small footprint. The goal is to keep it below 50 KiB of binary code and below
	20 KiB when rarely used features are removed.
- Available as static library. A dynamic library is planned.
- Platform independent without build automation system. No cmake or autotools
	are needed to build the module. At the moment it only builds on Windows.
- UTF-8 by default but also works with UTF-16 on Windows.
- Preprocessor definitions to include or remove rarely used features.
- Bindings for other programming languages. Right now only C is supported, though.
- Command-line utility to capture the output of executables and scripts.
	This is planned but doesn't exist yet.

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

Cunilog writes event texts to the console and/or logfiles. It compresses and/or deletes less recent files.
Basically, it writes out something like this:

	2024-08-02 23:36:00.076+01:00 
	2024-08-02 23:36:00.076+01:00 ----------
	2024-08-02 23:36:00.076+01:00 Hello from a 64 bit MSVC build!
	2024-08-02 23:36:00.076+01:00 A simple line to go in the logfile.

What it does in detail is highly configurable, and the way it does this is quick,
very quick. The software's origins are in automation with realtime constraints.

## What it is not

- It is not a replacement for existing logging facilities like syslog in Linux
	systems or Windows event logging.

- It is even further away from software like Apache Kafka and Pulsar. These serve
	totally different purposes.

## Status

It builds and works on Windows with MSVC. It's not fully tested yet.

It is prepared for Linux but neither builds nor works. Some preparational work
has been done for MacOS but it won't build and certainly won't work either.

Once it builds and works on Linux it will most likely also build and work on
Android.

## How to build Cunilog

To find out how to build Cunilog, see [Building Cunilog](building.md).

## Using Cunilog

To use Cunilog in your own projects, see [Using Cunilog](using.md).

