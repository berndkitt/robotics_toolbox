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
        buildDiscarder(
            logRotator(
                artifactDaysToKeepStr: "30",
                artifactNumToKeepStr:  "5",
                daysToKeepStr:         "30",
                numToKeepStr:          "5"
            )
        )
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
        stage("CMake (Release, GCC 11)")
        {
            steps
            {
                sh "cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_CXX_COMPILER=/usr/bin/g++-11 -B ./${env.CMAKE_BUILD_DIRECTORY}/ -S ./"
            }

        }
        stage("Source Code Checks")
        {
            parallel
            {
                stage("Clang-Format")
                {
                    steps
                    {
                        sh "python3 ./scripts/RunClangFormat.py --base_directory ./ --configuration_json ./settings/clang_format/file_configuration_all.json --dry_run"
                    }
                }
                stage("Clang-Tidy")
                {
                    steps
                    {
                        sh "python3 ./scripts/RunClangTidy.py --base_directory ./ --configuration_json ./settings/clang_tidy/file_configuration_all.json --filename_output ./${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/clang_tidy_results.txt"
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
        stage("Modules")
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
                        stage("GoogleTest & Gcovr")
                        {
                            steps
                            {
                                GoogleTest("../modules/mapping_and_localization/libraries/", "libFB", "unit_tests_libFB", 0)
                            }
                        }
                        stage("Code Coverage")
                        {
                            steps
                            {
                                sh "python3 ./scripts/CheckCodeCoverage.py --filename_gcovr_summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/gcovr_libFB_summary.json --threshold_branch_coverage 25.1 --threshold_function_coverage 100.0 --threshold_line_coverage 100.0"
                            }
                        }
                        stage("Doxygen & Coverage")
                        {
                            steps
                            {
                                Doxygen("./modules/mapping_and_localization/libraries/", "libFB")
                            }
                        }
                        stage("Cppcheck")
                        {
                            steps
                            {
                                sh "python3 ./scripts/RunCppcheck.py --base_directory ./modules/mapping_and_localization/libraries/libFB/ --configuration_xml ./modules/mapping_and_localization/libraries/libFB/testing/cppcheck/configuration.xml --cppcheck_configuration_json ./settings/cppcheck/CppcheckDefault.json --filename_report ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/cppcheck_libFB.log"
                            }
                        }
                        stage("Metrix++")
                        {
                            steps
                            {
                                sh "python3 ./scripts/RunMetrixPlusPlus.py --base_directory ./modules/mapping_and_localization/libraries/libFB/ --configuration_json ./modules/mapping_and_localization/libraries/libFB/testing/metrixplusplus/file_configuration.json --metrixplusplus_configuration ./settings/metrixplusplus/MetrixplusplusDefault.json --filename_report ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFB/metrixplusplus_libFB.log"
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
                        stage("GoogleTest & Gcovr")
                        {
                            steps
                            {
                                GoogleTest("../modules/mapping_and_localization/libraries/", "libFBVis", "unit_tests_libFBVis", 4)
                            }
                        }
                        stage("Doxygen & Coverage")
                        {
                            steps
                            {
                                Doxygen("./modules/mapping_and_localization/libraries/", "libFBVis")
                            }
                        }
                        stage("Cppcheck")
                        {
                            steps
                            {
                                sh "python3 ./scripts/RunCppcheck.py --base_directory ./modules/mapping_and_localization/libraries/libFBVis/ --configuration_xml ./modules/mapping_and_localization/libraries/libFBVis/testing/cppcheck/configuration.xml --cppcheck_configuration_json ./settings/cppcheck/CppcheckDefault.json --filename_report ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFBVis/cppcheck_libFBVis.log"
                            }
                        }
                        stage("Metrix++")
                        {
                            steps
                            {
                                sh "python3 ./scripts/RunMetrixPlusPlus.py --base_directory ./modules/mapping_and_localization/libraries/libFBVis/ --configuration_json ./modules/mapping_and_localization/libraries/libFBVis/testing/metrixplusplus/file_configuration.json --metrixplusplus_configuration ./settings/metrixplusplus/MetrixplusplusDefault.json --filename_report ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFBVis/metrixplusplus_libFBVis.log"
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
                        stage("GoogleTest & Gcovr")
                        {
                            steps
                            {
                                GoogleTest("../modules/mapping_and_localization/libraries/", "libFM", "unit_tests_libFM", 8)
                            }
                        }
                        stage("Doxygen & Coverage")
                        {
                            steps
                            {
                                Doxygen("./modules/mapping_and_localization/libraries/", "libFM")
                            }
                        }
                        stage("Cppcheck")
                        {
                            steps
                            {
                                sh "python3 ./scripts/RunCppcheck.py --base_directory ./modules/mapping_and_localization/libraries/libFM/ --configuration_xml ./modules/mapping_and_localization/libraries/libFM/testing/cppcheck/configuration.xml --cppcheck_configuration_json ./settings/cppcheck/CppcheckDefault.json --filename_report ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFM/cppcheck_libFM.log"
                            }
                        }
                        stage("Metrix++")
                        {
                            steps
                            {
                                sh "python3 ./scripts/RunMetrixPlusPlus.py --base_directory ./modules/mapping_and_localization/libraries/libFM/ --configuration_json ./modules/mapping_and_localization/libraries/libFM/testing/metrixplusplus/file_configuration.json --metrixplusplus_configuration ./settings/metrixplusplus/MetrixplusplusDefault.json --filename_report ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libFM/metrixplusplus_libFM.log"
                            }
                        }
                    }
                }
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
                        stage("GoogleTest & Gcovr")
                        {
                            steps
                            {
                                GoogleTest("../modules/environment_modeling/libraries/", "libWPG", "unit_tests_libWPG", 12)
                            }
                        }
                        stage("Code Coverage")
                        {
                            steps
                            {
                                sh "python3 ./scripts/CheckCodeCoverage.py --filename_gcovr_summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/gcovr_libWPG_summary.json --threshold_branch_coverage 18.5 --threshold_function_coverage 100.0 --threshold_line_coverage 100.0"
                            }
                        }
                        stage("Doxygen & Coverage")
                        {
                            steps
                            {
                                Doxygen("./modules/environment_modeling/libraries/", "libWPG")
                            }
                        }
                        stage("Cppcheck")
                        {
                            steps
                            {
                                sh "python3 ./scripts/RunCppcheck.py --base_directory ./modules/environment_modeling/libraries/libWPG/ --configuration_xml ./modules/environment_modeling/libraries/libWPG/testing/cppcheck/configuration.xml --cppcheck_configuration_json ./settings/cppcheck/CppcheckDefault.json --filename_report ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/cppcheck_libWPG.log"
                            }
                        }
                        stage("Metrix++")
                        {
                            steps
                            {
                                sh "python3 ./scripts/RunMetrixPlusPlus.py --base_directory ./modules/environment_modeling/libraries/libWPG/ --configuration_json ./modules/environment_modeling/libraries/libWPG/testing/metrixplusplus/file_configuration.json --metrixplusplus_configuration ./settings/metrixplusplus/MetrixplusplusDefault.json --filename_report ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/libWPG/metrixplusplus_libWPG.log"
                            }
                        }
                    }
                }
            }
        }
        stage("Compiler Checks")
        {
            when
            {
                expression{env.GIT_BRANCH == "main"}
            }
            matrix
            {
                axes
                {
                    axis
                    {
                        name "BUILD_TYPE"
                        values "Debug", "Release"
                    }
                    axis
                    {
                        name "CXX_COMPILER"
                        values "clang++-14", "g++-11"
                    }
                }
                stages
                {
                    stage("CMake")
                    {
                        steps
                        {
                            sh "cmake -D CMAKE_BUILD_TYPE=${BUILD_TYPE} -D CMAKE_CXX_COMPILER=/usr/bin/${CXX_COMPILER} -D OPTION_COPY_TO_TARGET_DIRECTORIES=OFF -B ./${env.CMAKE_BUILD_DIRECTORY}_${CXX_COMPILER}_${BUILD_TYPE}/ -S ./"
                        }
                    }
                    stage("CMake Build")
                    {
                        steps
                        {
                            sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}_${CXX_COMPILER}_${BUILD_TYPE}/ -t all -j${env.NUMBER_OF_THREADS}"
                        }
                    }
                    stage("GoogleTest")
                    {
                        steps
                        {
                            sh "./${env.CMAKE_BUILD_DIRECTORY}_${CXX_COMPILER}_${BUILD_TYPE}/modules/mapping_and_localization/libraries/libFB/testing/google_test/unit_tests_libFB"
                            sh "./${env.CMAKE_BUILD_DIRECTORY}_${CXX_COMPILER}_${BUILD_TYPE}/modules/mapping_and_localization/libraries/libFBVis/testing/google_test/unit_tests_libFBVis"
                            sh "./${env.CMAKE_BUILD_DIRECTORY}_${CXX_COMPILER}_${BUILD_TYPE}/modules/mapping_and_localization/libraries/libFM/testing/google_test/unit_tests_libFM"
                            sh "./${env.CMAKE_BUILD_DIRECTORY}_${CXX_COMPILER}_${BUILD_TYPE}/modules/environment_modeling/libraries/libWPG/testing/google_test/unit_tests_libWPG"
                        }
                    }
                }
            }
        }
        stage("Docker")
        {
            when
            {
                expression{env.GIT_BRANCH == "main"}
            }
            steps
            {
                // this requires that the jenkins user is part of the docker group
                // 1) add jenkins user to docker group: "sudo usermod -a -G docker jenkins"
                // 2) restart Jenkins: "sudo systemctl restart jenkins"
                sh "docker build -t robotics_toolbox ."
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

// Function to run Doxygen and Coverxygen
// - base_path (str): Base path to the libraries directory.
// - entity (str):    Entity to check.
def Doxygen(base_path, entity)
{
    // create Doxygen documentation
    sh "python3 ./scripts/GenerateDoxygenDocumentation.py --base_path ${base_path} --entity ${entity} --output_path ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/${entity}/"

    // check documentation coverage
    sh "python3 ./scripts/CheckDoxygenCoverage.py --base_path ${base_path} --entity ${entity} --output_path ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/${entity}/"
}

// Function to run GoogleTest and Gcovr
// - base_path (str):  Base path to the libraries directory.
// - entity (str):     Entity to check.
// - binary (str):     Name of the unit test binary.
// - sleep time (int): Time (seconds) to wait before running Gcovr.
def GoogleTest(base_path, entity, binary, sleep_time)
{
    // run unit tests
    sh "cmake --build ./${env.CMAKE_BUILD_DIRECTORY}/ -t ${binary} -j${env.NUMBER_OF_THREADS}"
    sh "./bin/${binary} --gtest_output=json:${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/${entity}/googletest_${entity}.json"

    // determine code coverage
    sleep(time: sleep_time, unit: "SECONDS") // avoid running multiple instances of Gcovr in parallel
    sh "cd build && gcovr --filter ${base_path}${entity}/ --json-pretty --json ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/${entity}/gcovr_${entity}_coverage.json"
    sh "cd build && gcovr --filter ${base_path}${entity}/ --json-summary-pretty --json-summary ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/${entity}/gcovr_${entity}_summary.json"
    sh "cd build && gcovr --filter ${base_path}${entity}/ --html-details ${env.WORKSPACE}/${env.JENKINS_BUILD_ARTIFACTS_DIRECTORY}/${entity}/gcovr_${entity}_details.html"
}
