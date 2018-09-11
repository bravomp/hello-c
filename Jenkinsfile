pipeline {
	agent any

	environment {
		STREAM = 'hello'
		IDIR = 'idir'
	}

	stages {
		stage('build') {
			steps {
				withCoverityEnv(coverityToolName: '2018.06', connectInstance: 'localhost') {
					sh "cov-build --dir ${IDIR} make clean hello"
				}
			}
		}
		stage('analyze') {
			steps {
				withCoverityEnv(coverityToolName: '2018.06', connectInstance: 'localhost') {
					sh "cov-analyze --dir ${IDIR} --strip-path ${WORKSPACE} --all --enable-callgraph-metrics --enable-fnptr --enable-virtual"
				}
			}
		}
		stage('commit') {
			steps {
				withCoverityEnv(coverityToolName: '2018.06', connectInstance: 'localhost') {
					sh "cov-commit-defects --dir ${IDIR} --host ${COVERITY_HOST} --stream ${STREAM} --scm git --description ${BUILD_TAG} --target Linux_x86_64 --version ${GIT_COMMIT}"
				}
			}
		}
		stage('results') {
			steps {
				coverityResults connectInstance: 'localhost', connectView: 'High Impact Outstanding', projectId: 'hello'
			}
		}
	}
}
