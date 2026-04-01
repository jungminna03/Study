cmake_minimum_required(VERSION 4.1)
cmake_minimum_required(VERSION 3.20)
project(Algorithm)

set(CMAKE_CXX_STANDARD 20)

# 1. 'Esey' 폴더 안에 있는 모든 .cpp 파일을 리스트로 가져옵니다.
file(GLOB ESEY_FILES "Esey/*.cpp")

# 2. 각 파일마다 개별적인 실행 파일(Target)로 만듭니다.
foreach(FILE ${ESEY_FILES})
    # 파일 경로에서 확장자를 뺀 순수 이름만 추출 (예: Two_Sum)
    get_filename_component(FILE_NAME ${FILE} NAME_WE)

    # 그 이름으로 실행 파일을 생성! (예: add_executable(Two_Sum Esey/Two_Sum.cpp))
    add_executable(${FILE_NAME} ${FILE}
            Esey/Reverse_Bits.cpp
    )
endforeach()