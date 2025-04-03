#!/usr/bin/perl
#************************************************************************************
#
#	File:		Creates the file def/libcunilog.def, which contains the ordinals
#				for functions and variables exported by the DLL.
#	Why:		To make it easier to include cunilog in other projects.
#	OS:			Perl script
#   Author:		Thomas
#	Created:	2025-04-01
#
#   License:	Public domain.
#
#	History
#	-------
#
#	When		Who				what
#	---------------------------------------------------------------------------------
#	2025-04-01	Thomas			Created.
#
#***********************************************************************************/
use Config;
use strict;
use warnings;
use POSIX qw(strftime);

#print "$Config{osname}\n";
#print "$Config{archname}\n";
if ("MSWin32" == "$Config{osname}")
{
	system ('cls');
} else
{
	system ('clear');
}

print ("*************************************************************************\n");
print ("Perl script to create the ordinal definitions for the Windows DLLs.\n");
print ("*************************************************************************\n");
print ("\n");
print ("Press any key to carry out the creation, or press CTRL-C to cancel.\n");
<>;

my $inp_def_file	= "./libcunilog_src.def";
my $out_def_file	= "../src/def/libcunilog.def";
my $in_head_file	= "./libcunilog_src_head.def";

my $headcnts		= "";
my $contents		= "";

my $first_ordinal	= 100;									# Lowest ordinal to assign.
my $ordinal_width	= 3;									# Width of an ordinal.

my $iso_date_and_time = strftime "%Y-%m-%d %H:%M:%S", localtime;

#sub writeOut
#{
#	print ("$cunilog$ext\n");
#	open (dfile, ">:raw", "$cunilog$ext");
#	print dfile $contents;
#	close (dfile);
#}

# Read header.
open (sfile, "<:raw", $in_head_file);
while (<sfile>) { $headcnts .= $_ }
# print ("$headcnts");
close (sfile);

# Replace "__ISO_DATE_AND_TIME" with current date and time.
$headcnts =~ s/__ISO_DATE_AND_TIME/$iso_date_and_time/;

# Open outpud .def file and write header.
open (dfile, ">:raw", $out_def_file);
print dfile $headcnts;

# Start with our lowest ordinal.
my $i_ordinal = $first_ordinal;

# Open input file and go through every line.
my $sdefs=$inp_def_file;
open my $info, "<$sdefs" or die "Could not open $sdefs: $!";
while (my $line = <$info>)
{
	$line = substr ($line, 0, -1);
	if	(
				$line eq ""
			||	";" eq substr ($line, 0, 1)
		)
	{
		print dfile "$line\n";
	} else
	{
		$line =~ s/^\s+//;							# Remove white space from start.
		if	(
					"LIBRARY libcunilog" eq $line
				||	"EXPORTS" eq $line
				||	";" eq substr ($line, 0, 1)
			)
		{
			print dfile "$line\n";
		} else
		{
			# Current ordinal as formatted string.
			my $ordnl = sprintf("%0${ordinal_width}d", $i_ordinal);
			if ($line =~ /(\S+)/)
			{
				my $funcvarname = $1;		# Function or variable name.
			}
			$line =~ s/\@nnn/\@$ordnl/;
			# print ("$line\n");
			print dfile "\t$line\n";
			$i_ordinal ++;
		}
	}
}
close (dfile);

print ("Done. Press any key.");
<>;
print ("\n");
