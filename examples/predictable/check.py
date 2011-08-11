#!/usr/bin/env python

from __future__ import print_function

import os
import subprocess
import sys
import unittest

class TestPredictable(unittest.TestCase):
	
	def _exec_or_fail(self, command):
		try:
			subprocess.check_output(command, stderr=subprocess.STDOUT)
		except subprocess.CalledProcessError as process_err:
			print("`{0}`: {1}".format(" ".join(command),
				process_err.output), file=sys.stderr)
			sys.exit(process_err.returncode)
	
	def setUp(self):
		self._exec_or_fail(["insmod", "predictable.ko"])
	
	def tearDown(self):
		self._exec_or_fail(["rmmod", "predictable"])
	
	def test_predictable(self):
		self.assertTrue(os.path.exists("/proc/predictable"))
		with open("check.data", "r") as f:
			expected_numbers = [line.strip() for line in f]
		for expected in expected_numbers:
			with open("/proc/predictable", "r") as f:
				actual = f.read()
				self.assertEqual(expected, actual)

if __name__ == '__main__':
	unittest.main()

