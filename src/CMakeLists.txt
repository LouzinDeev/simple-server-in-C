add_executable(server
    "common.h"
    "server.h"
    "server.c"
    "main.c" 
)

target_link_libraries(server PUBLIC
    "pthread"
)