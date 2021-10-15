cmake_minimum_required(VERSION 3.16)
project (flow_control)

###############################################################################
# foreach

foreach (i 1 2 3)
	message (${i})
endforeach (i)

###############################################################################
# while

set (a 10)
while (${a} GREATER 0)
	message ("a=${a}")

	if (5 EQUAL ${a})
		message ("Found ${a}")
	else ()
		# do nothing
	endif ()

	math(EXPR a "${a}-1")
endwhile ()

###############################################################################
# function

function (DetermineTime _time)
	set (${_time} "1:23:45" PARENT_SCOPE) # use PARENT_SCOPE to update variable in parent scope
endfunction ()

DetermineTime(current_time)

if (DEFINED current_time)
	message(STATUS "The time is now: ${current_time}")
endif ()

###############################################################################
# macro

macro (assert TEST COMMENT)
	if (NOT ${TEST})
		message ("Assertion failed: ${COMMENT}")
	endif (NOT ${TEST})
endmacro (assert)

find_library (FOO_LIB foo /usr/local/lib)
assert (${FOO_LIB} "Unable to find library foo")
