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
- [ ] correct environment (check comment in ft_tools_env.c)
- [x] correct small problem with history and signal (check rl rediplay and rl on new line)
- [ ] check if all memory allocation when using function like ft_strdup are protected and unleakable, else do it

MAYBE
- [ ] correct priority in < and > (check tchat with gauthier the 5/2 at 8pm)

FINAL TASKS
- [ ] norm
- [ ] test
- [ ] full check at 42