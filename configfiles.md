# Configuration files
## Windows ini config files

Cunilog includes a config file reader that supports a format very similar to Windows ini files (https://en.wikipedia.org/wiki/INI_file) with some notable extensions.

Windows ini files consist of ***sections***, ***keys***, and ***values***. Sometimes, ***keys*** are also called ***properties***, but for the sake of this document we stick to the term ***key***.

```ini
[section]
key=value
```
Comments are allowed and ignored when they start with a semicolon as the first character on a line:
```ini
[section]
; Comment
key=value
```

More details on Windows ini files can be found in the Windows API documentation, for instance for the [GetPrivateProfileStringW](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-getprivateprofilestringw) function.

Cunilog supports reading Windows ini files in a platform-independent way. It provides a config file reader and supporting functions that allow for several useful extensions.

## Cunilog extensions
### New line characters/line endings

Cunilog's ini file reader supports all sorts of line endings, and in particular doesn't distinguish between Windows and POSIX. These config files are therefore binary compatible between Cunilog builds, independent of the end of line sequence found.

Build options however exist to extend or reduce support for various line endings.

### Case sensitivity

Cunilog supports both, case sensitive and case insensitive sections and keys. Values are always verbatim and returned as-is.

### Single and multi-line comments
In addition to the standard semicolon single line comment, Cunilog recognises several more characters and character combinations as the start of a one-line comment: 

| Single line comment | Notes                                |
| ------------------- | -------------------------------------|
| //                  | C/C++ style single line comment      |
| #                   | PHP, shell scripts, and config files |
| ;                   | Configuration files                  |
| +                   | Denotes an addition                  |
| --                  | Common double dash line comment      |
| !                   | Cisco routers and Fortran 90         |

| Multi-line comment | Notes                          |
| ------------------ | ------------------------------ |
| /* Comment */      | C/C++ style multi-line comment |
| {- Comment -}      | Haskell                        |
| (* Comment *)      | Pascal, Delphi, Applescript... |

All of these are also valid at the end of a line, but require at least one white space character after the value.
```ini
! This is a comment.
# This is also a comment.
[section]
; Comment
(* Our keys and their values are below. *)
key    = value    // Another comment.
newkey = value 2  // This makes it "value 2".
key 03 = value 3  # "value 3"
colour = green    /* Like grass */
```

```ini
[section]
key   = Hello!
key2  = Hello !
key3  = Hello ! Comment.
```
The exclamation mark belongs to the value of ***key***, because there's no space between the text "Hello" and the exclamation mark. This makes it "Hello!".
The value of ***key2*** is "Hello" without the exclamation mark, because it denotes the start of an (empty) line comment. The same goes for ***key3*** but the line comment is not empty.

### Section and key on the same line

A single key with its value can reside on the same line as a section name.
```ini
[section] key = value
```

### No sections

The config files Cunilog can read do not require sections:
```ini
key1 = value1
key2 = value2
key3 = value3
```

### Quotes and white space

Keys and values may contain [white space](https://en.wikipedia.org/wiki/Whitespace_character).
However, white space is removed before the first and after the last non-white-space character
unless the key or values is enclosed in quotation characters.

| Opening quote | Closing quote |
| ------------- | ------------- |
| "             | "             |
| '             | '             |
| [             | ]             |
| {             | }             |

```ini
[section]
  key 1 = colour is green
  key 2 = length is short
```
The example above shows a ***key 1*** and a ***key 2***, both in section ***section***.
The value of ***key 1*** is ***colour is green***, while the value of ***key 2*** is
***length is short***.

White space at the start of each line is ignored, as well as white space after
the last non-white-space character of the key.

```ini
[section]
  "key 1 " = colour is green
  [key 2 ] = length is short
  {key 3 } = colour is green
  {key 4 } = length is short
```
The example above shows a ***key 1_***, a ***key 2_***, a ***key 3_***, and a ***key 4_***.
Note the space at the end of each key's name, which has been replaced with an
underscore character ("***_***") for clarity.

### Comma is white space

Cunilog treats a comma (",") as [white space](https://en.wikipedia.org/wiki/Whitespace_character) on the right-hand side of the equality sign (the side with the value).
Other white space consists of the characters SPC (space, blank), BS (backspace), TAB,
VT (vertical tab), and FF (form feed).

### Multi-value keys

Keys can have more than one value. For instance,
```ini
[section]
key = "value1" "value2" "value3"
```
denotes a key with three values. Since Cunilog sees commas as white space,
primitive array definitions are possible:
```ini
[section]
key  = "value1", "value2", "value3"
key2 = [value1], [value2], [value]"
```
