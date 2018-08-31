# Learn C The Hard Way

### Overview
* book not really about learning C
  * become better defensive programmer
  * understand legacy code

### The Undefined Behaviorists
* ways to write C for which compiler can disregard what's written
  * example: NUL Byte Overruns

### C Compilation Process
* **Preprocessing** -> analyzes preprocessor commands, lines starting with #, are **macros** which form own language
  * practically -> **inlines libraries, i.e., <stdio.h>**
* **Compilation** (name is confusing) -> C code to **assembly specific** to **target processor architecture**
  * allows for C programs to contain inline assembly instructions
  * some C compilers include integrated assemblers avoiding the need to invoke an assembler and this intermediate stage
* **Assembly** -> assembler used to translate the **assembly to machine code (also known as object code)**
* **Linking** -> rearrange machine code; **merges various modules from source files**
  * linker -> arranges pieces of machine code so that functions in some pieces can call functions in other pieces
  * **final stage** -> **produces single executable file**

### Make
![SimpleMakefileRule](./images/SimpleMakefileRule.png)
* [Make](https://www.gnu.org/software/make/) -> controls the genereation of executables and other non-source files of a program from the program's source files
  * Makefile -> tells make how to compile and link a program
    * [examples](http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)
  * enables end user to build and **install package without knowing details**
  * **not limited** to particular language (or even programming for that matter)
  * Rules and Targets
    * rule -> **how** to execute a series of commands to **build a target file** from source files
      * specifies list of dependencies of the target file
      * target -> usually the name of a file generated by the program
      * prerequisite -> file that is used as input to create target
      * recipe -> action that make carries out
        * may have more than 1 command
    * can specify which targets to update; otherwise, Make will update first target
  * Phony Target -> one that is not really the name of a file
    * name for a recipe to be executed when you make an explicit request
    * can be used to avoid name conflict with a file and a target and performance
  * How Make Works -> **declare dependencies** and then **describe how to build them**
    * relies also on the program's internal knowledge of how to build most common software
    * recompilation -> done if the source file, or any header files named as pre-reqs, is more recent than the object file, or if the object file does not exist
      * make is smart enough to **only recompile files that have changed**
      * sidenote -> linkage takes care of name resolution in C
        * whether two or more declarations for that name are valid

* sidenote / reminder: can pass ENV variables before running a command and they will be set accordingly only during that command
