if(EXISTS "/home/marat/projects/test_task/server/test/build/test_server[1]_tests.cmake")
  include("/home/marat/projects/test_task/server/test/build/test_server[1]_tests.cmake")
else()
  add_test(test_server_NOT_BUILT test_server_NOT_BUILT)
endif()
