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
