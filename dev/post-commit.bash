set -e
unset GIT_DIR
if [[ -z "${SKIP_POST_COMMIT}" ]]; then
	echo going to perf branch 
	git checkout perf

	echo merge dev
	git merge dev
else
	echo including pre-commit change
	SKIP_POST_COMMIT=true git commit -a --amend --no-verify --no-edit
	
fi

