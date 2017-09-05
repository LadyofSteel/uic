#!/usr/bin/env python3

import subprocess
import enum
import collections
import time
import sys
import os
import signal


class TestResultType(enum.Enum):
    TRANSFER_ERROR = 0
    TRANSFER_TIMEOUT = 1
    SLOW_TRANSFER = 2
    FAST_TRANSFER = 3

TestArguments = collections.namedtuple('TestArguments', "file loss delay buffer")
TestCase = collections.namedtuple("TestCase", "args secs")
TestResult = collections.namedtuple("TestResult", "type duration")

def run_test_case(case: TestCase) -> TestResult:
    full_credit_time = case.secs * 1.5
    half_credit_time = case.secs * 2.0
    start_time = time.time()

    test_args = ["python3", "tester.py", "--file", case.args.file, "--loss",
                 case.args.loss, "--buffer", case.args.buffer,
                 "--delay", case.args.delay]

    try:
        test_proc = subprocess.Popen(test_args, stdout=subprocess.DEVNULL,
                                     stderr=subprocess.DEVNULL,
                                     preexec_fn=os.setsid)
    except OSError:
        os.killpg(test_proc.pid, signal.SIGINT)
        return TestResult(TestResultType.TRANSFER_ERROR, None)

    try:
        test_proc.wait(timeout=half_credit_time)
    except subprocess.TimeoutExpired:
        os.killpg(test_proc.pid, signal.SIGINT)
        return TestResult(TestResultType.TRANSFER_TIMEOUT, None)

    if test_proc.returncode != 0:
        print(str(test_proc.returncode))
        try:
            os.killpg(test_proc.pid, signal.SIGINT)
        except ProcessLookupError:
            pass
        return TestResult(TestResultType.TRANSFER_ERROR, None)

    end_time = time.time()
    duration = end_time - start_time
    if duration <= full_credit_time:
        result_type = TestResultType.FAST_TRANSFER
    else:
        result_type = TestResultType.SLOW_TRANSFER
    return TestResult(result_type, duration)

TEST_CASES = [
    TestCase(TestArguments("grading_data/test-1.bin", "0", ".5", "10"), 7),
    TestCase(TestArguments("grading_data/test-2.bin", "0", "0.1", "20"), 5),
    TestCase(TestArguments("grading_data/test-3.bin", "0", ".01", "30"), 6),
    TestCase(TestArguments("grading_data/test-4.bin", "0.1", ".1", "40"), 6),
    TestCase(TestArguments("grading_data/test-5.bin", "0.1", ".01", "50"), 32),
    TestCase(TestArguments("grading_data/test-6.bin", "0", ".01", "60"), 12),
]

TOTAL_SCORE = 0
MAX_SCORE = 12
for CASE_NUM, A_CASE in enumerate(TEST_CASES):
    FULL_CREDIT_TIME = A_CASE.secs * 1.5
    HALF_CREDIT_TIME = A_CASE.secs * 2.0
    print("Test case: {}".format(CASE_NUM + 1))
    print("  - File: {}".format(A_CASE.args.file))
    print("  - Loss: {}%".format(100 * float(A_CASE.args.loss)))
    print("  - Delay: {} seconds".format(A_CASE.args.delay))
    print("  - Buffer: {} packets".format(A_CASE.args.buffer))
    print("  - Full credit: {} secs".format(round(FULL_CREDIT_TIME)))
    print("  - Half credit: {} secs".format(round(HALF_CREDIT_TIME)))
    print("----------")

    CASE_RESULT = run_test_case(A_CASE)
    if CASE_RESULT.type == TestResultType.TRANSFER_ERROR:
        print("  ! 0 points, file was transferred incorrectly")
    elif CASE_RESULT.type == TestResultType.TRANSFER_TIMEOUT:
        print("  ! 0 points, file not transferred in {} secs".format(
            round(HALF_CREDIT_TIME)))
    elif CASE_RESULT.type == TestResultType.SLOW_TRANSFER:
        print("  ~ 1 point, transferred in {} secs".format(round(CASE_RESULT.duration)))
        TOTAL_SCORE += 1
    elif CASE_RESULT.type == TestResultType.FAST_TRANSFER:
        print("  * 2 points, transferred in {} secs".format(round(CASE_RESULT.duration)))
        TOTAL_SCORE += 2
    print("")

print("==========")
print("Total Score: {} / {}".format(TOTAL_SCORE, MAX_SCORE))
sys.exit(0 if TOTAL_SCORE == MAX_SCORE else 1)