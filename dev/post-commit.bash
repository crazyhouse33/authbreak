set -e
unset GIT_DIR
if [[ -z "${SKIP_POST_COMMIT}" ]]; then
	git commit -a --amend --no-verify
	echo going to perf branch 
	git checkout perf

	echo merge dev
	git merge dev --no-commit --no-ff
	git checkout dev
	cd ../build
	cmake --build . --target kvhf
	git commit -a -m"Merging dev and reporting performances"
else
	echo including pre-commit change
	SKIP_POST_COMMIT=true git commit -a --amend --no-verify --no-edit
	
fi

