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

- [ ] write redirection in (< and <<)
- [ ] write redirection out (> and >>)
- [ ] pipe implementation in main loop
- [ ] make build-in
- [x] correct leaks when an "error" occured
- [x] correct the leaks created by the char * "buffer" in "ft_readnext" (in file "ft_readcmd.c")
- [ ] hard test leaks
- [ ] signal adjustement
- [ ] protect from malloc error (ex after using strdup)
- [ ] regroup file's, fonction's and variable's name for more coherences
- [ ] delete duplicated funciton
- [ ] norm
- [ ] implementation of & and &&
