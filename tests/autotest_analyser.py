#!/usr/bin/env python
"""
  autotest_analyser.py
  This script works with the output of a QTest application and parses it 
  for failed and skipped tests. It can handle the output of multiple tests,
  when produced e.g. with the autotest.h of Rob Caldecott:
  http://qtcreator.blogspot.de/2010/04/sample-multiple-unit-test-project.html
"""

import sys
#import subprocess

#p = subprocess.Popen("/path/to/test_all", 
#		stdout = subprocess.PIPE)

failed = ["******* Failed Tests *******"]
skipped = ["******* Skipped Tests *******"]

if not sys.stdin.isatty():
	lines = sys.stdin.readlines()
else:
	quit()
	
for line in lines:
	if( 'Start testing of' in line ):
		words = line.split();
		actualTest = words[4];
	elif( 'PASS' in line ):
		pass
	elif( 'FAIL!' in line ):
		words = line.split();
		failedTest = words[2]
		failedMessage = line[ line.rfind( str(failedTest)) + len(str(failedTest))  :  ]
		failed.append( "_______" + actualTest + "_______" )
		failed.append( failedTest + ": " + failedMessage )
	elif( 'SKIP' in line ):
		skippedTest = line[ line.find(":")+2 : line.find(")")+1 ]
		skippedMessage = line[ line.find(")")+1 : -1 ]
		skipped.append( "_______" + actualTest + "_______" )
		skipped.append( skippedTest + ": " + skippedMessage )
		
if( len(failed) > 1 ):
	for message in failed:
		print message	
		print ""

if( len(skipped) > 1 ):
	for message in skipped:
		print message			
		
if( len(skipped) == 1 and len(failed) == 1 ):
	print "***** All tests PASSED *****"