#!/usr/bin/perl
 
use strict;
use warnings;
use Getopt::Long;
use File::Copy;
use Cwd;

sub generate_target
{
	my @vars = (@_);

	mkdir "build";
	chdir "build";

	system("cmake -G $vars[0] -DOptMode:STRING=$vars[1] -DSYSTEM_ARCHITECTURE:STRING=$vars[2] VERBOSE=1 ..");

	chdir "..";
}

sub showHelp
{
	print "For executing properly this bat file you shall provide a project to be produced and a supported platform (default value is Windows).";
}

my $project = '';	# option variable with default value
my $platform = '';
if($^O eq 'linux')
{
	$platform = 'Linux';
}
elsif($^O eq "darwin")
{
	$platform = 'iOS';
}
elsif($^O eq "MSWin32")
{
	$platform = 'Windows';
}

my $optmode='Release';
my $architecture= 'x86-64';

GetOptions ('platform=s' => \$platform, 'Mode=s' => \$optmode, 'arch=s' => \$architecture);

if($platform eq "Windows")
{
	generate_target("\"Visual Studio 15 2017 Win64\"",$optmode,$architecture);
}
elsif($platform eq "Linux")
{
	generate_target("\"CodeBlocks - Unix Makefiles\"",$optmode,$architecture);
}
elsif($platform eq "iOS")
{
	generate_target("\"Xcode\"",$optmode,$architecture);
}
else
{
	echo $platform
	showHelp();
	
	exit -1;
}

exit 0;
