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
    }
}
