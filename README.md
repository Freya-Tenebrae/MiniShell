# Minishell

This Repositorie contains my solution to the project `Minishell` of 42 (Paris).

[![cmaginot's 42 stats](https://badge42.vercel.app/api/v2/cl1s5sord008509mlo7xr33zy/stats?cursusId=21&coalitionId=45)](https://github.com/JaeSeoKim/badge42)

[![jaeskim's 42 stats](https://badge42.herokuapp.com/api/stats/gadeneux?cursus=42cursus&privacyName=true)](https://github.com/JaeSeoKim/badge42)

[![cmaginot's 42 stats](https://badge42.vercel.app/api/v2/cl1s5sord008509mlo7xr33zy/stats?cursusId=21&coalitionId=45)](https://github.com/JaeSeoKim/badge42)

## Cloning

```shell
git clone --recurse-submodules https://github.com/Freya-Tenebrae/MiniShell.git
```

## Using

```shell
./minishell
```

#### Uses
This project aims to make a fonctionnal and simplified "SHELL" (similar to `bash -posix`)

> ONLY SOME FONCTIONNALITY ARE SUPORTED: SOMETHING NOT LISTED BELOW WILL HAVE AN INDETERMINATED BAHAVIOR
 - Launching an executable (with absolute or relative path)
 - Launchinf a build in command :
 	- exit
 	- echo
 	- pwd
 	- cd
 	- env
 	- export
 	- unset
 - Signals : 
 	- ctrl-C 
 	- ctrl-D 
 	- ctrl-\\
 	- crtl-l
 - Quote :
 	- '
 	- "
 - Redirection :
 	- <
 	- <<
 	- \>
 	- \>\>
 - Pipes 
 	- |
 - VARIABLES
 	- $?
 	- $VAR (with VAR is a sequence of characters)
 - A simple working history
