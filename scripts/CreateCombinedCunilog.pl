#!/usr/bin/perl
#************************************************************************************
#
#	File:		Creates the combined/merged unilog source code file.
#	Why:		To make it easier to include cunilog in other projects.
#	OS:			Perl script
#   Author:		Thomas
#	Created:	2024-11-04
#
#   License:	Public domain.
#
#	History
#	-------
#
#	When		Who				what
#	------------------------------------------------------------------------------------
#	2024-11-04	Thomas			Created.
#
#***********************************************************************************/
use Config;
use strict;
use warnings;

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
print ("Perl script to create the combined cunilog source code files.\n");
print ("*************************************************************************\n");
print ("\n");
print ("Press any key to carry out the creation, or press CTRL-C to cancel.\n");
<>;

my $ext					= "";
my $newext				= "";
my $destcombinedpath	= "../src/c/combined";
my $cunilog				= "$destcombinedpath/cunilog_combined";
my $src					= "../src/c";
my $onefile				= "";
my $contents			= "";

sub writeOut
{
	print ("$cunilog$ext\n");
	open (dfile, ">:raw", "$cunilog$ext");
	print dfile $contents;
	close (dfile);
}

my $sfiles="./SingleFiles.txt";
open my $info, "<$sfiles" or die "Could not open $sfiles: $!";
while (my $line = <$info>)
{
	$line = substr ($line, 0, -1);
	if ($line ne "")
	{
		if (":" eq substr ($line, 0, 1))
		{
			$newext = substr ($line, 1, 2);
			if ($ext ne $newext)
			{
				if ("." eq substr ($newext, 0, 1))
				{
					if ($ext ne "")
					{	# Header.
						writeOut ();
					}
					$ext = $newext;
				}
			}
			$contents	= "";
		} else
		{
			if (";" ne substr ($line, 0, 1))
			{
				if ("/" eq substr ($line, 0, 1))
				{
					$onefile = "$src$line$ext";
				} else
				{
					$onefile = "$line$ext";
				}
				print ("$onefile\n");
				open (sfile, "<:raw", $onefile);
				while (<sfile>) { $contents .= $_ }
				close (sfile);
				#print ("$contents");
			}
		}
	}
}
close $info;
# Code.
writeOut ();

print ("Done.\n");
<>;
