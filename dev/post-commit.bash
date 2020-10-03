set -e
unset GIT_DIR

echo including pre-commit change
git commit -a --amend --no-verify --no-edit

echo going to perf branch 
git checkout perf

echo merge dev
git merge dev --no-commit --no-ff
git checkout dev
cd ../build
cmake --build . --target kvhf
git commit -a -m"Merging dev and reporting performances"



