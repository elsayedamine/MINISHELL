# ----------------------------------------------------------#


## read this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# SEGV
    ila mssahna l env : MAZAL MAKHDMNAHACH

# I need to add a fct that switches the places of strings in an array

```bash
we have a big problem  in redirection parsing unfortunately 
wa naaaaaaari treatement dial redirections 3ndna khaaaaaaaaaaari m3a ro7o waaaaaaaaa3 
we still have a big prob in the pipeline 
so many errors in the logic
```


```bash
some test cases:

minishell$ echo "$""HOME"
echo $HOME
$HOME
minishell$ bash
bash
aelsayed@c3r9p8:~/Desktop/minishell$ echo "$""HOME"
$HOME
aelsayed@c3r9p8:~/Desktop/minishell$ echo $""HOME
HOME
minishell$ echo $""HOME
echo $HOME
$HOME
```

```bash
minishell$ echo $a
a        b       c
minishell$ echo "$a"
a        b       c
```

env -i bash
aelsayed@c3r9p2:/home/aelsayed$ export
declare -x OLDPWD
declare -x PWD="/home/aelsayed"
declare -x SHLVL="1"

if u unset the OLDPWD and then change the directory u need to add it
if i set SHLVL to 9999999999999999 and then enter to an new minishell i become 0 instead of 1

```bash
mkdir a 
cd a
mkdir b
cd b
mkdir c
cd c
rm -rf ../../b
cd .. or cd ../../ or cd ../../../ should work instead of giving u an error