set -e
git commit -a --amend -C
git checkout perf
git merge dev
