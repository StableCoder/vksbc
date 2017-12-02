pipeline {
    agent none
    environment {
        CUSTOM_CMAKE_OPTIONS = ''
    }
    stages {
        stage('Debug Builds/Tests') {
            environment {
                BUILD_TYPE = 'Debug'
            }
            parallel {
                stage('Debug/Linux/GCC') {
                    agent {
                        label 'linux && gcc && cmake'
                    }
                    steps {
                        sh '''
                            rm -rf build/
                            mkdir build
                            cd build
                            gcc --version
                            cmake -G "Unix Makefiles" ../ $CUSTOM_CMAKE_OPTIONS -DCMAKE_BUILD_TYPE=$BUILD_TYPE
                            make
                        '''
                    }
                }
                stage('Debug/Linux/Clang') {
                    agent {
                        label 'linux && clang && cmake'
                    }
                    environment {
                        CC = 'clang'
                        CXX = 'clang++'
                    }
                    steps {
                        sh '''
                            rm -rf build/
                            mkdir build
                            cd build
                            clang --version
                            cmake -G "Unix Makefiles" ../ $CUSTOM_CMAKE_OPTIONS -DCMAKE_BUILD_TYPE=$BUILD_TYPE
                            make
                        '''
                    }
                }
                stage('Debug/Windows/GCC') {
                    agent {
                        label 'windows && gcc && cmake'
                    }
                    steps {
                        bat'''
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            gcc --version
                            call cmake -G "MinGW Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            mingw32-make
                        '''
                    }
                }
                stage('Debug/Windows/Clang') {
                    agent {
                        label 'windows && clang && cmake'
                    }
                    environment {
                        CC = 'clang'
                        CXX = 'clang++'
                    }
                    steps {
                        bat'''
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            clang --version
                            call cmake -G "MinGW Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            mingw32-make
                        '''
                    }
                }
                stage('Debug/Windows/MSVC2015') {
                    agent {
                        label 'windows && msvc2015 && cmake'
                    }
                    steps {
                        bat '''
                            set VSCMD_START_DIR=%CD%
                            call "%MSVC2017_BUILD_TOOLS%" x64 %WIN10_SDK_VER% -vcvars_ver=14.0
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            call cmake -G "NMake Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            nmake
                        '''
                    }
                }
                stage('Debug/Windows/MSVC2017') {
                    agent {
                        label 'windows && msvc2017 && cmake'
                    }
                    steps {
                        bat '''
                            set VSCMD_START_DIR=%CD%
                            call "%MSVC2017_BUILD_TOOLS%" x64 %WIN10_SDK_VER%
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            call cmake -G "NMake Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            nmake
                        '''
                    }
                }
            }
        }
        stage('Release Builds/Tests') {
            environment {
                BUILD_TYPE = 'Release'
            }
            parallel {
                stage('Release/Linux/GCC') {
                    agent {
                        label 'linux && gcc && cmake'
                    }
                    steps {
                        sh '''
                            rm -rf build/
                            mkdir build
                            cd build
                            gcc --version
                            cmake -G "Unix Makefiles" ../ $CUSTOM_CMAKE_OPTIONS -DCMAKE_BUILD_TYPE=$BUILD_TYPE
                            make
                        '''
                    }
                }
                stage('Release/Linux/Clang') {
                    agent {
                        label 'linux && clang && cmake'
                    }
                    environment {
                        CC = 'clang'
                        CXX = 'clang++'
                    }
                    steps {
                        sh '''
                            rm -rf build/
                            mkdir build
                            cd build
                            clang --version
                            cmake -G "Unix Makefiles" ../ $CUSTOM_CMAKE_OPTIONS -DCMAKE_BUILD_TYPE=$BUILD_TYPE
                            make
                        '''
                    }
                }
                stage('Release/Windows/GCC') {
                    agent {
                        label 'windows && gcc && cmake'
                    }
                    steps {
                        bat'''
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            gcc --version
                            call cmake -G "MinGW Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            mingw32-make
                        '''
                    }
                }
                stage('Release/Windows/Clang') {
                    agent {
                        label 'windows && clang && cmake'
                    }
                    environment {
                        CC = 'clang'
                        CXX = 'clang++'
                    }
                    steps {
                        bat'''
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            clang --version
                            call cmake -G "MinGW Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            mingw32-make
                        '''
                    }
                }
                stage('Release/Windows/MSVC2015') {
                    agent {
                        label 'windows && msvc2015 && cmake'
                    }
                    steps {
                        bat '''
                            set VSCMD_START_DIR=%CD%
                            call "%MSVC2017_BUILD_TOOLS%" x64 %WIN10_SDK_VER% -vcvars_ver=14.0
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            call cmake -G "NMake Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            nmake
                        '''
                    }
                }
                stage('Release/Windows/MSVC2017') {
                    agent {
                        label 'windows && msvc2017 && cmake'
                    }
                    steps {
                        bat '''
                            set VSCMD_START_DIR=%CD%
                            call "%MSVC2017_BUILD_TOOLS%" x64 %WIN10_SDK_VER%
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            call cmake -G "NMake Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            nmake
                        '''
                    }
                }
            }
        }
        stage('MinSizeRel Builds/Tests') {
            environment {
                BUILD_TYPE = 'MinSizeRel'
            }
            parallel {
                stage('MinSizeRel/Linux/GCC') {
                    agent {
                        label 'linux && gcc && cmake'
                    }
                    steps {
                        sh '''
                            rm -rf build/
                            mkdir build
                            cd build
                            gcc --version
                            cmake -G "Unix Makefiles" ../ $CUSTOM_CMAKE_OPTIONS -DCMAKE_BUILD_TYPE=$BUILD_TYPE
                            make
                        '''
                    }
                }
                stage('MinSizeRel/Linux/Clang') {
                    agent {
                        label 'linux && clang && cmake'
                    }
                    environment {
                        CC = 'clang'
                        CXX = 'clang++'
                    }
                    steps {
                        sh '''
                            rm -rf build/
                            mkdir build
                            cd build
                            clang --version
                            cmake -G "Unix Makefiles" ../ $CUSTOM_CMAKE_OPTIONS -DCMAKE_BUILD_TYPE=$BUILD_TYPE
                            make
                        '''
                    }
                }
                stage('MinSizeRel/Windows/GCC') {
                    agent {
                        label 'windows && gcc && cmake'
                    }
                    steps {
                        bat'''
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            gcc --version
                            call cmake -G "MinGW Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            mingw32-make
                        '''
                    }
                }
                stage('MinSizeRel/Windows/Clang') {
                    agent {
                        label 'windows && clang && cmake'
                    }
                    environment {
                        CC = 'clang'
                        CXX = 'clang++'
                    }
                    steps {
                        bat'''
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            clang --version
                            call cmake -G "MinGW Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            mingw32-make
                        '''
                    }
                }
                stage('MinSizeRel/Windows/MSVC2015') {
                    agent {
                        label 'windows && msvc2015 && cmake'
                    }
                    steps {
                        bat '''
                            set VSCMD_START_DIR=%CD%
                            call "%MSVC2017_BUILD_TOOLS%" x64 %WIN10_SDK_VER% -vcvars_ver=14.0
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            call cmake -G "NMake Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            nmake
                        '''
                    }
                }
                stage('MinSizeRel/Windows/MSVC2017') {
                    agent {
                        label 'windows && msvc2017 && cmake'
                    }
                    steps {
                        bat '''
                            set VSCMD_START_DIR=%CD%
                            call "%MSVC2017_BUILD_TOOLS%" x64 %WIN10_SDK_VER%
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            call cmake -G "NMake Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            nmake
                        '''
                    }
                }
            }
        }
        stage('RelWithDebInfo Builds/Tests') {
            environment {
                BUILD_TYPE = 'RelWithDebInfo'
            }
            parallel {
                stage('RelWithDebInfo/Linux/GCC') {
                    agent {
                        label 'linux && gcc && cmake'
                    }
                    steps {
                        sh '''
                            rm -rf build/
                            mkdir build
                            cd build
                            gcc --version
                            cmake -G "Unix Makefiles" ../ $CUSTOM_CMAKE_OPTIONS -DCMAKE_BUILD_TYPE=$BUILD_TYPE
                            make
                        '''
                    }
                }
                stage('RelWithDebInfo/Linux/Clang') {
                    agent {
                        label 'linux && clang && cmake'
                    }
                    environment {
                        CC = 'clang'
                        CXX = 'clang++'
                    }
                    steps {
                        sh '''
                            rm -rf build/
                            mkdir build
                            cd build
                            clang --version
                            cmake -G "Unix Makefiles" ../ $CUSTOM_CMAKE_OPTIONS -DCMAKE_BUILD_TYPE=$BUILD_TYPE
                            make
                        '''
                    }
                }
                stage('RelWithDebInfo/Windows/GCC') {
                    agent {
                        label 'windows && gcc && cmake'
                    }
                    steps {
                        bat'''
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            gcc --version
                            call cmake -G "MinGW Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            mingw32-make
                        '''
                    }
                }
                stage('RelWithDebInfo/Windows/Clang') {
                    agent {
                        label 'windows && clang && cmake'
                    }
                    environment {
                        CC = 'clang'
                        CXX = 'clang++'
                    }
                    steps {
                        bat'''
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            clang --version
                            call cmake -G "MinGW Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            mingw32-make
                        '''
                    }
                }
                stage('RelWithDebInfo/Windows/MSVC2015') {
                    agent {
                        label 'windows && msvc2015 && cmake'
                    }
                    steps {
                        bat '''
                            set VSCMD_START_DIR=%CD%
                            call "%MSVC2017_BUILD_TOOLS%" x64 %WIN10_SDK_VER% -vcvars_ver=14.0
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            call cmake -G "NMake Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            nmake
                        '''
                    }
                }
                stage('RelWithDebInfo/Windows/MSVC2017') {
                    agent {
                        label 'windows && msvc2017 && cmake'
                    }
                    steps {
                        bat '''
                            set VSCMD_START_DIR=%CD%
                            call "%MSVC2017_BUILD_TOOLS%" x64 %WIN10_SDK_VER%
                            set PATH=%PATH%;%MINGW64%;
                            rmdir /Q /S build
                            mkdir build
                            cd build
                            call cmake -G "NMake Makefiles" ../ %CUSTOM_CMAKE_OPTIONS% -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
                            nmake
                        '''
                    }
                }
            }
        }
    }
}