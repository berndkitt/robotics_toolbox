pipeline
{
    agent any

    environment
    {
        JENKINS_BUILD_ARTIFACTS_DIRECTORY = "jenkins_build_artifacts"
    }

    options
    {
        disableConcurrentBuilds()
    }

    stages
    {
        stage("Prepare Environment")
        {
            steps
            {
                sh "mkdir ./${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}"
            }
        }
        stage("Flake8 Checks")
        {
            steps
            {
                sh "python3 -m flake8 --tee --output-file ./${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/flake8_results.txt **/*.py"
            }
        }
    }
}
