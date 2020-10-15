pipeline {
	agent any

	environment {
		CONNECT = 'https://coverity.chuckaude.com:8443/'
		PROJECT = 'hello-c'
	}

	stages {
		stage('Build') {
			steps {
				sh 'make hello'
			}
		}
		stage('Test') {
			steps {
				sh 'make test'
			}
		}
		stage('Coverity Full Scan') {
			when {
				allOf {
					not { changeRequest() }
					expression { BRANCH_NAME ==~ /(master|stage|release)/ }
				}
			}
			steps {
				withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$PROJECT-$BRANCH_NAME") {
					sh '''
						cov-build --dir idir make clean hello
						cov-analyze --dir idir --ticker-mode none --strip-path $WORKSPACE
						cov-commit-defects --dir idir --ticker-mode none --url $COV_URL --stream $COV_STREAM \
							--description $BUILD_TAG --target Linux_x86_64 --version $GIT_COMMIT
					'''
				}
			}
		}
		stage('Coverity Incremental Scan') {
			when {
				allOf {
					changeRequest()
					expression { CHANGE_TARGET ==~ /(master|stage|release)/ }
				}
			}
			steps {
				withCoverityEnvironment(coverityInstanceUrl: "$CONNECT", projectName: "$PROJECT", streamName: "$PROJECT-$CHANGE_TARGET") {
					sh '''
						cov-build --dir idir make clean hello
						cov-run-desktop --dir idir --url $COV_URL --stream $COV_STREAM --reference-snapshot latest --present-in-reference false \
							--ignore-uncapturable-inputs true --set-new-defect-owner false --exit1-if-defects true $(git --no-pager diff origin/$CHANGE_TARGET --name-only)
					'''
				}
			}
		}
	}
}
