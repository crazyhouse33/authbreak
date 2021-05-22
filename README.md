# Authbreak 0.6
Generic authentification system injection point based tester for Linux.


# Function and motivation

Authbreak is a tool built to execute attacks that can work on every authentification system, with the same powerful user interface and complete set of feature. It's been done entirely in C ( Because I was willing to try the language Linux was coded with, and god I regret this decision). It also have an insane (first degree of the word) focus on performance. Yet it also follow manual but very strict continious integration, lot of tests (memory), per commit performance auditing.

# Install

```bash
git clone --recursive https://github.com/crazyhouse33/authbreak
cd authbreak/build
cmake ..
# Add -DCMAKE_INSTALL_PREFIX:PATH=/path/to/install to the last command to install in another directory than your system default executable location (need root)
 cmake --build . target install 
```

The binary ends up in the bin directory.

# Repo

Each version of authbreak is a commit in the master branch. The version changelog is the git log of master branch. 

The dev branch contains additional continuous integration files, and has a usual git messy history :)


# Usage

The philosophy is to provide a command with some configurable injection points along with boolean combination of some target execution metrics (time, stdout...) to allow differentiation of success and failures. The different implementeds attacks will try to exploit the target using your inputs in the most efficient way they can to get a success. A sheduler make sure we converge as quick as we can to a working attack, or toward the brutforcer.

authbreak -h for a complete explanation of how this version works.


# Attacks

## Brutforcer

The brutforcer iterate once on every possible combination defined by the differents injections points.

### Iteration order
The trickiest thing with the Brutforcer is to understand what the default does compared to cartesian option.

If user contains:

```
ansible
toto
root
```

```
admiN123
1234
password
```
Then the authbreak generate followings outputs:

# Coming

Developpement will fist focus on implementing a really powerfull brutforcer. Then a larger set of generic attacks will be implemented and mixed with a sheduling system.

1. Automatic timing attack over generics shemes: Clear creds comparaison, enummeration assuming weak data structures...
2. Big and small performance improvement (cache the loading (idk how yet) of the targeted process)
3. User interface improvement (press key to print state,  automatic sessioning on interuption/crash, others classifiers (regexp match), better output gestion)
5. More control over what's done 
7. Make it cross platform 
