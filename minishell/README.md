*This project has been created as part of the 42 curriculum by <mpietri> & <ls-phabm>*

## Description
The `minishell` project is a small Unix shell written in C. It is builtd as a simplified but faithful reimplementation of `bash`. This project's goal is to understand how a command-line interpreter works from the inside :
reading a line, breaking it down, resolving variables and quotes, wiring up pipes and redirections, and lauching processes while handling signals like a real interractive shell.

Minishell tokenises a line of input, builds a list of commands linked, then executes builtins and external programs. Interractive prompt and history are provided through the GNU `readline`. `bash` is used as the reference for behaviour in amibguous cases.

Main features:
- Interactive prompt with history (via `readline`).
- Tokeniser that respects single (`'`) and double (`"`) quotes.
- Pipelines of arbitrary length (`cmd1 | cmd2 | ... | cmdN`).
- Input, output and append redirections (`<`, `>`, `>>`) and here-documents (`<<`).
- Variable expansion (`$VAR`, `$?`) with correct quote handling.
- Builtins: `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Signal handling matching `bash` (`Ctrl-C`, `Ctrl-\`, `Ctrl-D`).
- Runs cleanly under `valgrind`: no leaks and no leaked file descriptors in the shell.

## Instructions
> any relevant information about compilation, installation, and/or execution

make          # build the minishell binary
make clean    # remove object files
make fclean   # remove objects and the binary
make re       # rebuild from scratch
make valgrind # build the minishell binary with valgrind

```
make
./minishell
```
Compile and enter interative mode

```
make valgrind
```
Compile with all flags (all leaks, track fds, show origins) and enter interactive mode


Non-interactive mode:
```
printf "echo lol" | ./minishell

```
Execute 1 command
```
printf "pwd\necho hello\n" | ./minishell
```
Execute multiple commands

### Requirements
- C compiler (`cc`) and `make`.
- The GNU `readline` library.
    - Debian/Ubuntu: `sudo apt install libreadline-dev`
    - macOS (Homebrew): `brew install readline`

## Resources
> listing classic references related to the topic (documentation, articles, tutorials, etc.)
> a description of how AI was used — which tasks and which parts of the project.

- bash : 
  - <https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html>
  - man
- roadmap : 
  - <https://ganivetj.github.io/minishell/>
  - <https://medium.com/@santiagobedoa/coding-a-shell-using-c-1ea939f10e7e>
  - <https://medium.com/@zouhairlrs/minishell-building-a-mini-bash-a-42-project-5dc20d671fbb>
  - <https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218>
- parsing : 
  - <https://eli.thegreenplace.net/2012/08/02/parsing-expressions-by-precedence-climbing>
  - <https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf>
- expand : <https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html>
- heredocs : <https://linuxize.com/post/bash-heredoc/>
- exit codes : <https://www.redhat.com/en/blog/exit-codes-demystified>
- Valgrind supp : <https://medium.com/@moritz.knoll/learning-valgrind-the-hard-way-creating-suppression-files-that-actually-work-80e246215678>
- funcheck : <https://github.com/froz42/funcheck>
- Markdown : <https://www.markdownguide.org/cheat-sheet/>
- AI was used to break down the roadmap (lexing, parsing, expand, exec, signals, redirections), coding best practices (architecture design), debug edge cases.
