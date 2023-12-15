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
        stage("CMake (Release)")
        {
            steps
            {
                sh "cmake -D CMAKE_BUILD_TYPE=Release -B ./${env.CMAKE_BUILD_DIRECTORY}/ -S ./"
            }

        }
        stage("Source Code Checks")
        {
            parallel
            {
                stage("Clang-Tidy")
                {
                    steps
                    {
                        sh "python3 ./scripts/RunClangTidy.py --output_path ./${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/"
                    }
                }
                stage("Flake8")
                {
                    steps
                    {
                        sh "python3 -m flake8 --tee --output-file ./${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/flake8_results.txt **/*.py"
                    }
                }
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
                                sh "cd build && gcovr --filter ../modules/environment_modeling/libraries/libWPG/ --json-pretty --json ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/gcovr_libWPG_coverage.json"
                                sh "cd build && gcovr --filter ../modules/environment_modeling/libraries/libWPG/ --json-summary-pretty --json-summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/gcovr_libWPG_summary.json"
                                sh "cd build && gcovr --filter ../modules/environment_modeling/libraries/libWPG/ --html-details ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/gcovr_libWPG_details.html"
                            }
                        }
                        stage("Code Coverage")
                        {
                            steps
                            {
                                sh "python3 ./scripts/CheckCodeCoverage.py --filename_gcovr_summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/gcovr_libWPG_summary.json --threshold_branch_coverage 20.0 --threshold_function_coverage 100.0 --threshold_line_coverage 100.0"
                            }
                        }
                        stage("Doxygen")
                        {
                            steps
                            {
                                sh "python3 ./scripts/GenerateDoxygenDocumentation.py --base_path ./modules/environment_modeling/libraries/ --entity libWPG --output_path ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/"
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
                                sleep(time: 1, unit: 'SECONDS') // avoid running multiple instances of Gcovr in parallel
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFB/ --json-pretty --json ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/gcovr_libFB_coverage.json"
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFB/ --json-summary-pretty --json-summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/gcovr_libFB_summary.json"
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFB/ --html-details ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/gcovr_libFB_details.html"
                            }
                        }
                        stage("Code Coverage")
                        {
                            steps
                            {
                                sh "python3 ./scripts/CheckCodeCoverage.py --filename_gcovr_summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/gcovr_libFB_summary.json --threshold_branch_coverage 25.4 --threshold_function_coverage 100.0 --threshold_line_coverage 100.0"
                            }
                        }
                        stage("Doxygen")
                        {
                            steps
                            {
                                sh "python3 ./scripts/GenerateDoxygenDocumentation.py --base_path ./modules/mapping_and_localization/libraries/ --entity libFB --output_path ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/"
                            }
                        }
                    }
                }
                stage("libFBVis")
                {
                    stages
                    {
                        stage("CMake Build")
                        {
                            steps
                            {
                                sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t FBVis -j${env.NUMBER_OF_THREADS}"
                            }
                        }
                        stage("GoogleTest")
                        {
                            steps
                            {
                                sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t unit_tests_libFBVis -j${env.NUMBER_OF_THREADS}"
                                sh "./bin/unit_tests_libFBVis --gtest_output=json:${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFBVis/googletest_libFBVis.json"
                            }
                        }
                        stage("Gcovr")
                        {
                            steps
                            {
                                sleep(time: 11, unit: 'SECONDS') // avoid running multiple instances of Gcovr in parallel
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFBVis/ --json-pretty --json ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFBVis/gcovr_libFBVis_coverage.json"
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFBVis/ --json-summary-pretty --json-summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFBVis/gcovr_libFBVis_summary.json"
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFBVis/ --html-details ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFBVis/gcovr_libFBVis_details.html"
                            }
                        }
                        stage("Doxygen")
                        {
                            steps
                            {
                                sh "python3 ./scripts/GenerateDoxygenDocumentation.py --base_path ./modules/mapping_and_localization/libraries/ --entity libFBVis --output_path ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFBVis/"
                            }
                        }
                    }
                }
                stage("libFM")
                {
                    stages
                    {
                        stage("CMake Build")
                        {
                            steps
                            {
                                sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t FM -j${env.NUMBER_OF_THREADS}"
                            }
                        }
                        stage("GoogleTest")
                        {
                            steps
                            {
                                sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t unit_tests_libFM -j${env.NUMBER_OF_THREADS}"
                                sh "./bin/unit_tests_libFM --gtest_output=json:${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFM/googletest_libFM.json"
                            }
                        }
                        stage("Gcovr")
                        {
                            steps
                            {
                                sleep(time: 21, unit: 'SECONDS') // avoid running multiple instances of Gcovr in parallel
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFM/ --json-pretty --json ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFM/gcovr_libFM_coverage.json"
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFM/ --json-summary-pretty --json-summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFM/gcovr_libFM_summary.json"
                                sh "cd build && gcovr --filter ../modules/mapping_and_localization/libraries/libFM/ --html-details ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFM/gcovr_libFM_details.html"
                            }
                        }
                        stage("Doxygen")
                        {
                            steps
                            {
                                sh "python3 ./scripts/GenerateDoxygenDocumentation.py --base_path ./modules/mapping_and_localization/libraries/ --entity libFM --output_path ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFM/"
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
            archiveArtifacts artifacts: "${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/**, libs/**", allowEmptyArchive: true, fingerprint: true, onlyIfSuccessful: false

            // workspace cleanup
            cleanWs()
        }
    }
}
