echo "alias mstest='bash /workspaces/minishell/42_minishell_tester/tester.sh'" >> ~/.bashrc
bash -c -y "$(curl -fsSL https://raw.github.com/xicodomingues/francinette/master/bin/install.sh)"
echo 'Container created. Happy coding!'
bash
cd /workspaces/minishell/