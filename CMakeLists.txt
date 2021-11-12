cmake_minimum_required(VERSION 3.19)
project(MySchoolCode C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(MySchoolCode
        CProgramExercise/iMooc/SortEvaluate.c
#        test/comp1.c
#        test/test2.c
        )
