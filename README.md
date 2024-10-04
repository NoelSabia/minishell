# Minishell
The objective of this project is for you to create a simple shell.

# Ressources
- [pipes](https://reactive.so/post/42-a-comprehensive-guide-to-pipex)
- [minishell guide](https://achrafbelarif.medium.com/42cursus-minishell-29cd25f972e6)
- [shunting yard for the win](https://somethingorotherwhatever.com/shunting-yard-animation/)

# Tester
- https://github.com/zstenger93/42_minishell_tester
- run this command when wanting to use the tester: `bash -c "$(curl -fsSL https://raw.githubusercontent.com/zstenger93/42_minishell_tester/master/install.sh)"` 

# Bashversion
42 = bash3.2
Docker Container = bash5.1

make && valgrind --gen-suppressions=all --suppressions=readline.supp -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
