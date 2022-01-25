# Minishell

This Repositorie contains my solution to the project `Minishell` of 42 (Paris).

[![jaeskim's 42 stats](https://badge42.herokuapp.com/api/stats/cmaginot?cursus=42cursus&privacyName=true)](https://github.com/JaeSeoKim/badge42)

[![jaeskim's 42 stats](https://badge42.herokuapp.com/api/stats/gadeneux?cursus=42cursus&privacyName=true)](https://github.com/JaeSeoKim/badge42)

[![jaeskim's 42Project Score](https://badge42.herokuapp.com/api/project/cmaginot/minishell)](https://github.com/JaeSeoKim/badge42)

### Cloning

```shell
git clone --recurse-submodules https://github.com/Freya-Tenebrae/MiniShell.git
```

### TODO

GAUTHIER
- [ ] make build-in

CELIA - avant le demenagement
- [ ] revoir les sorties (stdout = 1, stderr = 2)
- [ ] refaire runline et checksyntaxe pour ressembler au shell (faire les etapes une par une)
- [ ] faire passer les erreur d'execline a runline 
- [ ] pipe function
- [ ] regroup file's, fonction's and variable's name for more coherences
- [ ] signal adjustement ('ctrl+\')

CELIA - apres le demenagement
- [ ] redirection >
- [ ] redirection >>
- [ ] delete global
- [ ] protect from malloc error (ex after using strdup) in ft_readcmd.c, ft_execcmd.c, and ft_tools_str*.c
- [ ] norm

A REPARTIR
- [ ] modifier execcmd pour fonctionner avec les redirection in
- [ ] redirection <
- [ ] redirection <<
- [ ] make history