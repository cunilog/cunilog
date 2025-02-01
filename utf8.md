
# Cunilog and UTF-8

Cunilog does not understand the concept of UTF-8. All strings are handled like
ASCII strings. Cunilog treats a UTF-8 codepoint consisting of two or more
octets/bytes like a string that consists of two or more ASCII characters.

For this reason Cunilog generally does not check if UTF-8 strings provided are
actually well-formed and valid UTF-8. An exception are functions that
distinguish between text and binary data and detect the correct output data
implicitely.

Cunilog however includes a module/unit called check_utf8 written by
YASUOKA Masahiko (https://github.com/yasuoka/check_utf8). Since the function
name is probably relatively common, it has been renamed to c_check_utf8 () in
order to avoid name clashes.

Since checking if text is well-formed and valid UTF-8 is a relatively expensive
operation, it is recommended to reduce the amount of checks as much as possible
but maybe not so far down to a point where security issues might arise.

Texts that are logged to a target are passed between Cunilog processors and
almost always end up in a text file. If these texts are not correct UTF-8, the
worst that can happen in most cases is that they end up somewhat crippled in a
text file. This of course assumes that software used to view or further
process these logfiles isn't crashing due to malformed UTF-8 sequences.

On the other hand, when a SCUNILOGTARGET structure is initialised with the
dedicated functions and logging folder and application name are provided, who
knows what kind of filename the operating system produces when creating a logfile?
Initialisation usually only happens once per target throughout the lifetime of
an application. In this case checking beforehand if the arguments are valid
UTF-8 might be a good habit. However, if these parameters come from user input
or other unknown sources, it should go without saying that UTF-8 checks are a must.
