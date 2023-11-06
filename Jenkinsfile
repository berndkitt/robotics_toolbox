pipeline
{
    agent any

    environment
    {
        CMAKE_BUILD_DIRECTORY             = "build"
        JENKINS_BUILD_ARTIFACTS_DIRECTORY = "jenkins_build_artifacts"
        NUMBER_OF_THREADS                 = "8"
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
        stage("Environment Modeling")
        {
            parallel
            {
                stage("libWPG")
                {
                    stages
                    {
                        stage("CMake Build")
                        {
                            steps
                            {
                                sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t WPG -j${env.NUMBER_OF_THREADS}"
                            }
                        }
                        stage("GoogleTest")
                        {
                            steps
                            {
                                sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t unit_tests_libWPG -j${env.NUMBER_OF_THREADS}"
                                sh "./bin/unit_tests_libWPG --gtest_output=json:${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/googletest_libWPG.json"
                            }
                        }
                    }
                }
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
