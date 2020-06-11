# Authbreak 
Generic authentification system injection point based tester for Linux.

# Repo
Each version of authbreak is a commit in the master branch. The version changelog is the git log. Each readme of every commits is the actualized documentation of the tool.

The dev branch contain additional continious integration files, and have a regular messy history :)

# Functionnement and motivation
Authbreak is a tool built to do attacks than can be generically done on every authentification system, whit the same simple and powerfull user interface.

In this version, it does:

1. guessing


# Install

```bash
git clone https://github.com/crazyhouse33/authbreak
cd authbreak/build
cmake ..
make authbreak
```

The binary end up in the bin directory.

# Usage
The philosophy is to provide a command with some configurable injection points and some classifiers differentiate success and fails. The different backends use what you specified to generate their attacks the most efficiently as they can.

authbreak -h for a complete explanation of how this version work.

# Comming
1. Automatic timing attack
2. Big and small perf improvement (use a thread to categorize previous output while current is running, collect only metrics usefull to used classifier, cache the loading (idk how yet) of the targeted process)
3. User interface improvement (press key to print state, pause and continue later at any interuption, use a more powerfull front for classfiers --NOT --success time<5 --success out="tata" --OR --sucess time=<4, Others classifiers (regexp match, return status))
4. Various furtivity options (hidden cartesian product, manual waiting in between actions with automatic adjustement in function of previous responses)
5. More controle over what's done (pass some attacks, log or exit at success?)
6. For the file template, actually filter the guesses to match given charset and len
7. Make it cross platform 



