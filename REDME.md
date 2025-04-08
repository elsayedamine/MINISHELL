commmand not found: DONE<br>
ls && . : DONE<br>
ls && : DONE<br>
ls && (cat Makefile ) : SEGV <br>
ls && (cat Makefile ) (space)  2 doubl frees : SEGV <br>
cat Makefile (ls) : DONE <br>
cat "Makefile && (ls) : 2double free  : SEGV <br>