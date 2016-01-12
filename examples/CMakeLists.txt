add_executable(s2example s2example.cc)

target_link_libraries(s2example
        s2
        s2cellid
        -lcrypto
        -lgflags
        -lssl
        -lpthread)