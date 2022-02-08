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
- [ ] correct segfault when < $var
- [ ] correct new leaks
- [ ] check if all memory allocation when using function like ft_strdup are protected and unleakable, else do it
- [ ] changer gnl par readline et ajuster les signaux pour fonctionner avec
- [ ] make a working history (with arrow up and down)
- [ ] make buil-in exit

MAYBE
- [ ] correct priority in < and >

POTENTIAL ERROR
- [ ] erreur avec < et > (voic onvo avec gauthier le 5/2 a 20h00)
- [ ] exit doit etre modifier (par ex exit 1 | exit 0 ne doit rien afficher)
	- exit -> exit normalement
	- exit "arg numerique" -> exit normalement
	- exit "arg non numerique"  -> msg argument numerique necessaire puis exit
	- exit "plusieur arguments" -> erreur non numerique if 1rst non numerique (mais quitte si un seul arg numerique) sinon msg trop d'arguments
	- presence d'un pipe : n'existe pas mais passe au suivant (qui pourra affichher une erreur mais n'exitera pas)
	- le mettre en bi specifique ...

FINAL TASKS
- [ ] passer des testeur
- [ ] check complet a 42, push du projet sur le github de l'intra, et testeur a 42