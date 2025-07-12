# Minishell
Minishell is a project whose main objective is to develop a functional basic terminal. It is an intermediate project for the 42 Common Core. It focuses on implementing the basic functionalities that a terminal must have in order to be used without problems. Therefore, the following are implemented:
- Execution of one or more commands in parallel (using pipes)
- Redirection of both input (files or heredoc) and output (truncating or appending to the end of the file)
- Integration of basic built-ins (cd, pwd, env, export, unset, echo, exit)
- Handling the ctrl+C and ctrl+D signals

![Bash](https://camo.githubusercontent.com/9406f69901373a0b58714114af5c8b132bb50984eefff992486204ddbc8f9347/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f4c696e75782d613f7374796c653d666f722d7468652d6261646765266c6f676f3d6c696e757826636f6c6f723d67726579)
![C](https://camo.githubusercontent.com/c3fd6682e8cca0f7c262a00f94ef0f65cadd0c8470669a2d7d6f3614e81b10c2/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f632d2532333030353939432e7376673f7374796c653d666f722d7468652d6261646765266c6f676f3d63266c6f676f436f6c6f723d7768697465)

# Compiling and running the project
1- Clone the repository
```bash
git clone https://github.com/Luiz-Pastor/42-minishell.git
```

2- Navigate to the directory and run the `make` command
```bash
# Move and compile
cd 42-minishell
make

# Execute the program
./minishell
```
