pipeline
{
    agent any

    environment
    {
        CMAKE_BUILD_DIRECTORY             = "build"
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
        stage("CMake")
        {
            steps
            {
                sh "cmake -B ./${env.CMAKE_BUILD_DIRECTORY}/ -S ./"
            }
        }
    }

    post
    {
        always
        {
            // workspace cleanup
            cleanWs()
        }
    }
}
