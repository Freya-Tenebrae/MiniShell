# Minishell

This Repositorie contains my solution to the project `Minishell` of 42 (Paris).

[![jaeskim's 42 stats](https://badge42.herokuapp.com/api/stats/cmaginot?cursus=42cursus&privacyName=true)](https://github.com/JaeSeoKim/badge42)

[![jaeskim's 42 stats](https://badge42.herokuapp.com/api/stats/gadeneux?cursus=42cursus&privacyName=true)](https://github.com/JaeSeoKim/badge42)

[![jaeskim's 42Project Score](https://badge42.herokuapp.com/api/project/cmaginot/minishell)](https://github.com/JaeSeoKim/badge42)

## Cloning

```shell
git clone --recurse-submodules https://github.com/Freya-Tenebrae/MiniShell.git
```

## Using

```shell
./minishell
```

#### /!\\ ONLY SOME FONCTIONNALITY ARE SUPORTED /!\\
 - launching an executable or system command
 - signals : 
 	- ctrl-C 
 	- ctrl-D 
 	- ctrl-\\
 - simple character supported : 
 	- '
 	- "
 	- <
 	- <<
 	- \>
 	- \>\>
 	- |
 	- $ (only if followd by ? or a sequence of characters)
 - A simple working history (arrow up and down without autocompletion)

## TODO

GAUTHIER
- [ ] make build-in

CELIA
- [x] correct small problem with history and signal (check rl rediplay and rl on new line)
- [x] put error file too long for redirection > and >>
- [x] correct error when a empty space is present at end line : an orror occured ... (line error)
- [ ] correct environment (check comment in ft_tools_env.c) and check if all memory allocation when using function like ft_strdup are protected and unleakable, else do it
- [ ] check if all memory allocation when using function like ft_strdup are protected and unleakable, else do it
- [ ] replace gnl on ft_tools_file_to_str by readline; (for ctrl-c handling and to put a '> ' before when << is used) (and to let ctrl-c be possible)
- [ ] norm all file modified for protection malloc (and change tools error to send null or -1 and not only -1 too save lines)

MAYBE
- [ ] correct priority in < and > (check discord with gauthier the 5/2 at 8pm)

FINAL TASKS
- [ ] test
- [ ] full check at 42