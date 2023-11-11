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
        stage("CMake (Release)")
        {
            steps
            {
                sh "cmake -D CMAKE_BUILD_TYPE=Release -B ./${env.CMAKE_BUILD_DIRECTORY}/ -S ./"
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
                        stage("Gcovr")
                        {
                            steps
                            {
                                sh "gcovr --json-pretty --json ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/gcovr_libWPG_coverage.json"
                                sh "gcovr --json-summary-pretty --json-summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/gcovr_libWPG_summary.json"
                            }
                        }
                        stage("Code Coverage")
                        {
                            steps
                            {
                                sh "python3 ./scripts/CheckCodeCoverage.py --filename_gcovr_summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/gcovr_libWPG_summary.json --threshold_branch_coverage 20.0 --threshold_function_coverage 100.0 --threshold_line_coverage 100.0"
                            }
                        }
                    }
                }
            }
        }
        stage("Mapping and Localization")
        {
            parallel
            {
                stage("libFB")
                {
                    stages
                    {
                        stage("CMake Build")
                        {
                            steps
                            {
                                sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t FB -j${env.NUMBER_OF_THREADS}"
                            }
                        }
                        stage("GoogleTest")
                        {
                            steps
                            {
                                sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t unit_tests_libFB -j${env.NUMBER_OF_THREADS}"
                                sh "./bin/unit_tests_libFB --gtest_output=json:${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/googletest_libFB.json"
                            }
                        }
                        stage("Gcovr")
                        {
                            steps
                            {
                                sh "gcovr --json-pretty --json ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/gcovr_libFB_coverage.json"
                                sh "gcovr --json-summary-pretty --json-summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/gcovr_libFB_summary.json"
                            }
                        }
                        stage("Code Coverage")
                        {
                            steps
                            {
                                sh "python3 ./scripts/CheckCodeCoverage.py --filename_gcovr_summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/gcovr_libFB_summary.json --threshold_branch_coverage 20.0 --threshold_function_coverage 100.0 --threshold_line_coverage 100.0"
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
            // build artifacts archiving
            archiveArtifacts artifacts: "${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/**, libs/**", allowEmptyArchive: true, fingerprint: true, onlyIfSuccessful: true

            // workspace cleanup
            cleanWs()
        }
    }
}
