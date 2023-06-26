
add_library(hfmenc STATIC)

target_sources(hfmenc 
    PRIVATE
        huffman_encoder.cpp 
        huffman_encoder.h 
)

add_executable(huffman_encoder main.cpp)
target_link_libraries(huffman_encoder PRIVATE hfmenc)

    