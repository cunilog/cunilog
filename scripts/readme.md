# Creating the combined Cunilog module source code files

To create the combined source code files the following scripts are provided:

- __CreateCombinedCunilog.cmd__ (Windows command-line script/batch file)
- __CreateCombinedCunilog.pl__ (Perl script)
- __CreateCombinedCunilog.sh__ (Bash shell script)

The scripts have identical functionality. They read the file __SingleFiles.txt__
and use it as the basis to create the files __cunilog_combined.c__ and
__cunilog_combined.h__ in folder __src/c/combined__.

These files can then either be added to your project(s), or serve as the basis
for the static library __libcunilog__.

See [Building Cunilog](https://github.com/cunilog/cunilog/blob/master/building.md) for details on how to build Cunilog as a static library or directly add the combined files to your project(s).
