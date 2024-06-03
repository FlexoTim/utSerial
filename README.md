# OpenCat Serial Library Unit Tests

Unit test program for the OpenCat Serial library (v1.2.0) using Google gtest testing framework under Visual Studio

## Requires
* Visual Studio Community Editon (or equivalent)
* Google GTEST package installed in Visual Studio.
* Arduino UNO as a serial loopback connector

## Usage
Run utSerial -h for program usage

>  This program contains tests written using Google Test. You can use the  
  following command line flags to control its behavior:  
>  
  Test Selection:  
    --gtest_list_tests  
        List the names of all tests instead of running them. The name of  
        TEST(Foo, Bar) is "Foo.Bar".  
    --gtest_filter=POSTIVE_PATTERNS[-NEGATIVE_PATTERNS]  
        Run only the tests whose name matches one of the positive patterns but  
        none of the negative patterns. '?' matches any single character; '*'  
        matches any substring; ':' separates two patterns.  
    --gtest_also_run_disabled_tests  
        Run all disabled tests too.  
>  
  Test Execution:  
    --gtest_repeat=[COUNT]  
        Run the tests repeatedly; use a negative count to repeat forever.  
    --gtest_shuffle  
        Randomize tests' orders on every iteration.  
    --gtest_random_seed=[NUMBER]  
        Random number seed to use for shuffling test orders (between 1 and  
        99999, or 0 to use a seed based on the current time).  
>  
  Test Output:  
    --gtest_color=(yes|no|auto)  
        Enable/disable colored output. The default is auto.  
    --gtest_print_time=0  
        Don't print the elapsed time of each test.  
    --gtest_output=(json|xml)[:DIRECTORY_PATH\|:FILE_PATH]  
        Generate a JSON or XML report in the given directory or with the given  
        file name. FILE_PATH defaults to test_details.xml.  
>  
  Assertion Behavior:  
    --gtest_break_on_failure  
        Turn assertion failures into debugger break-points.  
    --gtest_throw_on_failure  
        Turn assertion failures into C++ exceptions for use by an external  
        test framework.  
    --gtest_catch_exceptions=0  
        Do not report exceptions as test failures. Instead, allow them  
        to crash the program or throw a pop-up (on Windows).  
>  
  Except for --gtest_list_tests, you can alternatively set the corresponding
  environment variable of a flag (all letters in upper-case). For example, to
  disable colored text output, you can either specify --gtest_color=no or set
  the GTEST_COLOR environment variable to no.

### Test list
<pre>
  utfListSerialPorts.
    echo_list
  utfwin32.
    ctor_valid
    unexpected_error_fails
    expected_error
    on_error_ERROR_SUCCESS
    on_error_unexpected_fails
    on_error_expected
  utfSerialClosed.
    available
    close_nothrow
    flush_throw_PortNotOpenedException
    flushInput_throw_PortNotOpenedException
    flushOutput_throw_PortNotOpenedException
    isOpen_false
    open_throw_invalid_argument
    open_throw_IOException
    open_throw_SerialException
    read_size_throw_PortNotOpenedException
    read_string_throw_PortNotOpenedException
    read_vector_throw_PortNotOpenedException
    read_ptr_throw_PortNotOpenedException
    readline_size_throw_PortNotOpenedException
    readline_string_throw_PortNotOpenedException
    readlines_vector_throw_PortNotOpenedException
    sendBreak_throw_IOException
    setBreak_throw_PortNotOpenedException
    setDTR_throw_PortNotOpenedException
    setRTS_throw_PortNotOpenedException
    waitByteTimes_throw_IOException
    waitForChange_throw_PortNotOpenedException
    waitReadable_throw_IOException
    write_string_throw_PortNotOpenedException
    write_vector_throw_PortNotOpenedException
    write_ptr_throw_PortNotOpenedException
  utfSerialException.
    SerialException_copy_ctor_valid
    IOException_copy_ctor_valid
    PortNotOpenedException_copy_ctor_valid
  utfSerialGetters.
    getBaudrate
    getBytesize
    getCD_throw_PortNotOpenedException
    getCTS_throw_PortNotOpenedException
    getDSR_throw_PortNotOpenedException
    getFlowcontrol
    getParity
    getPort
    getRI_throw
    getStopbits
    getTimeout
  utfSerialLoopback.
    ctor_available_empty
    write_string_match_count
    write_string_match
    write_ptr_match_count
    write_ptr_match
    write_vector_match_count
    write_vector_match
    read_ptr_match_count
    read_ptr_match
    read_vector_match_count
    read_vector_match
    read_string_match_count
    read_string_match
    readline_newline_match_count
    readline_newline_match
    readline_tilda_match_count
    readline_tilda_match
    readline_string_newline_match_count
    readline_string_newline_match
    readline_no_eol
    readlines_newline_match_count
    readlines_newline_match
    readlines_no_eol
  utfSerialOpen.
    available_empty
    close_nothrow
    close_is_closed
    flush_nothrow
    flush_empty
    flushInput_nothrow
    flushOutput_nothrow
    read_size_zero_nothrow
    read_size_nothrow
    read_size_match
    read_match_size_match
    read_string_nothrow
    read_string_empty
    read_vector_empty
    read_ptr_isempty
    readline_size_nothrow
    readline_size_empty
    readline_string_empty
    readlines_vector_empty
    sendBreak_throw_IOException
    setBreak_nothrow
    setDTR_nothrow
    setRTS_nothrow
    waitByteTimes_throw_IOException
    DISABLED_waitForChange_nothrow
    waitReadable_throw_IOException
    write_empty_string_nothrow
    write_empty_string_zero
    write_string_nothrow
    write_string_match_count
    DISABLED_write_empty_vector_throw
    write_nullptr_zero_nothrow
    write_dereference_nullptr_throw
    write_nullptr_zero
    write_default_ptr_nothrow
    write_default_ptr_zero
  utfSerialSetters.
    setBaudrate_nothrow
    setBaudrate_match
    setBytesize
    setFlowcontrol
    setParity
    setPort
    setStopbits
    setTimeout
  utfTimeout.
    ctor_valid
    copy_ctor_valid
    equality_valid
    inequality_valid
    assignment_valid
  utfTask.
    ctor_Command_nothrow
    ctor_Command_match
    ctor_Command_arguments_empty
    ctor_Command_delay_zero
    ctor_Command_delay_nothrow
    ctor_Command_delay_Command_match
    ctor_Command_delay_arguments_empty
    ctor_Command_delay_delay_match
    ctor_Full_nothrow
    ctor_Full_Command_match
    ctor_Full_arguments_match
    ctor_Full_delay_match
    copy_ctor_nothrow
    copy_ctor_Command_match
    copy_ctor_argument_match
    copy_ctor_delay_match
    assignment_nothrow
    assignment_match
  TimeoutValue/utfExample_NoFlush.
    read_more/0  # GetParam() = 1000
    read_more/1  # GetParam() = 250
    read_match/0  # GetParam() = 1000
    read_match/1  # GetParam() = 250
    read_less/0  # GetParam() = 1000
    read_less/1  # GetParam() = 250
  TimeoutValue/utfExample_Flush.
    read_more/0  # GetParam() = 1000
    read_more/1  # GetParam() = 250
    read_match/0  # GetParam() = 1000
    read_match/1  # GetParam() = 250
    read_less/0  # GetParam() = 1000
    read_less/1  # GetParam() = 250
</pre>

## Documentation
Google gtest documentation should apply (though the package under Visual Studio is out of date).

OpenCat_Serial_cpp documentation should apply.
