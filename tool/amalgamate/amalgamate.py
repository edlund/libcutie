#!/usr/bin/env python

# amalgamate.py - Amalgamate C source and header files.
# Copyright (c) 2011, Erik Edlund <erik.o.edlund@gmail.com>
# 
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# 
#  * Redistributions of source code must retain the above copyright notice,
#  this list of conditions and the following disclaimer.
# 
#  * Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation
#  and/or other materials provided with the distribution.
# 
#  * Neither the name of Erik Edlund, nor the names of its contributors may
#  be used to endorse or promote products derived from this software without
#  specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

from __future__ import print_function

import argparse
import json
import os
import re
import subprocess
import sys

class Amalgamation(object):
	
	def file_path(self, file_path, include_paths=None):
		if include_paths == None:
			include_paths = self.include_paths
		
		paths = [os.path.join(self.source_path, path) for path in include_paths]
		paths.insert(0, self.source_path)
		for path in paths:
			tmp_path = os.path.join(path, file_path)
			if os.path.exists(tmp_path):
				return tmp_path
		return None
	
	def __init__(self, args):
		with open(args.config, 'r') as f:
			config = json.loads(f.read())
			for key in config:
				setattr(self, key, config[key])
			
			self.verbose = args.verbose == 'yes'
			self.source_path = args.source_path
			self.included_files = []
	
	def generate(self):
		amalgamation = ""
		
		if self.verbose:
			print("Config:")
			print(" target        = {0}".format(self.target))
			print(" working_dir   = {0}".format(os.getcwd()))
			print(" include_paths = {0}".format(self.include_paths))
		print("Creating amalgamation:")
		for file_path in self.sources:
			# Do not check the include paths while processing the source
			# list, all given source paths must be correct.
			actual_path = self.file_path(file_path, [])
			print(" - processing \"{0}\"".format(actual_path))
			if not actual_path:
				raise IOError("File not found: \"{0}\"".format(file_path))
			tunit = TranslationUnit(actual_path, self)
			amalgamation += tunit.content
		
		with open(self.target, 'w') as f:
			f.write(amalgamation)
		
		print("...done!\n")
		if self.verbose:
			print("Files processed: {0}".format(self.sources))
			print("Files included: {0}".format(self.included_files))
		print("")

class TranslationUnit(object):
	
	skippable_patterns = [
		re.compile(r'".*?(?<=[^\\])"'), # "complex \"string\" value"
		re.compile(r"//.*?\n"),         # // comment
		re.compile(r"/\*.*?\*/", re.S)  # /* comment */
	]
	
	# Handle simple include directives. Support for advanced
	# directives where macros and defines needs to expanded is
	# not a concern right now.
	include_pattern = re.compile(
		r'#\s*include\s*(<|")(?P<path>.*?)("|>)', re.S)
	
	def _include_files(self):
		# Find contexts in the content in which a found include
		# directive should be ignored.
		skippable_matches = []
		for pattern in self.skippable_patterns:
			skippable_match = pattern.search(self.content)
			while skippable_match:
				skippable_matches.append(skippable_match)
				skippable_match = pattern.search(self.content,
					skippable_match.end())
		
		# Search for include directives in the content, collect those
		# which should be included into the content.
		includes = []
		include_match = self.include_pattern.search(self.content)
		while include_match:
			should_include = True
			for skippable in skippable_matches:
				if include_match.start() > skippable.start() and \
						include_match.end() < skippable.end():
					should_include = False
					break
			include_path = include_match.group("path")
			actual_path = self.amalgamation.file_path(include_path)
			if should_include and actual_path:
				includes.append((include_match, actual_path))
			
			include_match = self.include_pattern.search(self.content,
				include_match.end())
		
		# Handle all collected include directives.
		prev_end = 0
		tmp_content = ''
		for include in includes:
			include_match, actual_path = include
			tmp_content += self.content[prev_end:include_match.start()]
			tmp_content += "// {0}\n".format(include_match.group(0))
			if not actual_path in self.amalgamation.included_files:
				tunit = TranslationUnit(actual_path, self.amalgamation)
				tmp_content += tunit.content
			prev_end = include_match.end()
		tmp_content += self.content[prev_end:]
		self.content = tmp_content
		
		return len(includes)
	
	def __init__(self, file_path, amalgamation):
		self.file_path = file_path
		self.amalgamation = amalgamation
		
		self.amalgamation.included_files.append(self.file_path)
		
		with open(self.file_path, 'r') as f:
			self.content = f.read()
			self._include_files()

def main():
	argsparser = argparse.ArgumentParser(
		description="Amalgamate C source and header files.",
		usage="amalgamate.py [-v] -c path/to/config.json -s path/to/source/dir")
	
	argsparser.add_argument('-v', '--verbose', dest='verbose',
		choices=['yes', 'no'], metavar="", help="be verbose")
	
	argsparser.add_argument('-c', '--config', dest='config',
		required=True, metavar="", help="path to a JSON config file")
	
	argsparser.add_argument('-s', '--source', dest='source_path',
		required=True, metavar="", help="source code path")
	
	amalgamation = Amalgamation(argsparser.parse_args())
	amalgamation.generate()

if __name__ == '__main__':
	main()

