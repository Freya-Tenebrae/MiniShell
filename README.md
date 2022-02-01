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

CELIA
- [x] refaire runline et checksyntaxe pour ressembler au shell (faire les etapes une par une)
- [x] include pipe
- [x] gerer les output de run_cmd_2.c correctement
- [ ] redirection > et >>
- [x] redirection < et <<
- [ ] delete global et put in each function when needed
- [ ] revoir les sorties (stdout = 1, stderr = 2)
- [x] normer run_cmd_2.c
- [ ] normer readcmd.c
- [ ] protect all memory allocation when using function like ft_strdup
- [ ] regroup file's, fonction's and variable's name for more coherences
- [ ] check complet norme

A REPARTIR
- [ ] faire ft_tools_check_access_ok
- [ ] refaire les signaux
- [ ] make a working history (with arrow up and down)
- [ ] passer des testeur
- [ ] check complet a 42, push du projet sur le github de l'intra, et testeur a 42

MAYBE
- [ ] modifier gnl pour accepter NULL sur line -> free le fd